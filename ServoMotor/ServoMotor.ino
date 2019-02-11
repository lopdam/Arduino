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
