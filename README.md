# Arduino
Proyectos realizados utilizando la plataforma de Arduino.

Las carpetas muestran la configuracion inicial de los diferentes componentes

```c++
//lopdam

//Vamos a Realizar el Hola Mudno en la Plataforma de Arduino

// El pin 13 ya lleva por defecto integrado un led

const int hola=13;
const int tim=1000;

void setup(){
  // Declaramos el modo del pin 13
  pinMode(hola,OUTPUT);

}

void loop(){
//Encendemos el pin 13 por un momento
digitalWrite(hola,HIGH);
delay(tim);
//Apagamos el pin 13 por un momento
digitalWrite(hola,LOW);
delay(tim);

}

```
![Arduino](/BtnRebote/BtnRebote.png)
