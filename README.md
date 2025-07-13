# ESP32 - PLC

Este proyecto tiene como objetivo desarrollar un modulo PLC con fines pedagógicos empleando 
el SoC denominado ESP32 de Expressif. Para ello se utilizan las plataformas de desarrollo 
Arduino & OpenPLC.

Como prueba de concepto, se han desarrollado 3 rutinas en Arduino y OpenPLC para demostrar 
el funcionamiento del SoC. Dichas rutinas emplean un sistema con diferentes entradas 
y salidas digitales.

## Composición del Sistema

El sistema esta compuesto por los siguientes elementos:

+ Dos fuentes DC reguladas.

+ Dos fuentes AC.

+ Dos botones normalmente abiertos.

+ Un interruptor normalmente abierto.

+ Dos contactores normalmente abiertos.

+ Una pantalla LCD.

+ Conjunto de cinco LEDs.

Además, las rutinas programadas empleando Arduino emplean la librería: [LiquidCrystal_I2C de Frank de 
Brabander](https://docs.arduino.cc/libraries/liquidcrystal-i2c/)

## Miembros

+ Nicolas Rosero.

+ Andrés Cabal.

+ Steven Mambague.

+ Wilmer Cuaical.

+ Luis Benavides.

+ Mauricio Diaz. (ing.vago)
