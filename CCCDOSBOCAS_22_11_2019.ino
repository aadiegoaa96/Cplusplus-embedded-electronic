/*  Proyecto: "BANCO DE PRUEBAS HIDROSTÁTICAS".
 *  Presenta: DIEGO NORBERTO BERMÚDEZ CASTILLO.
 *  Escuela:  INSTITUTO TECNOLÓGICO DE VERACRUZ.
 *  Carrera:  ING. MECATRÓNICA.
 *  E-mail:   dbcpachuca@hotmail.com .  
 */

#include "max6675.h"            // Incluimos libreria para controlar el módulo del termopar tipo K.
#define ktcSO 8                 // Declaramos el pin digital 8 y le asignamos el nombre de ktcSO. Este pin controlará el módulo MAX6675.
#define ktcCS 9                 // Declaramos el pin digital 9 y le asignamos el nombre de ktcCS. Este pin controlará el módulo MAX6675.
#define ktcCLK 10               // Declaramos el pin digital 10 y le asignamos el nombre de ktcCLK. Este pin controlará el reloj del módulo MAX6675.
#define analogPin1 14           // Declaramos el pin analógico A0 ó pin digital 14 y le asignamos el nombre de analogPin1.
#define pinLED 13               // Este led comprueba que la prueba hidrostática siga dentro de los parámetros de presión deseados para una válvula en buenas condiciones.
#define relevador 7             // Este relevador controlará la bomba hidráulica de A.C.

 
long time_now1 = 0;                           // La función millis que lo utiliza tarda hasta 50 días en desbordar sus registros, es decir; podemos contar hasta 50 días con esta variable de tipo long.
extern volatile unsigned long timer0_millis;  // Variale necesaria para controlar el reinicio del temporizador.
long previousMillis = 0;                      // Variale necesaria para controlar el reinicio del temporizador.
unsigned long new_value = 0;                  // valor al que se espera regresar en el caso 1 del Switch Case de control.
static float metodo_presion_map1;             // Variable será tratada con la función map para representar distintos valores eléctricos del transmisor de presión.
static float metodo_presion_map2;             // Variable será tratada con la función map para representar distintos valores eléctricos del transmisor de presión.
static float metodo_presion_map3;             // Variable será tratada con la función map para representar distintos valores eléctricos del transmisor de presión.
static double valordelSensor;                 // Variable que guarda el valor del puerto analógico proveniente del transmisor de presión Rosemount.
static float temp_modulo = 0;                 // Variable que se utiliza para guardar los valor de temperatura provenientes del módulo Max6675.
static String valor = "";                     // Declaramos un tipo de dato string llamado valor y le asignamos una cadena vacía.
int bandera;                                  // Utilizamos esta variable booleana para controlar las veces que se entra a un bucle.
int estado = 0;                               // Esta variable se utiliza para controlar el posible estado de trabajo al que puede estar el microcontrolador sometido, incluye 5 estados posibles.
int Estado_de_la_valvula = 0;                 // Esta variable se utiliza para generar un estado de falla o mal funcionamiento en la válvula.
static float presion1;                        // En esta variable se guardará el valor de retorno que contiene el método: "metodo_presion".
static float presion2;                        // En esta variable se guardará el valor de retorno que contiene el método: "metodo_presion".
static float presion3;                        // En esta variable se guardará el valor de retorno que contiene el método: "metodo_presion".

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);                                      // Parámetros de la librería MAX6675.
     
static float metodo_presion1(int samplesNumber1, float (*funct)())      // Método para minizar el ruido eléctrico de las válvulas de 2000 Lb.
{
   float sum1;                                                          // La variable "sum" almacenará el valor de cualquier cantidad de muestras deseadas.
   for (int i = 0; i < samplesNumber1; i++)                             // Se utiliza el bucle for para reservar un espacio de memoria en el que se almacenen un número deseado de muestras.
   {
      sum1 += obtener_metodo_presion1();                                // Se sumarán todos los valores obtenidos del transmisor de presión y el resultado se guardará en "sum".
   }
 
   return sum1 / samplesNumber1;                                        // Se promediará la presión dividiendo el resultado de "sum" entre el número de muestras.
}  
static float metodo_presion2(int samplesNumber2, float (*funct)())      // Método para minizar el ruido eléctrico de las válvulas de 1500 Lb.
{
   float sum2;                                                          // La variable "sum" almacenará el valor de cualquier cantidad de muestras deseadas.
   for (int j = 0; j < samplesNumber2; j++)                             // Se utiliza el bucle for para reservar un espacio de memoria en el que se almacenen un número deseado de muestras.
   {
      sum2 += obtener_metodo_presion2();                                // Se sumarán todos los valores obtenidos del transmisor de presión y el resultado se guardará en "sum".
   }
 
   return sum2 / samplesNumber2;                                        // Se promediará la presión dividiendo el resultado de "sum" entre el número de muestras.
}  
static float metodo_presion3(int samplesNumber3, float (*funct)())      // Método para minizar el ruido eléctrico de las válvulas de 300 Lb.
{
   float sum3;                                                          // La variable "sum" almacenará el valor de cualquier cantidad de muestras deseadas.
   for (int k = 0; k < samplesNumber3; k++)                             // Se utiliza el bucle for para reservar un espacio de memoria en el que se almacenen un número deseado de muestras.
   {
      sum3 += obtener_metodo_presion3();                                // Se sumarán todos los valores obtenidos del transmisor de presión y el resultado se guardará en "sum".
   }
 
   return sum3 / samplesNumber3;                                        // Se promediará la presión dividiendo el resultado de "sum" entre el número de muestras.
}
 
//Funcion que sensará PRESIÓN
float obtener_metodo_presion1()                                        // Funcion que sensará la temperatura y retorna el valor flotante guardado en la variable metodo_presion_map.
{
    
         valordelSensor = analogRead(analogPin1);                      // Tomaremos una lectura con un potenciómetro y este dato será guardado en la variable valordelSensor.
         metodo_presion_map1 = map(valordelSensor,0,1023,0,2000);      // Utilizamos la función map con la variable: "valordelSensor" para representarlos en una nueva escala de 0 a 2000 valores posibles.
         return metodo_presion_map1;                                   // Retornamos metodo_presion_map. Esta variable contendrá una representación de un  eléctrico con su equivalencia de 0 a 2000 psi.
}

//Funcion que sensará PRESIÓN
float obtener_metodo_presion2()                                         // Funcion que sensará la temperatura y retorna el valor flotante guardado en la variable metodo_presion_map.
{
    
         valordelSensor = analogRead(analogPin1);                      // Tomaremos una lectura con un potenciómetro y este dato será guardado en la variable valordelSensor.
         metodo_presion_map2 = map(valordelSensor,0,1023,0,1500);      // Utilizamos la función map con la variable: "valordelSensor" para representarlos en una nueva escala de 0 a 2000 valores posibles.
         return metodo_presion_map2;                                   // Retornamos metodo_presion_map. Esta variable contendrá una representación de un  eléctrico con su equivalencia de 0 a 2000 psi.
}

//Funcion que sensará PRESIÓN
float obtener_metodo_presion3()                                         // Funcion que sensará la temperatura y retorna el valor flotante guardado en la variable metodo_presion_map.
{
    
         valordelSensor = analogRead(analogPin1);                       // Tomaremos una lectura con un potenciómetro y este dato será guardado en la variable valordelSensor.
         metodo_presion_map3 = map(valordelSensor,0,1023,0,300);        // Utilizamos la función map con la variable: "valordelSensor" para representarlos en una nueva escala de 0 a 2000 valores posibles.
         return metodo_presion_map3;                                    // Retornamos metodo_presion_map. Esta variable contendrá una representación de un  eléctrico con su equivalencia de 0 a 2000 psi.
}
void setMillis(unsigned long new_millis)                        // Método para reiniciar a 0 el valor del contador de la función millis           
{
  uint8_t oldSREG = SREG;                                       //
  timer0_millis = new_millis;                                   //
  SREG = oldSREG;                                               //
}

     
void setup() {                                                  // Declaramos el método setup.
  Serial.begin(9600);                                           // Iniciamos la comunicación serial a 9600 baudios.
  pinMode(pinLED, OUTPUT);                                      // Declaramos como salida el pin 13 digital para controlar el encendido dela bomba hidráulica de CA.
  pinMode(relevador, OUTPUT);                                      // Declaramos como salida el pin 13 digital para controlar el encendido dela bomba hidráulica de CA.
  bandera = 1;                                                  // Se asigna a la variable bandera un valor booleano true, esta varible nos ayudará a controlar el encendido dela bomba hidráulica de CA.
}

void loop() {                                                   // Iniciamos el ciclo.
        if (Serial.available())                                 // Si se cumple que existen datos transfiriéndose por el puerto serial entonces ...
   {  
   char temp = Serial.read();                                   // Guardamos lo que capture el método read en la variable llamada: "temp".
            if(temp == '0')                                     // Leemos temp, y si es 0... 
            {estado = 0;}                                       // Entonces escribimos 0 en la variable llamada: "estado".
            if(temp == '1')                                     // Leemos temp, y si es 1... 
            {estado = 1;}                                       // Entonces escribimos 1 en la variable llamada: "estado".
            if(temp == '2')                                     // Leemos temp, y si es 2... 
            {estado = 2;}                                       // Entonces escribimos 2 en la variable llamada: "estado".
            if(temp == '3')                                     // Leemos temp, y si es 3... 
            {estado = 3;}                                       // Entonces escribimos 3 en la variable llamada: "estado".
            if(temp == '4')                                     // Leemos temp, y si es 4... 
            {estado = 4;}                                       // Entonces escribimos 4 en la variable llamada: "estado".
            if(temp == '5')                                     // Leemos temp, y si es 5... 
            {estado = 5;}                                       // Entonces escribimos 5 en la variable llamada: "estado".
   } 
        switch(estado)                                          // Una vez que la variable tipo char llamada letra distinga algunos tipos de caracteres binarios (simbolos ASCII).
     {                                                          // Se ejecutará la correspondiente función de ese caracter y el programa regresará a esperar una nueva indicación (símbolo ASCII).     
         case 0:                                                // ESTADO 0. PAUSAR EL MICROCONTROLADOR.
         break;                                                 // Salimos del blucle.
         
         case 1:                                                // ESTADO 1. REINICIAR valorES DE SENSORES.
         bandera = 0;
         setMillis(new_value);                                  // Se iguala al valor del contador de Arduino; es decir, se reinicia a cero.
         time_now1 = 0;                                         // Se reinicia a cero la variable que almacena el valor del tiempo actual.
         metodo_presion_map1 = 0;                               // Se reinicia a cero el metodo_presion_map. 
         metodo_presion_map2 = 0;                               // Se reinicia a cero el metodo_presion_map. 
         metodo_presion_map3 = 0;                               // Se reinicia a cero el metodo_presion_map. 
         temp_modulo = 0;                                       // Se reinicia a cero la variable encargada de almacenar la temperatura.
         valordelSensor = 0;                                    // Leemos el puerto analógico 0 de la placa Arduino Uno. 
         bandera = true;                                        // Declaramos la bandera como estado alto para que entre por primera vez al bucle, pero nunca más de una vez.
         Estado_de_la_valvula = 0;                              // La prueba contiene dos posibles estados principales. Cuando es 0, la válvula es hermética, cuando es diferente que 0 no será hermética.
         presion1 = 0;                                          // Reniciamos el valor de las válvulas de 2000 PSI.
         presion2 = 0;                                          // Reniciamos el valor de las válvulas de 1500 PSI.
         presion3 = 0;                                          // Reniciamos el valor de las válvulas de 300 PSI.
         apaga();                                               // Apagamos el led y el relevador.
         break;                                                 // Salimos del blucle.
         
         case 2:                                                   // ESTADO 2. REALIZAR PRUEBA HIDROSTÁTICA DE: 2000 PSI. PARA: VÁLVULA DE VENTEO ALTO, VÁLVULA DE REECIRCULACIÓN, VÁLVULA PEGGING, VÁLVULA DE ALIMENTACIÓN DE AGUA, VÁLVULA DE FLUJO MÍNIMO.
         presion1 = metodo_presion1(20, obtener_metodo_presion1);  // Leeremos presión en el pin 
         temp_modulo = ktc.readCelsius();                          // Tomaremos una lectura con el módulo MAX6675 y este dato será guardado en la variable: "valordelSensor1".
         delay(222);                                               // Esperamos 222 milisegundos por que el módulo MAX6675 indica en su hoja de datos un muestreo óptimo a esa frecuencia de actualización.
         time_now1 = millis();                                     // Iniciamos el contador de tiempo y guardamos su resultado en la variable: "time_now1".
          
         if(bandera == 1 && metodo_presion_map1<1900)              // Si le hace falta presión y bandera es 1.
         {
          prende();                                                // Se encenderá la bomba hidráulica de CA.
          bandera = 2;                                             // La bandera valdrá 2.
         }
         if(bandera == 2 && metodo_presion_map1>1900)              // Si la presión llega al valor requerido y bandera es 2.
         {
          apaga();                                                 // Se apagará la bomba hidráulica de CA.
          bandera = 3;                                             // La bandera valdrá 3.
         }
         if(bandera == 3 && metodo_presion_map1<1700)              // Si la presión baja se puede inferir que la válvula no es hermética; es decir presenta un daño. Por lo que se da aviso que la válvula está dañada.
         {
          estado = 5;                                              // Se ingresará al estado 5, encargado de indicar si la válvula sufrió caida de presión consecuencia de que la válvula no es hermética.
          break;                                                   // Salimos del blucle.
         }
         
         valor+= time_now1/1000;                     // Guardamos lo que contenga en ese momento la variable valordelSensor1 en la varible String llamada valor.
         valor+= '|';                                // Guardamos el caracter '|' en la variable String llamada valor. 
         valor+= temp_modulo;                        // Guardamos lo que contenga en ese momento la variable valordelSensor en la varible String llamada valor. 
         valor+= '|';                                // Guardamos el caracter '|' en la variable String llamada valor. 
         valor+= time_now1/1000;                     // Guardamos lo que contenga en ese momento la variable valordelSensor1 en la varible String llamada valor.
         valor+= '|';                                // Guardamos el caracter '|' en la variable String llamada valor. 
         valor+= metodo_presion_map1;                // Guardamos lo que contenga en ese momento la variable valordelSensor en la varible String llamada valor. 
         Serial.println(valor);                      // Envíamos por el puerto serial la variable valor; esta describe en que momento se leen los valores de presión y temperatura.
         valor = " ";                                // Limpiamos lo que contenga guardado la variable valor.
         break;                                      // Salimos del blucle.
        
         
         case 3:                                                   // ESTADO 3. REALIZAR PRUEBA HIDROSTATICA DE: 1500 PSI. PARA: VÁLVULA ATEMPERADORA DE VAPOR SOBRE CALENTADO, VÁLVULA DE PURGA CONTINUA, VÁLVULA DE PURGA INTERMITENTE.
         presion2 = metodo_presion2(20, obtener_metodo_presion2);  // Declaramos 10 muestras, y guardamos el resultado del algoritmo anti ruido en la variable: "leer_metodo_presion2".
         temp_modulo = ktc.readCelsius();                          // Tomaremos una lectura con el módulo MAX6675 y este dato será guardado en la variable valordelSensor1.
         delay(222);                                               // Pausamos al microcontrolador 222 milisegundos.
         time_now1 = millis();                                     // Comienza el conteo de tiempo y se almacena en la variable: "time_now1"
         if(bandera == 1 && metodo_presion_map2<1400)              // Si le hace falta presión y bandera es 1.
         {
          prende();                                                // Se encenderá la bomba hidráulica de CA.
          bandera = 2;                                             // La bandera valdrá 2.
         }
         if(bandera == 2 && metodo_presion_map2>1400)              // Si la presión llega al valor requerido y bandera es 2.
         {
          apaga();                                                 // Se apagará la bomba hidráulica de CA.
          bandera = 3;                                             // La bandera valdrá 3.
         }
         if(bandera == 3 && metodo_presion_map2<1200)              // Si la presión baja se puede inferir que la válvula no es hermética; es decir presenta un daño. Por lo que se da aviso que la válvula está dañada.
         {
          estado = 5;                                              // Se ingresará al estado 5, encargado de indicar si la válvula sufrió caida de presión consecuencia de que la válvula no es hermética.
          break;                                                   // Salimos del blucle.
         }
         valor+= time_now1/1000;                     // Guardamos lo que contenga en ese momento la variable valor en la varible String llamada valor.
         valor+= '|';                                // Guardamos el caracter '|' en la variable String llamada: "valor". 
         valor+= temp_modulo;                        // Guardamos lo que contenga en ese momento la variable string llamada: "valor". 
         valor+= '|';                                // Guardamos el caracter '|' en la variable String llamada: "valor". 
         valor+= time_now1/1000;                     // Guardamos lo que contenga en ese momento la variable string llamada: "valor".
         valor+= '|';                                // Guardamos el caracter '|' en la variable String llamada: "valor". 
         valor+= metodo_presion_map2;                // Guardamos lo que contenga en ese momento la variable string llamada: "valor".
         Serial.println(valor);                      // Envíamos por el puerto serial la variable String llamada: "valor".
         valor = " ";                                // Limpiamos lo que contenga guardado la variable string llamada: "valor".
         break;                                      // Salimos del blucle.
         
         case 4:                                                   // ESTADO 4. REALIZAR PRUEBA HIDROSTATICA DE: 300 PSI. PARA: VÁLVULA DE VENTEO BAJA, VÁLVULA DUMP, VÁLVULA DE CONDENSADO.
         presion3 = metodo_presion3(20, obtener_metodo_presion3);  // Declaramos 10 muestras, y guardamos el resultado del algoritmo anti ruido en la variable: "leer_metodo_presion".
         temp_modulo = ktc.readCelsius();                          // Tomaremos una lectura con el módulo MAX6675 y este dato será guardado en la variable: "temp_modulo".
         delay(222);                                               // Pausamos al microcontrolador 222 milisegundos.
         time_now1 = millis();                                     // Comienza el conteo de tiempo y se almacena en la variable: "time_now1"
         if(bandera == 1 && metodo_presion_map3<250)               // Si le hace falta presión y bandera es 1.
         {
          prende();                                                // Se encenderá la bomba hidráulica de CA.
          bandera = 2;                                             // La bandera valdrá 2.
         }
         if(bandera == 2 && metodo_presion_map3>250)               // Si la presión llega al valor requerido y bandera es 2.
         {
          apaga();                                                 // Se apagará la bomba hidráulica de CA.
          bandera = 3;                                             // La bandera valdrá 3.
         }
         if(bandera == 3 && metodo_presion_map3<180)               // Si la presión baja se puede inferir que la válvula no es hermética; es decir presenta un daño. Por lo que se da aviso que la válvula está dañada.
         {
          estado = 5;                                              // Se ingresará al estado 5, encargado de indicar si la válvula sufrió caida de presión consecuencia de que la válvula no es hermética.
          break;                                                   // Salimos del blucle.
         }
         valor+= time_now1/1000;                     // Guardamos lo que contenga en ese momento la variable valordelSensor1 en la varible String llamada valor.
         valor+= '|';                                // Guardamos el caracter '|' en la variable String llamada valor. 
         valor+= temp_modulo;                        // Guardamos lo que contenga en ese momento la variable valordelSensor en la varible String llamada valor. 
         valor+= '|';                                // Guardamos el caracter '|' en la variable String llamada valor. 
         valor+= time_now1/1000;                     // Guardamos lo que contenga en ese momento la variable valordelSensor1 en la varible String llamada valor.
         valor+= '|';                                // Guardamos el caracter '|' en la variable String llamada valor. 
         valor+= metodo_presion_map3;                // Guardamos lo que contenga en ese momento la variable valordelSensor en la varible String llamada valor. 
         Serial.println(valor);                      // Envíamos por el puerto serial la variable valor; esta describe en que momento se leen los valores de presión y temperatura.
         valor = " ";                                // Limpiamos lo que contenga guardado la variable valor.
         break;                                      // Salimos del blucle.

         case 5:                                                // ESTADO 5. CONTROLAR EL ESTADO DE LA VÁLVULA (ES HERMÉTICA Ó NO LO ES).
         Estado_de_la_valvula = 666;                            // Envíamos el número 666 para indicar que la válvula está dañada
         Serial.println(Estado_de_la_valvula);                  // Envíamos por el puerto serial la variable paqutee_de_Datos; esta indica si la vávula tiene un daño.
         Serial.println('|');                                   // Envíamos por el puerto serial el caracter '|' que indicará al visual studio que la válvula está dañada.
         break;                                                 // Salimos del blucle.
       }
    }
void apaga()                                                    // Método que apaga el led del pin 13 y el relevador del pin 7.
{
  digitalWrite(pinLED,LOW);                                     // El pin 13 se declara como estado bajo.
  digitalWrite(relevador,LOW);                                  // El pin 7 se declara como estado bajo.
}
void prende()                                                   // Método que prende led del pin 13 y el relevador del pin 7.
{
  digitalWrite(pinLED,HIGH);                                    // El pin 13 se declara como estado alto.
  digitalWrite(relevador,HIGH);                                 // El pin 7 se declara como estado bajo.
}
