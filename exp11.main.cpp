#include <Arduino.h>

// Thermistor and circuit parameters
const int THERMISTOR_PIN = A0; // ADC0 = GP26
const float BETA = 3950.0;     // Beta value from datasheet
const float R0 = 10000.0;      // Resistance at 25°C
const float T0 = 298.15;       // 25°C in Kelvin
const float R_FIXED = 10000.0; // Fixed resistor in voltage divider

void setup() {
  Serial.begin(9600);  // Initialize UART
  analogReadResolution(12); // Use 12-bit ADC (0-4095)
}

float readTemperature() {
  int adcValue = analogRead(THERMISTOR_PIN);  // Read analog value (0–4095)
  float voltage = (adcValue / 4095.0) * 3.3;   // Convert to voltage
  float resistance = R_FIXED * (3.3 / voltage - 1); // Calculate thermistor resistance

  // Apply Beta formula
  float tempK = 1.0 / ((1.0 / T0) + (1.0 / BETA) * log(resistance / R0));
  float tempC = tempK - 273.15; // Kelvin to Celsius
  return tempC;
}

void loop() {
  float temperature = readTemperature();
  Serial.printf("Temperature: %.2f C\r\n", temperature);
  delay(1000);  // Wait 1 second
}
