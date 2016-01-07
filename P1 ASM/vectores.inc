/********************************
* Fichero de inclusión que define la tabla de vectores.
* Se definen todos los vectores a _start salvo en aquellos para los 
*  que exista una etiqueta vi_nombre, en cuyo caso se usará esa etiqueta.

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática 
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: vectores.inc,v 13.2 2013/11/25 19:23:02 alberto Exp $

  Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo 
  los términos de la Licencia Pública General de GNU según es publicada 
  por la Free Software Foundation, bien de la versión 2 de dicha Licencia 
  o bien (según su elección) de cualquier versión posterior. 

  Este programa se distribuye con la esperanza de que sea útil, pero 
  SIN NINGÚN TIPO DE GARANTÍA, incluso sin la garantía MERCANTIL implícita 
  o sin garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. 
  Véase la Licencia Pública General de GNU para más detalles. 

******************************************/

/*
            
Todos los vectores de interrupción quedan apuntando 
  a la etiqueta 'vi_default', salvo el vector de reset de 
  encendido que queda apuntando a la etiqueta '_start'.
  A su vez, si no se define, 'vi_default'  apuntará a '_start'.


  Para modificar algún vector de interrupción es necesario
    definir la etiqueta correspondiente, asignándole un valor 
    con un equ o utilizándola como nombre de 
    la rutina de tratamiento de la interrupción. 
    El nombre de las etiquetas es el que aparece en la siguiente lista:

  * vi_osc   Interrupción del sistema oscilador
  * vi_cantx   Transmisión en el subsistema CAN
  * vi_canrx   Recepción en el subsistema CAN
  * vi_canerr   Errores en el subsistema CAN
  * vi_pabov   Desbordamiento del acumulador de pulsos B
  * vi_cmuv   Cuenta final del contador de módulo
  * vi_kwgh   Activación de los puestos G ó H
  * vi_canwu   Activación del subsistema CAN
  * vi_atd   Conversores analógicos
  * vi_sci1   Interrupción del sistema SCI 1
  * vi_sci0   Interrupción del sistema SCI 0
  * vi_spi   Interrupción del sistema SPI
  * vi_pai   Flanco del acumulador de pulsos
  * vi_paov   Desbordamiento del acumulador de pulsosA
  * vi_tov   Desbordamiento del temporizador
  * vi_ioc7   Canal 7 del temporizador
  * vi_ioc6   Canal 6 del temporizador
  * vi_ioc5   Canal 5 del temporizador
  * vi_ioc4   Canal 4 del temporizador
  * vi_ioc3   Canal 3 del temporizador
  * vi_ioc2   Canal 2 del temporizador
  * vi_ioc1   Canal 1 del temporizador
  * vi_ioc0   Canal 0 del temporizador
  * vi_rti   Interrupción de tiempo real
  * vi_irq   Interrupción línea IRQ
  * vi_xirq   Interrupción línea XIRQ 
  * vi_swi   Instrucción SWI
  * vi_trap   Instrucción Ilegal
  * vi_copreset   Reset por temporizador COP
  * vi_clkreset   Reset por fallo del reloj
  * vi_poreset   Reset externo o reset de encendido

 Estas etiquetas han de estar definidas cuando se carga este fichero,
  por ello, debe incluirse el final del código fuente de cada programa.

*/
             



/*Vectores de interrupción*/
      .ifndef vi_default
            .equ vi_default,_start
      .endif

     .section .vectors
Pos_VI: 

;;Interrupción del sistema oscilador
    .ifdef    vi_osc
        .word    vi_osc
    .else
        .word    vi_default
    .endif

;;Transmisión en el subsistema CAN
    .ifdef    vi_cantx
        .word    vi_cantx
    .else
        .word    vi_default
    .endif

;;Recepción en el subsistema CAN
    .ifdef    vi_canrx
        .word    vi_canrx
    .else
        .word    vi_default
    .endif

;;Errores en el subsistema CAN
    .ifdef    vi_canerr
        .word    vi_canerr
    .else
        .word    vi_default
    .endif

;;Desbordamiento del acumulador de pulsos B
    .ifdef    vi_pabov
        .word    vi_pabov
    .else
        .word    vi_default
    .endif

;;Cuenta final del contador de módulo
    .ifdef    vi_cmuv
        .word    vi_cmuv
    .else
        .word    vi_default
    .endif

;;Activación de los puestos G ó H
    .ifdef    vi_kwgh
        .word    vi_kwgh
    .else
        .word    vi_default
    .endif

;;Activación del subsistema CAN
    .ifdef    vi_canwu
        .word    vi_canwu
    .else
        .word    vi_default
    .endif

;;Conversores analógicos
    .ifdef    vi_atd
        .word    vi_atd
    .else
        .word    vi_default
    .endif

;;Interrupción del sistema SCI 1
    .ifdef    vi_sci1
        .word    vi_sci1
    .else
        .word    vi_default
    .endif

;;Interrupción del sistema SCI 0
    .ifdef    vi_sci0
        .word    vi_sci0
    .else
        .word    vi_default
    .endif

;;Interrupción del sistema SPI
    .ifdef    vi_spi
        .word    vi_spi
    .else
        .word    vi_default
    .endif

;;Flanco del acumulador de pulsos
    .ifdef    vi_pai
        .word    vi_pai
    .else
        .word    vi_default
    .endif

;;Desbordamiento del acumulador de pulsosA
    .ifdef    vi_paov
        .word    vi_paov
    .else
        .word    vi_default
    .endif

;;Desbordamiento del temporizador
    .ifdef    vi_tov
        .word    vi_tov
    .else
        .word    vi_default
    .endif

;;Canal 7 del temporizador
    .ifdef    vi_ioc7
        .word    vi_ioc7
    .else
        .word    vi_default
    .endif

;;Canal 6 del temporizador
    .ifdef    vi_ioc6
        .word    vi_ioc6
    .else
        .word    vi_default
    .endif

;;Canal 5 del temporizador
    .ifdef    vi_ioc5
        .word    vi_ioc5
    .else
        .word    vi_default
    .endif

;;Canal 4 del temporizador
    .ifdef    vi_ioc4
        .word    vi_ioc4
    .else
        .word    vi_default
    .endif

;;Canal 3 del temporizador
    .ifdef    vi_ioc3
        .word    vi_ioc3
    .else
        .word    vi_default
    .endif

;;Canal 2 del temporizador
    .ifdef    vi_ioc2
        .word    vi_ioc2
    .else
        .word    vi_default
    .endif

;;Canal 1 del temporizador
    .ifdef    vi_ioc1
        .word    vi_ioc1
    .else
        .word    vi_default
    .endif

;;Canal 0 del temporizador
    .ifdef    vi_ioc0
        .word    vi_ioc0
    .else
        .word    vi_default
    .endif

;;Interrupción de tiempo real
    .ifdef    vi_rti
        .word    vi_rti
    .else
        .word    vi_default
    .endif

;;Interrupción línea IRQ
    .ifdef    vi_irq
        .word    vi_irq
    .else
        .word    vi_default
    .endif

;;Interrupción línea XIRQ 
    .ifdef    vi_xirq
        .word    vi_xirq
    .else
        .word    vi_default
    .endif

;;Instrucción SWI
    .ifdef    vi_swi
        .word    vi_swi
    .else
        .word    vi_default
    .endif

;;Instrucción Ilegal
    .ifdef    vi_trap
        .word    vi_trap
    .else
        .word    vi_default
    .endif

;;Reset por temporizador COP
    .ifdef    vi_copreset
        .word    vi_copreset
    .else
        .word    vi_default
    .endif

;;Reset por fallo del reloj
    .ifdef    vi_clkreset
        .word    vi_clkreset
    .else
        .word    vi_default
    .endif

;;Reset externo o reset de encendido
    .ifdef    vi_poreset
        .word    vi_poreset
    .else
        .word    _start
    .endif


/* fin tabla vectores*/