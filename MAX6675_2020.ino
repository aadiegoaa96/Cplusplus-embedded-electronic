/**
   GeekFactory - "INNOVATING TOGETHER"
   Distribucion de materiales para el desarrollo e innovacion tecnologica
   www.geekfactory.mx

   SKETCH PARA MEDIR TEMPERATURA CON TERMOPAR Y MAX6675. MUESTRA EL RESULTADO
   DE LA MEDICION EN EL MONITOR SERIAL DE ARDUINO. ESTE EJEMPLO USA LA LIBRERIA
   PARA EL MAX6675 DE ADAFRUIT.
*/
#include "max6675.h"

// CONFIGURACION DE LOS PINES UTILIZADOS PARA LA COMUNICACIÓN CON EL MAX6675
#define CONFIG_TCGND_PIN      8
#define CONFIG_TCVCC_PIN      9
#define CONFIG_TCSCK_PIN      10
#define CONFIG_TCCS_PIN       11
#define CONFIG_TCDO_PIN       12

// OBJETO UTILIZADO PARA LA COMUNICACION CON EL MAX6675
MAX6675 thermocouple(CONFIG_TCSCK_PIN, CONFIG_TCCS_PIN, CONFIG_TCDO_PIN);

double temperatura;


void setup() {
  // PREPARAR LA INTERFAZ SERIAL
  Serial.begin(9600);

  // USAR PINES DE ARDUINO PARA ALIMENTAR EL MODULO MAX6675
  pinMode(CONFIG_TCVCC_PIN, OUTPUT); digitalWrite(CONFIG_TCVCC_PIN, HIGH);
  pinMode(CONFIG_TCGND_PIN, OUTPUT); digitalWrite(CONFIG_TCGND_PIN, LOW);

  // IMPRIMR MENSAJE INICIAL A LA TERMINAL
  Serial.println(F("----------------------------------------------------"));
  Serial.println(F("      TUTORIAL TERMOPAR CON ARDUINO Y MAX6675       "));
  Serial.println(F("            http://www.geekfactory.mx               "));
  Serial.println(F("----------------------------------------------------"));

  // ESPERAR A QUE SE ESTABILICE LA ENERGIA
  delay(500);
}

void loop() {
  // IMPRIMIR LA TEMPERATURA EN LA TERMINAL SERIAL
  Serial.print("C = ");
  temperatura = thermocouple.readCelsius();
  Serial.println(temperatura);
  
  //Serial.println(thermocouple.readCelsius());

  // ESPERAR UN SEGUNDO ENTRE LAS LECTURAS
  delay(1000);
}
 
