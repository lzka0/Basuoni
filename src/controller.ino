#include <Bluepad32.h>

extern GamepadPtr cntrl;

extern bool manual, autono, cali, basic;

extern int speed;

extern void pid();
extern void pid_reset();
extern void basic_auto();

void onConnected(GamepadPtr gp) {
  if(cntrl == nullptr)
    cntrl = gp;
}

void onDisconnected(GamepadPtr gp){
  if(cntrl == gp)
    cntrl = nullptr;
}

void manual_control() {

  if(cntrl->buttons() == 0x0001) { speed += 50; delay(100); }
  else if(cntrl->buttons() == 0x0008) { speed -= 50; delay(100); }
  if(speed < 0) speed = 0;
  if (speed > 255) speed = 255; 
  // else if(cntrl->buttons() == 0x0002) {
  //   manual = true;
  //   autono = false;
  // }
  // else if(cntrl->buttons() == 0x0004) {
  //   manual = false;
  //   autono = true;
  //   return;
  // }

  //  Serial.print("Up Arrow: "); Serial.println(cntrl->dpad() == 0x01);
  //  Serial.print("Down Arrow: "); Serial.println(cntrl->dpad() == 0x02);
  //  Serial.print("Right Arrow: "); Serial.println(cntrl->dpad() == 0x04);
  //  Serial.print("Left Arrow: "); Serial.println(cntrl->dpad() == 0x08);
  //  Serial.print("X Button: "); Serial.println(cntrl->buttons() == 0x0001);
  //  Serial.print("O Button: "); Serial.println(cntrl->buttons() == 0x0002);
  //  Serial.print("Tri Button: "); Serial.println(cntrl->buttons() == 0x0008);
  //  Serial.print("Square Button: "); Serial.println(cntrl->buttons() == 0x0004);

  
  if(cntrl->dpad() == 0x01) forward(speed);
  else if(cntrl->dpad() == 0x02) backward(speed);
  else if(cntrl->dpad() == 0x04) right(speed);
  else if(cntrl->dpad() == 0x08) left(speed);
  else if(cntrl->dpad() == 0x05) f_right(speed);
  else if(cntrl->dpad() == 0x09) f_left(speed);
  else if(cntrl->dpad() == 0x06) b_right(speed);
  else if(cntrl->dpad() == 0x0a) b_left(speed);
  else stop();
}

void controller_init() {
  Serial.begin(115200);
  BP32.setup(&onConnected, &onDisconnected);
  BP32.forgetBluetoothKeys();
  BP32.enableVirtualDevice(false);
  Serial.println("PS4 Controller : Connected");
}

void process() {
  bool status = BP32.update();
  bool connected = cntrl && cntrl->isConnected();

  if(status && connected){
    if(cntrl->buttons() == 0x0002) {
      Manual();
      manual_led();
      beep(2);
      manual = true;
      autono = false;
      cali = false;
      basic = false;
    }
    else if(cntrl->buttons() == 0x0004) {
      Calibration();
      cali_led();
      beep(2);
      manual = false;
      cali = true;
      autono = false;
      basic = false;
    }
    else if(cntrl->l1()) {
      Automatic();
      auto_led();
      beep(2);
      if(!autono) pid_reset();
      manual = false;
      cali = false;
      autono = true;
      basic = false;
    }
    else if(cntrl->r1()){
      Automatic();
      auto_led();
      beep(2);
      manual = false;
      cali = false;
      autono = false;
      basic = true;
    }
    if(cntrl->r2()) {
      print_values();
    }
  }

  if(cali) { stop(); calibrate(); cali = false; manual = true; }
  if(autono) {
    pid_2();
  }
  if(basic) basic_auto();
  if(manual) {
    if(!connected) stop();
    else if(status) manual_control();
  }
}
