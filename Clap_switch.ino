int sensor = 2;   // Connected to digital output of KY-038 sound sensor module
int led = 13;     // Connected to positive of LED
boolean is_on = false; // Tracks LED state

void setup() {
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int data = digitalRead(sensor);

  if (data == 1) {
    is_on = !is_on;
    digitalWrite(led, is_on ? HIGH : LOW);

    delay(300); // debounce: ignore further triggers briefly so one clap = one toggle
    while (digitalRead(sensor) == 1); // wait for the sound to actually stop
  }
}