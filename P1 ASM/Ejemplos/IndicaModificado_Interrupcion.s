/* ************************************************************
* Programa ejemplo de manejo de las entradas y salidas digitales
*  con interrupciones
*  Cuando se produce un flanco de bajada en un pin del puerto H
*  En el puerto G se activa led correspondiente al pin modificado

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería Informática y de Sistemas
   Universidad de La Laguna

   $Id: IndicaModificado_Interrupcion.s,v 1.3 2014/11/13 19:00:11 alberto Exp $

  Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo
  los términos de la Licencia Pública General de GNU según es publicada
  por la Free Software Foundation, bien de la versión 2 de dicha Licencia
  o bien (según su elección) de cualquier versión posterior.

  Este programa se distribuye con la esperanza de que sea útil, pero
  SIN NINGÚN TIPO DE GARANTÍA, incluso sin la garantía MERCANTIL implícita
  o sin garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR.
  Véase la Licencia Pública General de GNU para más detalles.


***************************************** */

        ;; Incuimos la definición del nombre de todos los registros de control
        .include "registros.inc"




/***************************************
* Datos
*/
        .section .bss

tmp:    .skip   1    ;Variable temporal para los cálculos

/* El programa *****************************/
        .global _start
        .text
_start:
Inicio:
        ;;Inicialización del sistema
        lds	#_stack     ;Inicializamos SP al final de la RAM
        ldx	#_io_ports	; Inicializamos X a dirección base de registros I/O

        ;;Inicializamos los periféricos
        movb  #0xFF,DDRG   ;Puerto G como salidas
        movb  #0x00,PORTG  ;lo ponemos a 0

        movb  #0x00,DDRH   ;Puerto H como entrada
        bset  PUCR,#PUPH   ;activamos el pull-up

        ldaa  KWIFH    ;Limpiamos registro flags de H
        staa  KWIFH
        movb  #0xFF,KWIEH  ;Habilitamos interrupción por todas las líneas de H

        cli		;permitimos las interrupciones enmascarables

        ;; Bucle infinito del programa principal
espera:

        bra  espera

;;;**********************************************
;;; Tratamiento de las interrupciones de KW puertos G y H

vi_kwgh:
        ;;Directamente en KWIFH tenemos pin modificado
        ldaa  KWIFH
        staa  PORTG
        ;;bajamos banderines interrupción
        staa  KWIFH


        rti


        ;; Para poner vectores de interrupción en su sitio
        .include "vectores.inc"

