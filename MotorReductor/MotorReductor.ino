//lopdam
// Uso del motor Reductor
  /* Comontes:
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
