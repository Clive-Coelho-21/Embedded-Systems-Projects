#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID   "------------" 
#define BLYNK_TEMPLATE_NAME "Automatic Humidifier Dehumidifier"
#define BLYNK_AUTH_TOKEN    "---------------------"

#include<WiFi.h>
#include<BlynkSimpleEsp32.h>
#include<DHT.h>

const char* SSID     = "------"; 
const char* Password = "-------";

#define DHT22_PIN        23
#define DEHUM_RELAY_PIN  4
#define HUM_RELAY_PIN    5

#define VP_AUTO          V0
#define VP_TEMP          V1
#define VP_HUM           V2
#define VP_DEHUM_PWR     V3
#define VP_HUM_PWR       V4

const float DEHUM_ON   = 70.0F; 
const float DEHUM_OFF  = 65.0F;
const float HUM_ON     = 30.0F;
const float HUM_OFF    = 35.0F;

DHT dht22(DHT22_PIN,DHT22);
BlynkTimer timer; 

int AutoState   = 0;
int DehumState  = 0;
int HumState    = 0;

void setup() 
{
  Serial.begin(115200);
  delay(500);

  dht22.begin();
  
  pinMode(DEHUM_RELAY_PIN,OUTPUT);
  pinMode(HUM_RELAY_PIN,OUTPUT);
  digitalWrite(DEHUM_RELAY_PIN,LOW);
  digitalWrite(HUM_RELAY_PIN,LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN,SSID,Password);
  timer.setInterval(2000L,SensorData); 
}

void loop() 
{
  Blynk.run();
  timer.run();
} 

void SyncRelays()
{
  if(AutoState)
  {
    digitalWrite(DEHUM_RELAY_PIN,LOW);
    digitalWrite(HUM_RELAY_PIN,LOW);
  }
  else
  {
    if(DehumState)
      digitalWrite(DEHUM_RELAY_PIN,HIGH);
    else
      digitalWrite(DEHUM_RELAY_PIN,LOW);

    if(HumState)
      digitalWrite(HUM_RELAY_PIN,HIGH);
    else
      digitalWrite(HUM_RELAY_PIN,LOW);
  }
}

void SensorData()
{
  float Hum = dht22.readHumidity();
  float TempC = dht22.readTemperature();

  if(isnan(Hum) || isnan(TempC)) 
  {
    Serial.println("Failed to read DHT22 Sensor!");
    if(AutoState)
    {
      digitalWrite(DEHUM_RELAY_PIN,LOW);
      digitalWrite(HUM_RELAY_PIN,LOW);
    }
    Blynk.virtualWrite(VP_HUM,0);
    Blynk.virtualWrite(VP_TEMP,0);
  } 
  else 
  {
    Serial.print("Humidity: ");
    Serial.print(Hum);
    Serial.println("%");
    Blynk.virtualWrite(VP_HUM,Hum);
    
    Serial.print("Temperature: ");
    Serial.print(TempC);
    Serial.println("*C");
    Blynk.virtualWrite(VP_TEMP,TempC);
  }

  if(AutoState)
  {
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
  }
}

BLYNK_WRITE(VP_AUTO)
{
  AutoState = param.asInt();
  if(AutoState)
  {
    Serial.println("Auto Mode");
    Blynk.virtualWrite(VP_DEHUM_PWR,0);
    Blynk.virtualWrite(VP_HUM_PWR,0);
  }
  else
    Serial.println("Manual Mode");
  SyncRelays(); 
}

BLYNK_WRITE(VP_DEHUM_PWR)
{
  if(AutoState) 
    return; 

  DehumState = param.asInt();
  if(DehumState)
    Serial.println("Dehumidifier ON");
  else
    Serial.println("Dehumidifier OFF");

  if(!AutoState && DehumState)
    digitalWrite(DEHUM_RELAY_PIN,HIGH);
  else if(!AutoState && !DehumState)
    digitalWrite(DEHUM_RELAY_PIN,LOW);
}

BLYNK_WRITE(VP_HUM_PWR)
{
  if(AutoState) 
    return; 

  HumState = param.asInt();
  if(HumState)
    Serial.println("Humidifier ON");
  else
    Serial.println("Humidifier OFF");

  if(!AutoState && HumState)
    digitalWrite(HUM_RELAY_PIN,HIGH);
  else if(!AutoState && !HumState)
    digitalWrite(HUM_RELAY_PIN,LOW);
}