Arduino ide
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define LCD_ADDRESS 0x27
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
const int LED = 3;
const int POT_PIN1 = A1;
const int POT_PIN2 = A0;
#define RELAY_PIN 7
const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 10;
const int LED4 = 11;
bool rainDetected = false;
bool normalDetected = false;
void setup()
{
Serial.begin(9600);
Serial.println("DHT11 Test!");
pinMode(LED, OUTPUT);
40 | P a g e
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);
pinMode(4, OUTPUT);
lcd.init();
lcd.backlight();
dht.begin();
pinMode(RELAY_PIN, OUTPUT);
digitalWrite(RELAY_PIN, HIGH);
delay(2000);
}
void loop()
{
if(Serial.available()){
char command = Serial.read();
if(command == 'A'){
digitalWrite(4, HIGH);
delay(1000);
digitalWrite(4, LOW);
}
}
float h = dht.readHumidity();
float t = dht.readTemperature();
int potValue1 = analogRead(POT_PIN1);
int potValue2 = analogRead(POT_PIN2);
float rain = map(potValue1, 0, 1023, 20, 40);
41 | P a g e
float moisture = map(potValue2, 0, 1023, 20, 40);
if (isnan(h) || isnan(t))
{
Serial.println("Failed to read from DHT sensor!");
lcd.clear();
lcd.print("DHT Error");
delay(2000);
return;
}
Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.println(" *C");
Serial.print("Rain: ");
Serial.println(rain);
Serial.print("Moisture : ");
Serial.println(moisture);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("T:");
lcd.print(t);
lcd.print("*C");
lcd.print(" H:");
lcd.print(h);
lcd.print("%");
lcd.setCursor(0, 1);
lcd.print("R:");
lcd.print(rain);
lcd.print(" M:");
lcd.print(moisture);
if (rain< 32 && !rainDetected)
{
lcd.setCursor(0, 1);
lcd.print("R: RAIN");
digitalWrite(LED1, HIGH);
digitalWrite(LED2, LOW);
digitalWrite(LED3, HIGH);
digitalWrite(LED4, LOW);
delay(5000);
digitalWrite(LED1, LOW);
digitalWrite(LED2, HIGH);
digitalWrite(LED3, LOW);
digitalWrite(LED4, HIGH);
rainDetected = true;
normalDetected = false;
}
else if (rain> 32 && !normalDetected)
{
lcd.setCursor(0, 1);
lcd.print("R:NORMAL");
digitalWrite(LED1, LOW);
digitalWrite(LED2, HIGH);
digitalWrite(LED3, LOW);
digitalWrite(LED4, HIGH);
delay(5000);
digitalWrite(LED1, HIGH);
43 | P a g e
digitalWrite(LED2, LOW);
digitalWrite(LED3, HIGH);
digitalWrite(LED4, LOW);
normalDetected = true;
rainDetected = false;
}
digitalWrite(LED1, LOW);
digitalWrite(LED2, LOW);
digitalWrite(LED3, LOW);
digitalWrite(LED4, LOW);
if (moisture < 30)
{
lcd.setCursor(9, 1);
lcd.print(" M:WET");
digitalWrite(RELAY_PIN, HIGH);
}
else
{
lcd.setCursor(9, 1);
lcd.print(" M:DRY");
digitalWrite(RELAY_PIN, LOW);
}
delay(2000);
}
