#include <Arduino.h>
#include "HwMotor/HwMotor.h"
#include <string.h>

HwMotor motor1(&Serial1);

void setup() {
    Serial.begin(57600);
}

void loop() {
    int ret = motor1.update_telem();
    if (ret == 1) {
        Serial.println("Could not read data from motor");
    } else if (ret == 2) {
        Serial.println("CRC check failed");
    } else if (ret == 0) {
        Serial.println("--------------------------------------");
        Serial.print("Input Throttle: \t");
        Serial.println(motor1.get_input_throttle(), DEC);
        Serial.print("Output Throttle:\t");
        Serial.println(motor1.get_output_throttle(), DEC);
        Serial.print("RPM:            \t");
        Serial.println(motor1.get_rpm(), DEC);
        Serial.print("Input Voltage:  \t");
        Serial.println(motor1.get_input_voltage(), DEC);
        Serial.print("Input Current:  \t");
        Serial.println(motor1.get_input_current(), DEC);
        Serial.print("Phase Current:  \t");
        Serial.println(motor1.get_phase_current(), DEC);
        Serial.print("MOS Temperature:\t");
        Serial.println(motor1.get_mos_temp(), DEC);
        Serial.print("Cap Temperature:\t");
        Serial.println(motor1.get_cap_temp(), DEC);
        Serial.print("Error Bitmask:  \t");
        Serial.println(motor1.get_error_bits(), DEC);
        delay(1000);
    }
}