// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  blink("brief");
  delay(1000);
  blink("brief");
  delay(1000);
  blink("long");
  delay(1000);
}

void blink(String blinkStyle) {
  if (blinkStyle == "brief") {
    blinkOnFor(figureOutGoodNumber());
  }
  else if (blinkStyle == "long") {
    blinkOnFor(1000);
  }
}

// Turns the light on for onDuration, 
// does not control off duration
void blinkOnFor(int onDuration) {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(onDuration);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
}


// This just tests returning and memaloc
// returns 100 hopefully
int figureOutGoodNumber() {
  // do math before returning a hard coded number
  int my_number = 0;
  my_number = my_number + 2;
  my_number = my_number * 50;
  return my_number;
}



