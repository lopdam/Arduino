# Arduino
Proyectos realizados utilizando la plataforma de Arduino.

Las carpetas muestran la configuracion inicial de los diferentes componentes

[Instagram](http://instagram.com/lopdam.ec)

[Telegram](https://t.me/lopdam)

## Arduino, Qué es ?
Arduino es una plataforma de creación de hardware y software libre, la cual nos permite materializar nuestras ideas ya que es flexible y fácil de usar, porque posee una capa de abstracción lo que la hace ideal para makers, desarrolladores y entusiastas al mudo de la tecnología, los cuales no deben tener conocimietos profundos sobre electronica para comenzar a realizar sus proyectos.

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
Para realizar una correcta lectura de un Button(pulsador) hay que tener en cuenta que existe el rebote del Button, esto consciste en que al pulsar, las laminas internas vibran varias veces antes de llegar a la posicion de estado cerrado, lo cual puede llevar errores en lectura ya que el Arduino trabaja a altas velocidades y puede tomar la lectura como un alto o como un bajo.

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

Con el led RGB podemos crear una cantidad considerable de colores, ya que podemos combinar los colore primarios (Rojo)(Verde)(Azul) para optener el color deseado, la forma en la cual lo hacemos es utilizando las salidas pwm en las cuales podemos modular el ancho de pulso, que vendria a ser una salida analogica de 8 bits y que tomaria 256 valores posible 0-255, esto permite regular la intensidad de cada color.

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

La practica del semaforo es muy sencilla ya que solo se usan salidas digitales para poder realizar este proyecto,tambien se debe usar un retardo (delay()) para poder controlar el tiempo en que toma en cambiar de un color a otro. 

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

Para poder realizar una secuencia de leds correcta se va a utilizar una estructura de contro for() con la cual podremos definir el modo de los pines sin tener que hacerlo uno por uno, lo mismo hacemos para el encendido y apagado.

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
Para esta practica se va a usar un servo y un potencimetro.

Para usar el Servo se necesita incluir la libreria Servo.h ya que esta contiene los metodos necesarios para poder controlar el servo, en esta caso solo se va a usar dos metodos attach() y write(), attach()  este metodo define el pin que se va a usar para el control, write() con este metodo se puede controlar la poscision del servo esta funcion recibe valores de 0-180 que vendrian a ser los grados de inclinacion de la pala del servo.

El potenciometro se va a usar para poder controlar el servo, de tal modo que vendria a ser un entrada analogica que toma 1024 valores 0-1023.

Tambien se tiene que tomar en cuenta que hay que hacer las transformaciones en equivalencias respectivas 0-1023 a 0-180, esto lo logramos usando el metodo map() que recibe 5 valores map(value, fromLow, fromHigh, toLow, toHigh).

value: el número a mapear

fromLow: el límite inferior del rango actual del valor

fromHigh: el límite superior del rango actual del valor

toLow: el límite inferior del rango objetivo del valor

toHigh: el límite superior del rango objetivo del valor

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
```c++
// lopdam
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

## Sensor PIR

```c++
//lopdam

// Vamos a utilizar el sensor PIR
/* Componetes:
Arduino
Sernsor PIR
Led
*/

/* El sensor PIR es un sensor electrónico que mide
la luz infrarroja radiada de los objetos situados en su campo de visión.*/

// Tipo de sensor DIGITAL

// Declaramos los pines a utilizar

const int pir=2;
const int led=3;
// Varible a usar para guardar la lectura del sensor
int mov;

void setup(){
pinMode(pir,INPUT);
pinMode(led,OUTPUT);
}


void loop(){
mov=digitalRead(pir);
if(mov==HIGH){
  digitalWrite(led,HIGH);
}
else{
  digitalWrite(led,LOW);
}

}
```
![SensorPIR](/SensorPIR/SendorPIR.png)

## Modulo Bluetooth
```c++
//lopdam
// Configuracion de modulo Bluetooth

#include <SoftwareSerial.h>
// Incluimos la librería  SoftwareSerial
  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
 
void setup()
{
  BT.begin(9600);       // Inicializamos el puerto serie BT que hemos creado
  Serial.begin(9600);   // Inicializamos  el puerto serie  
}

 
void loop()
{

    if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     BT.write(Serial.read());
  }

  
  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    Serial.write(BT.read());
  }
 
  
}

//La configuracion del modulo Bluetooth se hace mediante comandos AT
// Test de comunicación

// Comando -> Salida_Consola

//Configuracion

//Verificar que la conexion esta correcta
// AT -> OK

//Cambiar nombre del modulo
// AT+NAME<Name> -> OKsetname

//Cambiar clave de conexion del modulo
//AT+PIN<Clave> -> OKsetPIN

//Cambiar la velocidad de los baudios
//AT+BAUD<Numero> -> OK<Numero>
/*1 ---------1200

  2 ---------2400

  3 ---------4800

  4 ---------9600

  5 ---------19200

  6 ---------38400

  7 ---------57600

  8 ---------115200*/

//Consultar Version
//AT+VERSION -> OK<Version>

```
![BLuetooth](/ModuloBluetooth/Bluetooth.png)

## Car Bluetooth
```c++
#include <SoftwareSerial.h>

#include <Servo.h>


//Declaracion de las variables

//Motor 1 Derecho
const int M11=8;
const int M12=7;

//Motor 2 Izquierdo
const int M22=4;
const int M21=2;

//Control de velocidad de los motores
const int M1PWM=3;
const int M2PWM=5;

//Buzzer
const int Buzzer=6;

//Control del servo
const int Serv=9;

//Comunicacion con el cell
const int RX=10;//Receptor
const int TX=11;//Transmisor

//Declarion de pines para el ultrasonido
const int Echo=12;//Receptor
const int Triger=13;//Transmisor

//Declarion de variables temporales
int vel=175;//velocidad por defecto

int pos=20;//posicion minima que el servo puede llegar y 160 para la maxima apertura.
int dis; // distancia del objeto
char r;// Lectura de datos para saber que accion ejecutar

long tiempoEntrada;  // Almacena el tiempo de respuesta del sensor de entrada
float distanciaEntrada;  // Almacena la distancia en cm a la que se encuentra el objeto
const int distmin=25;//es la distancia minima a la que puede estar ub objeto para esquivarlo

//funcionamiento del sensorymotores

//Creacion de Objetos
Servo S;//Servo
SoftwareSerial BT(RX,TX);//comunicacion con cell




void setup() {

S.attach(Serv);

BT.begin(9600);

//Declarion de modo de pines motor 1
pinMode (M11, OUTPUT);
  pinMode (M12, OUTPUT);

//Declarion de modo de pines motor 2
  pinMode (M21, OUTPUT);
  pinMode (M22, OUTPUT);

//Declarion de modo de pines motor control de velocidad
  pinMode (M1PWM, OUTPUT);
  pinMode (M2PWM, OUTPUT);

  //Declarion de modo de pin para el Buzzer
 pinMode(Buzzer,OUTPUT);

  pinMode(Triger,OUTPUT); // El emisor emite por lo que es configurado como salida
  pinMode(Echo,INPUT);   // El receptor recibe por lo que es configurado como entrada

//Declaramos la velocidad inicializal
  analogWrite(M1PWM,vel);
  analogWrite(M2PWM,vel);

// Accion que realiza el auto al inciarce
Buzz();//pitido de encendido
ServoInit();//movimiento del servo para comprobar que funcion
Buzz();//pitido de inicio del ciclo loop

}


void loop() {

       //FunObs(); //Funciomiento por reconocimento de obastaculos
       FunBT();//Funcionamiento por control BT

    }



void robotAvance()
{
  // Motor Derecho
  // Al mantener un pin HIGH y el otro LOW el motor gira en un sentido

  digitalWrite (M11, HIGH);
  digitalWrite (M12, LOW);
  // Motor Izquierdo
  // Al mantener un pin HIGH y el otro LOW el motor gira en un sentido
  digitalWrite (M21, HIGH);
  digitalWrite (M22, LOW);
}
/*
  Función robotRetroceso: esta función hará que ambos motores se activen a máxima potencia
  en sentido contrario al anterior por lo que el robot avanzará hacia atrás
*/
void robotRetroceso()
{

  // Motor Derecho
  // Al mantener un pin LOW y el otro HIGH el motor gira en sentido contrario al anterior
  digitalWrite (M11, LOW);
  digitalWrite (M12, HIGH);
  // Motor Izquierdo
  // Al mantener un pin LOW y el otro HIGH el motor gira en sentido contrario al anterior
  digitalWrite (M21, LOW);
  digitalWrite (M22, HIGH);
}
/*
  Función robotDerecha: esta función acccionará el motor izquierdo y parará el derecho
  por lo que el coche girará hacia la derecha (sentido horario)
*/
void robotIzquierda()
{
  //  Motor Derecho
  // Se activa el motor Derecho
  digitalWrite (M11, HIGH);
  digitalWrite (M12, LOW);

  // Motor Izquierdo
  // Se para el motor Izquierdo

  digitalWrite (M21, LOW);
  digitalWrite (M22, LOW);
}
/*
  Función robotIzquierda: esta función acccionará el motor derecho y parará el izquierdo
  por lo que el coche girará hacia la izquierda (sentido antihorario)
*/
void robotDerecha ()
{
   //  Motor Derecho
  // Se para el motor Derecho

  digitalWrite (M11, LOW);
  digitalWrite (M12, LOW);
  // Motor Izquierdo
  // Se activa el motor Izquierdo
  digitalWrite (M21, HIGH);
  digitalWrite (M22, LOW);
}
/*
  Función robotParar: esta función parará ambos motores
  por lo que el robot se parará.
*/
void robotParar()
{
  // Motor Derecho
  // Se para el motor Derecho
  digitalWrite (M11, LOW);
  digitalWrite (M12, LOW);

  // Motor Izquierdo
  // Se para el motor Izquierdo
  digitalWrite (M21, LOW);
  digitalWrite (M22, LOW);
}

////////////////////////////////////////////////////////////////////////////
//Funcionamiento del auto por medio del control Bt

 void FunBT(){
     if(BT.available())
  {


r=BT.read();

  if(r=='W'){
    robotAvance();
    }
   else if(r=='S'){
    robotRetroceso();}

   else if(r=='A'){
    robotIzquierda();}

   else if(r=='D'){
    robotDerecha();}

  else if(r=='X'){
  Buzz();
  //Motor Derecho
  digitalWrite (M11, LOW);
  digitalWrite (M12, HIGH);
  // Motor Izquierdo
  // Se activa el motor Izquierdo
  digitalWrite (M21, HIGH);
  digitalWrite (M22, LOW);
  delay(1500);
  robotParar();
 Buzz();

  }



else if(r=='F'){
if(vel<255){
  vel+=10;
analogWrite(M1PWM,vel);
analogWrite(M2PWM,vel);
}
}
else if(r=='f'){
  if(vel>75){
    vel-=10;
analogWrite(M1PWM,vel);
analogWrite(M2PWM,vel);  }
  }
  else {
    robotParar();
    }


}}
/////////////////////////////////////////////////////////////////////////////
// metodo para el buzzer y el servo
void Buzz(){
     tone(Buzzer,2200);
 delay(100);
noTone(Buzzer);
delay(50);
tone(Buzzer,2200);
delay(100);
noTone(Buzzer);
  }

void ServoInit(){
    S.write(20);//mini para que no colisiones y 160 maximo

  for(int i=20;i <=160;i++){
    S.write(i);
    delay(10);
    }
  for(int i=140;i >=40;i--){
    S.write(i);
    delay(10);
    }

    for(int i=60;i <=120;i++){
    S.write(i);
    delay(10);
    }
     for(int i=100;i >=80;i--){
    S.write(i);
    delay(5);
    }
    for(int i=85;i <=95;i++){
    S.write(i);
    delay(5);
    }

    S.write(90);
    }

///////////////////////////////////////////////////////////////////////////////////////
//Funcionamiento del auto por medio de reconociminetos de obstaculos por el ultrasonido
void FunObs(){


  while(pos<=160){

    pos++;
    S.write(pos);
    dis=sensorUltrasonidos();

    if(dis<distmin && pos>=20 && pos<=80 ){
     robotIzquierda();
     delay(100);
      }
    else if(dis<distmin && pos>=80 && pos<=100){
      robotRetroceso();
      delay(100);

      }
    else if(dis<distmin && pos>=100 && pos<=160){

       robotDerecha();
       delay(100);
      }
    else{
      robotAvance();
      }

      delay(1);
    }
  while(pos>=20){
    pos--;
    S.write(pos);

    dis=sensorUltrasonidos();
    if(dis<distmin && pos>=20 && pos<=80 ){
     robotIzquierda();
     delay(100);
      }
    else if(dis<distmin && pos>=80 && pos<=100){
      robotRetroceso();
      delay(100);
      }
    else if(dis<distmin && pos>=100 && pos<=160){

       robotDerecha();
       delay(100);
      }
    else{
      robotAvance();
      }

      delay(1);
    }
  }

  //Funcionamiento del Ultrasonido
  int sensorUltrasonidos()
  {
      // Se inicializa el sensor de infrasonidos
      digitalWrite(Triger,LOW);  // Para estabilizar
      delayMicroseconds(10);

      // Comenzamos las mediciones
      // Se envía una señal activando la salida trigger durante 10 microsegundos
      digitalWrite(Triger, HIGH);  // envío del pulso ultrasónico
      delayMicroseconds(10);
      tiempoEntrada=pulseIn(Echo, HIGH);
      return distanciaEntrada= int(0.017*tiempoEntrada); // Fórmula para calcular la distancia en cm
  }
```
![CarBluetooth](/CarBluetooth/CarDesing.png)
