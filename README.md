# Clap Switch (Sound-Activated LED)

A simple Arduino project that uses a KY-038 sound sensor module to toggle an LED whenever a clap or sufficiently loud sound is detected.

## Features

- Sound-triggered LED control.
- Each detected sound event toggles the LED state.
- A short debounce delay helps prevent one clap from causing multiple toggles.
- Uses the KY-038 module's digital output.

## Components

- Arduino Uno or compatible board
- KY-038 sound sensor module
- LED (or the Arduino Uno built-in LED)
- Current-limiting resistor for an external LED (typically 220–330 Ω)
- Jumper wires and breadboard

## Wiring

| Component | Arduino connection |
|---|---|
| KY-038 VCC | 5V (verify your module's voltage requirement) |
| KY-038 GND | GND |
| KY-038 DO | D2 |
| LED anode | D13 (or external LED through a current-limiting resistor) |
| LED cathode | GND |

The sketch uses Arduino pin 13, which is connected to the built-in LED on many Arduino Uno boards. If you use an external LED, connect it with a suitable series resistor.

## How it works

1. The KY-038 detects sound and presents a digital signal on its `DO` pin.
2. The Arduino reads the sensor signal on digital pin 2.
3. When the signal is HIGH, the sketch reverses the stored LED state.
4. The LED is updated to match the new state.
5. A 300 ms delay reduces repeated triggering from the same clap, and the sketch waits for the sensor output to return LOW before accepting another event.

The sensor module's onboard potentiometer adjusts its sound-detection threshold. Adjust it gradually while observing the digital output and serial-free LED behavior.

## Uploading the sketch

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Connect your Arduino board over USB.
3. Open `Clap_switch.ino`.
4. Select the correct board under **Tools → Board**.
5. Select the correct port under **Tools → Port**.
6. Click **Verify**, then **Upload**.
7. Adjust the KY-038 potentiometer until claps reliably trigger the LED without excessive false detections.

No third-party Arduino libraries are required.

## Configuration

The pin assignments are declared at the beginning of the sketch:

```cpp
int sensor = 2;
int led = 13;
```

Change these values if your wiring uses different pins. The debounce interval is controlled by:

```cpp
delay(300);
```

Increase the delay if one clap triggers more than once. Decrease it if you need faster repeated clap detection, while checking for false or duplicate triggers.

## Troubleshooting

| Issue | What to check |
|---|---|
| LED never changes | Confirm KY-038 VCC, GND, and DO wiring; verify the threshold potentiometer setting. |
| LED toggles continuously | Reduce sensor sensitivity by adjusting the potentiometer; check for background noise or unstable power. |
| One clap toggles more than once | Increase the debounce delay and ensure the sensor output returns LOW between events. |
| External LED does not light | Check LED polarity, pin assignment, and the series resistor. |

## Limitations

- The sketch relies on the KY-038 digital output and its onboard comparator threshold.
- It does not distinguish claps from other loud sounds.
- Detection reliability depends on sensor sensitivity, distance, room acoustics, and background noise.
- The blocking delay and wait-for-LOW loop pause other sketch activity while handling an event.

## Possible improvements

- Replace blocking delays with a non-blocking `millis()` state machine.
- Add serial diagnostics for sensor events.
- Add a configurable lockout interval and more robust event filtering.
- Use a microphone/amplifier with signal processing if clap recognition, rather than general sound detection, is required.

## License

Released under the MIT License. See [LICENSE](LICENSE).
