#include "max6675.h"
#include <PID_v1.h>

// CONFIGURACION DE LOS PINES UTILIZADOS PARA LA COMUNICACIÓN CON EL MAX6675
#define CONFIG_TCGND_PIN      8
#define CONFIG_TCVCC_PIN      9
#define CONFIG_TCSCK_PIN      10
#define CONFIG_TCCS_PIN       11
#define CONFIG_TCDO_PIN       12

// OBJETO UTILIZADO PARA LA COMUNICACION CON EL MAX6675
MAX6675 thermocouple(CONFIG_TCSCK_PIN, CONFIG_TCCS_PIN, CONFIG_TCDO_PIN);

int salidaPWM = 3;  // salida de señal PWM
//Defina las variables con las que nos conectaremos
double temperatura;
double temp,error,Setpoint,Output;
 

double Kp=13, Ki=4, Kd=2;



PID myPID(&temp, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
 
void setup() {
 
  Serial.begin(9600);

  // USAR PINES DE ARDUINO PARA ALIMENTAR EL MODULO MAX6675
  pinMode(CONFIG_TCVCC_PIN, OUTPUT); digitalWrite(CONFIG_TCVCC_PIN, HIGH);
  pinMode(CONFIG_TCGND_PIN, OUTPUT); digitalWrite(CONFIG_TCGND_PIN, LOW);
  
  pinMode(salidaPWM, OUTPUT);  // decimos que pinOut es salida
  //Activar el PID
  myPID.SetSampleTime(20);
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0,255);
  
  
}
void loop() {

  Setpoint = 55; // velocidad referencia
 // temp = analogRead(0)*500.0/1024.0;
  temp = thermocouple.readCelsius();
  Serial.println(temp);
  delay(222);
  myPID.Compute(); // calcula salida Output  ( 0-255)
  analogWrite(salidaPWM,Output);
  
   
}
