float corriente = 0.0; 
float R=250; 



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i=1; i<=20; i++)
{
  corriente = (float) analogRead(0)*(5/1023.0)/R+corriente;
}

Serial.print(corriente*1000/20,3); //EL ,3 es para indicar que queremos mostrar el resultado con 3 dígitos de exactitud
Serial.println(" mA :");

delay(30); 

corriente = 0; 

}
