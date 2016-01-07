/*************************************************************
* Programa ejemplo de manejo de la serial SCI
*   LEE UN NUMERO ESCRITO EN UNA LINEA DE LA SERIAL
*   Y LO CONVIERTE EN DOBLE BYTE HACIENDO ECO DE LOS DIGITOS
*   Tras realizar la conversión envía mensaje indicando si
*    el número cabe o no.
* Variantes:
*     1- Desabilitar la recepción mientras se trata buffer
*     2- Descartar los 0 iniciales

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: LeeNumeroMensaje.s,v 13.3 2014/11/13 19:05:38 alberto Exp $

  Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo
  los términos de la Licencia Pública General de GNU según es publicada
  por la Free Software Foundation, bien de la versión 2 de dicha Licencia
  o bien (según su elección) de cualquier versión posterior.

  Este programa se distribuye con la esperanza de que sea útil, pero
  SIN NINGÚN TIPO DE GARANTÍA, incluso sin la garantía MERCANTIL implícita
  o sin garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR.
  Véase la Licencia Pública General de GNU para más detalles.


******************************************/

;;; Incuimos la definición del nombre de todos los registros de control
        .include "registros.inc"

        ;; se deben definir las etiquetas de las rutina de tratamiento de
        ;;  interrupciones antes de incluir vectores.inc


        .equ    SC9600BAUDIOS,52 ; constante para obtener baudios en SC
        .equ    SC38400BAUDIOS,13
        .equ    BAUDIOS,SC38400BAUDIOS

        .equ    MAXCARA,6
        .equ    CR,'\r         ; codigo ascii del retorno de carro
        .equ    LF,'\n         ; codigo ascii del salto de linea


;;; Variables no inicializadas
        .section .bss

buffer:         .skip	MAXCARA         ;almacena caracteres introducidos
completo:       .skip	1               ;indica cuando la linea esta completa
numcar:         .skip	1               ;indica el numero de caracteres validos
                                        ;  en el buffer
valor:          .skip	1       ;donde se almacenara el valor de la linea

temp:           .skip	2       ;variable temporal para los calculos


;;; Las constantes van en la zona de programa
        .section .rodata

men_hola:       .asciz  "\n\r$Id: LeeNumeroMensaje.s,v 13.3 2014/11/13 19:05:38 alberto Exp $\n\rBienvenido"
men_ok:         .asciz  "correcto"
men_error:      .asciz  "no cabe"


;;; ***************************************
;;;  programa

        .text
        .global _start
inicio:
_start:
        lds	#_stack     ;inicializaciones habituales
        ldx	#_io_ports  ; de sp e indice x

;;; debemos inicializar el sistema sci
        movw    #BAUDIOS,SC0BDH	; Fijamos la velocidad

;;; Fijamos transmisión de 8 bits sin paridad
        clr     _SC0CR1,X

;;; Borramos todos los flags activos accediendo a SCSR y luego a SCDR
        ldaa    _SC0SR1,X
        ldaa    _SC0DRL,X          ;Por si hay algun flag de recepción

;;; Activamos la recepción y transmisión y las interrupciones de recepcion
        movb   #(RIE|TE|RE),SC0CR2

        cli		;permitimos las interrupciones enmascarables

        ;; Sacamos mensaje de bienvenida
        ldy     #men_hola
        bsr     saca_mensaje

;;; Bucle principal del programa
siguiente:
        clr     numcar
        clr     completo        ;para que se empiezen a recibir caracteres

;;; bucle de espera de buffer completo
espera_completo:
        brclr   completo,#1,espera_completo

;;; tenemos linea, pasamos a convertirla en numero
        ldx     #buffer
        clra            ;ponemos a=0 para que junto a b
        ldab    0,x     ; forme el primer valor
        subb    #'0		;obtenemos el valor del 1er. digito
        std     temp    ;obtenemos la primera suma parcial
sig_car:
        dec     numcar
        beq     tenemos_valor
        inx             ;pasamos al siguiente caracter
        ;; multiplicamos por 10=(4+1)*2 la suma parcial
        ;; pero antes comprobamos que va a caber
        cpd     #0xffff/10
        bhi     no_cabe

        ;;;	ldd	temp   ;no es necesario
        asld
        asld            ; temp*4
        addd    temp    ; temp*4+temp=5*temp
        asld            ; 5*temp*2=10*temp
        std     temp    ; gurdamos
        clra            ;ponemos a=0 para que junto a b
        ldab    0,x     ; forme valor del siguiente
        subb    #'0    ; digito en d
        addd    temp    ; añadimos la suma parcial
        bcs     no_cabe	;vemos a comprobar que cabe
        std     temp
        bra     sig_car
tenemos_valor:
        ;; ya hemos revisado todos los caracteres
        std     valor
        ldy     #men_ok
        bsr     saca_mensaje
        bra     siguiente

no_cabe:
        clr     valor
        ldy     #men_error
        bsr     saca_mensaje
        bra     siguiente


/***************************************************
* saca_mensaje
*   saca por la serial el mensaje apuntado por Y
*   que debe estar terminado en 0
*   se envia el cr y lf al final del mensaje
*   se supone que sci inicializado y transmision habilitada
*/
saca_mensaje:
        psha            ;salvamos los registros modificados
        pshx
        pshy

        ldx     #_io_ports       ;inicializamos para usar indirecto

sig_caracter:
        ldaa    0,y     ;cargamos siguiente caracter
        beq     fin_linea       ;si es 0 ya termino la cadena

        brclr   _SC0SR1,X,TC,.        ;esperamos que transmision disponible
        staa    _SC0DRL,X  ;enviamos el caracter en a

        iny             ;para pasar al siguiente caracater
        bra     sig_caracter

fin_linea:
        brclr   _SC0SR1,X,TC,.	;esperamos que transmision disponible
        ldaa    #CR		;enviamos retorno de carro
        staa    _SC0DRL,X

        brclr   _SC0SR1,X,TC,.	;esperamos que transmision disponible
        ldaa    #LF     ;enviamos salto de linea
        staa    _SC0DRL,X

        puly    ;recuperamos los registros
        pulx
        pula
        rts

/**********************************************
* tratamiento de las interrupciones de sci
*   lee caracteres y descarta los que no sean
*   digitos. los digitos los almacena en buffer
*   cuando se detecta un fin de linea activa completa
*/
vi_sci0:
        ldx     #_io_ports       ;restablecemos x

;;; cargamos registro de estado de sci
        ldaa    _SC0SR1,X
        anda    #RDRF           ;¿se ha recibido algo?
        beq     descarta

        ;; si se ha recibido
        ldaa    _SC0DRL,X        ;copiamos el dato
        tst     completo        ;solo acetamos caracteres si
                                ; el buffer esta libre
        bne     descarta

        cmpa    #CR             ;codigo del retorno

        bne     mira_digito
;;; tenemos el fin de linea
        tst     numcar          ;si la linea no tiene caraceres
        beq     hace_eco        ;  no indicamos completo
        com     completo        ;indicamos completo
                                ;(invirtiendo sus bits)
        ;; debemos mandar el CR y LF
        staa    _SC0DRL,X          ;hacemos eco
        brclr   _SC0SR1,X,TDRE,.   ; esperamos a que se mande
        ldaa    #LF

        bra     hace_eco        ; y hacemos eco

mira_digito:
;;;    primero miramos que quede sition en el buffer
        ldab    numcar
        cmpb    #MAXCARA
        beq     descarta

        cmpa    #'0
        blo     descarta        ;si es menor de 0
        cmpa    #'9
        bhi     descarta        ;si es mayor de 9

        ;;; es digito => lo almacenamos y hacemos eco
        ldy     #buffer         ;hacemos apuntar y al la posicion
        ldab    numcar          ; del siguiente caracter libre
/*
;;;  no metemos los 0 iniciales
        bne	meter
        cmpa	#'0'
        beq	descarta
*/

meter:
        aby
        staa    0,Y             ;almacenamos el caracter leido
        inc     numcar          ;incrementamos el numero de caracteres
hace_eco:
        staa    _SC0DRL,X          ;hacemos eco


descarta:
        rti

        .include        "vectores.inc"

/*
TAMDATA=20
TAMPILA=10
*/

