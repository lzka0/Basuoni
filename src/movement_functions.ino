#define IN1 4
#define IN2 16
#define IN3 17
#define IN4 18
#define EN1 19
#define EN2 23


void motors_init() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
} 

void setMotors(int leftSpeed, int rightSpeed) {
  leftSpeed  = constrain(leftSpeed,  -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  digitalWrite(IN1, leftSpeed < 0);
  digitalWrite(IN2, leftSpeed >= 0);
  digitalWrite(IN3, rightSpeed < 0);
  digitalWrite(IN4, rightSpeed >= 0);

  analogWrite(EN1, abs(leftSpeed));
  analogWrite(EN2, abs(rightSpeed));
}


void forward(const int& speed) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void forward(const int& speedr, const int& speedl) {
  analogWrite(EN1, speedr);
  analogWrite(EN2, speedl);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void backward(const int& speed) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}


void right(const int& speed) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void left(const int& speed) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void f_left(const int& speed) {
  analogWrite(EN1, speed/3);
  analogWrite(EN2, speed);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void f_right(const int& speed) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed/3);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void b_left(const int& speed) {
  analogWrite(EN1, speed/3);
  analogWrite(EN2, speed);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void b_right(const int& speed) {
  analogWrite(EN1, speed);
  analogWrite(EN2, speed/3);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void stop() {
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 1);
}