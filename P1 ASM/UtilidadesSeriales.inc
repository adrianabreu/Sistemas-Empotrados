/********************************
* Fichero de inclusión para la llamada a las utilidades seriales 
*  que se encuentran en la flash
*        

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática 
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: UtilidadesSeriales_cabecera.inc,v 13.2 2013/11/25 19:23:02 alberto Exp $

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


;;; Macro para sacar caracteres constantes
        .macro  PutChar car
        brclr   SC0SR1,TDRE,.  ;loop waitin for the TDRE bit to be set
        movb    #\car,SC0DRL             ;send char
        .endm

;;; Macro para mandar salto de lines y cr
        .macro NuevaLinea
        brclr   SC0SR1,TDRE,.  ;loop waitin for the TDRE bit to be set
        movb    #'\n,SC0DRL             ;send char
        brclr   SC0SR1,TDRE,.  ;loop waitin for the TDRE bit to be set
        movb    #'\r,SC0DRL             ;send char
        .endm

;;; Macro para mandar mensajes definidos directamente
       .macro  PrintMensaje    m
                .section        .rodata
                dato\@:         
                                .asciz   "\m"
                .text
        ;; para no perder y
                pshy
                ldy    #dato\@
                jsr     OutStr
                puly
        .endm
        

;;; ---------------------------------------------
;;; InicializaSerial:
;;; Rutina de inicialización de la SC0 a 38400 baudios
;;;  Se activa transmisión y recepción sin interrupciones
;;; ---------------------------------------------
  .global InicializaSerial
  
;;; ----------------------------------------------------
;;; PrintBinByte:
;;; Saca byte en binario contenido en B
;;; ----------------------------------------------------
  .global PrintBinByte

;;; ----------------------------------------------------
;;; PrintBinWord:
;;; Saca word en binario contenido en D
;;; ----------------------------------------------------
       
;;; ----------------------------------------------------
;;; PrintHexByte:
;;; Saca byte en hexadecimal contenido en B
;;; ----------------------------------------------------
  .global PrintHexByte

;;; ----------------------------------------------------------
;;; PrintHexWord:
;;; Saca en hexadecimal el contenido de D
;;; ----------------------------------------------------------
  .global PrintHexWord

;;; -------------------------------------------------------------------
;;; PrintDecByte:
;;; Saca en decimal el contenido de B
;;; -------------------------------------------------------------------
  .global PrintDecByte

;;; --------------------------------------------------------------
;;; PrintDecWord:
;;; Saca en decimal el contenido de D
;;; -----------------------------------------------------------
  .global PrintDecWord

;;; -------------------------------------------------------------------
;;; ScanDecByte:
;;;  Invoca a ScanDecWord y devuelve la parte baja de D en B.
;;; ------------------------------------------------------------------
  .global ScanDecByte
        
;;; -------------------------------------------------------------------
;;; ScanDecWord:
;;; Lee digitos para formar decimal, despreciando no dígitos, 
;;;   y permitiendo borrar, termina con CR. No permite 0 iniciales.
;;;  Para introducir 0 pulsar CR sin ningún dígito.
;;;  No se controla ni se indica desbordamiento aunque sólo se permiten 5
;;;   dígitos
;;;   Número se devuelve en D.
;;; ------------------------------------------------------------------
  .global ScanDecWord

;;; -------------------------------------------------------------------
;;; ScanHexWord:
;;; Lee digitos para formar hexadecimal, despreciando no dígitos, 
;;;   y permitiendo borrar, termina en CR. No permite 0 iniciales.
;;;  Para introducir 0 pulsar CR sin ningún dígito.
;;;  No permite el desbordamiento (sólo 4 dígitos).
;;;   Número lo devuelve en D
;;; ------------------------------------------------------------------
  .global ScanHexWord
        
;;; -------------------------------------------------------------------
;;; ScanHexByte:
;;; Lee digitos para formar hexadecimal, despreciando no dígitos, 
;;;   y permitiendo borrar, termina en CR. No permite 0 iniciales.
;;;  Para introducir 0 pulsar CR sin ningún dígito.
;;;  No permite el desbordamiento (sólo 2 dígitos).
;;;   Número lo devuelve en B
;;; ------------------------------------------------------------------
  .global ScanHexByte
        
;;; -------------------------------------------------------------------
;;; ScanBinByte:
;;; Lee 0s y 1s para formar binario y permitiendo borrar, termina en CR.
;;; No permite 0 iniciales.
;;;  Para introducir 0 pulsar CR sin ningún dígito.
;;;  No permite el desbordamiento (sólo 8 dígitos).
;;;   Número lo devuelve en B.
;;; ------------------------------------------------------------------
  .global ScanBinByte
          .global putchar

;;;--------------------------------------------------------------------------
;;; getchar:
;;;  Lee caracte y lo devuelve en B
;;; -------------------------------------------------------------------------
  .global getchar

;;; -----------------------------------------------------------------------
;;; OutStr:
;;; Saca Cadena apuntada por Y y terminada en 0.
;;;   Y queda apuntando al final (caracter 0)
;;; ----------------------------------------------------------------------
  .global OutStr

;;; ----------------------------------------------------------------------
;;; putchar:
;;;  Saca caracter almacenado en B
;;; ----------------------------------------------------------------------
  .global putchar

putchar=0x0000e02a
ScanHexWord=0x0000e01b
ScanDecByte=0x0000e015
PrintDecByte=0x0000e00f
InicializaSerial=0x0000e000
ScanHexByte=0x0000e01e
ScanBinByte=0x0000e021
PrintBinWord=0x0000e006
PrintBinByte=0x0000e003
OutStr=0x0000e027
getchar=0x0000e024
PrintHexWord=0x0000e00c
PrintDecWord=0x0000e012
ScanDecWord=0x0000e018
PrintHexByte=0x0000e009
