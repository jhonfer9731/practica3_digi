# -*- coding: utf-8 -*-
"""
Created on Sun Jan 17 18:46:17 2021

@author: user
"""

import cv2
import pytesseract


pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'


def extraerTexto(imagenDir):
    
    scale_percent = 200
    imgOriginal  = cv2.imread(imagenDir)
    gray_img = cv2.cvtColor(imgOriginal,cv2.COLOR_BGR2GRAY)
    #calculate the 50 percent of original dimensions
    width = int(gray_img.shape[1] * scale_percent / 100)
    height = int(gray_img.shape[0] * scale_percent / 100)
    gray_img = cv2.resize(gray_img,(width, height))
    _,img = cv2.threshold(gray_img,150,255,cv2.THRESH_BINARY)
    
    text = pytesseract.image_to_string(img)
    text = text.split('\n')
    text2 = [numHex.split('$') for numHex in text]
    text4 = [ bytes.fromhex(numHex.pop(-1)).decode("ASCII") for numHex in text2[:-1]]
    text4 = "".join(text4)
    return text4




texto = ''
texto = texto+extraerTexto('imgPrueba.png')
texto = texto+extraerTexto('imgPrueba2.png')
texto = texto+extraerTexto('imgPrueba3.png')
# texto = texto+extraerTexto('imgPrueba4.png')
# texto = texto+extraerTexto('imgPrueba5.png')


print(texto)