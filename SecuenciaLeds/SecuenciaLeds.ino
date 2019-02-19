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
