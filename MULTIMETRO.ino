#define SALIDA 13
#define SALIDA2 12

const double conversion = 0.0048828125;

  float voltajeSensor;
  float corriente=0;

  
void setup()
{
  Serial.begin(9600);
  pinMode(SALIDA,OUTPUT); 
  pinMode(SALIDA2,OUTPUT); 
}



void loop()
{

  digitalWrite(13,HIGH); 
  digitalWrite(12,HIGH); 
/*
  float voltaje;
  voltaje = (analogRead(A0));
  voltaje=voltaje*conversion;
  Serial.print("VOLTAJE: ");
  Serial.println(voltaje);
*/

    voltajeSensor = analogRead(A0) * (5.0 / 1023.0);//lectura del sensor
    //corriente=0.9*corriente+0.1*((voltajeSensor-2.527)/Sensibilidad); //Ecuación  para obtener la corriente
    //corriente=0.9*corriente+0.1*((voltajeSensor-2.527)); //Ecuación  para obtener la corriente
    corriente=0.9*corriente+0.1*voltajeSensor; //Ecuación  para obtener la corriente

    Serial.print("VOLTAJE :");
    Serial.println(voltajeSensor);
    Serial.print("CORRIENTE :");
    Serial.println(corriente);

}
