/*****************************************
* Salida onda genral por el OC2. Se especifica periondo en
 alta y en baja de la señal en dos variables.

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática 
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: OndaGeneralOC2.s,v 13.3 2013/11/26 12:22:43 alberto Exp $

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

;;;  variables del programa 
        .section .bss
Altos:          .skip 2
Bajos:          .skip 2
        

        .text
        .global _start
_start:	
	
        lds     #_stack	;Inicializaciones habituales
        ldx     #_io_ports	; de SP e indice X

;;; Inicializamos sistema serial haciendo uso de las utilidades
        jsr     InicializaSerial
        PrintMensaje     "\n\r$Id: OndaGeneralOC2.s,v 13.3 2013/11/26 12:22:43 alberto Exp $\n\rBienvenido\n\r"

        ;; inicilizamos las variables
        movw    #48,Altos
        movw    #100,Bajos
        
;;; Configuramos los periféricos
        ;; Configuramos OC2
        bset    _TIOS,X,#IOS2    ; configuramos como OC

        ;; acción que tomará el OC2
        bclr    _TCTL2,X,#OM2	
        bset    _TCTL2,X,#OL2           ; invertirá

       
;; Inicializamos el temporizador
;        bclr   _TMSK2,X,#(PR2|PR1|PR0) ; a la máxima frecuencia
        bset   _TMSK2,X,#(PR2|PR1|PR0) ; a la mínima frecuencia
        
        ldd     _TCNT,X		;Tomamos el valor del temporizador
        addd    Bajos		;Le sumamos el valor del periodo
        std     _TC2,X		;Preparamos el OC2

        ldaa    #C2F	
        staa    _TFLG1,X         ;Ponemos a 0 el flag del OC2
        bset    _TMSK1,X,#C2I    ;Habilitamos las interrupcines del OC2
;        movb    #C2I,TMSK1    ;Habilitamos las interrupcines del OC2

        bset    _TSCR,X,#TEN     ; habilitamos el temporizador

        cli                     ;Habilitamos las interrupciones
        
FIN:	
        bra	.                     ; bucle de espera eterna

;;; *****************************
;;;  Rutina de tratamiento de la interrupción OC2
vi_ioc2:        
        ldx     #_io_ports

        ldaa    _TFLG1,X
        anda    #C2F	;Sacamos el valor del flag del OC2
        beq     FIN_TRATA_OC2	;Si no está acivo el flag salimos
/*    ahora estamos seguros que se disparó el OC2 */
        ldaa    #C2F
        staa    _TFLG1,X	;Ponemos a 0 el flag del OC2

        ldd     _TC2,X	;Cargamos el valor que dio el disparo
        brclr   _PORTT,X,#PT2,PT2_a0
        ;; PT2 a pasado a 1
        addd    Altos
        bra     Actualiza_TC2
PT2_a0:
        addd    Bajos
Actualiza_TC2:  
        std     _TC2,X	;Ponemos la nueva cuenta

FIN_TRATA_OC2:  
        rti

;;; *****************************
;;; Rutina por defecto par el resto de interrupciones
vi_default:
        PrintMensaje    "\r\nEntramos vi_default"
        rti
        
        .include "vectores.inc"

        