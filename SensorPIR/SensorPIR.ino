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
