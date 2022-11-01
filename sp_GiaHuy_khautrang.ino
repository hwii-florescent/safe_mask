#include <DHT.h>
#include <Arduino.h>

#define DHTPIN PD3
#define MQ135 PC1
#define QUAT PC6


#ifdef DHTPIN
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float dht_tem, dht_hum;
float readDhtHum() {
  return dht.readHumidity();
}
float readDhtTemp() {
  return dht.readTemperature();
}
#endif

#ifdef MQ135
int co2;
#endif

String readString;
unsigned long lastGet;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("++++++KHAU TRANG THONG MINH+++++++");
  Serial.println("");
#ifdef DHTPIN
  dht.begin();
#endif
  pinMode(QUAT, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    readString += c;
  }
  if (readString.length() > 0) {
    Serial.println(readString);
    if (readString == "bat quat") {
      digitalWrite(QUAT, HIGH);
    }
    if (readString == "tat quat") {
      digitalWrite(QUAT, LOW);
    }
    readString = "";
  }

  if (millis() - lastGet > 3000) {
    dht22_mq();
    lastGet = millis();
  }
}

void dht22_mq() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //  float f = dht.readTemperature(true);
  int co2 = analogRead(MQ135);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  Serial.print("CO2 density: ");
  Serial.println(co2);
  Serial.println("");

}
