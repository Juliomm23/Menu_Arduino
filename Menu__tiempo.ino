#include <DHT.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

#define DHTPIN 3 //Asignación de Pin
#define DHTTYPE DHT11
#define buttonPin 9 //Asignación de Pin

DS3231 rtc(SDA, SCL);
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 10, 7, 6, 5, 4);

int menu = 3;
int boton = HIGH;
int ultimo_estado = HIGH;
unsigned long lastDebounceTime = 0; //Variable para evitar rebote
unsigned long debounceDelay = 50; //Variable para evitar rebote

void setup() {
  Serial.begin(9600);
  rtc.begin();
  lcd.begin(16, 2);
  dht.begin();
  pinMode(buttonPin, INPUT);
}

void loop() {
  int estado = digitalRead(boton); //Variable para determinar el estado del boton

  //Segmento que se encagara de evitar el efecto rebote
  if (estado != ultimo_estado) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (estado != boton) {
      boton = estado;

      if (boton == LOW) {
        menu++;
        if (menu > 3) {
          menu = 1;
        }
        lcd.clear();
      }
    }
  }

  ultimo_estado = estado;

  do {
    switch(menu) {
      case 1:
        Tiempo();
        delay(3000);
        break;
      case 2:
        Humedad_Tempe();
        delay(3000);
        break;
      case 3:
        Temperatura_Index();
        delay(3000);
        break;
      default:
        break;
    }
  } while (boton == HIGH);
  
}

void Tiempo() {
  lcd.setCursor(0, 0);
  lcd.print("Hora: ");
  lcd.print(rtc.getTimeStr());

  lcd.setCursor(0, 1);
  lcd.print("Fecha:");
  lcd.print(rtc.getDateStr());
}

void Humedad_Tempe() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.setCursor(0, 0);
  lcd.print("Humedad:");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Tempe:");
  lcd.print(t);
  lcd.print("C");
}

void Temperatura_Index() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Ind.Calor:");
  lcd.print(hic);
  lcd.print("C");
}
