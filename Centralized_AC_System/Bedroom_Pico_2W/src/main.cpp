#include<WiFi.h>
#include<PubSubClient.h>
#include<DHT.h>
#include<ArduinoJson.h>
#include<IRremote.hpp>
#include"State.h"
#include"Lookup_Table.h"

#define DHT_PIN 14
#define TYPE DHT22
#define SEND_PIN 13

#define ADDRESS 0x88
#define REPEATS 1

const char* SSID     = "---------";
const char* Password = "---------";

const char* mqtt_broker = "------";
const char* User        = "------";
const char* Pass        = "------";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht22(DHT_PIN,TYPE);

unsigned long currenttime;
unsigned long lasttime1 = 0;
unsigned long lasttime2 = 0;

AC_State currentState = {"OFF","COOL","24","Medium",false,false,false};

void callback(char* topic, byte* message, unsigned int length);
void reconnect();

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  dht22.begin();
  IrSender.begin(SEND_PIN,true); 

  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID,Password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_broker,1883);
  client.setCallback(callback);
}

void loop() 
{
  if(!client.connected()) 
  {
    reconnect();
  } 
  client.loop();

  currenttime = millis();
  if(currenttime - lasttime2 > 1000)
  {
    char Heatbeat[] = "ALIVE";
    client.publish("Bedroom/Heartbeat",Heatbeat);

    lasttime2 = currenttime;
  }

  currenttime = millis();
  if(currenttime - lasttime1 > 2000)
  {
    float temp = dht22.readTemperature();
    float hum = dht22.readHumidity();

    if (isnan(hum) || isnan(temp)) 
    {
      Serial.println("Failed to read from DHT sensor!");
    }
    else
    {
      char tempString[8];
      dtostrf(temp,1,2,tempString);
      client.publish("Bedroom/Temperature",tempString);

      char humString[8];
      dtostrf(hum,1,2,humString);
      client.publish("Bedroom/Humidity",humString);
    }

    lasttime1 = currenttime;
  }
}

void callback(char* topic,byte* payload,unsigned int length) 
{
  DynamicJsonDocument doc(512);
  deserializeJson(doc,payload,length);
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);
  Serial.println("Message: ");
  serializeJsonPretty(doc,Serial);
  Serial.println();

  if(strcmp(topic,"Bedroom/Power") == 0) 
  {
    AC_State newState;
    newState.Power = doc["Power"].as<String>();
    newState.Mode  = doc["Mode"].as<String>();
    newState.Temp  = doc["Temp"].as<String>();
    newState.Fan_Speed = doc["Fan_Speed"].as<String>();
    newState.Swing = false;
    newState.Plasma = false;
    newState.Auto_Clean = false;
    
    if(!isStateChanged(newState)) 
      return;

    for(size_t i = 0; i < ToggleSize; i++)
    {
      if(strcmp(Toggle[i].Power,doc["Power"].as<const char*>()) == 0)
      {
        IrSender.sendLG(ADDRESS,Toggle[i].command,REPEATS);
        currentState = newState;
        return;
      }
    }
  }

  if(strcmp(topic,"Bedroom/LUT2") == 0) 
  {
    for(size_t i = 0;i < LUT2Size;i++)
    {
      const char* cmd = doc["str"];

      AC_State newState;
      newState.Power = currentState.Power;
      newState.Mode  = currentState.Mode;
      newState.Temp  = currentState.Temp;
      newState.Fan_Speed = currentState.Fan_Speed;
      if(strcmp("Swing ON",cmd) == 0)
        newState.Swing = true;
      else if(strcmp("Swing OFF",cmd) == 0)
        newState.Swing = false;

      if(strcmp("Plasma ON",cmd) == 0)
        newState.Plasma = true;
      else if(strcmp("Plasma OFF",cmd) == 0)
        newState.Plasma = false;

      if(strcmp("Start Autoclean",cmd) == 0)
        newState.Auto_Clean = true;
      else if(strcmp("Stop Autoclean",cmd) == 0)
        newState.Auto_Clean = false;

      if(!isStateChanged(newState)) 
        return;

      if(strcmp(LUT2[i].str,cmd) == 0)
      {
        IrSender.sendLG(ADDRESS,LUT2[i].command,REPEATS);
        currentState = newState;
        return;
      }
    } 
  }

  if(strcmp(topic,"Bedroom/LUT1") == 0) 
  {
    AC_State newState;
    newState.Power = doc["Power"].as<String>();
    newState.Mode = doc["Mode"].as<String>();
    newState.Temp = doc["Temp"].as<String>();
    newState.Fan_Speed = doc["Fan_Speed"].as<String>();
    newState.Swing = currentState.Swing;
    newState.Plasma = currentState.Plasma;
    newState.Auto_Clean = currentState.Auto_Clean;

    if(!isStateChanged(newState)) 
      return;

    for(size_t i = 0;i < LUT1Size ;i++) 
    {
      if(strcmp(LUT1[i].Mode,doc["Mode"].as<const char*>()) == 0 && strcmp(LUT1[i].Temp,doc["Temp"].as<const char*>()) == 0 && strcmp(LUT1[i].Fan_Speed,doc["Fan_Speed"].as<const char*>()) == 0)
      {
        IrSender.sendLG(ADDRESS,LUT1[i].command,REPEATS);
        currentState = newState;
        return;
      }
    }
  }
}


void reconnect() 
{
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    if(client.connect("Bedroom_AC",User,Pass)) 
    {
      Serial.println("Connected to MQTT Broker");
      client.subscribe("Bedroom/LUT1");
      client.subscribe("Bedroom/LUT2");
      client.subscribe("Bedroom/Power");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}
