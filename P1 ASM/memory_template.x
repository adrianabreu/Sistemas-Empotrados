/* memory.x 

   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática 
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: memory_template.x,v 13.2 2013/11/26 10:15:43 alberto Exp $

  Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo 
  los términos de la Licencia Pública General de GNU según es publicada 
  por la Free Software Foundation, bien de la versión 2 de dicha Licencia 
  o bien (según su elección) de cualquier versión posterior. 

  Este programa se distribuye con la esperanza de que sea útil, pero 
  SIN NINGÚN TIPO DE GARANTÍA, incluso sin la garantía MERCANTIL implícita 
  o sin garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. 
  Véase la Licencia Pública General de GNU para más detalles. 



$Id: memory_template.x,v 13.2 2013/11/26 10:15:43 alberto Exp $

  Definimos la configuración para las placas de TechArt.
Device: 912D60
EEPROM: $0C00 - $0FFF
Flash: $1000 - $FFFF
RAM: $0200 - $07FF
I/O Regs: $0000

Queremos colocar los programas en la RAM
En la rutina de inicialización del sistema haremos que los registros
de control pasen a la dirección 0x0800 y pondremos los seudovectores
a partir de la dirección 0x07C2
*/

/* Definimos la posicion de la tabla de vectores*/
vectors_addr = 0x07c2; 
/*etiqueta para la pila en lo alto de la memoria RAM no usada.  */
_stack = vectors_addr - 1;

/*Donde estan los registros de control de perifericos*/
_io_ports = 0x0800;

/*No parece posible usar variables en las siguientes expresiones,
pero se pueden poner las expersiones con constantes
*/

MEMORY
{
  page0 (rwx) : ORIGIN = 0x0, LENGTH = 256    
  data        : ORIGIN = 0x0000, LENGTH = $TAMDATA
 /*                                    Vectores   TamPila  Fin Datos */
 text  (rx)  : ORIGIN = 20, LENGTH = 	0x07c2 - $TAMPILA   - $TAMDATA
  eeprom      : ORIGIN = 0x0C00, LENGTH = 1024
}


