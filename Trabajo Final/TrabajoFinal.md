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

###Requisitos
* **Batería autónoma:** El sistema debe contar con una batería autonoma que le permita seguir en activo aunque se produzca alguna caida en cuanto al suministro elétrico. 

* **Controlador de energia:** Que gestione las placas solares de la casa, el consumo general y la bateria que habra instalada en la casa.

    * **Gestionar placas solares:** Incluye llevar registro de la potencia obtenida a lo largo de los dias, orientarlas hacia donde haya mas sol, controlar fallos etc.

    * **Gestionar bateria:** Nivel de carga (potencia disponible para usar), aviso de carga baja antes de tirar de la instalacion electrica externa, control de ciclos de carga, control de fallos y control de carga con las placas solares

    * **Consumo general:** Simplemente registro de consumos, y (opcionalmente) gestion de luces automaticamente

* **Sistema de prevision meteorologica:** El S.E obtendrá de internet la [prevision del día siguiente][info-meteo] para, de acuerdo con ella, hacer planificaciones del almacenamiento y aprovechamiento de la carga.

------------------------

##Desarrollo de la idea
Para esta propuesta queriamos adoptar un enfoque open-hardware, que nos permita hacerlo llegar al máximo posible de personas, además de que cada uno pueda adaptarlo a las necesidades de cada casa. Se ha pensado en la implementacion con Raspberry Pi, por ser un producto barato y accesible al usuario, además de ser simple en cuanto a configuración. La raspberry nos permitirá además usarla como el propio servidor de la base de datos, con lo cual no dependeremos de servicios externos para almacenar y gestionar los datos del sistema de autoabastecimiento. 

La batería principal de la casa, una Tesla Powerwall, contará con una potencia de 7kWh, y proporcionará al S.E información de su estado: nivel de carga, salud de la bateria, etc. Proporcionará energía a las luces de la casa, así como a algunos aparatos eléctricos más. Para hacernos una idea sobre la capacidad real de esta batería:

* televisor de pantalla plana consumiría 0,1 kWh por hora;
* una bombilla convencional, 0,1 kwh por hora;
* portátil, 0,05 kWh por hora;
* refrigerador, 4,8 kWh por día
* lavadora, 2,3 kWh por lavado;
* secadora, 3,3 kWh por uso.

[Más info (FairCompanies)][Tesla-bat] 
[Más info (wikipedia)][Tesla-bat2] 
[Página oficial][Tesla-off]

Los [paneles fotovoltaicos][panelsinfo] que suministran la energia a la batería, pueden ser fijos o con orientación móvil, por lo que se debe implementar un sistema que permita controlar el movimiento. Para ello, basandonos en los valores recogidos por un conjunto de sensores LDR además de los propios valores de energia recogida aportado por los paneles, podemos determinar la orientación ideal para optimizar la obtención de energía.  Adicionalmente se puede utilizar la información de la predicción meteorológica para saber si el cambio de orientación llegaría a resultar rentable. Además, al analizar los valores de energía recogida, si algún panel supera un umbral de diferencia respecto a los paneles más cercanos, podemos detectar algún tipo de fallo en ese panel y comunicarlo al propietario del sistema.

Con esto, pretendemos que el S.E sea capaz de detectar fallos y comunicarlos para ayudar en la solucion del problema. El S.E también será el encargado de registrar el consumo de la vivienda, el uso de la bateria, etc; para realizar tablas y mostrar resumenes de información en la aplicación asociada que permitirán al usuario poder revisar con facilidad el uso del sistema de autoabastecimiento.

![Esquema de funcionamiento][EsquemaFuncionamiento]

-------------------------------------------------

##Materiales

###Raspberry Pi 2: Model B

**$$$:** 35 dolares
**CPU:** ARM11 ARMv7 ARM Cortex-A7 4 núcleos @ 900 MHz 
**Ram:** 1 GB LPDDR2 SDRAM 450 MHz 
**Eth:** 10/100 Mbps 
**Con:** 5v, 900mA, aunque depende de la carga de trabajo de los 4 cores 
**HDD:** [microSD 16Gb][microSD] 

[Más caracteristicas][Rasp2B]

Se ha escogido una Raspberry al ser un producto que nos proporciona una gran flexibilidad, además de ser barato y accesible para la gran mayoría del público al que se dirige el producto. Cuenta con todas las opciones deseables (potencia, consumo reducido, conexión de red) y es fácilmente operable y mejorable modularmente.

###Batería de la Raspberry

**Voltaje:** 5 V
**Intensidad:** 2.4/3.4 A
**Capacidad:** 16000 mAh
**Protecciones:** Fusible, Sobrecarga, Deflagración.

La [batería escogida][bateria] es un ejemplo, puede usarse cualquiera siempre y cuando cumpla con ciertas condiciones:

* El voltaje debe ser de **5 V**.
* Debe contar con al menos una salida de intensidad **2 A o más**.
* Tiene que soportar ser cargada a la vez que da corriente.
* La capacidad debería ser de al menos **6000 mAh**.
* *Deseable* que cuente con protecciones para picos de tensión.

La batería se escoge sin tener demasiado en cuenta su peso puesto que no será un sistema portátil, pero siempre de un límite lógico. Al usarse como una especie de UPS, se busca que tenga una capacidad que permita afrontar periodos medianamente largos de ausencia de alimentación principal, además de que como un UPS, es ideal que tenga protecciones contra irregularidades en la alimentación principal, que permita proteger a la electrónica de la Raspberry. [Aquí][InfoBatt] encontramos pruebas con ella de satisfactorio resultado.

###Tesla Powerwall

**Voltaje:** 350-450 V
**Potencia (continua):** 5 kW 
**Potencia (picos):** 7 kW
**Intensidad:** 5,8/8,6 A
**Peso:** 100 kg 
**Dimensiones:** 1300 mm x 860 mm x 180 mm.

**Otras:**

* Disponen de un control de temperatura y refrigeración por líquido.
* El Powerwall no incluye el inversor DC-AC.
* Diseño modular. Pueden conectarse hasta 9 paquetes. 
* Tesla ofrece una garantía de 10 años.
* Las patentes serán liberadas para ser open source.

------------------------

##Funcionamiento

###Gestión de los paneles fotovoltaicos

###Información meteorológica
Para la obtención de la información meteorológica del día siguiente, el S.E ejecutará un [script de python][script-meteo] que nos proporcionará la información que deseamos acerca de la cantidad de sol durante las horas/dia siguiente. Con ello, el S.E podrá dar consejos acerca de como proceder con el consumo de los días siguientes (reservando más energía, por ejemplo).

Para más simplicidad, el programa encargado de estas funciones está escrito también en Python, que tiene módulos dedicados al manejor de los pines de la Raspberry, como nos muestran en la [documentación][pythonrasp].

###Gestión de la batería

###Gestión de la instalación eléctrica de la casa


-------------------------------------------------------------------------------------------------------------------------------------------------

[OPENSOFTHARDWARE]:http://www.open-electronics.org/wp-content/uploads/2013/02/OSS-OSHW-logo.jpg
[OPENSOFTWARE]: https://upload.wikimedia.org/wikipedia/commons/thumb/4/42/Opensource.svg/2000px-Opensource.svg.png
[OPENHARDWARE]: https://upload.wikimedia.org/wikipedia/commons/thumb/f/fd/Open-source-hardware-logo.svg/2000px-Open-source-hardware-logo.svg.png
[RASPBERRY]: https://upload.wikimedia.org/wikipedia/en/thumb/c/cb/Raspberry_Pi_Logo.svg/810px-Raspberry_Pi_Logo.svg.png
[PYTHON]: https://upload.wikimedia.org/wikipedia/commons/thumb/c/c3/Python-logo-notext.svg/1024px-Python-logo-notext.svg.png

[Tesla-bat]: http://faircompanies.com/blogs/view/tesla-powerwall-una-bateria-domestica-entre-casa-y-el-coche/
[Tesla-bat2]: https://es.wikipedia.org/wiki/Tesla_Powerwall
[Tesla-off]: https://www.teslamotors.com/powerwall
[EsquemaFuncionamiento]: https://github.com/AndresCidoncha/Sistemas-Empotrados/blob/master/Trabajo%20Final/EsquemaFinal.png?raw=true
[info-meteo]: http://www.eltiempo.tv/Santa-Cruz-de-Tenerife/Santa-Cruz-de-Tenerife.html
[panelsinfo]: http://www.sfe-solar.com/paneles-solares-fotovoltaicos/solon/solon-black-220-16-240-245-250w/
[Rasp2B]: http://www.xatakahome.com/trucos-y-bricolaje-smart/probamos-la-nueva-raspberry-pi-2-a-fondo
[microSD]: http://www.amazon.es/Samsung-Evo-MB-SP16D-EU-Tarjeta/dp/B00J4G88ZU/ref=sr_1_6?s=electronics-accessories&ie=UTF8&qid=1452540757&sr=1-6&keywords=sd+clase+10
[bateria]: http://www.tecknet.co.uk/iep1500-black-new.html
[InfoBatt]: http://blog.myombox.com/connected-objects/test-and-comparison-of-6-external-batteries-for-raspberry-pi-smartphones-and-tablets
[script-meteo]: https://github.com/AndresCidoncha/Sistemas-Empotrados/blob/master/Trabajo%20Final/get-meteo.py
[pythonrasp]: https://www.raspberrypi.org/documentation/usage/python/more.md