#define BUZZ 25
#define MAN 26
#define AUT 27

void feature_init() {
  pinMode(BUZZ, OUTPUT);
  pinMode(MAN, OUTPUT);
  pinMode(AUT, OUTPUT);
  digitalWrite(BUZZ, 0);
  digitalWrite(MAN, 0);
  digitalWrite(AUT, 0);
}

void beep(const int& times) {
  for(int i = 0; i < times; ++i) {
    digitalWrite(BUZZ, 1);
    delay(100);
    digitalWrite(BUZZ, 0);
    if(i < times - 1) delay(100);
  }
}

void manual_led() {
  digitalWrite(AUT, 0);
  digitalWrite(MAN, 1);
}

void auto_led() {
  digitalWrite(MAN, 0);
  digitalWrite(AUT, 1);
}

void cali_led() {
  digitalWrite(MAN, 1);
  digitalWrite(AUT, 1);
  delay(500);
  digitalWrite(MAN, 0);
  digitalWrite(AUT, 0);
  delay(500);
  digitalWrite(MAN, 1);
  digitalWrite(AUT, 1);
}