#include <ArduinoJson.h>

#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "WIFI name"; // Enter your WiFi name
const char *password = "password";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "Broker_IP";
const char *topic = "TOPIC_NAME";

const char *mqtt_username = "username";
const char *mqtt_password = "password";
const int mqtt_port = 1883;
const char *lotid="6125e25b5f69fb0021fd1254";
char json_char_array[100] = "";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 // Set software serial baud to 115200;
 Serial.begin(115200);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 // publish and subscribe
 
 client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
 char str[length+1];
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 int i=0;
  
for (i = 0; i < length; i++) {
      
    json_char_array[i] = ((char)payload[i]);    
     
}
Serial.println(json_char_array);

 Serial.println();
 Serial.println("-----------------------");
}

void loop() {
 client.loop();
}
