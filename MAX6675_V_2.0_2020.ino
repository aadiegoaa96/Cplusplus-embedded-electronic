/*  Proyecto: "BANCO DE PRUEBAS HIDROSTÁTICAS".
 *  Presenta: DIEGO NORBERTO BERMÚDEZ CASTILLO.
 *  Escuela:  INSTITUTO TECNOLÓGICO DE VERACRUZ.
 *  Carrera:  ING. MECATRÓNICA.
 *  E-mail:   dbcpachuca@hotmail.com .  
 */

#include "max6675.h"            // Incluimos libreria para controlar el módulo del termopar MAX6675 tipo K, utiliza el protocolo de comunicación SPI.
#define ktcSO 8                 // Declaramos el pin digital 8 y le asignamos el nombre de ktcSO. Este pin controlará el módulo MAX6675.
#define ktcCS 9                 // Declaramos el pin digital 9 y le asignamos el nombre de ktcCS. Este pin controlará el módulo MAX6675.
#define ktcCLK 10               // Declaramos el pin digital 10 y le asignamos el nombre de ktcCLK. Este pin controlará el reloj del módulo MAX6675.
static double temp_modulo;                     // Variable que se utiliza para guardar los valor de temperatura provenientes del módulo Max6675.
static String valor = "  ";                    // Declaramos un tipo de dato string llamado valor y le asignamos una cadena vacía.
int estado = 0;                                // Esta variable se utiliza para controlar el posible estado de trabajo al que puede estar el microcontrolador sometido, incluye 5 estados posibles.
int Estado_de_la_valvula = 0;                  // Esta variable se utiliza para generar un estado de falla o mal funcionamiento en la válvula.
static int var1;
static int var2;                               // SI LA INICIAS CON CERO TENDRÁS PROBLEMAS, NO SE ACTUALIZARÁ EL VALOR... 
static int bandera;                            // Utilizamos esta variable booleana para controlar las veces que se entra a un bucle.
static int bandera2;                           // Utilizamos esta variable booleana para controlar las veces que se entra a un bucle.
int dato;
static int measureN;
static int DatoTratado;                        // Variable para corregir los valores erróneos del módulo Convertidor de corriente.
static float measureT;
static int formula;


MAX6675 ktc(ktcCLK, ktcCS, ktcSO);                    // Parámetros de la librería MAX6675.
     



void setup() {                                                  // Declaramos el método setup.
  Serial.begin(9600);                                           // Iniciamos la comunicación serial a 9600 baudios.
                                                // Se asigna a la variable bandera un valor booleano true, esta varible nos ayudará a controlar el encendido dela bomba hidráulica de CA.
}



void loop() {                                                   // Iniciamos el ciclo.
  
         char temp = Serial.read();                          // Guardamos lo que capture el método read en la variable llamada: "temp".
           
         temp_modulo = ktc.readCelsius();                               // Tomaremos una lectura con el módulo MAX6675 y este dato será guardado en la variable: "valordelSensor1".

         Serial.println(temp_modulo);
         delay(500);       
}        
