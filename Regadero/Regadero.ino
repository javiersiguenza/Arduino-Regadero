const int rele = 7;

unsigned long previousMillis = 0;
unsigned long startTime;                             // Variable para almacenar el tiempo de inicio
const unsigned long executionTime = 1 * 60 * 1000;   // 5 minutos en milisegundos
const unsigned long duration = 5UL * 60UL * 1000UL;  // 5 minutos en milisegundos

const int horaInicio = 15;
const int minutosInicio = 25;
boolean active = false;

#include <DS3231.h>
#include <Wire.h>
DS3231 Clock;                                 //  Direccionamiento del hardware
RTClib RTC;                                   // Declaración de la función RTC
int year, month, date, hour, minute, second;  //se declaran variables para guardar fecha y hora obtenida



void setup() {
  Serial.begin(9600);
  // Aquí puedes agregar la configuración inicial de tus pines y componentes
  pinMode(rele, OUTPUT);

  Wire.begin();  //se inicia la comunicación por I2C
  //configurarHora();
  startTime = millis();
  regar();
}

void loop() {
  DateTime now = RTC.now();  //Se obtiene la fecha y la hora y se guarda en su respectiva variable
  year = now.year();
  month = now.month();
  date = now.day();
  hour = now.hour();
  minute = now.minute();
  second = now.second();
  //Serial.println(now.minute());
  // Comprobar si es la hora programada (8:00 AM)

  if (hour == horaInicio && minute == minutosInicio /*&& second == 0*/) {
    regar();
    Serial.println("Parando tarea...");
    digitalWrite(rele, LOW);
    active = false;
  }
}

void regar(){

  unsigned long currentMillis = millis();
    // Ejecutar durante 5 minutos
    unsigned long taskEndTime = currentMillis + duration;
   while (currentMillis <= taskEndTime) {
      if (!active) {
        Serial.println("Ejecutando tarea...");
        digitalWrite(rele, HIGH);
        active = true;
      }
      currentMillis = millis();
    }
}

void configurarHora() {
  year = 23;
  month = 6;
  date = 26;
  hour = 13;
  minute = 10;
  second = 0;
  Wire.begin();                   // Se inicial la interfaz I2c
  Clock.setClockMode(false);      //Se establece el modo horario en 24 horas (true = 12h)
  Clock.setYear((byte)year);      //Año
  Clock.setMonth((byte)month);    //Mes
  Clock.setDate((byte)date);      //Día
  Clock.setHour((byte)hour);      //Hora
  Clock.setMinute((byte)minute);  //Minutos
  Clock.setSecond((byte)second);  //Segundos
}
