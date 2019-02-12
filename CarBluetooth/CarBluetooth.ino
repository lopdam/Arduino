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
