#include <DHT.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

#define DHTPIN 3 //Asignación de Pin
#define DHTTYPE DHT11
#define boton 2 //Asignación de Pin para interrupcion externa

int selectmenu=0; //Variable encargada de hacer la selección de menu

DS3231 rtc(SDA, SCL);
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 10, 7, 6, 5, 4);


void setup() {
  rtc.begin();
  lcd.begin(16, 2);
  dht.begin();
  pinMode(boton,INPUT);
  attachInterrupt(boton,RISING,menu);
  Serial.begin(9600);
}

void loop() {
  
menu();


}
void menu(){
  int estado=digitalRead(boton);
  if(estado==HIGH){
    selectmenu++;
   switch(selectmenu) {
      case 1:
        Tiempo();
        delay(3000);
        lcd.clear();
        break;
      case 2:
        Humedad_Tempe();
        delay(3000);
        lcd.clear();
        break;
      case 3:
        Temperatura_Index();
        delay(3000);
        lcd.clear();
        break;
      default:
        break;
    }
    //Serial.println(selectmenu);
    };
    
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
