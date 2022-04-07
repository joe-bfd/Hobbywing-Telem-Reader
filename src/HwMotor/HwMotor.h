#ifndef HWMOTOR_H
#define HWMOTOR_H
#include <Arduino.h>

class HwMotor {
    private:
        HardwareSerial *ser;
        uint8_t telem[24];
        float input_throttle;
        float output_throttle;
        uint32_t rpm;
        float input_voltage;
        float input_current;
        float phase_current;
        uint32_t mos_temp;
        uint32_t cap_temp;
        uint32_t error_bits;
        uint16_t tempTable[209];
        
        uint8_t read_telem();
        void parse_telem();
        uint8_t verify_telem();
        void initialize_temp_table();
        uint32_t get_temp(uint8_t raw_temp);
    public:
        HwMotor(HardwareSerial *ser);
        uint8_t update_telem();
        float get_input_throttle();
        float get_output_throttle();
        uint32_t get_rpm();
        float get_input_voltage();
        float get_input_current();
        float get_phase_current();
        uint32_t get_mos_temp();
        uint32_t get_cap_temp();
        uint32_t get_error_bits();
};

#endif