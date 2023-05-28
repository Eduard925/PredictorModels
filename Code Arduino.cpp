#include "DHT.h"

#define DHTPIN 12     // Pin donde está conectado el sensor

#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
// Define the analog pin for sensor input
const int gasSensorPin = A0;

// Define variables
float gasResistance;
float gasPPM;


DHT dht(DHTPIN, DHTTYPE);
//Pines de conexión del driver
int Pin_Motor_Der_A = 4;
int Pin_Motor_Der_B = 7;
int PWMB = 6; 
int Pin_Motor_Izq_A = 8;
int Pin_Motor_Izq_B = 9;
int PWMA = 5;   //
int tiempo=0;

void setup() {
  // inicializar la comunicación serial a 9600 bits por segundo:
  Serial.begin(9600);
  Serial.print("Humidity,Temperature,PPM");
  Serial.print('\n');
  dht.begin();
  // configuramos los pines como salida
  pinMode(Pin_Motor_Der_A, OUTPUT);
  pinMode(Pin_Motor_Der_B, OUTPUT);
  pinMode(Pin_Motor_Izq_A, OUTPUT);
  pinMode(Pin_Motor_Izq_B, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(PWMA, OUTPUT);
  
  
}

void loop() {
  
  if (Serial.available()) {
    char dato= Serial.read();
    if(dato=='F')
    {
      Mover_Adelante();
      tiempo=0;
    }
    else if(dato=='B')
    { 
      Mover_Retroceso();
      tiempo=0;
    }
    else if(dato=='R')
    { 
      Mover_Derecha();
      tiempo=0;
    }
    else if(dato=='L')
    { 
      Mover_Izquierda();
      tiempo=0;
    }
    else if(dato=='W')
    { 
      delay(500);
      float h = dht.readHumidity(); //Leemos la Humedad
      float t = dht.readTemperature(); //Leemos la temperatura en grados Celsius
      float f = dht.readTemperature(true); //Leemos la temperatura en grados Fahrenheit
      //--------Enviamos las lecturas por el puerto serial-------------
      
      Serial.print(h);
      Serial.print(",");
      Serial.print(t);
      Serial.print(",");
      Serial.print(gasPPM);
      Serial.print('\n');
      int sensorValue = analogRead(gasSensorPin);
      
      // Calculate the gas resistance (in kilohms)
      gasResistance = ((1023.0 * 10.0) / sensorValue) - 10.0;
      
      // Use the gas resistance to estimate the gas concentration in parts per million (PPM)
      gasPPM = pow(10, ((log10(gasResistance) - 2.5651) / -0.4615));
      
      // Delay before the next reading
      delay(500);;
      
    }   
    else if(dato=='S')
    { 
      
      tiempo=0;
    }  
  }
  
  if(tiempo<200) // 100 cilcos de 1ms 
  {    
    tiempo=tiempo+1;
  }
  else   //ya transcurrió 100ms (100ciclos)
  {
    Mover_Stop();
  }
  
  
  delay(1); //pasusa de 1ms por ciclo
  
}

void Mover_Adelante()
{
  digitalWrite (Pin_Motor_Der_A, HIGH);
  digitalWrite (Pin_Motor_Der_B, LOW);
  digitalWrite (Pin_Motor_Izq_A, HIGH);
  digitalWrite (Pin_Motor_Izq_B, LOW);
  analogWrite(PWMA, 200);
  analogWrite(PWMB, 200);
}
void Mover_Retroceso()
{
  digitalWrite (Pin_Motor_Der_A,LOW );
  digitalWrite (Pin_Motor_Der_B,HIGH );
  digitalWrite (Pin_Motor_Izq_A,LOW );
  digitalWrite (Pin_Motor_Izq_B,HIGH );
  analogWrite(PWMA, 200);
  analogWrite(PWMB, 200);
}
void Mover_Derecha()
{
  digitalWrite (Pin_Motor_Der_A,LOW );
  digitalWrite (Pin_Motor_Der_B,HIGH );
  digitalWrite (Pin_Motor_Izq_A,HIGH );
  digitalWrite (Pin_Motor_Izq_B,LOW );
  analogWrite(PWMA, 200);
  analogWrite(PWMB, 200);
  
}
void Mover_Izquierda()
{
  digitalWrite (Pin_Motor_Der_A,HIGH);
  digitalWrite (Pin_Motor_Der_B,LOW);
  digitalWrite (Pin_Motor_Izq_A,LOW );
  digitalWrite (Pin_Motor_Izq_B,HIGH );
  analogWrite(PWMA, 200);
  analogWrite(PWMB, 200);
}
void Mover_Stop()
{
  digitalWrite (Pin_Motor_Der_A, LOW);
  digitalWrite (Pin_Motor_Der_B, LOW);
  digitalWrite (Pin_Motor_Izq_A, LOW);
  digitalWrite (Pin_Motor_Izq_B, LOW);
  
}