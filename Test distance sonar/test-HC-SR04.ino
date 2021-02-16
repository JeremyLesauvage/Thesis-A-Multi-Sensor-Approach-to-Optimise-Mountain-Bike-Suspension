const byte TRIGGER_PIN = 2; 
const byte ECHO_PIN = 3;    
const unsigned long MEASURE_TIMEOUT = 25000UL; // timeout 25ms = ~8m à 340m/s
const float SOUND_SPEED = 340.0 / 1000;

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
}
 
void loop() {
  digitalWrite(TRIGGER_PIN, HIGH); //send an HIGH impulse of 10µs
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT); //measure time between the impulse and the echo
  float distance_mm = measure / 2.0 * SOUND_SPEED;         //compute the distance
  Serial.println(distance_mm);
  delay(40);
}
