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

## Semaforo 
```c++
//lopdam

// En esta practica se va a realizar un Semaforo con Arduino

// Los unicos componentes a utilizar va a ser 3 diodos Rojo,Amarillo,Verde y una placa de Arduino
const int red=2;
const int yellow=4;
const int green=7;
const int tim=500;//tiempo que estan encindos las luces principales
void setup(){
  // Declaramos los modos de los pines
  // Ya que todos van a ser utilizados para encender un led
  // Los definimos como OUTPUT
pinMode(red,OUTPUT);
pinMode(yellow,OUTPUT);
pinMode(green,OUTPUT);


}

void loop(){

// Vamos a encender la luz roja por un tiempo y las demas apagadas
digitalWrite(red,HIGH);
digitalWrite(yellow,LOW);
digitalWrite(green,LOW);
delay(tim);
// Vamos a encender la luz amarilla por un tiempo mas corto y las demas apagadas
digitalWrite(red,LOW);
digitalWrite(yellow,HIGH);
digitalWrite(green,LOW);
delay(tim/5);
// Vamos a encender la luz verde por un tiempo y las demas apagadas
digitalWrite(red,LOW);
digitalWrite(yellow,LOW);
digitalWrite(green,HIGH);
delay(tim);


}
```
![](/Semaforo/semaforo.png)

## Secuencia de Leds
```c++

//lopdam

//Vamos hacer una secuencia de leds: tipo auto fantastico

//Declaramos desde que pin hasta que pin vamos a usar

const int inicio=2;
const int fin=13;

// Definimos el tiempo que va a demorar el cambio de cada led
const int time=100;

void setup() {
// Definimos el modo de los pines
  for(int i=inicio;i<=fin;i++){
    pinMode(i,OUTPUT);}

}


void loop() {
//Encendemos los leds secuencialmente
  for(int i=inicio;i<=fin;i++){
  digitalWrite(i,HIGH);
    delay(time);
     digitalWrite(i,LOW);
  }

  //Encendemos los leds secuencialmente pero del lado contrario
    for(int i=fin;i>=inicio;i--){
  digitalWrite(i,HIGH);
    delay(time);
     digitalWrite(i,LOW);
  }


  }

```
![LedsSecuencia](/SecuenciaLeds/SecuenciaLeds.png)

## Servo Motor
```c++
//lopdam
// Vamos a hacer funcionar un servo motor con un potenciometro

#include <Servo.h>

Servo s;//Intanciamos un objeto Servo

const int servo=3;//Declaramos el pin a usar para hacer funcionar el servo

const int pot=A0;//Decaramos el pin para el potenciometro

int grados=90;//Declaramos los grados de inclinacion de l servo los cuales por defecto van a ser 90
int r;// Declaramos la lectura del potenciometro

void setup(){
s.attach(servo);//Iniciamos el Servo
Serial.begin(9600);//Iniciamos la comunicacion Serial y Declaramos la velocidad
}

void loop(){
  
r=analogRead(pot);//Guardamos la lectura del potenciometro

grados=map(r,0,1023,0,180);//transformamos la lectura en un rango de 0-a-180 grados
s.write(grados);//Enviamos los grados que deseamos al Servo
Serial.print("Grados: ");
Serial.println(grados);


}

```
![Servo](/ServoMotor/ServoMotor.png)

## Motor Reductor
```c++
//lopdam
// Uso del motor Reductor
  /* Componentes:
  Puente H L293D
  Motor Reducctor
  Regulador de voltage a 5v
  Potenciometro
  Bateria 9v
  Arduino*/

// Declaramos los pines a usar

const int velocidad=A0;// Sirve para lectura del Potenciometro
const int direcc=A1;//Sirve para controlar el sentido giro del motor

const int motor1=2;// Controla un pin del motor
const int motor2=4;// Controla un pin del motor
const int motorVel=3;//Sirve para controlar la velocidad del motor

int vel;// Guarda la velocidad del los motores
int giro;//Guarda el sentido de giro de los motores

void setup(){
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(motorVel,OUTPUT);
}

void loop(){
  vel=map(analogRead(velocidad),0,1023,0,255);//lectura de la velocidad
  analogWrite(motorVel,vel);// Definimos la velocidad de los motores
  giro=analogRead(direcc);// lectura del giro

  if(giro<341){
    Adelante();
  }
  else if(giro>682){
    Atras();
  }
  else{
    Detener();
  }

}

// Declaramos las funciones para el sentido de giro delos motores

// Mueve el motor hacia atras
void Adelante(){
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);

}
// Mueve el motor hacia atras
void Atras(){
  digitalWrite(motor2,HIGH);
  digitalWrite(motor1,LOW);
}
//Detiene el motor
void Detener(){
  digitalWrite(motor2,LOW);
  digitalWrite(motor1,LOW);

}
```
![MotorReductor](/MotorReductor/MotorReductor.png)

## UltraSonido
```c++// lopdam
// Usar el sensor de Ultrasonido HC-SR04

// Declaramos los pines a usar del Arduino

const int trigger=10;//pin que envia la onda de sonido
const int echo=11;// pin que recibe la onda se sonido


float time;//variable utilizada para guardar el tiempo en que vija la onda
float distancia;// varible utilizada para guardar la distancia a le que se encuentra el objeto
const float velocidad=(1/29.2);// la velocida del sonido cm/Microseconds

void setup(){

pinMode(trigger,OUTPUT);//Declaramos el modo del pin trigger
pinMode(echo,INPUT);//Declaramos el modo del pin echo
Serial.begin(9600);// Declaramos el bautio de la comunicacion Serial
}

void loop(){

digitalWrite(trigger,LOW);//Apagamos 4 micros el trigger para evitar errores
delayMicroseconds(4);
digitalWrite(trigger,HIGH);//Encendemos el trigger por 10 micros
delayMicroseconds(10);


time=pulseIn(echo,HIGH);//Capturamos el tiempo de la onda

// Dividimos el tiempo por 2 ya que el sensor captura el tiempo de ida y vuelta de la onda

distancia=(time/2)*velocidad;//Calculamos la distancia del objeto

// Mostramos por consola los valores obtenidos
Serial.print("Distancia: ");
Serial.print(distancia);
Serial.println(" cm");


}

```
![UltraSonido](/Ultrasonido/ultrasonic.png)
