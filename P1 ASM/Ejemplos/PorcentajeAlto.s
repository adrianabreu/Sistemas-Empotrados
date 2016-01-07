/****************************************+
* Determina el procentaje (respecto al peridodo total)
* que está una señal en alto
* Señal se recibe por IC1
*

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática 
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: PorcentajeAlto.s,v 13.3 2013/11/26 12:43:21 alberto Exp $

  Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo 
  los términos de la Licencia Pública General de GNU según es publicada 
  por la Free Software Foundation, bien de la versión 2 de dicha Licencia 
  o bien (según su elección) de cualquier versión posterior. 

  Este programa se distribuye con la esperanza de que sea útil, pero 
  SIN NINGÚN TIPO DE GARANTÍA, incluso sin la garantía MERCANTIL implícita 
  o sin garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. 
  Véase la Licencia Pública General de GNU para más detalles. 


****************************************** */
        .include        "registros.inc"
        .include        "UtilidadesSeriales.inc"


;;; **************************************+
;;; Datos

                .section .bss
SUBIDA:         .skip   2
BAJADA:         .skip   2
PORCENT:        .skip   2

        
;;; Programa
        .text
        .global _start
_start: 
        lds	#_stack
        ldx	#_io_ports

        
        ;; vamos a usar la serial
        jsr     InicializaSerial
        ;; sacamos mensaje
        PrintMensaje    "\n\r$Id: PorcentajeAlto.s,v 13.3 2013/11/26 12:43:21 alberto Exp $\n\rBienvenido:\n\r"
        
;;; Configuramos los periféricos
        bclr    _TIOS,X,#IOS1    ; configuramos como IC
        bset    _TCTL4,X,#(EDG1B|EDG1A)	;CAPTURA CUALQUIER FLANCO

;; Inicializamos el temporizador
        movb    #0,TMSK2       ; máxima frecuencia
;        movb    #7,TMSK2       ; minima frecuencia



        ldaa    #C1F
        staa    _TFLG1,X		;Ponemos a 0 el flag del IC1
;        bset    _TMSK1,X,#C1I	;Habilitamos las interrupcines del IC1
        movb    #C1I,TMSK1      ; sólo la del 1
        
        bset    _TSCR,X,#TEN     ; habilitamos el temporizador
        
        cli			;Habilitamos las interrupciones


;;; Inicializamos varibles
        movw     #101,PORCENT   ;valor no valido, es distinto en la primera comparación
        ;; En D tenemos el porcentaje anterior
        ldd     PORCENT
        
MiraNuevo:
;        ldx     #10
;1:      ldy     #0xffff
        ;dbne    y,.             ; bucle de retraso
        ;dbne    x,1b
        ;PutChar '+'
        cpd     PORCENT
        beq     MiraNuevo
        ;; ha habido cambio, lo enviamos por la serial
        ldd     PORCENT
        jsr     PrintDecWord
        NuevaLinea
        
        bra     MiraNuevo

;;; *****************************
;;; Rutina de tratamiento de la interrupción IC1

vi_ioc1:        
        ldx	#_io_ports
        ldaa 	_TFLG1,X
        anda	#C1F		;Sacamos el valor del flag
        beq	FIN_TRATA_IC1	;Si no está acivo el flag salimos

        ldaa	#C1F
        staa	_TFLG1,X		;Ponemos a 0 el flag

        ldd     _TC1,X		;Cargamos el valor que dio el disparo
        brclr	_PORTT,X,#PT1,BAJO
        ;;         PutChar 'H'
        std     SUBIDA		;SOLO TENEMOS QUE ALMACENAR LA SUBIDA
        bra     FIN_TRATA_IC1
BAJO:
        ;;         PutChar 'L'
        ;; ya tenemos la subida y la bajada
        subd    BAJADA		;EN D TENEMOS LOS TOTALES
        xgdx			;LO ALMACENAMOS EN X

        ldd     TC1
        subd    SUBIDA		;EN D TENEMOS LOS ALTOS
        fdiv			;LOS DIVIDIMOS ENTRE LOS TOTALES
        xgdx			;PASAMOS EL COCIENTE A D
        ldx     #(0x10000/100)
        idiv
        stx     PORCENT

        ldd     TC1
        std     BAJADA
FIN_TRATA_IC1:  
        rti


;;; *****************************
;;; Rutina por defecto par el resto de interrupciones
vi_default:
        PrintMensaje    "\r\nEntramos vi_default\r\n"
        rti
                
        .include        "vectores.inc"
