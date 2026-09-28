#define RR 36
#define R 39
#define M 34
#define L 35
#define LL 32

// const int baseSpeed = 150;
// const int target = 2000;
// const char directions[5][100] = {"Far Right", "Right", "Middle", "Left", "FarLeft"}; 
// int sensorValues[5];
// int normalized_value[5];

// int bits[] = {1, 2, 4, 8, 16};

int maxValues[] = {0, 0, 0, 0, 0};
int minValues[] = {1023, 1023, 1023, 1023, 1023};

int irThreshold[5] = {40, 40, 40, 40, 40};

void sensors_init() {
  pinMode(RR, INPUT);
  pinMode(R, INPUT);
  pinMode(M, INPUT);
  pinMode(L, INPUT);
  pinMode(LL, INPUT);

  analogReadResolution(10);
}

void read_sensors_analog(int& rr, int& r, int& m, int& l, int& ll) {
  rr = analogRead(RR);
  r = analogRead(R);
  m = analogRead(M);
  l = analogRead(L);
  ll = analogRead(LL);
}

void read_sensors_digital(int& rr, int& r, int& m, int& l, int& ll) {
  rr = digitalRead(RR);
  r = digitalRead(R);
  m = digitalRead(M);
  l = digitalRead(L);
  ll = digitalRead(LL);
}

// bool check_fin() {
//   int sum = 0;
//   for(int i = 0; i < 5; ++i) {
//     if(analogRead(sensorPins[i]) < PWM) ++sum;
//   }
//   return !(sum);
// }

// bool pid(int& speedr, int& speedl, const int& Kp, const int& Ki, const int& Kd) {
//   long weightedSum = 0;
//   long sum = 0;
//   bool finish = true;
//   for (int i = 0; i < 5; i++) {
//     sensorValues[i] = analogRead(sensorPins[i]);

//     if(sensorValues[i] < PWM) finish = false;
    
//     weightedSum += (long)sensorValues[i] * (i * 1000);
//     sum += sensorValues[i];
//   }

//   if(finish) {
//     manual = true;
//     autono = false;
//     stop();
//     return autono;
//   }

//   int position = 2000;

//   if (sum > 50) {
//     position = weightedSum / sum;
//   }
  

//   int error = position - 2000;
//   int P = error;
//   I = I + error;
//   int D = error - lastError;
  
//   int pidOutput = (Kp * P) + (Ki * I) + (Kd * D);
//   lastError = error;



//   speedr = baseSpeed + pidOutput;
//   speedl = baseSpeed - pidOutput;

//   speedr = constrain(speedr, 0, 255);
//   speedl = constrain(speedl, 0, 255);
//   return autono;
// }


// void autonomous() {
//   //int r, l;

//   //int Kp = 2, Ki = 0, Kd = 0;
//   /*
//     int Kp = Serial.read();
//     int Ki = Serial.read();
//     int Kd = Serial.read();

//   */

//   //if(!(pid(r, l, Kp, Ki, Kd))) return;
//   //forward(r, l);

//   int fr, r, m, l, fl;
//   read_sensors(fr, r, m, l, fl);

//   bool state_far_right = fr > PWM;
//   bool state_right = r > PWM;
//   bool state_middle = m > PWM;
//   bool state_left = l > PWM;
//   bool state_far_left = fl > PWM;
//   int sum = 0;
//   if(state_middle) sum += 1;
//   if(state_right) sum += 2;
//   if(state_far_right) sum += 4;
//   if(state_left) sum += 8;
//   if(state_far_left) sum += 16;

//   if(sum == 1) Serial.print("MIDDLE ONLY");
//   else if(sum == 2) Serial.print("RIGHT");
//   else if(sum == 3) Serial.print("MIDDlE AND RIGHT");
//   else if(sum == 4) Serial.print("FAR RIGHT");
//   else if(sum == 5) Serial.print("FAR RIGHT AND MIDDLE");
//   else if(sum == 6) Serial.print("RIGHT AND FAR RIGHT");
//   else if(sum == 7) Serial.print("RIGHT MIDDLE AND FAR RIGHT");
//   else if(sum == 8) Serial.print("LEFT");
//   else if(sum == 9) Serial.print("LEFT and Middle");
//   else if(sum == 10) Serial.print("LEFT AND RIGHT");
//   else if(sum == 11) Serial.print("MIDDLE RIGHT AND LEFT");
//   else if(sum == 12) Serial.print("LEFT AND FAR RIGHT");
//   else if(sum == 13) Serial.print("LEFT FAR RIGHT AND MIDDLE");
//   else if(sum == 14) Serial.print("RIGHT FAR RIGHT AND LEFT");
//   else if(sum == 15) Serial.print("MIDDLE ONLY");
//   else if(sum == 16) Serial.print("FAR LEFT ONLY");
//   else if(!sum) Serial.print("NONE");
//   else Serial.print("OUT OF CASE");


//   if(sum == 1) forward(120);
//   else if(sum == 2) right(80);
//   else if(sum == 3) right(80);
//   else if(sum == 4) right(80);
//   else if(sum == 6) right(80);
//   else if(sum == 8) left(80);
//   else if(sum == 9) left(80);
//   else if(sum == 16) left(80);
//   else if(sum == 24) left(80);
//   else if(sum == 0) right(80);
//   else if(sum > 24) stop();

//   Serial.println();
// }

void calibrate() {
  stop();
  unsigned long start_time = millis();
  while(millis() - start_time < 5000){
    for(int i = 0; i < 5; ++i) {
      int value = analogRead(sensorPins[i]);
      if(value < minValues[i]) minValues[i] = value;
      if(value > maxValues[i]) maxValues[i] = value;
    }
  }

  for(int i = 0; i < 5; ++i) {
    irThreshold[i] = (maxValues[i] + minValues[i]) / 2;
  }

  for(int i : irThreshold) { Serial.print(i); Serial.print(" || "); }
  Serial.println();
}

void print_values() {
  for(const int& i : sensorPins) {
    Serial.print(analogRead(i)); Serial.print(" || ");
  }
  Serial.println();
}