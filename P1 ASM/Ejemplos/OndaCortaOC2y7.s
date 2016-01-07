/*****************************************
* Genera onda con periodo en alto todo lo pequeño que se quiera.
   el periodo en bajo tiene que ser suficientemente largo para que
   de tiempo ha ejecutarse la RTI

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática 
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: OndaCortaOC2y7.s,v 13.3 2013/11/26 12:27:02 alberto Exp $

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
        PrintMensaje     "\n\r$Id: OndaCortaOC2y7.s,v 13.3 2013/11/26 12:27:02 alberto Exp $\n\rBienvenido\n\r"

        ;; inicilizamos las variables
        movw    #1,Altos
        movw    #399,Bajos

               
;;; Configuramos temporizador
        bset    _TIOS,X,#(IOS2|IOS7)    ; configuramos como OC
        ;; configuramos como entrada para poder leer su valor
        bclr    _DDRT,X,#DDT2

        ;; acción que tomará el OC2
        bset	_TCTL2,X,#OM2
        bclr	_TCTL2,X,#OL2           ; pondrá a 0

        ;; preparamos la acción del oc7
        movb    #OC7M2,OC7M		;OC7 sólo afecta a OC2
        bset    _OC7D,X,#OC7D2           ; lo pone a 1 en cada disparo

;; Inicializamos el temporizador
;        movb    #0,TMSK2       ; máxima frecuencia
        movb    #7,TMSK2       ; minima frecuencia

        ldd     _TCNT,X		;Tomamos el valor del temporizador
        addd    Bajos
        std     _TC7,X      ; Preparamos el OC7
        addd    Altos		;Le sumamos el valor del periodo
        std     _TC2,X     ;Preparamos el OC2

        ldaa    #C2F	
        staa    _TFLG1,X         ;Ponemos a 0 el flag del OC2
        bset    _TMSK1,X,#C2I    ;Habilitamos las interrupcines del OC2

        bset    _TSCR,X,#TEN     ; habilitamos el temporizador

        cli                     ;Habilitamos las interrupciones
        
FIN:	bra	.                     ; bucle de espera eterna




/*****************************
* Rutina de tratamiento de la interrupción OC2
*/

vi_ioc2:        
		ldx       #_io_ports

		ldaa      _TFLG1,X
		anda      #C2F	;Sacamos el valor del flag del OC2
		beq       FIN_TRATA_OC2	;Si no está acivo el flag salimos
;;;     ahora estamos seguros que se disparó el OC2 */
		ldaa      #C2F
		staa      _TFLG1,X	;Ponemos a 0 el flag del OC2

		ldd       _TC2,X	;Cargamos el valor que dio el disparo
      addd      Bajos
      std       _TC7,X
      addd      Altos
		std       _TC2,X	;Ponemos la nueva cuenta

FIN_TRATA_OC2:  
        rti


;;; *****************************
;;; Rutina por defecto par el resto de interrupciones
vi_default:
        PrintMensaje    "\r\nEntramos vi_default"
        rti
        
        .include "vectores.inc"

        