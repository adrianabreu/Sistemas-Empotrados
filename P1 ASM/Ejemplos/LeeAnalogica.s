/************************************* 
*Programa para el sistema A/D.
* Saca por la serial el valor convertido.

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática 
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: LeeAnalogica.s,v 13.4 2014/11/13 19:01:14 alberto Exp $

  Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo 
  los términos de la Licencia Pública General de GNU según es publicada 
  por la Free Software Foundation, bien de la versión 2 de dicha Licencia 
  o bien (según su elección) de cualquier versión posterior. 

  Este programa se distribuye con la esperanza de que sea útil, pero 
  SIN NINGÚN TIPO DE GARANTÍA, incluso sin la garantía MERCANTIL implícita 
  o sin garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. 
  Véase la Licencia Pública General de GNU para más detalles. 


****************************************** */

        .include "registros.inc"
        .include "UtilidadesSeriales.inc"

        .section        .rodata

men_hola:       .asciz "\n\r$Id: LeeAnalogica.s,v 13.4 2014/11/13 19:01:14 alberto Exp $\n\rHola:\n\r"

        .section .bss
Actual: .skip   2               ; mantendra el último valor sacado

        .text
        .global _start
_start:
        lds     #_stack
        ldx     #_io_ports

        bsr     InicializaSerial
        ldy     #men_hola
        bsr     OutStr
        PutChar '\n
        PutChar '\r
        
        ;; configuramos el A/D 0
        movb    #(ADPU|DJM),ATD0CTL2 ; justificación a la dercha
        clr     ATD0CTL3        ; no FIFO y S1C=0
        ;; Fijamos 8 bits, muestreo 16 ciclos y frecuencia /10
        movb    #(SMP1|SMP0|PRS3),ATD0CTL4

        ;; Comenzamos 4 conversiones continuas, de único canal 1
        movb    #(SCAN|CA),ATD0CTL5

        ;; Esperamos que terminen las 1as. conversiones
ElPrimero:      
        brclr   _ATD0STAT0,x,#SCF,.
        ;; esperamos que las 4 medidas sean iguales
        ldd     _ADR00H,x
        cmpd    _ADR01H,x
        bne     ElPrimero
        cmpd    _ADR02H,x
        bne     ElPrimero
        cmpd    _ADR03H,x
        bne     ElPrimero

        ;; Tenemos un primer resultado coherente
        bsr     PrintDecWord
        PutChar '\n
        PutChar '\r
        
        std    Actual

        ;;  Repetimos comparando con Actual
NoCambio:       
        brclr   _ATD0STAT0,x,#SCF,.

        ldd     _ADR00H,x
        cpd    Actual
        beq     NoCambio
        ;; Las cuatro tienen que ser iguales para tenerlas en cuenta
        cpd    _ADR01H,x
        bne     NoCambio
        cpd    _ADR02H,x
        bne     NoCambio
        cpd    _ADR03H,x
        bne     NoCambio

        ;; Tenemos un nuevo valor
        bsr     PrintDecWord
        PutChar '\n
        PutChar '\r
        
        std    Actual

        bra     NoCambio
        
        .include        "vectores.inc"
                

        