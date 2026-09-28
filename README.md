# Basuoni
ESP32 line-following robot with PS4 gamepad control, PID line tracking, and an I2C LCD status display. Built for ZagEng's Deep Dive 2026.


# BASUONI: Line-Following & Gamepad-Controlled Robot 🤖

An ESP32-based robot that can be driven manually with a PS4 controller or left to follow a line on its own using PID control. It was built as the hands-on project for **Deep Dive 2026**, a month-long course run by the **ZagEng** community, where we went from the basics to a working robot in about four weeks.

## Features

- **Manual mode:** drive with the PS4 D-pad (8 directions) and adjust speed on the fly.
- **PID line following:** analog IR readings, weighted error, and P/I/D correction, with:
  - sensor normalization from calibration data
  - short "coast" through small gaps in the line
  - lost-line recovery that pivots toward the side where the line was last seen
  - automatic stop when all sensors see the line (finish marker)
- **Basic line following:** a simple rule-based digital-sensor mode, useful as a baseline to compare against PID.
- **Sensor calibration:** a 5-second sweep records min/max per sensor.
- **Feedback:** a 20x4 I2C LCD shows the current mode, LEDs indicate manual/auto/calibration, and a buzzer confirms mode changes.

## Hardware

| Part | Notes |
|---|---|
| ESP32 dev board | Main controller (Bluetooth via Bluepad32) |
| Dual H-bridge motor driver | IN1–IN4 on GPIO 4, 16, 17, 18; PWM enable on GPIO 19, 23 |
| 2 DC motors + chassis | Differential drive |
| 5x IR line sensors | GPIO 32, 35, 34, 39, 36 (left to right) |
| 20x4 I2C LCD | Address `0x27` |
| Buzzer + 2 LEDs | GPIO 25 (buzzer), 26 (manual LED), 27 (auto LED) |
| PS4 controller | Paired over Bluetooth |

## Controls

| Input | Action |
|---|---|
| D-pad | Drive (forward, back, turn, and diagonals) |
| ✕ / △ | Speed +50 / −50 |
| ○ | Manual mode |
| □ | Calibration mode |
| L1 | PID line-following mode |
| R1 | Basic line-following mode |
| R2 | Print raw sensor values to Serial |

## Code Structure

| File | Purpose |
|---|---|
| `DD.ino` | Main sketch: setup/loop, PID line-following logic, basic auto mode |
| `controller.ino` | PS4 gamepad handling, mode switching, manual driving |
| `movement_functions.ino` | Motor driver functions (forward, turn, `setMotors`, stop) |
| `auto.ino` | Sensor pins/reading, calibration |
| `LCD.ino` | LCD status screens |
| `Buzz.ino` | Buzzer and LED helpers |
| `app.ino` | Early Bluetooth-serial tuning app (kept commented out for reference) |

## Getting Started

1. Install the **ESP32 board package** and the **Bluepad32** and **LiquidCrystal_I2C** libraries.
2. Put all `.ino` files in a single folder named `DD` (Arduino requires the folder name to match the main sketch).
3. Wire the hardware as in the table above.
4. Upload to the ESP32, then pair your PS4 controller.
5. Press **□** to calibrate: sweep the sensors over the line and the floor for 5 seconds.
6. Press **L1** to start PID line following.

## Tuning

PID gains and speeds are at the top of `DD.ino`:

```cpp
float Kp = 40, Ki = 0, Kd = 20;
int base_speed = 80;
const bool LINE_IS_HIGH = true;  // flip if your line reads lower than the floor
```

## What We Learned

Over the month of Deep Dive 2026 we covered embedded programming on the ESP32, motor control with PWM and H-bridges, reading and calibrating analog sensors, PID control, Bluetooth gamepad input, and working as a team on a real hardware project.

## Credits

Built by the participants of **Deep Dive 2026** with the **ZagEng** community.
