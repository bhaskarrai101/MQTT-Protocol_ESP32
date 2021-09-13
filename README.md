# MQTT-Protocol_ESP32
code for pubsub client for ESP32 Arduino Ide 

installations
1.Install Ardiuno ide
2. In Ardiuno Ide open file, then  goto preferences, then add https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json in Addition noards manager url, click ok.\
3.  
Esp32 PubSubClient program
1. if arduino put a error such as "Cannot open /dev/ttyUSB0:Permission denied" than you have to provide necessary permissionas follows:
	1. open cmd line type command---sudo su
					 cd /
					 cd dev
					 chown username ttyUSB0
2. if arduino put error such as "No directory found name PubSubClient" than follow the steps:
	1. Open Arduio ide
	2. Goto sketch
	3. Include Liberary
	4. Manage Libraries
	5. In Search type "PubSubClient" 
	6. Select one lib and press INSTALL
3. if you are unable to upload the code than press the EN botton on ESP32 while uploading the code

4. Code for PubSubCLient

~ First, we will import the WiFi and PubSubClient libraries. The ESP8266WiFi library can connect ESP32 to Wi-Fi networks, and the PubSubClient library can connect ESP32 to the MQTT server to publish messages and subscribe to topics.
#include <WiFi.h>
#include <PubSubClient.h>

~ Set the Wi-Fi name and password, as well as the MQTT server connection address and port, and set the topic to "esp32/test".
#// WiFi
#const char *ssid = "mousse"; // Enter your WiFi name
#const char *password = "qweqweqwe";  // Enter WiFi password

#// MQTT Broker
#const char *mqtt_broker = "broker.emqx.io";
#const char *topic = "esp32/test";
#const char *mqtt_username = "emqx";
#const char *mqtt_password = "public";
#const int mqtt_port = 1883;
	
~ Open a serial connection to output the results of the program and connect to the Wi-Fi network.
#// Set software serial baud to 115200;
#Serial.begin(115200);
#// connecting to a WiFi network
#WiFi.begin(ssid, password);
#while (WiFi.status() != WL_CONNECTED) {
#    delay(500);
#    Serial.println("Connecting to WiFi..");
#}

~ Use PubSubClient to connect to the public MQTT Broker.
#client.setServer(mqtt_broker, mqtt_port);
#client.setCallback(callback);
#while (!client.connected()) {
#    String client_id = "esp32-client-";
#    client_id += String(WiFi.macAddress());
#    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
#    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
#        Serial.println("Public emqx mqtt broker connected");
#    } else {
#        Serial.print("failed with state ");
#        Serial.print(client.state());
#        delay(2000);
#    }
#}

~ After the MQTT server is successfully connected, ESP32 will publish messages to the MQTT server of esp/test and subscribe to the topic messages of 

#// publish and subscribe
#client.publish(topic, "Hi EMQ X I'm ESP32 ^^");
#client.subscribe(topic);

~ Set the callback function to print the topic name to the serial port and print the message received from the esp32/test topic.
#void callback(char *topic, byte *payload, unsigned int length) {
#    Serial.print("Message arrived in topic: ");
#    Serial.println(topic);
#    Serial.print("Message:");
#    for (int i = 0; i < length; i++) {
#        Serial.print((char) payload[i]);
#    }
#    Serial.println();
#    Serial.println("-----------------------");
#}









