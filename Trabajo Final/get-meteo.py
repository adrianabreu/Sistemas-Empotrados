#!/usr/bin/env python
# -*- coding: utf-8 -*-
from bs4 import BeautifulSoup
import requests

#http://www.eltiempo.tv/Santa-Cruz-de-Tenerife/Santa-Cruz-de-Tenerife.html
url = "http://www.eltiempo.tv/"
ciudad="Santa Cruz de Tenerife"

def get_url(ciudad):
	aux=ciudad.replace(' ','-')
	aux=url + aux + '/' + aux + ".html"
	return aux

def get(html, search_att, exp1, exp2):
	att=[]
	source = html.find_all("td", search_att)

	for linea in source:
		linea=str(linea)
		linea=linea[linea.find(exp1)+len(exp1):]
		linea=linea[:linea.find(exp2)]
		att.append(linea)
    
	return att

# Realizamos la petición a la web
url=get_url(ciudad)
req = requests.get(url)

# Comprobamos que la petición nos devuelve un Status Code = 200
statusCode = req.status_code
if statusCode == 200:
    html = BeautifulSoup(req.text, "lxml")
    horas = get(html,"detallada_hora",'>','<')
    temps = get(html,"detallada_icono",'title=\"','\">')

    for i in range(len(horas)):
    	print("Hora: %s Prevision: %s" % (horas[i],temps[i]))

