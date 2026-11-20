const int trigPin = 9;
const int echoPin = 10;
const int greenLedPin = 6;
const int redLedPin = 7;

unsigned long lastTriggerTime = 0;
const unsigned long cooldownMs = 4000; // Prevent rapid duplicate triggers

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}

long readDistanceCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return -1;
  return (duration * 0.034) / 2;
}

void triggerWelcome() {
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);
  delay(2500);
  digitalWrite(greenLedPin, LOW);
}

void triggerAlert() {
  digitalWrite(greenLedPin, LOW);
  // Rapid red LED blink to signal intruder alert without buzzer
  for (int i = 0; i < 6; i++) {
    digitalWrite(redLedPin, HIGH);
    delay(200);
    digitalWrite(redLedPin, LOW);
    delay(200);
  }
}

void loop() {
  long distance = readDistanceCm();

  if (distance >= 150 && distance <= 250) {
    if (millis() - lastTriggerTime > cooldownMs) {
      lastTriggerTime = millis();
      Serial.println(distance);
    }
  }

  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "WELCOME") {
      triggerWelcome();
    } else if (cmd == "ALERT") {
      triggerAlert();
    }
  }

  delay(120);
}


