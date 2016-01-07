/*****************************************
* Salida onda cuadrada por el OC2. Se especifica periondo en
*   variable.

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática 
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: OndaCuadradaOC2.s,v 13.5 2013/11/26 11:53:11 alberto Exp $

  Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo 
  los términos de la Licencia Pública General de GNU según es publicada 
  por la Free Software Foundation, bien de la versión 2 de dicha Licencia 
  o bien (según su elección) de cualquier versión posterior. 

  Este programa se distribuye con la esperanza de que sea útil, pero 
  SIN NINGÚN TIPO DE GARANTÍA, incluso sin la garantía MERCANTIL implícita 
  o sin garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. 
  Véase la Licencia Pública General de GNU para más detalles. 


******************************************/


        .include "registros.inc"
        .include "UtilidadesSeriales.inc"

;;; variables del programa 
        .section .bss
PERIODO:        .skip   2
CuentaI:        .skip   2       ;Cuenta de las interrupcines
        
;;; Las constantes van en la zona de programa

        .section .rodata
men_hola:       .asciz  "\n\r$Id: OndaCuadradaOC2.s,v 13.5 2013/11/26 11:53:11 alberto Exp $\n\rBienvenido\n\r"
        
        .text
        .global _start
_start:	
        lds     #_stack	;Inicializaciones habituales
        ldx     #_io_ports	; de SP e indice X

;;; Inicializamos sistema serial haciendo uso de las utilidades
        jsr     InicializaSerial
        
        ;; Sacamos mensaje de bienvenida
        ldy     #men_hola
        jsr     OutStr
                
        ;; inicilizamos las variables
;        movw   #31250,PERIODO
        movw   #5000,PERIODO
        movw    #0,CuentaI

;;; Inicializamos OC2
        bset    _TIOS,X,#IOS2    ; configuramos como OC
        ;; acción que tomará el OC2
       
        bclr    _TCTL2,X,#OM2	
        bset    _TCTL2,X,#OL2           ; invertirá

       
;; Inicializamos el temporizador
;        bclr   _TMSK2,X,#(PR2|PR1|PR0) ; a la máxima
;        bset   _TMSK2,X,#(PR2|PR1|PR0) ; a la mínima
        bset    _TMSK2,X,#(PR1|PR0) ; a la mínima
        bclr    _TMSK2,X,#(PR2)   

        ldd     _TCNT,X		;Tomamos el valor del temporizador
        addd    PERIODO		;Le sumamos el valor del periodo
        std     _TC2,X		;Preparamos el OC2

        ldaa    #C2F	
        staa    _TFLG1,X         ;Ponemos a 0 el flag del OC2
        bset    _TMSK1,X,#C2I    ;Habilitamos las interrupcines del OC2

        bset    _TSCR,X,#TEN     ; habilitamos el temporizador

        cli                   ;Habilitamos las interrupciones
                
        ;;Bucle del programa principal

Bucle:    
        jsr     getchar         ;espera a que se pulse una tecla
        cmpb    #'+
        bne     MiraMenos
        jsr     putchar
        ldd     PERIODO
        addd    #5
        std     PERIODO
        bra     MuestraCuenta
MiraMenos:
        cmpb    #'-
        bne     MuestraCuenta
        jsr     putchar
        ldd     PERIODO
        subd    #5
        std     PERIODO
MuestraCuenta:
        NuevaLinea
        ldd     CuentaI
        jsr     PrintDecWord

        bra     Bucle

;;; *****************************
;;; Rutina de tratamiento de la interrupción OC2

vi_ioc2:  ; nombre que debe terner la RTI de lo asociado a TC2
        ldx     #_io_ports
                
        ldaa    _TFLG1,X
        anda    #C2F    ;Sacamos el valor del flag del OC2
        beq     FIN_TRATA_OC2   ;Si no está acivo el flag salimos
;;;   ahora estamos seguros que se disparó el OC2 
                
        ldaa    #C2F
        staa    _TFLG1,X ;Ponemos a 0 el flag del OC2
        
        ;Incrementamos contador de interrupciones
        ldy     CuentaI
        iny
        sty     CuentaI
                
        ldd     _TC2,X   ;Cargamos el valor que dio el disparo
        addd    PERIODO ;Le sumamos el periodo
        std     _TC2,X   ;Ponemos la nueva cuenta
FIN_TRATA_OC2:
        rti
        
;;; *****************************
;;; Rutina por defecto par el resto de interrupciones
vi_default:
        PrintMensaje    "\r\nEntramos vi_default"
        rti
        
        
        .include "vectores.inc"

        