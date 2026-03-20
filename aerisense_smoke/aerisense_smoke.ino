#define MQ135_PIN A0
#define POT_PIN A1

#define MOSFET_PIN 5
#define GREEN_LED 6
#define RED_LED 7
#define BUZZER 8

const int FAN_MIN = 120;
const int FAN_MAX = 255;

void setup() {
  Serial.begin(9600);

  pinMode(MOSFET_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  int gasValue = analogRead(MQ135_PIN);
  int potValue = analogRead(POT_PIN);

  // Map potentiometer to fan speed
  int potSpeed = map(potValue, 0, 1023, FAN_MIN, FAN_MAX);
  int fanSpeed = potSpeed; // default fan speed

  Serial.print("Gas Level: "); Serial.println(gasValue);

  if (gasValue < 200) {
    // GOOD air
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);

    Serial.println("Air Quality: GOOD 😊");
    Serial.println("Threshold: <200 (Clean Air)");
  }
  else if (gasValue >= 200 && gasValue < 400) {
    // WARNING air
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, LOW);

    Serial.println("Air Quality: WARNING ⚠️");
    Serial.println("Threshold: 200–399 (Smoke / Polluted Air)");
  }
  else if (gasValue >= 400 && gasValue < 700) {
    // DANGEROUS
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    // Fan spikes but still allows gradual control with potentiometer
    fanSpeed = constrain(fanSpeed + 100, FAN_MIN, FAN_MAX); 

    Serial.println("Air Quality: DANGEROUS 🚨");
    Serial.println("Threshold: 400–699 (Heavy Smoke / Bad Air)");
  }
  else {
    // VERY DANGEROUS
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    fanSpeed = FAN_MAX; // maximum fan speed

    Serial.println("Air Quality: VERY DANGEROUS ☠️");
    Serial.println("Threshold: >=700 (Extremely Bad Air)");
  }

  analogWrite(MOSFET_PIN, fanSpeed);

  Serial.print("Pot Value: "); Serial.print(potValue);
  Serial.print(" | Fan Speed: "); Serial.println(fanSpeed);

  delay(200);
}