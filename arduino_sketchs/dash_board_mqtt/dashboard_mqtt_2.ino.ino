#include <WiFi.h>
#include <PubSubClient.h>

//#define RELAY 2 // relay connected to  GPIO0

const char* ssid = "TIM-23978315";
const char* password = "zpXDUrXFcMMAigFqdAaZ4ZwC";
const char* mqtt_server = "192.168.1.18";
const int buttonPin = 4;  // the number of the pushbutton pin
int buttonState = 0;
int stato_luce = 0;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

void setup(){
  //Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    //Serial.print ( "." );
  }

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //pinMode(RELAY,OUTPUT);
  pinMode(buttonPin, INPUT);
  //digitalWrite(RELAY, HIGH);
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
  
// Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '3') {
    ESP.restart();
    }
}
  
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Dash_Board")) {
      //Serial.println("connected");
      // Subscribe
      client.subscribe("relay_esp/Dash_Board");
    } else {
      //Serial.print("failed, rc=");
      //Serial.print(client.state());
      //Serial.println(" try again in 5 seconds");
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

  // read the state of the pushbutton value
  buttonState = digitalRead(buttonPin);
  //Serial.println(buttonState);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH
  /*
  if (buttonState == LOW) {
    // turn LED on
    //client.publish("relay_esp/SmartPlug_1", "0");
  } else {
    // turn LED off
    client.publish("relay_esp/SmartPlug_1", "1");
    stato = 1;
  }

  */
  if (buttonState == HIGH) {
    if (stato_luce == 0) {
      client.publish("relay_esp/Dash_Board", "1");
      stato_luce = 1;
      delay(1000);
    } else {
      client.publish("relay_esp/Dash_Board", "0");
      stato_luce = 0;
      delay(1000);
    }
  }
}
