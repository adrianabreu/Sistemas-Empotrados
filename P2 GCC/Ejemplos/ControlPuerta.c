/*****************************************
AUTORES:
    - Adrian Abreu Gonzalez
    - Andres Cidoncha Carballo

PUERTO T:
    FUNCION     PIN
     DISP_RS      9
     DISP_RW      8
     DISP_EN      7
     PITIDO      11 
     
PUERTO H:
    FUNCION     PINES
    DISPLAY     42-35
    
PUERTO G:
    FUNCION     PINES
    TECLADO     14-20
*************************************** */

#define DEBUG 0

#include <sys/param.h>
#include <sys/interrupts.h>
#include <sys/sio.h> //Es aqui donde están las seriales y eso @.@
#include <sys/locks.h>

typedef unsigned char byte;  /*por comodidad*/
typedef unsigned short word;  /*por comodidad*/

/*Acceso a IO PORTS como palabra*/
#define _IO_PORTS_W(d)  (((unsigned volatile short*) & _io_ports[(d)])[0])

#define NOP __asm__ __volatile__ ( "nop" )

/* Puerto de datos del display */
#define P_DATOS   M6812_PORTH
#define P_DATOS_DDR   M6812_DDRH
/* Puerto de control de dislplay */
#define P_CONT    M6812_PORTT
#define P_CONT_DDR    M6812_DDRT

/* Puerto de datos del teclado */
#define P_TEC   M6812_PORTG
#define P_TEC_DDR   M6812_DDRG

/* Bits de control del display */
#define B_EN      M6812B_PT7
#define B_RW      M6812B_PT6
#define B_RS      M6812B_PT5

/* Bits de control del display */
#define CLEAR     ( 1 )
#define SALTO     (( 1 << 7 )| ( 1 << 6 ))

#define RETURN    ( 1 << 1 )

#define CUR_INC    ( ( 1 << 2 ) | ( 1 << 1 ) )
#define SHIFT    ( ( 1 << 2 ) | 1 )

#define DISP_OFF    ( ( 1 << 3 ) )
#define DISP_ON    ( ( 1 << 3 ) | ( 1 << 2 ) )
#define CUR_ON      ( ( 1 << 3 ) | ( 1 << 1 ) )
#define CUR_BLIK      ( ( 1 << 3 ) | ( 1 ) )

#define SHIFT_DISP  ( ( 1 << 4 ) | ( 1 << 3 ) )
#define SHIFT_LEFT  ( ( 1 << 4 ) | ( 1 << 2 ) )

#define DL_8BITS   ( ( 1 << 5 ) | ( 1 << 4 ) )
#define DOS_FILAS   ( ( 1 << 5 ) | ( 1 << 3 ) )
#define FUENTE_5X10   ( ( 1 << 5 ) | ( 1 << 2 ) )

/*Definiciones del teclado*/
#define C1 (1 << 5)
#define C2 (1 << 7)
#define C3 (1 << 3)

#define F1 (1 << 6) 
#define F2 (1 << 1)
#define F3 (1 << 2)
#define F4 (1 << 4)

/*Constantes para OC2*/
#define  TCM_FACTOR ( 3 )  /*La potencia de 2 a aplicar al factor*/
#define  TCM_FREQ ( M6812_CPU_E_CLOCK / ( 1 << TCM_FACTOR ) )
/*Pasa de microsegundos a ticks*/
#define  USG_2_TICKS(us)  ( ( us ) * ( TCM_FREQ / 1000000L ) )
/*Pasa de milisegundos a ticks*/
#define  MSG_2_TICKS(ms)  ( ( ms ) * ( TCM_FREQ / 1000L ) )

unsigned short Periodo; /* Ticks del temporizador que dura el periodo */
unsigned short cuenta_irqs; /* Se incremente en cada interrupción */

/*Tamaño de la clave por defecto y tamaño del temporizador de acceso por defecto */
#define SIZEPASSWD 4
#define CUENTAATRAS 15

/*
   función que realiza un retarso del el número de microsegundos indicados
   en el parámetro usg
   Utiliza canal 6 del temporizador
*/
void delayusg( unsigned long useg ) {
    unsigned int numCiclos;
    unsigned long numCiclosL;

    /* Desconectamos para no afectar al pin */
    _io_ports[ M6812_TCTL1 ] &= ~(M6812B_OM6 | M6812B_OL6);

    /* Vemos velocidad del temporizador*/
    byte factorT = _io_ports[ M6812_TMSK2 ] & 0x07; /*Factor de escalado actual*/
    unsigned long frec = M6812_CPU_E_CLOCK/( 1 << factorT ); /* Frecuencia del temporizador*/
    /* Según la frecuencia elegimos el modo de dividir para evitar desbordamientos */
    if( frec/1000000 )
        numCiclosL = frec/1000000 * useg;
    else
        numCiclosL = frec/100 * useg/10000;

    unsigned int numDisparos = numCiclosL >> 16;  /* Numero de disparos necesarios */
    numCiclos = numCiclosL & 0xffff; /* Número restante de ciclos */

    /* Por si escalado muy grande y useg pequeño */
    if( ( numCiclos == 0 ) && ( numDisparos == 0 ) ) numCiclos = 1;

    _io_ports[ M6812_TIOS ] |= M6812B_IOS6; /*configuramos canal como comparador salida*/
    _io_ports[ M6812_TFLG1 ] = M6812B_C6F; /*Bajamos el banderín  */
    /*preparamos disparo*/
 
    _IO_PORTS_W( M6812_TC6 ) = _IO_PORTS_W( M6812_TCNT ) + numCiclos ;

    /*Habilitamos el temporizador, por si no lo está*/
    _io_ports[ M6812_TSCR ] |= M6812B_TEN;

    /* Esparamos los desboradmientos necesarios */
    do {
        /* Nos quedamos esperando a que se produzca la igualdad*/
        while ( ! ( _io_ports[ M6812_TFLG1 ] & M6812B_C6F ) );
        _io_ports[ M6812_TFLG1 ] = M6812B_C6F; /* Bajamos el banderín */
    } while( numDisparos-- );
}

/* función que genera un cilo de la señal E para realizar un acceso al display
   los valores de las señales RW, RS y datos deben de fijarse antes de llamar a esta
   función */
void cicloAcceso( ) {
    NOP;
    NOP;
    NOP;
    _io_ports[ P_CONT ] |= B_EN; /* subimos señal E */
    NOP;
    NOP;
    NOP;
    NOP;
    NOP;
    NOP;
    _io_ports[ P_CONT ] &= ~B_EN; /* bajamos señal E */
    NOP;
    NOP;
    NOP;
}

/* Envía un byte como comando */
void enviaComando( byte b ) {
    /* Ciclo de escritura con RS = 0 */
    _io_ports[ P_CONT ] &= ~( B_RS | B_RW );
    _io_ports[ P_DATOS ] = b;

    cicloAcceso( );

    /* Esperamos el tiempo que corresponda */
    if( ( b == 1 ) || ( ( b & 0xfe ) == 2 ) )
        delayusg( 1520UL );
    else
        delayusg( 37 );
}

/* Envía un byte como dato */
void enviaDato( byte b ) {
    /* Ciclo de escritura con RS = 1 */
    _io_ports[ P_CONT ] &= ~B_RW;
    _io_ports[ P_CONT ] |= B_RS;
    _io_ports[ P_DATOS ] = b;

    cicloAcceso( );

    /* Esperamos el tiempo que corresponde */
    delayusg( 37 );
}

/*
 *=========================================================
 *FUNCIONES DE INICIALIZACION
 *=========================================================
 */
 
void inicializaDisplay( ) {

    /*======== Configurar puertos del display como salida ============= */
    _io_ports[P_DATOS_DDR]=0xff;
    _io_ports[P_CONT_DDR] |=(B_EN | B_RW | B_RS);
    delayusg( 15000UL );
    enviaComando( DL_8BITS );

    /*======== Resto de la inicialización ============= */
    delayusg( 5000UL );
    enviaComando( DL_8BITS );
    delayusg( 150UL );
    enviaComando( DL_8BITS );    
    enviaComando( DL_8BITS | DOS_FILAS | FUENTE_5X10 );  
    enviaComando( DISP_OFF );
    enviaComando( CLEAR );
    enviaComando( CUR_INC );

    /* Encendemos display con cursor parpadeante */
    enviaComando( DISP_ON | CUR_ON );

}

void iniciaTeclado(){
    
    /* Debido a que usamos el puerto G que tiene pulldown hay que ponerlos a 1*/
    _io_ports[P_TEC_DDR] = F1 | F2 | F3 | F4; 
    _io_ports[P_TEC] = F1 | F2 | F3 | F4; 
    
}

void inicializaSonido(){
    cuenta_irqs = 0;

    /* Iniciamos periodo según microsegundos que queremos que dure */
    Periodo = USG_2_TICKS( 1500 );  /* se hace en tiempo de COMPILACION */
    serial_printdecword( Periodo/USG_2_TICKS( 1 ) );

    /*Inicialización del Temporizador*/
    _io_ports[ M6812_TMSK2 ] = TCM_FACTOR;

    /* OC2 Invierte el pin en cada disparo */
    _io_ports[ M6812_TCTL2 ] &= ~M6812B_OM2;
    _io_ports[ M6812_TCTL2 ] &= ~M6812B_OL2;

    /*preparamos disparo*/
    _IO_PORTS_W( M6812_TC2 ) = _IO_PORTS_W( M6812_TCNT ) + Periodo;


    /*configuramos canal 2 como comparador salida*/
    _io_ports[ M6812_TIOS ] |= M6812B_IOS2;
        
    _io_ports[ M6812_TFLG1 ] = M6812B_IOS2; /*Bajamos el banderín de OC2 */
    _io_ports[ M6812_TMSK1 ] |= M6812B_IOS2; /*habilitamos sus interrupciones*/
    _io_ports[ M6812_TSCR ] = M6812B_TEN; /*Habilitamos temporizador*/

}

/* Invocamos esta funcion para inicializar todo */ 
void inicializa_todo(){
    /* Deshabilitamos interrupciones */
    lock ( );

    /* Inicializamos la serial */
    serial_init( );
    
    inicializaDisplay( ); //Iniciamos display
    iniciaTeclado( ); //Iniciamos teclado
    inicializaSonido(); //Preparamos sonido
    unlock( ); /* habilitamos interrupciones */
    serial_print( "\n\rTerminada inicialización\n\r" );
}

/*
 *================================================================================
 *Funciones de salida
 *================================================================================
 */

/* Funcion para transformar un numero en byte a su equivalente en ASCII*/
byte converttoASCII(byte c){
    byte c_ascii=c+'0';
    return c_ascii;
}

/* Funcion para imprimir un caracter en el display, se debe pasar su codigo ASCII*/
void sacaDisplay( byte c ) {
    enviaDato(c);
}

/* Funcion para imprimir una cadena de texto en el display */
void sacaStringDisplay( char* cadena ){
    int i=0;
    
    while(cadena[i]!='\0'){
        enviaDato(cadena[i]);
        i++;
    }
}

/* Funcion para mostar por el display que se ha accedido y el tiempo restante */
void muestraCuenta (byte c) {
    sacaStringDisplay("ABIERTO");
    enviaComando(SALTO); //SALTO DE LINEA
    sacaStringDisplay("Tiempo:");
    sacaDisplay(converttoASCII(c));
    enviaComando( DISP_ON ); //QUITAMOS EL CURSOR
}

/*
 *En esta funcion generamos el sonido interminente
 *de modo que imite a una alarma
 *Lo hacemos apagando y encendiendo los pines
 */
void delaySonido(int ciclos){
    
    while(ciclos > 0){
        //Encendemos los pines
        _io_ports[ M6812_TCTL2 ] &= ~M6812B_OM2;
        _io_ports[ M6812_TCTL2 ] |= M6812B_OL2;
        delayusg(250000); //Delay de medio segundo
        //Apagamos los pines
        _io_ports[ M6812_TCTL2 ] &= ~M6812B_OM2;
        _io_ports[ M6812_TCTL2 ] &= ~M6812B_OL2;
        delayusg(250000); //Delay de medio segundo
        ciclos--;
    }
   
}

/*
 *======================================================
 *Funciones de entrada
 *======================================================
 */

byte leedesdeteclado(){
  
    byte devolver=0;

    _io_ports[P_TEC] = F1 | F2 | F3 | F4;
    //serial_print("Esperamos a que se suelte la tecla");
    //Esperamos a que se suelte la tecla
    while ((_io_ports[P_TEC] &C1 || _io_ports[P_TEC] &C2 || _io_ports[P_TEC] & C3));
    delayusg(20000UL);

    //serial_print("Esperamos nueva pulsacion");
    //Esperamos una nueva pulsacion
    _io_ports[P_TEC] = F1 | F2 | F3 | F4;
    while (!(_io_ports[P_TEC] &C1 || _io_ports[P_TEC] &C2 || _io_ports[P_TEC] & C3));

    //serial_print("Pulsacion detectada");
    /*
    *Depuracion
    *serial_printbinbyte(_io_ports[P_TEC]);
    *serial_print("\n\r");
    */
    delayusg(20000UL);

    _io_ports[P_TEC] &= ~ (F2 | F3 | F4);
    _io_ports[P_TEC] |= F1;
    if (_io_ports[P_TEC] & C1)
        devolver=1;

    _io_ports[P_TEC] &= ~ (F1 | F3 | F4);
    _io_ports[P_TEC] |= F2;
    if (_io_ports[P_TEC] & C1)
    devolver=4;

    _io_ports[P_TEC] &= ~ (F1 | F2 | F4);
    _io_ports[P_TEC] |= F3;
    if (_io_ports[P_TEC] & C1)
        devolver=7;

    _io_ports[P_TEC] &= ~ (F2 | F3 | F4);
    _io_ports[P_TEC] |= F1;
    if (_io_ports[P_TEC] & C2)
        devolver=2;

    _io_ports[P_TEC] &= ~ (F1 | F3 | F4);
    _io_ports[P_TEC] |= F2;
    if (_io_ports[P_TEC] & C2)
        devolver=5;

    _io_ports[P_TEC] &= ~ (F1 | F2 | F4);
    _io_ports[P_TEC] |= F3;
    if (_io_ports[P_TEC] & C2)
        devolver=8;

    _io_ports[P_TEC] &= ~ (F2 | F3 | F4);
    _io_ports[P_TEC] |= F1;
    if (_io_ports[P_TEC] & C3)
        devolver=3;

    _io_ports[P_TEC] &= ~ (F1 | F3 | F4);
    _io_ports[P_TEC] |= F2;
    if (_io_ports[P_TEC] & C3)
        devolver=6;

    _io_ports[P_TEC] &= ~ (F1 | F2 | F4);
    _io_ports[P_TEC] |= F3;
    if (_io_ports[P_TEC] & C3)
        devolver=9;

    
    return devolver;
}

/*
 *======================================================
 *Funciones del programa principal
 *======================================================
 */

/*Concedemos el acceso durante CUENTAATRAS segundos*/
void printtiempo(){
    int i,j;
    byte number;

    /*Establecemos una cuenta atras que se ira imprimiendo por pantalla*/
    for(i=CUENTAATRAS;i>0;i--){
        enviaComando(CLEAR);
        j=i;
        
        /*Si el numero es mayor de 10 debemos descomponerlo en sus digitos para imprimirlo*/
        if(j>=10){
            number=(unsigned char)j/10;
            j=j%10;
            muestraCuenta(number);
            sacaDisplay(converttoASCII((unsigned char)j));
        }
        else{
            number=(unsigned char)j;
            muestraCuenta(number);           
        }
       /*Esperamos un segundo aprox para que sea en tiempo real*/
       delayusg(1000000);
    }
    enviaComando(CLEAR);
}


/* En caso de error debe sonar la alarma */
void printerror(){
    
    enviaComando(CLEAR);
    sacaStringDisplay("CLAVE ERRONEA");
    enviaComando(SALTO);
    sacaStringDisplay("CALL POLICE");
    enviaComando( DISP_ON ); //QUITAMOS EL CURSOR
    delaySonido(6); 
    enviaComando(CLEAR);
    
}

/* Funcion para comparar la clave original con la clave introducida */
int compararnumeros (byte* a, byte* b){
    int i=0;
    for(i=0;i<SIZEPASSWD;i++)
        if(a[i]!=b[i]){ //SI ALGUN DIGITO ES DISTINTO
            return 0; //EQUIVALENTE A FALSE
        }
        
    return 1; //EQUIVALENTE A TRUE
}

/* Funcion para limpiar el array de la entrada */
void resetpasswd(byte* insert){
    int i;

    for(i=0;i<SIZEPASSWD;i++){
        insert[i]=0;
    }

}

/* Funcion para recibir desde teclado una clave de SIZEPASSWD digitos */
void leeteclado(byte* insert){
    int leidos=0;
    while (leidos < SIZEPASSWD) {
        insert[leidos]=leedesdeteclado();
        sacaStringDisplay("*");
        leidos++;
    }
}

/*
 *=====================================================================
 *=====================================================================
 *                    PROGRAMA PRINCIPAL
 *=====================================================================
 *=====================================================================
 */
 
int main(void){
    /* Reservamos los vectores de bytes para las claves */
    byte pass[SIZEPASSWD];
    byte insert[SIZEPASSWD];
    
    /*Inicializamos teclado, pantalla y altavoz*/
    inicializa_todo();
    
    /* Limpiamos el array de pass */
    resetpasswd(pass);
    
    /*Forzamos el cambio de la contraseña*/
    sacaStringDisplay("INITIAL SETUP");
    enviaComando(SALTO);
    sacaStringDisplay("NUEVA PASS: ");
    leeteclado(pass);
    
    /*Entramos en bucle REPL*/
    while(1){
        enviaComando(CLEAR);
        /*Borramos la respuesta anterior*/
        resetpasswd(insert);
        
        /*Solicitamos la password para abrir*/
        sacaStringDisplay("CERRADA");
        enviaComando(SALTO);
        enviaComando( DISP_ON | CUR_ON);
        sacaStringDisplay("PASS: ");
        
        /* Llamamos a la funcion para almacenar la entrada en insert*/
        leeteclado(insert);
        
        /*Actuamos en base al resultado*/
        if(compararnumeros(pass,insert)==1){
            printtiempo();
        }
        else {
            printerror();
        }
    }
    return 0;
}


/* Manejador interrupciones del OC2  */
void __attribute__( ( interrupt ) ) vi_ioc2 ( void )
{
    _io_ports[ M6812_TFLG1 ] = M6812B_IOS2; /*Bajamos el banderín de OC2 */

    /*preparamos siguiente disparo*/
    _IO_PORTS_W( M6812_TC2 ) = _IO_PORTS_W( M6812_TC2 ) + Periodo;
}

