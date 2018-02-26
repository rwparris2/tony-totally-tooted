/*
  sensor information from https://www.jayconsystems.com/tutorials/gas-sensor-tutorial/
  current_resistance / resistance_in_fresh_air  = 4.4 ppm
*/

#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

const int GAS_SENSOR_PIN = A0;
const float m = -0.318; // slope
const float b = 1.133; // y-intercept

float resistance_in_fresh_air = 13.70;

void setup() {
  Serial.begin(9600);
  Serial.println();

  init_display();
}

void loop() {
  double ppm = getGasPPM();
  double percentage = ppm / 10000; //Convert to percentage

  Serial.print(ppm);
  Serial.print(" - (");
  Serial.print(percentage); //Load screen buffer with percentage value
  Serial.println("%)"); //Load screen buffer with "%"

  oled.setFont(font8x8);
  oled.setTextXY(1, 0);
  oled.putString(String(ppm) + " ppm");

  //  display.drawString(10, 128, String(ppm));
  //  display.display();

  delay(1000); //Wait 1 second
}

void init_display() {
  Wire.begin();
  oled.init();                      // Initialze SSD1306 OLED display
  oled.clearDisplay();              // Clear screen
  oled.setTextXY(0, 0);             // Set cursor position, start of line 0
  oled.setFont(font5x7);            // Set font type (default 8x8)
  oled.putString("TONY TOTALLY TOOTED");
}

//float calculateFreshAirValue() {
//  float sensor_volt; //Define variable for sensor voltage
//  float RS_air; //Define variable for sensor resistance
//  float R0; //Define variable for R0
//  float sensorValue; //Define variable for analog readings
//  for (int x = 0 ; x < 500 ; x++) //Start for loop
//  {
//    sensorValue = sensorValue + analogRead(A0); //Add analog values of sensor 500 times
//  }
//  sensorValue = sensorValue / 500.0; //Take average of readings
//  sensor_volt = sensorValue * (5.0 / 1023.0); //Convert average to voltage
//  RS_air = ((5.0 * 10.0) / sensor_volt) - 10.0; //Calculate RS in fresh air
//  R0 = RS_air / 4.4; //Calculate R0
//
//  Serial.print("R0 = "); //Display "R0"
//  Serial.println(R0); //Display value of R0
//  delay(1000); //Wait 1 second
//}

/**
   Get gas parts per million
*/
double getGasPPM() {
  float current_sensor_value = getSmoothedSensorValue();
  float current_sensor_voltage = convertAnalogSensorValueToVoltage(current_sensor_value);
  float current_sensor_resistance = ((5.0 * 10.0) / current_sensor_voltage) - 10.0; // all of these numbers are ~~magic~~
  float ratio = current_sensor_resistance / resistance_in_fresh_air;
  double ppm_log = (log10(ratio) - b) / m; //Get ppm value in linear scale according to the the ratio value
  double ppm = pow(10, ppm_log); //Convert ppm value to log scale
  return ppm;
}

/**
   Sample sensor x times and take the average value
*/
float getSmoothedSensorValue() {
  float sensor_value;
  for (int i = 0; i < 500; i++) {
    sensor_value = sensor_value + analogRead(GAS_SENSOR_PIN);
  }
  sensor_value = sensor_value / 500;
  return sensor_value;
}

/**
   Converts raw sensor value to voltage value
*/
float convertAnalogSensorValueToVoltage(float sensor_value) {
  //  https://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
  const float min_value = 5.0;
  const float max_value = 1023.0;
  return sensor_value * (5.0 / 1023.0);
}

