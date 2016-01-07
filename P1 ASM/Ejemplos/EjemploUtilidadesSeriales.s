/************************************* 
* Programe de ejemplo de manejo de las UtilidadesSeriales.inc

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática 
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: EjemploUtilidadesSeriales.s,v 13.2 2013/11/26 10:12:47 alberto Exp $

  Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo 
  los términos de la Licencia Pública General de GNU según es publicada 
  por la Free Software Foundation, bien de la versión 2 de dicha Licencia 
  o bien (según su elección) de cualquier versión posterior. 

  Este programa se distribuye con la esperanza de que sea útil, pero 
  SIN NINGÚN TIPO DE GARANTÍA, incluso sin la garantía MERCANTIL implícita 
  o sin garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. 
  Véase la Licencia Pública General de GNU para más detalles. 


****************************************** */

;;; Includes necesarios
        .include "registros.inc"
        .include "UtilidadesSeriales.inc" ; Debemos inculir este fichero

        
        .section .bss
WLeido:         .skip   2       ; almacena palabra leida
BLeido:         .skip   1       ; almacena byte leido
        
        .text
        .global _start
_start:
        lds     #_stack
        ldx     #_io_ports
        ;; es imprescindible inicializar serial para poder usar resto funciones
        jsr     InicializaSerial

        ;; Esta macro permite poner el mensaje directamente
        PrintMensaje  "\n\r\n\r$Id: EjemploUtilidadesSeriales.s,v 13.2 2013/11/26 10:12:47 alberto Exp $"

        ;; PrintMensaje
        PrintMensaje     "\n\rHola 1"
        ;; es equivalente a

        .section        .rodata
men1:   .asciz  "\n\rHola 2"

        .text
        pshy
        ldy     #men1
        jsr     OutStr
        puly

;;; Si un mensaje se va a repetir en muchos puntos distintos del programa
;;; se puede ahorrar memoria si se define en la .rodata y se invoca 
;;; directamente OutStr. Si es un mensaje en un bucle no se ahorra nada
;;; Salvo en este caso, es más cómodo y EVITA ERRORES usar PrintMensaje

Bucle:  
        
        PrintMensaje "\n\r\n\rIntroduce word (en decimal), puede usar <- para borrar, <Enter> para terminar \n\r(no se permiten 0 iniciales): "        
        ;; Leemos número decimal, quedará en D
        ;; No se controla ni indica desbordamiento, si metemos número > 65535
        ;;  dará resultado incorrecto
        jsr     ScanDecWord
        
        PrintMensaje "\n\rEl número introducido es : "
        ;; Escribimos número en D en decimal
        jsr     PrintDecWord
        
        PrintMensaje    "\t0x"
        ;; Escribimos número en D en hexadecimal
        jsr     PrintHexWord

        PrintMensaje    "\t0b"
        ;; Escribimos número en D en binario
        jsr     PrintBinWord

;;; Tambien podemos leer bytes
        PrintMensaje "\n\r\n\rIntroduce byte (en binario), puede usar <- para borrar, <Enter> para terminar \n\r(no se permiten 0 iniciales):  0b"        
        ;; Leemos número en binario , quedará en B
        ;; Se controla el desbordamiento ya sólo pueden ser 8 dígitos
        jsr     ScanBinByte
        
        PrintMensaje "\n\rEl número introducido es : "
        ;; Escribimos número en B en decimal
        jsr     PrintDecByte
        
        PrintMensaje    "\t0x"
        ;; Escribimos número en B en hexadecimal
        jsr     PrintHexByte

        PrintMensaje    "\t0b"
        ;; Escribimos número en B en binario
        jsr     PrintBinByte


;;; Sumamos dos números introducidos en hexadecimal
        PrintMensaje    "\n\r\n\rEntra sumandos: 0x"
        ;; Leemos byte en hexadecimal , quedará en B
        ;; Se controla el desbordamiento ya sólo pueden ser 2 dígitos
        jsr     ScanHexByte
        ;; Salvamos en variable
        stab     BLeido
        PrintMensaje    " + 0x"
        jsr     ScanHexByte
        ;; hacemos suma
        PrintMensaje    " = 0x"
        ldaa    BLeido
        aba                     ; el resultado queda en A
        ;; Sacamos un 1 si ha habido acarreo
        bcc     NoAcarreo
        PutChar '1              ; Macro para sacar 1 caracter constante
NoAcarreo:      
        ;; tenemos que pasar a B para poder sacarlo
        tab
        jsr     PrintHexByte
        
        ;; volvemos al principio
        bra Bucle

;;; imprescindible terminar programa inculyendo vectores.inc
        .include "vectores.inc"

