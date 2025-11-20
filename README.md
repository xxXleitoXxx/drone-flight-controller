# Implementacion de control PID en cuadracoptero
[![Build Status](https://travis-ci.org/lobodol/drone-flight-controller.svg?branch=master)](https://travis-ci.org/lobodol/drone-flight-controller)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Este es un Fork de un proyecto antiguo de automatizacion de un Drone, la idea es estudiar,ver y reutilizar algunas funciones de control para el aprendizaje e implementacion de un drone físico, algunas funciones deben ser refactorizadas y adaptadas a las especificaciones técnicas de cada drone

# Pasos para hacer drone
## Paso 1:Probar control RF
Tenemos que probar el control de radiofrecuencia, con el sketch servo_controlRF.ino ubicado en el proyecto
lo que hace este sketch es utilizar las interrupciones de arduino para tomar los pulsos pwm del control,
como es pwm y varia los pulsos el ancho de pulso entre encendido y apagado, tomamos el tiempo desde que se encendio hasta que se apagó para calcular el tiempo
de duracion y así el ancho del mismo


