const int trigger=10;
const int echo=11;

float time;
 int distancia;

void setup(){

pinMode(trigger,OUTPUT);
pinMode(echo,INPUT);

}

void loop(){

digitalWrite(trigger,LOW);
delayMicroseconds(10);

time=pulseIn(echo,4);

distancia=(time/2)*(1/29.2);

Serial.println(distancia);


}