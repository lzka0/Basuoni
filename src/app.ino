// extern float Kp, Ki, Kd;

// extern bool cali, manual, autono, consts;

// extern void manual_control();
// extern void pid();
// extern void calibrate();
// extern void basic_auto();
// extern BluetoothSerial BT;

// void application() {
//   if(BT.available() > 0){
//     char command = BT.read();
//     if(command == 'V') {
//       float newKp = BT.parseFloat();
//       float newKi = BT.parseFloat();
//       float newKd = BT.parseFloat();

//       Kp = newKp;
//       Ki = newKi;
//       Kd = newKd;

//       while(BT.available() > 0 && BT.read() != '\n') {}
//       BT.print(Kp); BT.print(" || "); BT.print(Ki); BT.print(" || "); BT.println(Kd);
//       autono = false;
//     }
//     else if(command == 'C') {
//       autono = false;
//       BT.println("Calibrating...");
//       calibrate();
//       BT.println("Done Calibrating");
//     }
//     else if(command == 'A') {
//       autono = true;
//       consts = false;
//     }
//     else if(command == 'Y') {
//       consts = true;
//       autono = false;
//     }
//     else if(command == 'S'){
//       autono = false;
//       consts = false;
//       BT.println("Stopping");;
//       stop();;
//     }
//   }
//   if(autono) pid();
//   if(consts) basic_auto();
// }