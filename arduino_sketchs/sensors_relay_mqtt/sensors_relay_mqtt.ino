#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

// Replace the next variables with your SSID/Password combination
const char* ssid = "********";
const char* password = "**********";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "192.168.1.****";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//uncomment the following lines if you're using SPI
/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI
float temperature = 0;
float humidity = 0;
float pressure = 0;
int elevation = 250;
float sealevel_P = 0;
const int relay_pin = 26;

// LED Pin
//const int ledPin = 4;

void setup() {
  Serial.begin(115200);
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  //status = bme.begin();  
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //pinMode(ledPin, OUTPUT);
  pinMode(relay_pin, OUTPUT);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

// Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '0') {
    digitalWrite(relay_pin, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.println("relay_pin -> LOW");
    //relayState = LOW;
  } else if ((char)payload[0] == '1') {
    digitalWrite(relay_pin, HIGH);  // Turn the LED off by making the voltage HIGH
    Serial.println("relay_pin -> HIGH");
    //relayState = HIGH;
    //EEPROM.write(0, relayState);    // Write state to EEPROM
    //EEPROM.commit();
  }
}
  
  
  
  
  
  
  
  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  //if (String(topic) == "esp32/output") {
    //Serial.print("Changing output to ");
    //if(messageTemp == "on"){
      //Serial.println("on");
      //digitalWrite(relay, HIGH);
      //}
      //else if(messageTemp == "off"){
      //Serial.println("off");
      //digitalWrite(relay, LOW);
      //}
    //}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/relay");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 300000) {
    lastMsg = now;
    
    // Temperature in Celsius
    temperature = bme.readTemperature();   
    // Uncomment the next line to set temperature in Fahrenheit 
    // (and comment the previous temperature line)
    //temperature = 1.8 * bme.readTemperature() + 32; // Temperature in Fahrenheit
    
    // Convert the value to a char array
    char tempString[8];
    dtostrf(temperature, 1, 2, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    client.publish("esp32/temperature", tempString);

    humidity = bme.readHumidity();
    
    // Convert the value to a char array
    char humString[8];
    dtostrf(humidity, 1, 2, humString);
    Serial.print("Humidity: ");
    Serial.println(humString);
    client.publish("esp32/humidity", humString);

    pressure = bme.readPressure();
    sealevel_P = (((pressure)/pow((1-((float)(elevation))/44330), 5.255))/100.0);

    // Convert the value to a char array
    char pressString[8];
    dtostrf(sealevel_P, 1, 2, pressString);
    Serial.print("Pressure: ");
    Serial.println(pressString);
    client.publish("esp32/pressure", pressString);
  }
}
