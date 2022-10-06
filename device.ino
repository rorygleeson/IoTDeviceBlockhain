#include "secrets.h"
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <HTTPClient.h>



WiFiClientSecure net = WiFiClientSecure();

//String for storing server response
String response = "";
String tokenBalance = "";

//JSON document
DynamicJsonDocument doc(2048);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  Serial.println(" ");
  Serial.println("Connected to Wi-Fi !!");


  
 
  
  
}




void setup() {
  Serial.begin(9600);
  Serial.println(" ");
  connectAWS();
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Setup done  !");

}

void loop() {
  Serial.println("In loop, flash LED !");
  //Initiate HTTP client
  HTTPClient http;
  String request = "https://api-testnet.bscscan.com/api?module=account&action=balance&address=0x99999&apikey= 9999999";
  Serial.println("send request!");
  Serial.println(request);

  
  //Start the request
  http.begin(request);
  //Use HTTP GET request
  http.GET();
  //Response from server
  response = http.getString();


  Serial.println("Response is");
  Serial.println(response);
  
  //Parse JSON, read error if any
  DeserializationError error = deserializeJson(doc, response);
  if(error) {
     Serial.println(F("deserializeJson() failed: "));
     Serial.println(error.f_str());
     return;
  }

  tokenBalance = doc["result"].as<char*>();
  Serial.println("Token Balance is");
  Serial.println(tokenBalance);
  

  
  //Close connection  
  http.end();
  //Wait two seconds for next joke
  delay(2000);

  
  // flashLed();                    
}




void flashLed() {
  Serial.println("In flash LED !");

  for (int i = 0; i <= 5; i++) {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   

}
                   
  
}



