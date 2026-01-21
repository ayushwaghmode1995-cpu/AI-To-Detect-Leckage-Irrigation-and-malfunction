/ Define sensor pins
#define SENSOR1_PIN 13  // Sensor 1 (Upstream)
#define SENSOR2_PIN 12  // Sensor 2 (Middle)
#define SENSOR3_PIN 14  // Sensor 3 (Downstream)

// Define relay pin
#define RELAY_PIN 35 // Pin connected to the relay module

// Variables to count pulses
volatile int pulseCount1 = 0;
volatile int pulseCount2 = 0;
volatile int pulseCount3 = 0;

// Variables for flow rates
float flowRate1 = 0;
float flowRate2 = 0;
float flowRate3 = 0;

// Time interval for measurement
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // 1 second

// Leakage detection flag
bool leakageDetected = false;

// Difference threshold for leakage detection
const float leakageThreshold = 0.5; // Adjust based on your requirements (e.g., 0.5 L/min)

void IRAM_ATTR pulseCounter1() { pulseCount1++; }
void IRAM_ATTR pulseCounter2() { pulseCount2++; }
void IRAM_ATTR pulseCounter3() { pulseCount3++; }

void setup() {
  Serial.begin(115200);

  // Configure sensor pins as input
  pinMode(SENSOR1_PIN, INPUT_PULLUP);
  pinMode(SENSOR2_PIN, INPUT_PULLUP);
  pinMode(SENSOR3_PIN, INPUT_PULLUP);

  // Configure relay pin as output
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Turn off the solenoid valve initially (active low)

  // Attach interrupts for sensors
  attachInterrupt(digitalPinToInterrupt(SENSOR1_PIN), pulseCounter1, RISING);
  attachInterrupt(digitalPinToInterrupt(SENSOR2_PIN), pulseCounter2, RISING);
  attachInterrupt(digitalPinToInterrupt(SENSOR3_PIN), pulseCounter3, RISING);
}

void loop() {
  unsigned long currentMillis = millis();

  // Measure flow rate every second
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Calculate flow rates (adjust the formula based on your sensor's specs)
    flowRate1 = (pulseCount1 / 7.5); // Example: 7.5 pulses = 1 L/min
    flowRate2 = (pulseCount2 / 7.5);
    flowRate3 = (pulseCount3 / 7.5);

    // Reset pulse counts
    pulseCount1 = 0;
    pulseCount2 = 0;
    pulseCount3 = 0;

    // Print flow rates
    Serial.print("Flow Rate 1: ");
    Serial.print(flowRate1);
    Serial.println(" L/min");

    Serial.print("Flow Rate 2: ");
    Serial.print(flowRate2);
    Serial.println(" L/min");

    Serial.print("Flow Rate 3: ");
    Serial.print(flowRate3);
    Serial.println(" L/min");

    // Leakage detection logic with threshold
    leakageDetected = false; // Reset leakage flag
    if (abs(flowRate1 - flowRate2) > leakageThreshold && abs(flowRate1 - flowRate3) > leakageThreshold) {
      Serial.println("Leakage Detected: Upstream (Sensor 1)");
      leakageDetected = true;
    } else if (abs(flowRate2 - flowRate1) > leakageThreshold && abs(flowRate2 - flowRate3) > leakageThreshold) {
      Serial.println("Leakage Detected: Middle (Sensor 2)");
      leakageDetected = true;
    } else if (abs(flowRate3 - flowRate1) > leakageThreshold && abs(flowRate3 - flowRate2) > leakageThreshold) {
      Serial.println("Leakage Detected: Downstream (Sensor 3)");
      leakageDetected = true;
    } else {
      Serial.println("No Leakage Detected.");
    }

    // Relay control moved into the main detection block
    if (leakageDetected) {
      stopWaterFlow(); // Stop water flow immediately
    } else {
      resumeWaterFlow(); // Resume normal operation
    }

    Serial.println("--------------------");
  }
}

// Function to stop water flow
void stopWaterFlow() {
  digitalWrite(RELAY_PIN, LOW); // Activate the relay (active low)
  Serial.println("Water flow stopped due to leakage!");
}

// Function to resume normal water flow
void resumeWaterFlow() {
  digitalWrite(RELAY_PIN, HIGH); // Deactivate the relay (active low)
  Serial.println("Water flow normal.");
}