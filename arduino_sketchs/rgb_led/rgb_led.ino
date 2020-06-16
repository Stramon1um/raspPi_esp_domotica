// Define RGB and BUZZER pins depending on the pinout.
#define red_pin 13
#define green_pin 14 
#define blue_pin 12


void setup(){
  
  // Configure LED PWM functionalities.
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  // Attach RGB pins.
  ledcAttachPin(red_pin, 0);
  ledcAttachPin(green_pin, 1);
  ledcAttachPin(blue_pin, 2);

  Serial.begin(115200);

}

void loop(){
  
  changeColor(255, 0, 255);

}

void changeColor(int R, int G, int B){
  // Display color pattern on the module.
  ledcWrite(0, 255 - R);
  ledcWrite(1, 255 - G);
  ledcWrite(2, 255 - B);

  // Define the rgb color variable and print it on the serial monitor.
  //String color = "rgb(" + String(R) + "," + String(G) + "," + String(B) + ")";
  //Serial.print("Color: " + color);

}


  
