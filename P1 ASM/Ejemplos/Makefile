#Makefile para compilar fichero del 68HC12 al formato .s19

AS=/usr/bin/m68hc11-as
LD=/usr/bin/m68hc11-ld
OBJCOPY=/usr/bin/m68hc11-objcopy

#Tamaños por defecto para los datos y la pila
TAM_DATA_DEF=40
TAM_PILA_DEF=10

fuentes:=$(wildcard *.s)

includes:=$(wildcard *.inc)

s19s:=$(fuentes:.s=.s19)


.PHONY : all

all : $(fuentes:.s=.elf) $(s19s)

%.o: %.s $(includes) Makefile
	$(AS) -L --gstabs -m68hc12 -o $@ $<

%.elf: %.o %.s memory_template.x Makefile
	@ TAM_DATA=$(shell egrep '^TAMDATA=[0-9]+' $(basename $<).s | head -1| sed -e's/^TAMDATA=\([0-9][0-9]*\).*$$/\1/' ); \
	TAM_PILA=$(shell egrep '^TAMPILA=[0-9]+' $(basename $<).s | head -1| sed -e's/^TAMPILA=\([0-9][0-9]*\).*$$/\1/'); \
	if [ "z$$TAM_DATA" = "z" ]; then TAM_DATA=$(TAM_DATA_DEF); fi; \
	if [ "z$$TAM_PILA" = "z" ]; then TAM_PILA=$(TAM_PILA_DEF); fi; \
        echo "Usando TAM_DATA=$$TAM_DATA y TAM_PILA=$$TAM_PILA" ; \
	sed -e"s/\$$TAMDATA/$$TAM_DATA/g" -e"s/\$$TAMPILA/$$TAM_PILA/g" memory_template.x > memory.x; 
	$(LD) -g -m m68hc12elfb -o $@ $<

%.s19: %.elf
	$(OBJCOPY)  --srec-len 20 --output-target=srec $< $@

.PHONY : clean

clean :
	rm -f *.elf *.s19 memory.x
	
zip : Ejemplos.zip

Ejemplos.zip : $(fuentes) $(includes) Makefile memory_template.x
	rm -f $@
	zip  $@ $^



