#include <DHT.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

#define DHTPIN 3
#define DHTTYPE DHT11
#define DHTIPO DHT22
#define DHTPIN1 9
#define DHTPIN2 8
#define boton 2

int selectmenu = 0;

DS3231 rtc(SDA, SCL);
DHT dht(DHTPIN, DHTTYPE);
DHT dht1(DHTPIN1, DHTIPO);
DHT dht2(DHTPIN2, DHTIPO);
//                RS   EN D4 D5 D6 D7
LiquidCrystal lcd(12, 10, 7, 6, 5, 4);

void setup() {
  rtc.begin();
  lcd.begin(16, 2);
  dht.begin();
  dht1.begin();
  dht2.begin();
  pinMode(boton, INPUT);
  Serial.begin(9600);
}

void loop() {
  menu();
}

void muest_disp() {
  lcd.setCursor(3, 0);
  lcd.print("Bienvenido");
  lcd.setCursor(0, 1);
  lcd.print("Selecciona el Menu");
  
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1: Tiempo y Hora");
  lcd.setCursor(0, 1);
  lcd.print("2: Temp y Humedad");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("3: Temp e Index");
  lcd.setCursor(0, 1);
  lcd.print("4: Salir");
  delay(3000);
  lcd.clear();
}

void menu() {
  //muest_disp();
  int estado = digitalRead(boton);
  
  if (estado == HIGH) {
    selectmenu++;
    
    switch (selectmenu) {
      case 1:
        Tiempo();
        Serial.print(Tiempo());
        delay(3000);
        lcd.clear();
        break;
      case 2:
        Sensor1();
        delay(3000);
        lcd.clear();
        break;
        
      case 3:
        Sensor2();
        delay(3000);
        lcd.clear();
        break;
        
      case 4:
        Sensor3();
        delay(3000);
        lcd.clear();
        selectmenu = 0; // Reiniciar el Selector
        break;
      default:
        selectmenu = 0; // Reiniciar el Selector
        break;
    }
  }
}

void Tiempo() {
  lcd.setCursor(0, 0);
  lcd.print("Hora: ");
  lcd.print(rtc.getTimeStr());

  lcd.setCursor(0, 1);
  lcd.print("Fecha:");
  lcd.print(rtc.getDateStr());
}

void Sensor1() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float ind = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0, 0);
  lcd.print("Humedad:");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Tempe:");
  lcd.print(t);
  lcd.print(" C");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Index:");
  lcd.print(ind);
  lcd.print(" C");
}

void Sensor2() {
  float humedad2 = dht1.readHumidity();
  float temp2 = dht1.readTemperature();
  float inde2 = dht1.computeHeatIndex(temp2,humedad2,false);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp2);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humedad: ");
  lcd.print(humedad2);
  lcd.print("%");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Index: ");
  lcd.print(inde2);
  lcd.print(" C");
}

void Sensor3() {
  float hum3 = dht2.readHumidity();
  float tem3 = dht2.readTemperature();
  float inde3 = dht2.computeHeatIndex(tem3,hum3,false);
  
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tem3);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humedad: ");
  lcd.print(hum3);
  lcd.print("%");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Index: ");
  lcd.print(inde3);
  lcd.print(" C");
}
