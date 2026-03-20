#define MQ135_PIN A0
#define POT_PIN A1

#define MOSFET_PIN 5
#define GREEN_LED 6
#define RED_LED 7
#define BUZZER 8

const int FAN_MIN = 140;
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

  int potSpeed = map(potValue, 0, 1023, FAN_MIN, FAN_MAX);
  int fanSpeed = potSpeed;   // fan controlled by potentiometer normally

  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  if (gasValue < 200) {
    // GOOD
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);

    Serial.println("Air Quality: GOOD 😊");
  }

  else if (gasValue >= 200 && gasValue < 400) {
    // WARNING
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, LOW);

    Serial.println("Air Quality: WARNING ⚠️");
  }

  else {
    // DANGEROUS
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    fanSpeed = FAN_MAX;   // override → max speed spike

    Serial.println("Air Quality: DANGEROUS 🚨");
  }

  analogWrite(MOSFET_PIN, fanSpeed);

  Serial.print("Pot Value: ");
  Serial.print(potValue);
  Serial.print(" | Fan Speed: ");
  Serial.println(fanSpeed);

  delay(200);
}