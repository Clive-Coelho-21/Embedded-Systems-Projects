#include<Wire.h> 
#include<LiquidCrystal_I2C.h>
#include<DHT.h>

#define DEHUM_RELAY_PIN  4
#define HUM_RELAY_PIN    5
#define DHT22_PIN        23
#define PIR_PIN          27 

#define NO_MOTION_TIME 120000  

const float DEHUM_ON   = 70.0F; 
const float DEHUM_OFF  = 65.0F;
const float HUM_ON     = 30.0F;
const float HUM_OFF    = 35.0F;

unsigned long lastMotionTime = 0;
unsigned long lastDHT22Time  = 0;
unsigned long pirHighStart   = 0;

DHT dht22(DHT22_PIN,DHT22);
LiquidCrystal_I2C lcd(0x27,16,2);

void goToSleep() 
{
  //Serial.println("Going to Sleep");

  digitalWrite(DEHUM_RELAY_PIN,LOW);
  digitalWrite(HUM_RELAY_PIN,LOW);

  lcd.noBacklight();
  lcd.clear();

  esp_sleep_enable_ext0_wakeup((gpio_num_t)PIR_PIN,HIGH); 
  esp_deep_sleep_start();
}

void setup()  
{
  //Serial.begin(115200);
  
  dht22.begin();
  
  lcd.init();
  lcd.backlight();

  pinMode(PIR_PIN,INPUT);
  pinMode(DEHUM_RELAY_PIN,OUTPUT);
  pinMode(HUM_RELAY_PIN,OUTPUT);
  digitalWrite(DEHUM_RELAY_PIN,LOW);
  digitalWrite(HUM_RELAY_PIN,LOW);
  
  if(esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) 
  {
    //Serial.println("Motion Detected!!!");
    lastMotionTime = millis();
  } 
  else 
    goToSleep();  

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humidifier/Dehumidifier");
  lcd.setCursor(4,1);
  lcd.print("Project"); 
  delay(4000);
}

void loop() 
{
  if(digitalRead(PIR_PIN) == HIGH) 
  {
    if(pirHighStart == 0)
      pirHighStart = millis();  

    if(millis() - pirHighStart >= 3000)
    {
      lastMotionTime = millis();
      //Serial.println("THe PIR Sensor detected Motion!!!");
    }
  }
  else
    pirHighStart = 0;

  /*Serial.print("Current time: ");
  Serial.print(millis() / 1000);
  Serial.println("Secs");

  Serial.print("lastMotionTime: ");
  Serial.print(lastMotionTime / 1000);
  Serial.println("Secs");*/

  unsigned long currentDHT22Time = millis();
  if(currentDHT22Time - 2000 >= lastDHT22Time)
  {
    float Hum  = dht22.readHumidity();
    float TempC = dht22.readTemperature();

    lcd.clear();
    if (isnan(Hum) || isnan(TempC)) 
    {
      lcd.setCursor(1,0);
      lcd.print("Failed to read");
      lcd.setCursor(2,1);
      lcd.print("DHT22 Sensor!");
    } 
    else 
    {
      lcd.setCursor(0,0);
      lcd.print("Humidity: ");
      lcd.setCursor(10,0);
      lcd.print(Hum);
      lcd.setCursor(15,0);
      lcd.print("%");

      lcd.setCursor(0,1);
      lcd.print("TempC: ");
      lcd.setCursor(7,1);
      lcd.print(TempC);
      lcd.setCursor(12,1);
      lcd.print("C");
    }

    if(Hum >= DEHUM_ON) 
    {
      digitalWrite(DEHUM_RELAY_PIN,HIGH);
    }
    else if(Hum <= DEHUM_OFF)
    {
      digitalWrite(DEHUM_RELAY_PIN,LOW);
    }

    if(Hum <= HUM_ON)
    {
      digitalWrite(HUM_RELAY_PIN,HIGH);
    }
    else if(Hum >= HUM_OFF)
    {
      digitalWrite(HUM_RELAY_PIN,LOW);
    }

    lastDHT22Time = currentDHT22Time;
  }

  if(millis() - lastMotionTime >= NO_MOTION_TIME)
    goToSleep();

  delay(200); 
} 