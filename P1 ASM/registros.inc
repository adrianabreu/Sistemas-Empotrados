/*
   Fichero con la definición de las direcciones de los registros
    de control del 68HC12 y los bits dentro de los registros 
    para el GNU AS.


   Copyright (C) Alberto F. Hamilton Castro
   Dpto. de Ingeniería de Sistemas y Automática 
        y Arquitectura y Tecnología de Comutadores
   Universidad de La Laguna

   $Id: registros.inc,v 13.2 2013/11/25 19:23:02 alberto Exp $

  Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo 
  los términos de la Licencia Pública General de GNU según es publicada 
  por la Free Software Foundation, bien de la versión 2 de dicha Licencia 
  o bien (según su elección) de cualquier versión posterior. 

  Este programa se distribuye con la esperanza de que sea útil, pero 
  SIN NINGÚN TIPO DE GARANTÍA, incluso sin la garantía MERCANTIL implícita 
  o sin garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. 
  Véase la Licencia Pública General de GNU para más detalles. 

*/
   .ifndef _io_ports
    .equ _io_ports,0x0800
   .endif


    .equ  _PORTA,0x0000
    .equ  PORTA,_PORTA+_io_ports
        .equ  PA7,1<<7
        .equ  PA6,1<<6
        .equ  PA5,1<<5
        .equ  PA4,1<<4
        .equ  PA3,1<<3
        .equ  PA2,1<<2
        .equ  PA1,1<<1
        .equ  PA0,1

    .equ  _PORTB,0x0001
    .equ  PORTB,_PORTB+_io_ports
        .equ  PB7,1<<7
        .equ  PB6,1<<6
        .equ  PB5,1<<5
        .equ  PB4,1<<4
        .equ  PB3,1<<3
        .equ  PB2,1<<2
        .equ  PB1,1<<1
        .equ  PB0,1

    .equ  _DDRA,0x0002
    .equ  DDRA,_DDRA+_io_ports
        .equ  DDA7,1<<7
        .equ  DDA6,1<<6
        .equ  DDA5,1<<5
        .equ  DDA4,1<<4
        .equ  DDA3,1<<3
        .equ  DDA2,1<<2
        .equ  DDA1,1<<1
        .equ  DDA0,1

    .equ  _DDRB,0x0003
    .equ  DDRB,_DDRB+_io_ports
        .equ  DDB7,1<<7
        .equ  DDB6,1<<6
        .equ  DDB5,1<<5
        .equ  DDB4,1<<4
        .equ  DDB3,1<<3
        .equ  DDB2,1<<2
        .equ  DDB1,1<<1
        .equ  DDB0,1

    .equ  _PORTE,0x0008
    .equ  PORTE,_PORTE+_io_ports
        .equ  PE7,1<<7
        .equ  PE6,1<<6
        .equ  PE5,1<<5
        .equ  PE4,1<<4
        .equ  PE3,1<<3
        .equ  PE2,1<<2
        .equ  PE1,1<<1
        .equ  PE0,1

    .equ  _DDRE,0x0009
    .equ  DDRE,_DDRE+_io_ports
        .equ  DDE7,1<<7
        .equ  DDE6,1<<6
        .equ  DDE5,1<<5
        .equ  DDE4,1<<4
        .equ  DDE3,1<<3
        .equ  DDE2,1<<2

    .equ  _PEAR,0x000A
    .equ  PEAR,_PEAR+_io_ports
        .equ  NDBE,1<<7
        .equ  CGMTE,1<<6
        .equ  PIPOE,1<<5
        .equ  NECLK,1<<4
        .equ  LSTRE,1<<3
        .equ  RDWE,1<<2
        .equ  CALE,1<<1
        .equ  DBENE,1

    .equ  _MODE,0x000B
    .equ  MODE,_MODE+_io_ports
        .equ  SMODN,1<<7
        .equ  MODB,1<<6
        .equ  MODA,1<<5
        .equ  ESTR,1<<4
        .equ  IVIS,1<<3
        .equ  EBSWAI,1<<2
        .equ  EME,1

    .equ  _PUCR,0x000C
    .equ  PUCR,_PUCR+_io_ports
        .equ  PUPH,1<<7
        .equ  PUPG,1<<6
        .equ  PUPE,1<<4
        .equ  PUPB,1<<1
        .equ  PUPA,1

    .equ  _RDRIV,0x000D
    .equ  RDRIV,_RDRIV+_io_ports
        .equ  RDPH,1<<6
        .equ  RDPG,1<<5
        .equ  RDPE,1<<3
        .equ  RDPB,1<<1
        .equ  RDPA,1

    .equ  _INITRM,0x0010
    .equ  INITRM,_INITRM+_io_ports
        .equ  RAM15,1<<7
        .equ  RAM14,1<<6
        .equ  RAM13,1<<5
        .equ  RAM12,1<<4
        .equ  RAM11,1<<3

    .equ  _INITRG,0x0011
    .equ  INITRG,_INITRG+_io_ports
        .equ  REG15,1<<7
        .equ  REG14,1<<6
        .equ  REG13,1<<5
        .equ  REG12,1<<4
        .equ  REG11,1<<3
        .equ  MMSWAI,1

    .equ  _INITEE,0x0012
    .equ  INITEE,_INITEE+_io_ports
        .equ  EE15,1<<7
        .equ  EE14,1<<6
        .equ  EE13,1<<5
        .equ  EE12,1<<4
        .equ  EEON,1

    .equ  _MISC,0x0013
    .equ  MISC,_MISC+_io_ports
        .equ  MAPROM,1<<7
        .equ  NDRF,1<<6
        .equ  RFSTR1,1<<5
        .equ  RFSTR0,1<<4
        .equ  EXSTR1,1<<3
        .equ  EXSTR0,1<<2
        .equ  ROMON28,1<<1
        .equ  ROMON32,1

    .equ  _RTICTL,0x0014
    .equ  RTICTL,_RTICTL+_io_ports
        .equ  RTIE,1<<7
        .equ  RSWAI,1<<6
        .equ  RSBCK,1<<5
        .equ  RTBYP,1<<3
        .equ  RTR2,1<<2
        .equ  RTR1,1<<1
        .equ  RTR0,1

    .equ  _RTIFLG,0x0015
    .equ  RTIFLG,_RTIFLG+_io_ports
        .equ  RTIF,1<<7

    .equ  _COPCTL,0x0016
    .equ  COPCTL,_COPCTL+_io_ports
        .equ  CME,1<<7
        .equ  FCME,1<<6
        .equ  FCMCOP,1<<5
        .equ  WCOP,1<<4
        .equ  DISR,1<<3
        .equ  CR2,1<<2
        .equ  CR1,1<<1
        .equ  CR0,1

    .equ  _COPRST,0x0017
    .equ  COPRST,_COPRST+_io_ports

    .equ  _INTCR,0x001E
    .equ  INTCR,_INTCR+_io_ports
        .equ  IRQE,1<<7
        .equ  IRQEN,1<<6
        .equ  DLY,1<<5

    .equ  _HPRIO,0x001F
    .equ  HPRIO,_HPRIO+_io_ports
        .equ  PSEL5,1<<5
        .equ  PSEL4,1<<4
        .equ  PSEL3,1<<3
        .equ  PSEL2,1<<2
        .equ  PSEL1,1<<1

    .equ  _BRKCT0,0x0020
    .equ  BRKCT0,_BRKCT0+_io_ports
        .equ  BKEN1,1<<7
        .equ  BKEN0,1<<6
        .equ  BKPM,1<<5
        .equ  BK1ALE,1<<3
        .equ  BK0ALE,1<<2

    .equ  _BRKCT1,0x0021
    .equ  BRKCT1,_BRKCT1+_io_ports
        .equ  BKDBE,1<<6
        .equ  BKMBH,1<<5
        .equ  BKMBL,1<<4
        .equ  BK1RWE,1<<3
        .equ  BK1RW,1<<2
        .equ  BK0RWE,1<<1
        .equ  BK0RW,1

    .equ  _BRKAH,0x0022
    .equ  BRKAH,_BRKAH+_io_ports

    .equ  _BRKAL,0x0023
    .equ  BRKAL,_BRKAL+_io_ports

    .equ  _BRKDH,0x0024
    .equ  BRKDH,_BRKDH+_io_ports

    .equ  _BRKDL,0x0025
    .equ  BRKDL,_BRKDL+_io_ports

    .equ  _PORTG,0x0028
    .equ  PORTG,_PORTG+_io_ports
        .equ  PG7,1<<7
        .equ  PG6,1<<6
        .equ  PG5,1<<5
        .equ  PG4,1<<4
        .equ  PG3,1<<3
        .equ  PG2,1<<2
        .equ  PG1,1<<1
        .equ  PG0,1

    .equ  _PORTH,0x0029
    .equ  PORTH,_PORTH+_io_ports
        .equ  PH7,1<<7
        .equ  PH6,1<<6
        .equ  PH5,1<<5
        .equ  PH4,1<<4
        .equ  PH3,1<<3
        .equ  PH2,1<<2
        .equ  PH1,1<<1
        .equ  PH0,1

    .equ  _DDRG,0x002A
    .equ  DDRG,_DDRG+_io_ports
        .equ  DDG7,1<<7
        .equ  DDG6,1<<6
        .equ  DDG5,1<<5
        .equ  DDG4,1<<4
        .equ  DDG3,1<<3
        .equ  DDG2,1<<2
        .equ  DDG1,1<<1
        .equ  DDG0,1

    .equ  _DDRH,0x002B
    .equ  DDRH,_DDRH+_io_ports
        .equ  DDH7,1<<7
        .equ  DDH6,1<<6
        .equ  DDH5,1<<5
        .equ  DDH4,1<<4
        .equ  DDH3,1<<3
        .equ  DDH2,1<<2
        .equ  DDH1,1<<1
        .equ  DDH0,1

    .equ  _KWIEG,0x002C
    .equ  KWIEG,_KWIEG+_io_ports
        .equ  WI2CE,1<<7
        .equ  KWIEG6,1<<6
        .equ  KWIEG5,1<<5
        .equ  KWIEG4,1<<4
        .equ  KWIEG3,1<<3
        .equ  KWIEG2,1<<2
        .equ  KWIEG1,1<<1
        .equ  KWIEG0,1

    .equ  _KWIEH,0x002D
    .equ  KWIEH,_KWIEH+_io_ports
        .equ  KWIEH7,1<<7
        .equ  KWIEH6,1<<6
        .equ  KWIEH5,1<<5
        .equ  KWIEH4,1<<4
        .equ  KWIEH3,1<<3
        .equ  KWIEH2,1<<2
        .equ  KWIEH1,1<<1
        .equ  KWIEH0,1

    .equ  _KWIFG,0x002E
    .equ  KWIFG,_KWIFG+_io_ports
        .equ  KWIFG6,1<<6
        .equ  KWIFG5,1<<5
        .equ  KWIFG4,1<<4
        .equ  KWIFG3,1<<3
        .equ  KWIFG2,1<<2
        .equ  KWIFG1,1<<1
        .equ  KWIFG0,1

    .equ  _KWIFH,0x002F
    .equ  KWIFH,_KWIFH+_io_ports
        .equ  KWIFH7,1<<7
        .equ  KWIFH6,1<<6
        .equ  KWIFH5,1<<5
        .equ  KWIFH4,1<<4
        .equ  KWIFH3,1<<3
        .equ  KWIFH2,1<<2
        .equ  KWIFH1,1<<1
        .equ  KWIFH0,1

    .equ  _SYNR,0x0038
    .equ  SYNR,_SYNR+_io_ports
        .equ  SYN5,1<<5
        .equ  SYN4,1<<4
        .equ  SYN3,1<<3
        .equ  SYN2,1<<2
        .equ  SYN1,1<<1
        .equ  SYN0,1

    .equ  _REFDV,0x0039
    .equ  REFDV,_REFDV+_io_ports
        .equ  REFDV2,1<<2
        .equ  REFDV1,1<<1
        .equ  REFDV0,1

    .equ  _PLLFLG,0x003B
    .equ  PLLFLG,_PLLFLG+_io_ports
        .equ  LOCKIF,1<<7
        .equ  PLLLOCK,1<<6
        .equ  LHIF,1<<1
        .equ  LHOME,1

    .equ  _PLLCR,0x003C
    .equ  PLLCR,_PLLCR+_io_ports
        .equ  LOCKIE,1<<7
        .equ  PLLON,1<<6
        .equ  AUTO,1<<5
        .equ  ACQ,1<<4
        .equ  PSTP,1<<2
        .equ  LHIE,1<<1
        .equ  NOLHM,1

    .equ  _CLKSEL,0x003D
    .equ  CLKSEL,_CLKSEL+_io_ports
        .equ  BCSP,1<<6
        .equ  BCSS,1<<5
        .equ  MCS,1<<2

    .equ  _SLOW,0x003E
    .equ  SLOW,_SLOW+_io_ports
        .equ  SLDV5,1<<5
        .equ  SLDV4,1<<4
        .equ  SLDV3,1<<3
        .equ  SLDV2,1<<2
        .equ  SLDV1,1<<1
        .equ  SLDV0,1

    .equ  _PWCLK,0x0040
    .equ  PWCLK,_PWCLK+_io_ports
        .equ  CON23,1<<7
        .equ  CON01,1<<6
        .equ  PCKA2,1<<5
        .equ  PCKA1,1<<4
        .equ  PCKA0,1<<3
        .equ  PCKB2,1<<2
        .equ  PCKB1,1<<1
        .equ  PCKB0,1

    .equ  _PWPOL,0x0041
    .equ  PWPOL,_PWPOL+_io_ports
        .equ  PCLK3,1<<7
        .equ  PCLK2,1<<6
        .equ  PCLK1,1<<5
        .equ  PCLK0,1<<4
        .equ  PPOL3,1<<3
        .equ  PPOL2,1<<2
        .equ  PPOL1,1<<1
        .equ  PPOL0,1

    .equ  _PWEN,0x0042
    .equ  PWEN,_PWEN+_io_ports
        .equ  PWEN3,1<<3
        .equ  PWEN2,1<<2
        .equ  PWEN1,1<<1
        .equ  PWEN0,1

    .equ  _PWPRES,0x0043
    .equ  PWPRES,_PWPRES+_io_ports

    .equ  _PWSCAL0,0x0044
    .equ  PWSCAL0,_PWSCAL0+_io_ports

    .equ  _PWSCNT0,0x0045
    .equ  PWSCNT0,_PWSCNT0+_io_ports

    .equ  _PWSCAL1,0x0046
    .equ  PWSCAL1,_PWSCAL1+_io_ports

    .equ  _PWSCNT1,0x0047
    .equ  PWSCNT1,_PWSCNT1+_io_ports

    .equ  _PWCNT0,0x0048
    .equ  PWCNT0,_PWCNT0+_io_ports

    .equ  _PWCNT1,0x0049
    .equ  PWCNT1,_PWCNT1+_io_ports

    .equ  _PWCNT2,0x004A
    .equ  PWCNT2,_PWCNT2+_io_ports

    .equ  _PWCNT3,0x004B
    .equ  PWCNT3,_PWCNT3+_io_ports

    .equ  _PWPER0,0x004C
    .equ  PWPER0,_PWPER0+_io_ports

    .equ  _PWPER1,0x004D
    .equ  PWPER1,_PWPER1+_io_ports

    .equ  _PWPER2,0x004E
    .equ  PWPER2,_PWPER2+_io_ports

    .equ  _PWPER3,0x004F
    .equ  PWPER3,_PWPER3+_io_ports

    .equ  _PWDTY0,0x0050
    .equ  PWDTY0,_PWDTY0+_io_ports

    .equ  _PWDTY1,0x0051
    .equ  PWDTY1,_PWDTY1+_io_ports

    .equ  _PWDTY2,0x0052
    .equ  PWDTY2,_PWDTY2+_io_ports

    .equ  _PWDTY3,0x0053
    .equ  PWDTY3,_PWDTY3+_io_ports

    .equ  _PWCTL,0x0054
    .equ  PWCTL,_PWCTL+_io_ports
        .equ  PSWAI,1<<4
        .equ  CENTR,1<<3
        .equ  RDPP,1<<2
        .equ  PUPP,1<<1
        .equ  PSBCK,1

    .equ  _PWTST,0x0055
    .equ  PWTST,_PWTST+_io_ports
        .equ  DISCR,1<<7
        .equ  DISCP,1<<6
        .equ  DISCAL,1<<5

    .equ  _PORTP,0x0056
    .equ  PORTP,_PORTP+_io_ports
        .equ  PP7,1<<7
        .equ  PP6,1<<6
        .equ  PP5,1<<5
        .equ  PP4,1<<4
        .equ  PP3,1<<3
        .equ  PP2,1<<2
        .equ  PP1,1<<1
        .equ  PP0,1

    .equ  _DDRP,0x0057
    .equ  DDRP,_DDRP+_io_ports
        .equ  DDP7,1<<7
        .equ  DDP6,1<<6
        .equ  DDP5,1<<5
        .equ  DDP4,1<<4
        .equ  DDP3,1<<3
        .equ  DDP2,1<<2
        .equ  DDP1,1<<1
        .equ  DDP0,1

    .equ  _ATD0CTL0,0x0060
    .equ  ATD0CTL0,_ATD0CTL0+_io_ports

    .equ  _ATD0CTL1,0x0061
    .equ  ATD0CTL1,_ATD0CTL1+_io_ports

    .equ  _ATD0CTL2,0x0062
    .equ  ATD0CTL2,_ATD0CTL2+_io_ports
        .equ  ADPU,1<<7
        .equ  AFFC,1<<6
        .equ  ASWAI,1<<5
        .equ  DJM,1<<4
        .equ  ASCIE,1<<1
        .equ  ASCIF,1

    .equ  _ATD0CTL3,0x0063
    .equ  ATD0CTL3,_ATD0CTL3+_io_ports
        .equ  S1C,1<<3
        .equ  FIFO,1<<2
        .equ  FRZ1,1<<1
        .equ  FRZ0,1

    .equ  _ATD0CTL4,0x0064
    .equ  ATD0CTL4,_ATD0CTL4+_io_ports
        .equ  RES10,1<<7
        .equ  SMP1,1<<6
        .equ  SMP0,1<<5
        .equ  PRS4,1<<4
        .equ  PRS3,1<<3
        .equ  PRS2,1<<2
        .equ  PRS1,1<<1
        .equ  PRS0,1

    .equ  _ATD0CTL5,0x0065
    .equ  ATD0CTL5,_ATD0CTL5+_io_ports
        .equ  S8C,1<<6
        .equ  SCAN,1<<5
        .equ  MULT,1<<4
        .equ  SC,1<<3
        .equ  CC,1<<2
        .equ  CB,1<<1
        .equ  CA,1

    .equ  _ATD0STAT0,0x0066
    .equ  ATD0STAT0,_ATD0STAT0+_io_ports
        .equ  SCF,1<<7
        .equ  CC2,1<<2
        .equ  CC1,1<<1
        .equ  CC0,1

    .equ  _ATD0STAT1,0x0067
    .equ  ATD0STAT1,_ATD0STAT1+_io_ports
        .equ  CCF7,1<<7
        .equ  CCF6,1<<6
        .equ  CCF5,1<<5
        .equ  CCF4,1<<4
        .equ  CCF3,1<<3
        .equ  CCF2,1<<2
        .equ  CCF1,1<<1
        .equ  CCF0,1

    .equ  _ATD0TESTH,0x0068
    .equ  ATD0TESTH,_ATD0TESTH+_io_ports
        .equ  SAR9,1<<7
        .equ  SAR8,1<<6
        .equ  SAR7,1<<5
        .equ  SAR6,1<<4
        .equ  SAR5,1<<3
        .equ  SAR4,1<<2
        .equ  SAR3,1<<1
        .equ  SAR2,1

    .equ  _ATD0TESTL,0x0069
    .equ  ATD0TESTL,_ATD0TESTL+_io_ports
        .equ  SAR1,1<<7
        .equ  SAR0,1<<6
        .equ  RST,1<<5
        .equ  TSTOUT,1<<4
        .equ  TST3,1<<3
        .equ  TST2,1<<2
        .equ  TST1,1<<1
        .equ  TST0,1

    .equ  _PORTAD0,0x006F
    .equ  PORTAD0,_PORTAD0+_io_ports
        .equ  PAD07,1<<7
        .equ  PAD06,1<<6
        .equ  PAD05,1<<5
        .equ  PAD04,1<<4
        .equ  PAD03,1<<3
        .equ  PAD02,1<<2
        .equ  PAD01,1<<1
        .equ  PAD00,1

    .equ  _ADR00H,0x0070
    .equ  ADR00H,_ADR00H+_io_ports

    .equ  _ADR00L,0x0071
    .equ  ADR00L,_ADR00L+_io_ports

    .equ  _ADR01H,0x0072
    .equ  ADR01H,_ADR01H+_io_ports

    .equ  _ADR01L,0x0073
    .equ  ADR01L,_ADR01L+_io_ports

    .equ  _ADR02H,0x0074
    .equ  ADR02H,_ADR02H+_io_ports

    .equ  _ADR02L,0x0075
    .equ  ADR02L,_ADR02L+_io_ports

    .equ  _ADR03H,0x0076
    .equ  ADR03H,_ADR03H+_io_ports

    .equ  _ADR03L,0x0077
    .equ  ADR03L,_ADR03L+_io_ports

    .equ  _ADR04H,0x0078
    .equ  ADR04H,_ADR04H+_io_ports

    .equ  _ADR04L,0x0079
    .equ  ADR04L,_ADR04L+_io_ports

    .equ  _ADR05H,0x007A
    .equ  ADR05H,_ADR05H+_io_ports

    .equ  _ADR05L,0x007B
    .equ  ADR05L,_ADR05L+_io_ports

    .equ  _ADR06H,0x007C
    .equ  ADR06H,_ADR06H+_io_ports

    .equ  _ADR06L,0x007D
    .equ  ADR06L,_ADR06L+_io_ports

    .equ  _ADR07H,0x007E
    .equ  ADR07H,_ADR07H+_io_ports

    .equ  _ADR07L,0x007F
    .equ  ADR07L,_ADR07L+_io_ports

    .equ  _TIOS,0x0080
    .equ  TIOS,_TIOS+_io_ports
        .equ  IOS7,1<<7
        .equ  IOS6,1<<6
        .equ  IOS5,1<<5
        .equ  IOS4,1<<4
        .equ  IOS3,1<<3
        .equ  IOS2,1<<2
        .equ  IOS1,1<<1
        .equ  IOS0,1

    .equ  _CFORC,0x0081
    .equ  CFORC,_CFORC+_io_ports
        .equ  FOC7,1<<7
        .equ  FOC6,1<<6
        .equ  FOC5,1<<5
        .equ  FOC4,1<<4
        .equ  FOC3,1<<3
        .equ  FOC2,1<<2
        .equ  FOC1,1<<1
        .equ  FOC0,1

    .equ  _OC7M,0x0082
    .equ  OC7M,_OC7M+_io_ports
        .equ  OC7M7,1<<7
        .equ  OC7M6,1<<6
        .equ  OC7M5,1<<5
        .equ  OC7M4,1<<4
        .equ  OC7M3,1<<3
        .equ  OC7M2,1<<2
        .equ  OC7M1,1<<1
        .equ  OC7M0,1

    .equ  _OC7D,0x0083
    .equ  OC7D,_OC7D+_io_ports
        .equ  OC7D7,1<<7
        .equ  OC7D6,1<<6
        .equ  OC7D5,1<<5
        .equ  OC7D4,1<<4
        .equ  OC7D3,1<<3
        .equ  OC7D2,1<<2
        .equ  OC7D1,1<<1
        .equ  OC7D0,1

    .equ  _TCNT,0x0084
    .equ  TCNT,_TCNT+_io_ports


    .equ  _TSCR,0x0086
    .equ  TSCR,_TSCR+_io_ports
        .equ  TEN,1<<7
        .equ  TSWAI,1<<6
        .equ  TSBCK,1<<5
        .equ  TFFCA,1<<4


    .equ  TCTL1,0X0088
    .equ  _TCTL1,0X0888
        .equ  OM7,1<<7
        .equ  OL7,1<<6
        .equ  OM6,1<<5
        .equ  OL6,1<<4
        .equ  OM5,1<<3
        .equ  OL5,1<<2
        .equ  OM4,1<<1
        .equ  OL4,1

    .equ  _TCTL2,0x0089
    .equ  TCTL2,_TCTL2+_io_ports
        .equ  OM3,1<<7
        .equ  OL3,1<<6
        .equ  OM2,1<<5
        .equ  OL2,1<<4
        .equ  OM1,1<<3
        .equ  OL1,1<<2
        .equ  OM0,1<<1
        .equ  OL0,1

    .equ  _TCTL3,0x008A
    .equ  TCTL3,_TCTL3+_io_ports
        .equ  EDG7B,1<<7
        .equ  EDG7A,1<<6
        .equ  EDG6B,1<<5
        .equ  EDG6A,1<<4
        .equ  EDG5B,1<<3
        .equ  EDG5A,1<<2
        .equ  EDG4B,1<<1
        .equ  EDG4A,1

    .equ  _TCTL4,0x008B
    .equ  TCTL4,_TCTL4+_io_ports
        .equ  EDG3B,1<<7
        .equ  EDG3A,1<<6
        .equ  EDG2B,1<<5
        .equ  EDG2A,1<<4
        .equ  EDG1B,1<<3
        .equ  EDG1A,1<<2
        .equ  EDG0B,1<<1
        .equ  EDG0A,1

    .equ  _TMSK1,0x008C
    .equ  TMSK1,_TMSK1+_io_ports
        .equ  C7I,1<<7
        .equ  C6I,1<<6
        .equ  C5I,1<<5
        .equ  C4I,1<<4
        .equ  C3I,1<<3
        .equ  C2I,1<<2
        .equ  C1I,1<<1
        .equ  C0I,1

    .equ  _TMSK2,0x008D
    .equ  TMSK2,_TMSK2+_io_ports
        .equ  TOI,1<<7
        .equ  PUPT,1<<5
        .equ  RDPT,1<<4
        .equ  TCRE,1<<3
        .equ  PR2,1<<2
        .equ  PR1,1<<1
        .equ  PR0,1

    .equ  _TFLG1,0x008E
    .equ  TFLG1,_TFLG1+_io_ports
        .equ  C7F,1<<7
        .equ  C6F,1<<6
        .equ  C5F,1<<5
        .equ  C4F,1<<4
        .equ  C3F,1<<3
        .equ  C2F,1<<2
        .equ  C1F,1<<1
        .equ  C0F,1

    .equ  _TFLG2,0x008F
    .equ  TFLG2,_TFLG2+_io_ports
        .equ  TOF,1<<7

    .equ  _TC0,0x0090
    .equ  TC0,_TC0+_io_ports

    .equ  _TC1,0x0092
    .equ  TC1,_TC1+_io_ports

    .equ  _TC2,0x0094
    .equ  TC2,_TC2+_io_ports

    .equ  _TC3,0x0096
    .equ  TC3,_TC3+_io_ports

    .equ  _TC4,0x0098
    .equ  TC4,_TC4+_io_ports

    .equ  _TC5,0x009A
    .equ  TC5,_TC5+_io_ports

    .equ  _TC6,0x009C
    .equ  TC6,_TC6+_io_ports

    .equ  _TC7,0x009E
    .equ  TC7,_TC7+_io_ports

    .equ  _PACTL,0x00A0
    .equ  PACTL,_PACTL+_io_ports
        .equ  PAEN,1<<6
        .equ  PAMOD,1<<5
        .equ  PEDGE,1<<4
        .equ  CLK1,1<<3
        .equ  CLK0,1<<2
        .equ  PAOVI,1<<1
        .equ  PAI,1

    .equ  _PAFLG,0x00A1
    .equ  PAFLG,_PAFLG+_io_ports
        .equ  PAOVF,1<<1
        .equ  PAIF,1

    .equ  _PACN3,0x00A2
    .equ  PACN3,_PACN3+_io_ports

    .equ  _PACN2,0x00A3
    .equ  PACN2,_PACN2+_io_ports

    .equ  _PACN1,0x00A4
    .equ  PACN1,_PACN1+_io_ports

    .equ  _PACN0,0x00A5
    .equ  PACN0,_PACN0+_io_ports

    .equ  _MCCTL,0x00A6
    .equ  MCCTL,_MCCTL+_io_ports
        .equ  MCZI,1<<7
        .equ  MODMC,1<<6
        .equ  RDMCL,1<<5
        .equ  ICLAT,1<<4
        .equ  FLMC,1<<3
        .equ  MCEN,1<<2
        .equ  MCPR1,1<<1
        .equ  MCPR0,1

    .equ  _MCFLG,0x00A7
    .equ  MCFLG,_MCFLG+_io_ports
        .equ  MCZF,1<<7
        .equ  POLF3,1<<3
        .equ  POLF2,1<<2
        .equ  POLF1,1<<1
        .equ  POLF0,1

    .equ  _ICPACR,0x00A8
    .equ  ICPACR,_ICPACR+_io_ports
        .equ  PA3EN,1<<3
        .equ  PA2EN,1<<2
        .equ  PA1EN,1<<1
        .equ  PA0EN,1

    .equ  _DLYCT,0x00A9
    .equ  DLYCT,_DLYCT+_io_ports
        .equ  DLY1,1<<1
        .equ  DLY0,1

    .equ  _ICOVW,0x00AA
    .equ  ICOVW,_ICOVW+_io_ports
        .equ  NOVW7,1<<7
        .equ  NOVW6,1<<6
        .equ  NOVW5,1<<5
        .equ  NOVW4,1<<4
        .equ  NOVW3,1<<3
        .equ  NOVW2,1<<2
        .equ  NOVW1,1<<1
        .equ  NOVW0,1

    .equ  _ICSYS,0x00AB
    .equ  ICSYS,_ICSYS+_io_ports
        .equ  SH37,1<<7
        .equ  SH26,1<<6
        .equ  SH15,1<<5
        .equ  SH04,1<<4
        .equ  TFMOD,1<<3
        .equ  PACMX,1<<2
        .equ  BUFEN,1<<1
        .equ  LATQ,1

    .equ  _TIMTST,0x00AD
    .equ  TIMTST,_TIMTST+_io_ports
        .equ  TCBYP,1<<1

    .equ  _PORTT,0x00AE
    .equ  PORTT,_PORTT+_io_ports
        .equ  PT7,1<<7
        .equ  PT6,1<<6
        .equ  PT5,1<<5
        .equ  PT4,1<<4
        .equ  PT3,1<<3
        .equ  PT2,1<<2
        .equ  PT1,1<<1
        .equ  PT0,1

    .equ  _DDRT,0x00AF
    .equ  DDRT,_DDRT+_io_ports
        .equ  DDT7,1<<7
        .equ  DDT6,1<<6
        .equ  DDT5,1<<5
        .equ  DDT4,1<<4
        .equ  DDT3,1<<3
        .equ  DDT2,1<<2
        .equ  DDT1,1<<1
        .equ  DDT0,1

    .equ  _PBCTL,0x00B0
    .equ  PBCTL,_PBCTL+_io_ports
        .equ  PBEN,1<<6
        .equ  PBOVI,1<<1

    .equ  _PBFLG,0x00B1
    .equ  PBFLG,_PBFLG+_io_ports
        .equ  PBOVF,1<<1

    .equ  _PA3H,0x00B2
    .equ  PA3H,_PA3H+_io_ports

    .equ  _PA2H,0x00B3
    .equ  PA2H,_PA2H+_io_ports

    .equ  _PA1H,0x00B4
    .equ  PA1H,_PA1H+_io_ports

    .equ  _PA0H,0x00B5
    .equ  PA0H,_PA0H+_io_ports

    .equ  _MCCNTH,0x00B6
    .equ  MCCNTH,_MCCNTH+_io_ports

    .equ  _MCCNTL,0x00B7
    .equ  MCCNTL,_MCCNTL+_io_ports

    .equ  _TC0H,0x00B8
    .equ  TC0H,_TC0H+_io_ports

    .equ  _TC1H,0x00BA
    .equ  TC1H,_TC1H+_io_ports

    .equ  _TC2H,0x00BC
    .equ  TC2H,_TC2H+_io_ports


    .equ  _TC3H,0x00BE
    .equ  TC3H,_TC3H+_io_ports

    .equ  _SC0BDH,0x00C0
    .equ  SC0BDH,_SC0BDH+_io_ports

    .equ  _SC0BDL,0x00C1
    .equ  SC0BDL,_SC0BDL+_io_ports


    .equ  _SC0CR1,0x00C2
    .equ  SC0CR1,_SC0CR1+_io_ports
        .equ  LOOPS,1<<7
        .equ  WOMS,1<<6
        .equ  RSRC,1<<5
        .equ  M,1<<4
        .equ  WAKE,1<<3
        .equ  ILT,1<<2
        .equ  PE,1<<1
        .equ  PT,1

    .equ  _SC0CR2,0x00C3
    .equ  SC0CR2,_SC0CR2+_io_ports
        .equ  TIE,1<<7
        .equ  TCIE,1<<6
        .equ  RIE,1<<5
        .equ  ILIE,1<<4
        .equ  TE,1<<3
        .equ  RE,1<<2
        .equ  RWU,1<<1
        .equ  SBK,1

    .equ  _SC0SR1,0x00C4
    .equ  SC0SR1,_SC0SR1+_io_ports
        .equ  TDRE,1<<7
        .equ  TC,1<<6
        .equ  RDRF,1<<5
        .equ  IDLE,1<<4
        .equ  OR,1<<3
        .equ  NF,1<<2
        .equ  FE,1<<1
        .equ  PF,1

    .equ  _SC0SR2,0x00C5
    .equ  SC0SR2,_SC0SR2+_io_ports
        .equ  SCSWAI,1<<7
        .equ  MIE,1<<6
        .equ  MDL1,1<<5
        .equ  MDL0,1<<4
        .equ  RAF,1

    .equ  _SC0DRH,0x00C6
    .equ  SC0DRH,_SC0DRH+_io_ports
        .equ  R8,1<<7
        .equ  T8,1<<6

    .equ  _SC0DRL,0x00C7
    .equ  SC0DRL,_SC0DRL+_io_ports

/*Los bits de los registros del SC1 son los mismos que los del SC0 */

    .equ  _SC1BDH,0x00C8
    .equ  SC1BDH,_SC1BDH+_io_ports

    .equ  _SC1BDL,0x00C9
    .equ  SC1BDL,_SC1BDL+_io_ports

    .equ  _SC1CR1,0x00CA
    .equ  SC1CR1,_SC1CR1+_io_ports

    .equ  _SC1CR2,0x00CB
    .equ  SC1CR2,_SC1CR2+_io_ports

    .equ  _SC1SR1,0x00CC
    .equ  SC1SR1,_SC1SR1+_io_ports

    .equ  _SC1SR2,0x00CD
    .equ  SC1SR2,_SC1SR2+_io_ports

    .equ  _SC1DRH,0x00CE
    .equ  SC1DRH,_SC1DRH+_io_ports

    .equ  _SC1DRL,0x00CF
    .equ  SC1DRL,_SC1DRL+_io_ports

    .equ  _SP0CR1,0x00D0
    .equ  SP0CR1,_SP0CR1+_io_ports
        .equ  SPIE,1<<7
        .equ  SPE,1<<6
        .equ  SWOM,1<<5
        .equ  MSTR,1<<4
        .equ  CPOL,1<<3
        .equ  CPHA,1<<2
        .equ  SSOE,1<<1
        .equ  LSBF,1

    .equ  _SP0CR2,0x00D1
    .equ  SP0CR2,_SP0CR2+_io_ports
        .equ  SPSWAI,1<<1
        .equ  SPC0,1

    .equ  _SP0BR,0x00D2
    .equ  SP0BR,_SP0BR+_io_ports
        .equ  SPR2,1<<2
        .equ  SPR1,1<<1
        .equ  SPR0,1

    .equ  _SP0SR,0x00D3
    .equ  SP0SR,_SP0SR+_io_ports
        .equ  SPIF,1<<7
        .equ  WCOL,1<<6
        .equ  MODF,1<<4

    .equ  _SP0DR,0x00D5
    .equ  SP0DR,_SP0DR+_io_ports

    .equ  _PORTS,0x00D6
    .equ  PORTS,_PORTS+_io_ports
        .equ  PS7,1<<7
        .equ  PS6,1<<6
        .equ  PS5,1<<5
        .equ  PS4,1<<4
        .equ  PS3,1<<3
        .equ  PS2,1<<2
        .equ  PS1,1<<1
        .equ  PS0,1

    .equ  _DDRS,0x00D7
    .equ  DDRS,_DDRS+_io_ports
        .equ  DDS7,1<<7
        .equ  DDS6,1<<6
        .equ  DDS5,1<<5
        .equ  DDS4,1<<4
        .equ  DDS3,1<<3
        .equ  DDS2,1<<2
        .equ  DDS1,1<<1
        .equ  DDS0,1

    .equ  _PURDS,0x00D9
    .equ  PURDS,_PURDS+_io_ports
        .equ  RDPS2,1<<6
        .equ  RDPS1,1<<5
        .equ  RDPS0,1<<4
        .equ  PUPS2,1<<2
        .equ  PUPS1,1<<1
        .equ  PUPS0,1

    .equ  _EEDIVH,0x00EE
    .equ  EEDIVH,_EEDIVH+_io_ports
        .equ  EEDIV9,1<<1
        .equ  EEDIV8,1

    .equ  _EEDIVL,0x00EF
    .equ  EEDIVL,_EEDIVL+_io_ports
        .equ  EEDIV7,1<<7
        .equ  EEDIV6,1<<6
        .equ  EEDIV5,1<<5
        .equ  EEDIV4,1<<4
        .equ  EEDIV3,1<<3
        .equ  EEDIV2,1<<2
        .equ  EEDIV1,1<<1
        .equ  EEDIV0,1

    .equ  _EEMCR,0x00F0
    .equ  EEMCR,_EEMCR+_io_ports
        .equ  NOBDML,1<<7
        .equ  NOSHB,1<<6
        .equ  FPOPEN,1<<4
        .equ  EESWAI,1<<2
        .equ  PROTLCK,1<<1
        .equ  DMY,1

    .equ  _EEPROT,0x00F1
    .equ  EEPROT,_EEPROT+_io_ports
        .equ  SHPROT,1<<7
        .equ  BPROT4,1<<4
        .equ  BPROT3,1<<3
        .equ  BPROT2,1<<2
        .equ  BPROT1,1<<1
        .equ  BPROT0,1

    .equ  _EEPROG,0x00F3
    .equ  EEPROG,_EEPROG+_io_ports
        .equ  BULKP,1<<7
;;; Es el mismo que en el PLL:  AUTO
        .equ  BYTE,1<<4
        .equ  ROW,1<<3
        .equ  ERASE,1<<2
        .equ  EELAT,1<<1
        .equ  EEPGM,1

    .equ  _FEE32LCK,0x00F4
    .equ  FEE32LCK,_FEE32LCK+_io_ports
        .equ  FEE32LOCK,1

    .equ  _FEE32MCR,0x00F5
    .equ  FEE32MCR,_FEE32MCR+_io_ports
        .equ  BOOTP,1

    .equ  _FEE32CTL,0x00F7
    .equ  FEE32CTL,_FEE32CTL+_io_ports
        .equ  FEESWAI,1<<4
        .equ  HVEN,1<<3
        .equ  ERAS,1<<1
        .equ  PGM,1

    .equ  _FEE28LCK,0x00F8
    .equ  FEE28LCK,_FEE28LCK+_io_ports
        .equ  FEE28LOCK,1

    .equ  _FEE28MCR,0x00F9
    .equ  FEE28MCR,_FEE28MCR+_io_ports
;;; ya está en el 32  BOOTP

    .equ  _FEE28CTL,0x00FB
    .equ  FEE28CTL,_FEE28CTL+_io_ports
                 ;;Los mismos bits que en 32

;;; Registros de subsistema CAN
    .equ  _CMCR0,0x0100
    .equ  CMCR0,_CMCR0+_io_ports
        .equ    CSWAI,1<<5
        .equ    SYNCH ,1<<4
        .equ    TLNKEN ,1<<3
        .equ    SLPAK ,1<<2
        .equ    SLPRQ ,1<<1
    .equ    SFTRES, 1
        
    .equ  _CMCR1,0x0101
    .equ  CMCR1,_CMCR1+_io_ports
        .equ    LOOPB ,1<<2
        .equ    WUPM ,1<<1
        .equ    CLKSRC ,1
         
    .equ  _CBTR0,0x0102
    .equ  CBTR0,_CBTR0+_io_ports
        .equ    SJW1 ,1<<7
        .equ    SJW0 ,1<<6
        .equ    BRP5 ,1<<5
        .equ    BRP4 ,1<<4
        .equ    BRP3 ,1<<3
        .equ    BRP2 ,1<<2
        .equ    BRP1 ,1<<1
        .equ    BRP0 ,1
                
        
    .equ  _CBTR1,0x0103
    .equ  CBTR1,_CBTR1+_io_ports
        .equ    SAMP ,1<<7
        .equ    TSEG22 ,1<<6
        .equ    TSEG21 ,1<<5
        .equ    TSEG20 ,1<<4
        .equ    TSEG13 ,1<<3
        .equ    TSEG12 ,1<<2
        .equ    TSEG11 ,1<<1
        .equ    TSEG10 ,1
                
    .equ  _CRFLG,0x0104
    .equ  CRFLG,_CRFLG+_io_ports
        .equ    WUPIF ,1<<7
        .equ    RWRNIF ,1<<6
        .equ    TWRNIF ,1<<5
        .equ    RERRIF ,1<<4
        .equ    TERRIF ,1<<3
        .equ    BOFFIF ,1<<2
        .equ    OVRIF ,1<<1
        .equ    RXF ,1
                
    .equ  _CRIER,0x0105
    .equ  CRIER,_CRIER+_io_ports
        .equ    WUPIE ,1<<7
        .equ    RWRNIE ,1<<6
        .equ    TWRNIE ,1<<5
        .equ    RERRIE ,1<<4
        .equ    TERRIE ,1<<3
        .equ    BOFFIE ,1<<2
        .equ    OVRIE ,1<<2
        .equ    RXFIE ,1
                
    .equ  _CTFLG,0x0106
    .equ  CTFLG,_CTFLG+_io_ports
        .equ    ABTAK2 ,1<<6
        .equ    ABTAK1 ,1<<5
        .equ    ABTAK0 ,1<<4
        .equ    TXE2 ,1<<2
        .equ    TXE1 ,1<<1
        .equ    TXE0 ,1
                
    .equ  _CTCR,0x0107
    .equ  CTCR,_CTCR+_io_ports
        .equ    ABTRQ2 ,1<<6
        .equ    ABTRQ1 ,1<<5
        .equ    ABTRQ0 ,1<<4
        .equ    TXEIE2 ,1<<2
        .equ    TXEIE1 ,1<<1
        .equ    TXEIE0 ,1
                
    .equ  _CIDAC,0x0108
    .equ  CIDAC,_CIDAC+_io_ports
        .equ    IDAM1 ,1<<5
        .equ    IDAM0 ,1<<4
        .equ    IDHIT2 ,1<<2
        .equ    IDHIT1 ,1<<1
        .equ    IDHIT0 ,1

    .equ  _CRXERR,0x010E
    .equ  CRXERR,_CRXERR+_io_ports
        .equ    RXERR7 ,1<<7
        .equ    RXERR6 ,1<<6
        .equ    RXERR5 ,1<<5
        .equ    RXERR4 ,1<<4
        .equ    RXERR3 ,1<<3
        .equ    RXERR2 ,1<<2
        .equ    RXERR1 ,1<<1
        .equ    RXERR0 ,1
                
    .equ  _CTXERR,0x010F
    .equ  CTXERR,_CTXERR+_io_ports
        .equ    TXERR7 ,1<<7
        .equ    TXERR6 ,1<<6
        .equ    TXERR5 ,1<<5
        .equ    TXERR4 ,1<<4
        .equ    TXERR3 ,1<<3
        .equ    TXERR2 ,1<<2
        .equ    TXERR1 ,1<<1
        .equ    TXERR0 ,1
                
    .equ  _CIDAR0,0x0110
    .equ  CIDAR0,_CIDAR0+_io_ports
        .equ    AC7 ,1<<7
        .equ    AC6 ,1<<6
        .equ    AC5 ,1<<5
        .equ    AC4 ,1<<4
        .equ    AC3 ,1<<3
        .equ    AC2 ,1<<2
        .equ    AC1 ,1<<2
        .equ    AC0 ,1
                
    .equ  _CIDAR1,0x0111
    .equ  CIDAR1,_CIDAR1+_io_ports

    .equ  _CIDAR2,0x0112
    .equ  CIDAR2,_CIDAR2+_io_ports
        
    .equ  _CIDAR3,0x0113
    .equ  CIDAR3,_CIDAR3+_io_ports

    .equ  _CIDMR0,0x0114
    .equ  CIDMR0,_CIDMR0+_io_ports
        .equ    AM7 ,1<<7
        .equ    AM6 ,1<<6
        .equ    AM5 ,1<<5
        .equ    AM4 ,1<<4
        .equ    AM3 ,1<<3
        .equ    AM2 ,1<<2
        .equ    AM1 ,1<<1
        .equ    AM0 ,1
        
    .equ  _CIDMR1,0x0115
    .equ  CIDMR1,_CIDMR1+_io_ports
        
    .equ  _CIDMR2,0x0116
    .equ  CIDMR2,_CIDMR2+_io_ports
        
    .equ  _CIDMR3,0x0117
    .equ  CIDMR3,_CIDMR3+_io_ports
        
    .equ  _CIDAR4,0x0118
    .equ  CIDAR4,_CIDAR4+_io_ports

    .equ  _CIDAR5,0x0119
    .equ  CIDAR5,_CIDAR5+_io_ports

    .equ  _CIDAR6,0x011A
    .equ  CIDAR6,_CIDAR6+_io_ports

    .equ  _CIDAR7,0x011B
    .equ  CIDAR7,_CIDAR7+_io_ports

    .equ  _CIDMR4,0x011C
    .equ  CIDMR4,_CIDMR4+_io_ports
        
    .equ  _CIDMR5,0x011D
    .equ  CIDMR5,_CIDMR5+_io_ports
        
    .equ  _CIDMR6,0x011E
    .equ  CIDMR6,_CIDMR6+_io_ports
        
    .equ  _CIDMR7,0x011F
    .equ  CIDMR7,_CIDMR7+_io_ports
        

    .equ  _PCTLCAN,0x013D
    .equ  PCTLCAN,_PCTLCAN+_io_ports
        .equ    PUPCAN ,1<<1
        .equ    RDPCAN ,1
        
    .equ  _PORTCAN,0x013E
    .equ  PORTCAN,_PORTCAN+_io_ports
        .equ    PCAN7 ,1<<7
        .equ    PCAN6 ,1<<6
        .equ    PCAN5 ,1<<5
        .equ    PCAN4 ,1<<4
        .equ    PCAN3 ,1<<3
        .equ    PCAN2 ,1<<2
        .equ    PCAN1 ,1<<1
        .equ    PCAN0 ,1
        
    .equ  _DDRCAN,0x013F
    .equ  DDRCAN,_DDRCAN+_io_ports
        .equ    DDCAN7 ,1<<7
        .equ    DDCAN6 ,1<<6
        .equ    DDCAN5 ,1<<5
        .equ    DDCAN4 ,1<<4
        .equ    DDCAN3 ,1<<3
        .equ    DDCAN2 ,1<<2
        .equ    DDCAN1 ,1<<1
        .equ    DDCAN0 ,1
        
    .equ  _RxFG,0x0140
    .equ  RxFG,_RxFG+_io_ports
        
    .equ  _Tx0,0x0150
    .equ  Tx0,_Tx0+_io_ports
        
    .equ  _Tx1,0x0160
    .equ  Tx1,_Tx1+_io_ports
        
    .equ  _Tx2,0x0170
    .equ  Tx2,_Tx2+_io_ports
        
;;; Fin de registros del sistema CAN


        
        
    .equ  _ATD1CTL0,0x01E0
    .equ  ATD1CTL0,_ATD1CTL0+_io_ports

    .equ  _ATD1CTL1,0x01E1
    .equ  ATD1CTL1,_ATD1CTL1+_io_ports

    .equ  _ATD1CTL2,0x01E2
    .equ  ATD1CTL2,_ATD1CTL2+_io_ports
        ;; los mismos bites que el 0

    .equ  _ATD1CTL3,0x01E3
    .equ  ATD1CTL3,_ATD1CTL3+_io_ports

    .equ  _ATD1CTL4,0x01E4
    .equ  ATD1CTL4,_ATD1CTL4+_io_ports

    .equ  _ATD1CTL5,0x01E5
    .equ  ATD1CTL5,_ATD1CTL5+_io_ports

    .equ  _ATD1STAT0,0x01E6
    .equ  ATD1STAT0,_ATD1STAT0+_io_ports

    .equ  _ATD1STAT1,0x01E7
    .equ  ATD1STAT1,_ATD1STAT1+_io_ports

    .equ  _ATD1TESTH,0x01E8
    .equ  ATD1TESTH,_ATD1TESTH+_io_ports

    .equ  _ATD1TESTL,0x01E9
    .equ  ATD1TESTL,_ATD1TESTL+_io_ports

    .equ  _PORTAD1,0x01EF
    .equ  PORTAD1,_PORTAD1+_io_ports
        .equ  PAD17,1<<7
        .equ  PAD16,1<<6
        .equ  PAD15,1<<5
        .equ  PAD14,1<<4
        .equ  PAD13,1<<3
        .equ  PAD12,1<<2
        .equ  PAD11,1<<1
        .equ  PAD10,1

    .equ  _ADR10H,0x01F0
    .equ  ADR10H,_ADR10H+_io_ports

    .equ  _ADR10L,0x01F1
    .equ  ADR10L,_ADR10L+_io_ports

    .equ  _ADR11H,0x01F2
    .equ  ADR11H,_ADR11H+_io_ports

    .equ  _ADR11L,0x01F3
    .equ  ADR11L,_ADR11L+_io_ports

    .equ  _ADR12H,0x01F4
    .equ  ADR12H,_ADR12H+_io_ports

    .equ  _ADR12L,0x01F5
    .equ  ADR12L,_ADR12L+_io_ports

    .equ  _ADR13H,0x01F6
    .equ  ADR13H,_ADR13H+_io_ports

    .equ  _ADR13L,0x01F7
    .equ  ADR13L,_ADR13L+_io_ports

    .equ  _ADR14H,0x01F8
    .equ  ADR14H,_ADR14H+_io_ports

    .equ  _ADR14L,0x01F9
    .equ  ADR14L,_ADR14L+_io_ports

    .equ  _ADR15H,0x01FA
    .equ  ADR15H,_ADR15H+_io_ports

    .equ  _ADR15L,0x01FB
    .equ  ADR15L,_ADR15L+_io_ports

    .equ  _ADR16H,0x01FC
    .equ  ADR16H,_ADR16H+_io_ports

    .equ  _ADR16L,0x01FD
    .equ  ADR16L,_ADR16L+_io_ports

    .equ  _ADR17H,0x01FE
    .equ  ADR17H,_ADR17H+_io_ports

    .equ  _ADR17L,0x01FF
    .equ  ADR17L,_ADR17L+_io_ports

