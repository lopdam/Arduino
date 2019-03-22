# Arduino
Proyectos realizados utilizando la plataforma de Arduino.

Las carpetas muestran la configuracion inicial de los diferentes componentes

[Instagram](http://instagram.com/lopdam.ec)

## Arduino, Qué es ?
Arduino es una plataforma de creación de hardware y software libre, la cual nos permite materializar nuestras ideas ya que es flexible y fácil de usar, porque posee una capa de abstracción lo que la hace ideal para creadores, desarrolladores y entusiastas al mudo de la tecnología.

## Hola Mundo
El Hola Mundo en Arduino es básicamente encender y apagar el led que ya viene incoporado en el pin #13.
Para eso vamos a definir dos variables, una para declara el pin #13 y otra para definir el tiempo que va a permanecer encendido y apagado el led.
También se procederá a definir en el método setup() el modo del pin en este caso OUTPUT.
Y al final se va a  implementar las acciones en el método loop().

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
## Button Rebote
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


## Led RGB

```c++
//lopdam

//Encender un led RGB combinando los colores
//El color va a ser generado aleatoriamente

//Declaramos lo pines a usar

const int red=3;
const int green=5;
const int blue=6;

const int tiempo=500;//Una variable tiempo para el cambio de color

void setup()
{
  // Definimos el modo de los leds
  pinMode(red, OUTPUT);
   pinMode(green, OUTPUT);
   pinMode(blue, OUTPUT);
}

void loop(){

// Generamos los colores
  int i=random(0,256);
  int k=random(0,256);
  int j=random(0,256);

// Encendemos los leds

  analogWrite(red,i);
  analogWrite(green,j);
  analogWrite(blue,k);
  delay(tiempo);

}
```

![LedRGB](/LedRGB/LedRGB.png)

