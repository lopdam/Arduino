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
