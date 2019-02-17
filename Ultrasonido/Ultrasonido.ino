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

// Mostramos por consola los valores
Serial.print("Distancia: ");
Serial.print(distancia);
Serial.println(" cm");


}
