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
