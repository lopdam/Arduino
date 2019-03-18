# Arduino
Proyectos realizados utilizando la plataforma de Arduino.

Las carpetas muestran la configuracion inicial de los diferentes componentes

[Instagram](instagram.com/lopdam.ec)

# Hola Mundo
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
# Button Rebote
```c++
//lopdam
// Practica de encendido con un Btn considerando el Rebote

const int Btn=2;
const int led=13;

int lectura;//lectura del Btn
int antes=0;//lectura anterior

//Estados de encendido del led
int estado=0;

void setup(){
pinMode(Btn,INPUT);
pinMode(led,OUTPUT);
}

void loop(){
  
delay(50);
lectura=digitalRead(Btn);

//Vamos necesitar que la lectura anterior sea diferente a la lectura actual 
//Para que si presionamos el Btn una vez y si lo mantenemos presionado, lo tome como una sola vez

if(lectura==1 && antes==0){
  antes=1;

//Cambiamos el estado del led si presionamos, eso va a depender del estado anterior del led
if(estado==1){
  estado=0;
}
else{
  estado=1;
}

}
else if(lectura==0 && antes==1){
  antes=0;
}


if(estado==1){
  digitalWrite(led,HIGH);
}
else{
  digitalWrite(led,LOW);
}


}

```
![Arduino](/BtnRebote/BtnRebote.png)

