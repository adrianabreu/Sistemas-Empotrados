#!/usr/bin/env python
# -*- coding: utf-8 -*-
from bs4 import BeautifulSoup
import requests

def get_url(city_name):
    #EJEMPLO: http://www.eltiempo.tv/Santa-Cruz-de-Tenerife/Santa-Cruz-de-Tenerife.html
    url = "http://www.eltiempo.tv/"
	aux=city_name.replace(' ','-')
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

def get_meteo(city_name):
	# Realizamos la petición a la web
    url = get_url(city_name)
    req = requests.get(url)
    meteo = dict()

	# Comprobamos que la petición nos devuelve un Status Code = 200
    statusCode = req.status_code
    if statusCode == 200:
        html = BeautifulSoup(req.text, "lxml")
        hours = get(html,"detallada_hora",'>','<')
        temps = get(html,"detallada_icono",'title=\"','\">')

        for i in range(len(horas)):
            meteo[horas[i]]=temps[i]

    return meteo

if __name__ == '__main__':
    print get_meteo("Santa Cruz de Tenerife")