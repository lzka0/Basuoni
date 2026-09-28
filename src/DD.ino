#include <Bluepad32.h>
#include <LiquidCrystal_I2C.h>
//#include "BluetoothSerial.h"

//BluetoothSerial BT;

LiquidCrystal_I2C lcd(0x27, 20, 4);

int lastError = 0;

int lastMove = 0;

bool autono = false, manual = true, cali = false, basic = false;

float Kp = 40, Ki = 0, Kd = 20;

const int sensorPins[] = {32, 35, 34, 39, 36}; // left to right

int P = 0, I = 0, D = 0;
extern int irThreshold[5];


int base_speed = 80;

// Set to false if your line reads LOWER than the floor on the sensors
const bool LINE_IS_HIGH = true;
const bool PID_DEBUG = false;

// from auto.ino (filled by calibrate())
extern int minValues[5];
extern int maxValues[5];

const unsigned long LOST_COAST_MS = 120;  // drive straight through short gaps
const int RECOVER_SPEED = 70;             // pivot speed when the line is really lost

static float pidLastError = 0;
static float pidIntegral = 0;
static float lastDir = 0;                 // +1 = line last seen on the right, -1 = left
static bool wasLost = false;
static unsigned long lostSince = 0;

void pid_reset() {
  pidLastError = 0;
  pidIntegral = 0;
  lastDir = 0;
  wasLost = false;
}

void pid() {
  const float weights[5] = {-2, -1, 0, 1, 2};
  float sum = 0, weighted = 0;
  int strong = 0;

  for (int i = 0; i < 5; ++i) {
    int v = analogRead(sensorPins[i]);

    int lo = minValues[i], hi = maxValues[i];
    if (hi - lo < 100) { lo = 0; hi = 1023; }
    float n = (float)(v - lo) / (float)(hi - lo);
    if (!LINE_IS_HIGH) n = 1.0f - n;
    n = constrain(n, 0.0f, 1.0f);

    if (n > 0.5f) ++strong;
    if (n < 0.3f) n = 0;

    sum += n;
    weighted += n * weights[i];
  }

  if (strong == 5) {
    stop();
    return;
  }

  if (sum < 0.3f) {
    if (!wasLost) { wasLost = true; lostSince = millis(); }

    if (lastDir == 0) { stop(); return; }             

    if (millis() - lostSince < LOST_COAST_MS) {          
      setMotors(base_speed, base_speed);
    } else {                                      
      setMotors((int)(lastDir * RECOVER_SPEED), (int)(-lastDir * RECOVER_SPEED));
    }
    return;
  }

  float error = weighted / sum;
  if (fabs(error) > 0.3f) lastDir = (error > 0) ? 1.0f : -1.0f;

  if (wasLost) {                 
    pidLastError = error;
    wasLost = false;
  }

  pidIntegral = constrain(pidIntegral + error, -50.0f, 50.0f);
  float derivative = error - pidLastError;
  pidLastError = error;

  int correction = (int)(Kp * error + Ki * pidIntegral + Kd * derivative);

  if (PID_DEBUG) {
    Serial.print(error); Serial.print(" | L="); Serial.print(base_speed + correction);
    Serial.print(" R="); Serial.println(base_speed - correction);
  }

  setMotors(base_speed + correction, base_speed - correction);
}


void pid_2() {
    const float weights[5] = {-2, -1, 0, 1, 2};

    int sensors[5];
    read_sensors_digital( sensors[0], sensors[1], sensors[2], sensors[3], sensors[4] );

    float sum = 0;
    float weighted = 0;
    int active = 0;

    // LOW = line detected
    for (int i = 0; i < 5; i++) {
        if (sensors[i] == LOW) {
            sum += 1.0;
            weighted += weights[i];
            active++;
        }
    }

    // All 5 sensors on line
    if (active == 5) {
        stop();
        return;
    }

    // No sensor sees the line
    if (active == 0) {
        if (!wasLost) {
            wasLost = true;
            lostSince = millis();
        }

        if (lastDir == 0) {
            stop();
            return;
        }

        if (millis() - lostSince < LOST_COAST_MS) {
            setMotors(base_speed, base_speed);
        }

        else {
            setMotors( (int)(lastDir * RECOVER_SPEED), (int)(-lastDir * RECOVER_SPEED) );
        }
        return;
    }

    float error = weighted / sum;

    if (fabs(error) > 0.3f) {
        lastDir = (error > 0) ? 1.0f : -1.0f;
    }

    if (wasLost) {
        pidLastError = error;
        wasLost = false;
    }

    pidIntegral = constrain( pidIntegral + error, -50.0f, 50.0f );

    float derivative = error - pidLastError;
    pidLastError = error;

    int correction =
        (int)(Kp * error +
              Ki * pidIntegral +
              Kd * derivative);

    if (PID_DEBUG) {
        Serial.print(error);
        Serial.print(" | L=");
        Serial.print(base_speed + correction);
        Serial.print(" R=");
        Serial.println(base_speed - correction);
    }

    setMotors(
        base_speed + correction,
        base_speed - correction
    );
}


void basic_auto() {
  int rr, r, m, l, ll;
  read_sensors_digital(rr, r, m, l, ll);
  bool state_fr = !rr ;
  bool state_r = !r ;
  bool state_m = !m ;
  bool state_l = !l ;
  bool state_ll = !ll;
  
  if(m && !r && !l && !ll && !rr ){
    forward(100);
    lastMove = 0;
  } 
  else if(m && r && l && !ll && !rr ) {
    forward(100);
    lastMove = 0;
  }
  else if(m && r && !l && !ll && !rr ) {
    right(100);
    lastMove = 1;
  }
  else if(!m && !r && !l && !ll && rr ){
    right(100);
    lastMove = 1;
  }
  else if(!m && r && !l && !ll && rr ){
    right(100);
    lastMove = 1;
  } 
  else if(m && r && !l && !ll && rr ){
    right(100);
    lastMove = 1;
  }
  else if(m && !r && l && !ll && !rr ){
    left(100);
    lastMove = 2;
  }
  else if(!m && !r && l && ll && !rr ){
    left(100);
    lastMove = 2;
  }
  else if(m && !r && l && ll && !rr ){
    left(100);
    lastMove = 2;
  } 
  else if(!m && !r && !l && ll && !rr ){
    left(100);
    lastMove = 2;
  }
  else if(!m && !r && !l && !ll && !rr){
    backward(100);
  }
  else if(m && r && l && ll && rr ) stop();
}

int speed = 115;

GamepadPtr cntrl;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  feature_init();
  //BT.begin("Basuoni");
  motors_init();
  sensors_init();
  controller_init();
  Welcome();
  delay(1000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  process();
  delay(2);
}

