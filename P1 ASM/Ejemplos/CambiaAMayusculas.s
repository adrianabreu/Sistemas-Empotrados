/* ************************************************************
* Programa ejemplo de manejo de la serial SCI
*  Realiza el eco de lo que le llega, devolviendolo con las
*  mayusculas invertidas

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: CambiaAMayusculas.s,v 13.4 2014/11/13 19:05:38 alberto Exp $

  Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo
  los términos de la Licencia Pública General de GNU según es publicada
  por la Free Software Foundation, bien de la versión 2 de dicha Licencia
  o bien (según su elección) de cualquier versión posterior.

  Este programa se distribuye con la esperanza de que sea útil, pero
  SIN NINGÚN TIPO DE GARANTÍA, incluso sin la garantía MERCANTIL implícita
  o sin garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR.
  Véase la Licencia Pública General de GNU para más detalles.


***************************************** */

        .equ    BIT5,0b00100000
        .equ    SC9600BAUDIOS,52 ; constante para obtener baudios en SC
        .equ    SC38400BAUDIOS,13
        .equ    BAUDIOS,SC38400BAUDIOS

        ;; Incuimos la definición del nombre de todos los registros de control
        .include "registros.inc"




/***************************************
* Datos
*/
        .section .bss
buffer:
        .skip   1

/* El programa *****************************/
        .global _start
        .text
_start:
Inicio:
        lds	#_stack     ;Inicializamos SP al final de la RAM
        ldx	#_io_ports	; Inicializamos X a dirección base de registros I/O

;;; Debemos inicializar el sistema SCI
        movw    #BAUDIOS,SC0BDH	; Fijamos la velocidad

;;; Fijamos transmisión de 8 bits sin paridad
        clr     _SC0CR1,X

;;; Borramos todos los flags de recepción accediendo a SCSR y luego a SCDR
        ldaa    _SC0SR1,X
        ldaa    _SC0DRL,X


;;; Activamos la recepción y transmisión y las interrupciones de recepcion
        movb   #(RIE|TE|RE),SC0CR2

        cli		;permitimos las interrupciones enmascarables

;; Bucle de espera de interrupciones
fin:
        bra	fin

;;;**********************************************
;;; Tratamiento de las interrupciones de SCI

vi_sci0:   ; nombre que ha de tener la RTI de SCI 0
        ldx     #_io_ports      ;restablecemos X

;;; cargamos registro de estado de SCI
        ldaa    _SC0SR1,X
        anda    #RDRF           ;¿SE HA RECIBIDO ALGO?
        beq     mira_transmision
;;; 	si se ha recibido
        ldaa    _SC0DRL,X        ;copiamos el dato
        cmpa    #'A
        blo     compru_minus
        cmpa    #'Z
        bhi     compru_minus
        ;; es mayuscula
        oraa    #BIT5           ;cambiamos a minuscula
        bra     almacena

compru_minus:
        cmpa    #'a
        blo     almacena
        cmpa    #'z
        bhi     almacena
        ;; es minuscula
        anda    #~BIT5          ;cambiamos a mayuscula

almacena:
        staa    buffer          ;almacenamos el dato a transmitir

mira_transmision:
        ldaa    _SC0SR1,X
        anda    #TDRE
        beq     fin_trata_sci   ;la transmision no ha terminado

        ldaa    buffer
        staa    _SC0DRL,X ;lanzamos el siguiente caracter

fin_trata_sci:
        rti

        ;; Para poner vectores de interrupción en su sitio
        .include "vectores.inc"

