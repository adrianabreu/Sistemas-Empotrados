
        .include "registros.inc"
        .include "UtilidadesSeriales.inc"

;;; variables del programa 
        .section .bss
PERIODO:        .skip   2
DispI:          .skip   1       ;Variable para display
WLeido:         .skip   2       ; almacena palabra leida
BLeido:         .skip   1       ; almacena byte leido
Digits1:        .skip   1       ;48
Digits2:        .skip   1       ;56
Digits3:        .skip   1       ;64
Digits4:        .skip   1       ;72
Cont:           .skip   1       ;VARIABLE CONTADOR
;;; Las constantes van en la zona de programa

        .text
        .global _start
_start:
        lds     #_stack
        ldy     #_io_ports
        ;; es imprescindible inicializar serial para poder usar resto funciones
        jsr     InicializaSerial

        ;; Esta macro permite poner el mensaje directamente
        PrintMensaje  "\n\r\n\r$Id: P1 - Adrian Andres$"

        ;; PrintMensaje
        PrintMensaje     "\n\rHola 1"
        
        movb   #0b11111111,DDRH ;;DEFINIMOS H TODO SALIDA

        ;;DEFINIMOS PERIODO
        movw   #5000,PERIODO
        movb    #0,DispI
        
        movb    #0,Cont
        
;;; Inicializamos OC2
        bset    _TIOS,Y,#IOS2    ; configuramos como OC
        ;; acción que tomará el OC2
       
        bclr    _TCTL2,Y,#OM2	
        bset    _TCTL2,Y,#OL2           ; invertirá

       
;; Inicializamos el temporizador
;       bclr   _TMSK2,Y,#(PR2|PR1|PR0) ; a la máxima
;       bset   _TMSK2,Y,#(PR2|PR1|PR0) ; a la mínima
        bset    _TMSK2,Y,#(PR1|PR0) ; a la mínima
        bclr    _TMSK2,Y,#(PR2)   

        ldd     _TCNT,Y		;Tomamos el valor del temporizador
        addd    PERIODO		;Le sumamos el valor del periodo
        std     _TC2,Y		;Preparamos el OC2

        ldaa    #C2F	
        staa    _TFLG1,Y         ;Ponemos a 0 el flag del OC2
        bset    _TMSK1,Y,#C2I    ;Habilitamos las interrupcines del OC2

        bset    _TSCR,Y,#TEN     ; habilitamos el temporizador

        cli                   ;Habilitamos las interrupciones

;;==============================================================================

Bucle:  
        
        PrintMensaje "\n\r\n\rIntroduce numero decimal de 4 cifras:"        
        jsr     ScanDecWord ;;Se guarda en D
        CPD     #9999 ;;Comparamos con 9999 
        BHI     FueraDeRango ;;Saltamos si es mayor
        PrintMensaje "\n\rSalida: "
        jsr     PrintDecWord

;;Digits1:        .skip   1       ;48
;;Digits2:        .skip   1       ;56
;;Digits3:        .skip   1       ;64
;;Digits4:        .skip   1       ;72 
        LDAA #16
        STAA Digits1
        LDAA #32
        STAA Digits2
        LDAA #64
        STAA Digits3
        LDAA #128
        STAA Digits4
        
        LDX #10 ;;10 en decimal
        IDIV
        ;;X COCIENTE D RESTO
        LDAA Digits1
        ABA
        STAA Digits1
        XGDX
        LDX #10 ;;10 en decimal
        IDIV
        ;;X COCIENTE D RESTO
        LDAA Digits2
        ABA
        STAA Digits2
        XGDX
        LDX #10 ;;10 en decimal
        IDIV
        ;;X COCIENTE D RESTO
        LDAA Digits3
        ABA
        STAA Digits3
        XGDX
        LDX #10 ;;10 en decimal
        IDIV
        ;;X COCIENTE D RESTO
        LDAA Digits4
        ABA
        STAA Digits4
        XGDX

;;==============================================================================
;;; *****************************
;;; Rutina de tratamiento de la interrupción OC2
resetcont:
        LDAA #48
        STAA Cont
        jmp  show

vi_ioc2:  ; nombre que debe terner la RTI de lo asociado a TC2
        ldy     #_io_ports
                
        ldaa    _TFLG1,Y
        anda    #C2F    ;Sacamos el valor del flag del OC2
        beq     FIN_TRATA_OC2   ;Si no está acivo el flag salimos
;;;   ahora estamos seguros que se disparó el OC2 
                
        ldaa    #C2F
        staa    _TFLG1,Y ;Ponemos a 0 el flag del OC2
        
;;==============================================================================
        LDAA #72
        CMPA Cont
        BHI resetcont
        LDAA Cont
        ADCA #8
        STAA Cont
show:
        LDX Cont
        LDAA 0,X
        STAA PORTH
;;==============================================================================
                
        ldd     _TC2,Y   ;Cargamos el valor que dio el disparo
        addd    PERIODO ;Le sumamos el periodo
        std     _TC2,Y   ;Ponemos la nueva cuenta
        
FIN_TRATA_OC2:
        rti
        
;;; *****************************
;;; Rutina por defecto par el resto de interrupciones
vi_default:
        PrintMensaje    "\r\nEntramos vi_default"
        rti
        
FueraDeRango:
        PrintMensaje "\n\rEl numero introducido es demasiado grande"
        
        .include "vectores.inc"
