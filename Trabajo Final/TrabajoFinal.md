#Trabajo Final de Empotrados

##Enunciado

El diseño debe tratar al menos los siguientes tópicos.

* Selección y justificación de la batería adecuada, incluyendo criterios de peso, precio, utilidad para el diseño, etc.
* Análisis de durabilidad de la batería utilizada, para ello se pueden utilizar las pruebas de la fuente de alimentación desarrollada en la práctica 1.
* Análisis de la arquitectura utilizada para desarrollar el sistema empotrado, según transparencias vistas en clase.
* Tamaño y velocidad del procesador / microcontrolador a utilizar.
* Tamaño de los distintos tipos de memoria a utilizar: RAM, ROM, EEPROM, Flash EEPROM.
* Lenguaje de programación y entorno a utilizar para el desarrollo de su firmware.
* Protocolos de comunicación usados.
* Diseños electrónicos, esquemas de conexión, selección de buses, etc
* Estimación de tiempo de desarrollo y pruebas en horas/hombre.

Se valorará:

* La eficiencia del sistema desarrollado
* La claridad del diseño
* La funcionalidad conseguida
* El grado de detalle y especificidad
* La factibilidad de la propuesta
* Utilidad de los esquemas y figuras incluidas
* Claridad y fluidez en la presentación

------------------------

##Introduccion
Se busca diseñar un sistema empotrado que realice el control central de un sistema de autoabastecimiento energético. Dicho sistema contará con una instalación de placas solares, así como una batería de alta capacidad para almacenar la carga recogida por dichas placas. Además, se desea que el sistema sea capaz de detectar fallos en el sistema de autoabastecimiento y de realizar informes periodicos.

Para esta propuesta queriamos adoptar un enfoque open-hardware, que nos permita hacerlo llegar al máximo posible de personas, además de que cada uno pueda adaptarlo a las necesidades de cada casa. Se ha pensado en la implementacion con Raspberry Pi, por ser un producto barato y accesible al usuario, además de ser simple en cuanto a configuración. La raspberry nos permitirá además usarla como el propio servidor de la base de datos, con lo cual no dependeremos de servicios externos para almacenar y gestionar los datos del sistema de autoabastecimiento. 

La batería principal de la casa, contará con una potencia de 10kWh, y proporcionará al S.E información de su estado: nivel de carga, salud de la bateria, etc. Proporcionará energía a las luces de la casa, así como a algunos aparatos eléctricos más. Para hacernos una idea sobre la capacidad real de esta batería:

* televisor de pantalla plana consumiría 0,1 kWh por hora;
* una bombilla convencional, 0,1 kwh por hora;
* portátil, 0,05 kWh por hora;
* refrigerador, 4,8 kWh por día
* lavadora, 2,3 kWh por lavado;
* secadora, 3,3 kWh por uso.

[Mas info][Tesla-bat]

Los paneles fotovoltaicos que suministran la energia a la batería, proporcionan al S.E información como cantidad de energia que estan produciendo, estado del panel, etc.

Con esto, pretendemos que el S.E sea capaz de detectar fallos y comunicarlos para ayudar en la solucion del problema. El S.E también será el encargado de registrar el consumo de la vivienda, el uso de la bateria, etc; para realizar tablas y mostrar resumenes de información en la aplicación asociada que permitirán al usuario poder revisar con facilidad el uso del sistema de autoabastecimiento.

![Esquema de funcionamiento](https://github.com/AndresCidoncha/Sistemas-Empotrados/blob/master/Trabajo%20Final/EsquemaFinal.png?raw=true)

------------------------

##Requisitos
* Batería autónoma: El sistema debe contar con una batería autonoma que le permita seguir en activo aunque se produzca alguna caida en cuanto al suministro elétrico. 
Controlador de energia: Que gestione las placas solares de la casa, el consumo general y la bateria que habra instalada en la casa.

* Gestionar placas solares: Incluye llevar registro de la potencia obtenida a lo largo de los dias, orientarlas hacia donde haya mas sol, controlar fallos etc.

* Gestionar bateria: Nivel de carga (potencia disponible para usar), aviso de carga baja antes de tirar de la instalacion electrica externa, control de ciclos de carga, control de fallos y control de carga con las placas solares

* Consumo general: Simplemente registro de consumos, y (opcionalmente) gestion de luces automaticamente

* Sistema de prevision meteorologica: El S.E obtendrá de internet la [prevision del día siguiente][info-meteo] para, de acuerdo con ella, hacer planificaciones del almacenamiento y aprovechamiento de la carga.

------------------------

##Materiales

###Raspberry Pi 2: Model B

[Caracteristicas][Rasp2B]
**$$$:** 35 dolares
**CPU:** ARM11 ARMv7 ARM Cortex-A7 4 núcleos @ 900 MHz 
**Ram:** 1 GB LPDDR2 SDRAM 450 MHz 
**Eth:** 10/100 Mbps 
**Con:** 5v, 900mA, aunque depende de la carga de trabajo de los 4 cores 
**HDD:** microSD

------------------------

##Funcionamiento

###Información meteorológica
Para la obtención de la información meteorológica del día siguiente, el S.E ejecutará un [script de python][script-meteo] que nos proporcionará la información que deseamos. Con ello, el S.E podrá dar consejos acerca de como proceder con el consumo de los días siguientes (reservando más energía, por ejemplo).

[info-meteo]: http://www.eltiempo.tv/Santa-Cruz-de-Tenerife/Santa-Cruz-de-Tenerife.html
[script-meteo]: https://github.com/AndresCidoncha/Sistemas-Empotrados/blob/master/Trabajo%20Final/get-meteo.py
[Rasp2B]: http://www.xatakahome.com/trucos-y-bricolaje-smart/probamos-la-nueva-raspberry-pi-2-a-fondo
[Tesla-bat]: http://faircompanies.com/blogs/view/tesla-powerwall-una-bateria-domestica-entre-casa-y-el-coche/
