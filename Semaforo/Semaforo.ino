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
