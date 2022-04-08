#include <Arduino.h>
#include "HwMotor/HwMotor.h"
#include <string.h>

HwMotor motor1(&Serial1);
HwMotor motor2(&Serial2);
HwMotor motor3(&Serial3);

void setup() {
    Serial.begin(57600);
}

void loop() {
    int ret1 = motor1.update_telem();
    if (ret1 == 1) {
        //Serial.println("Could not read data from motor 1");
    } else if (ret1 == 2) {
        Serial.println("CRC check failed on motor 1");
    } //else if (ret1 == 0) {
        Serial.println("------------- Motor 1 ----------------");
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
        //delay(1000);
    //}
    int ret2 = motor2.update_telem();
    if (ret2 == 1) {
        //Serial.println("Could not read data from motor 2");
    } else if (ret2 == 2) {
        Serial.println("CRC check failed on motor 2");
    } //else if (ret2 == 0) {
        Serial.println("------------- Motor 2 ----------------");
        Serial.print("Input Throttle: \t");
        Serial.println(motor2.get_input_throttle(), DEC);
        Serial.print("Output Throttle:\t");
        Serial.println(motor2.get_output_throttle(), DEC);
        Serial.print("RPM:            \t");
        Serial.println(motor2.get_rpm(), DEC);
        Serial.print("Input Voltage:  \t");
        Serial.println(motor2.get_input_voltage(), DEC);
        Serial.print("Input Current:  \t");
        Serial.println(motor2.get_input_current(), DEC);
        Serial.print("Phase Current:  \t");
        Serial.println(motor2.get_phase_current(), DEC);
        Serial.print("MOS Temperature:\t");
        Serial.println(motor2.get_mos_temp(), DEC);
        Serial.print("Cap Temperature:\t");
        Serial.println(motor2.get_cap_temp(), DEC);
        Serial.print("Error Bitmask:  \t");
        Serial.println(motor2.get_error_bits(), DEC);
        //delay(1000);
    //}
    int ret3 = motor3.update_telem();
    if (ret3 == 1) {
        //Serial.println("Could not read data from motor 3");
    } else if (ret3 == 2) {
        Serial.println("CRC check failed on motor 3");
    } //else if (ret3 == 0) {
        Serial.println("------------- Motor 3 ----------------");
        Serial.print("Input Throttle: \t");
        Serial.println(motor3.get_input_throttle(), DEC);
        Serial.print("Output Throttle:\t");
        Serial.println(motor3.get_output_throttle(), DEC);
        Serial.print("RPM:            \t");
        Serial.println(motor3.get_rpm(), DEC);
        Serial.print("Input Voltage:  \t");
        Serial.println(motor3.get_input_voltage(), DEC);
        Serial.print("Input Current:  \t");
        Serial.println(motor3.get_input_current(), DEC);
        Serial.print("Phase Current:  \t");
        Serial.println(motor3.get_phase_current(), DEC);
        Serial.print("MOS Temperature:\t");
        Serial.println(motor3.get_mos_temp(), DEC);
        Serial.print("Cap Temperature:\t");
        Serial.println(motor3.get_cap_temp(), DEC);
        Serial.print("Error Bitmask:  \t");
        Serial.println(motor3.get_error_bits(), DEC);
        delay(1000);
    //}
}