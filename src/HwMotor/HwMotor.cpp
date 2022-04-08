#include "HwMotor.h"
#include <CRC.h>

HwMotor::HwMotor(HardwareSerial *ser) {
    this->ser = ser;
    ser->begin(19200);
    initialize_temp_table();
}

uint8_t HwMotor::update_telem() {
    if (read_telem()) {
        return 1;
    }
    if (verify_telem()) {
        return 2;
    }
    parse_telem();
    return 0;
}
float HwMotor::get_input_throttle() {
    return input_throttle;
}
float HwMotor::get_output_throttle() {
    return output_throttle;
}
uint32_t HwMotor::get_rpm() {
    return rpm;
}
float HwMotor::get_input_voltage() {
    return input_voltage;
}
float HwMotor::get_input_current() {
    return input_current;
}
float HwMotor::get_phase_current() {
    return phase_current;
}
uint32_t HwMotor::get_mos_temp() {
    return mos_temp;
}
uint32_t HwMotor::get_cap_temp() {
    return cap_temp;
}
uint32_t HwMotor::get_error_bits() {
    return error_bits;
}
uint8_t HwMotor::read_telem() {
    uint8_t nextByte;
    int c = 0;
    while (ser->read() != -1 && c++ < 1000) {
    }
    c = 0;
    do {
        if (ser->available() > 0) {
            nextByte = ser->read();
            //delay(1000);
        }
    } while (nextByte != 0x9b && c++ < 1000);
    if (c >= 1000) {
        return 1;
    }
    telem[0] = nextByte;
    for (int i = 1; i < 24; i++) {
        while(ser->available() < 1) {
        }
        telem[i] = ser->read();
        //Serial.println(telem[i], HEX);
    }
    //delay(3000);
    return 0;
}
uint8_t HwMotor::verify_telem() {
    uint16_t crc_calc;
    uint16_t crc_given;

    crc_calc = crc16(telem, 22, 0x8005, 0xffff, 0, true, true);
    crc_given = telem[23]<<8 | telem[22];
    if (crc_calc != crc_given) {
        return 1;
    }
    return 0;
}
void HwMotor::parse_telem() {
    uint16_t input_throttle_raw     = telem[6]  <<8 | telem[7];
    uint16_t output_throttle_raw     = telem[8]  <<8 | telem[9];
    uint16_t rpm_raw                = telem[10] <<8 | telem[11];
    uint16_t input_voltage_raw      = telem[12] <<8 | telem[13];
    int16_t input_current_raw      = telem[14] <<8 | telem[15];
    int16_t phase_current_raw      = telem[16] <<8 | telem[17];
    uint8_t  mos_temp_raw           = telem[18];
    uint8_t  cap_temp_raw           = telem[19];
    uint16_t error_bits_raw         = telem[20] <<8 | telem[21];

    input_throttle = (float)input_throttle_raw * 100.0f / 1024.0f;
    output_throttle = (float)output_throttle_raw * 100.0f / 1024.0f;
    rpm = rpm_raw;
    input_voltage = (float)input_voltage_raw / 10.0;
    input_current = (float)input_current_raw / 64.0;
    phase_current = (float)phase_current_raw / 64.0;
    mos_temp = get_temp(mos_temp_raw);
    cap_temp = get_temp(cap_temp_raw);
    error_bits = error_bits_raw;
}
uint32_t HwMotor::get_temp(uint8_t raw_temp) {
    return tempTable[raw_temp-33];
}
void HwMotor::initialize_temp_table() {
    tempTable[0]   = 129;
    tempTable[1]   = 128;
    tempTable[2]   = 127;
    tempTable[3]   = 126;
    tempTable[4]   = 125;
    tempTable[5]   = 124;
    tempTable[6]   = 122;
    tempTable[7]   = 121;
    tempTable[8]   = 120;
    tempTable[9]   = 119;
    tempTable[10]  = 118;
    tempTable[11]  = 117;
    tempTable[12]  = 116;
    tempTable[13]  = 115;
    tempTable[14]  = 114;
    tempTable[15]  = 113;
    tempTable[16]  = 113;
    tempTable[17]  = 112;
    tempTable[18]  = 110;
    tempTable[19]  = 110;
    tempTable[20]  = 109;
    tempTable[21]  = 107;
    tempTable[22]  = 107;
    tempTable[23]  = 106;
    tempTable[24]  = 106;
    tempTable[25]  = 105;
    tempTable[26]  = 104;
    tempTable[27]  = 104;
    tempTable[28]  = 103;
    tempTable[29]  = 101;
    tempTable[30]  = 101;
    tempTable[31]  = 100;
    tempTable[32]  =  99;
    tempTable[33]  =  98;
    tempTable[34]  =  98;
    tempTable[35]  =  97;
    tempTable[36]  =  96;
    tempTable[37]  =  96;
    tempTable[38]  =  96;
    tempTable[39]  =  95;
    tempTable[40]  =  94;
    tempTable[41]  =  93;
    tempTable[42]  =  93;
    tempTable[43]  =  92;
    tempTable[44]  =  91;
    tempTable[45]  =  91;
    tempTable[46]  =  90;
    tempTable[47]  =  90;
    tempTable[48]  =  89;
    tempTable[49]  =  88;
    tempTable[50]  =  88;
    tempTable[51]  =  87;
    tempTable[52]  =  86;
    tempTable[53]  =  86;
    tempTable[54]  =  86;
    tempTable[55]  =  85;
    tempTable[56]  =  85;
    tempTable[57]  =  84;
    tempTable[58]  =  83;
    tempTable[59]  =  83;
    tempTable[60]  =  82;
    tempTable[61]  =  82;
    tempTable[62]  =  81;
    tempTable[63]  =  81;
    tempTable[64]  =  80;
    tempTable[65]  =  80;
    tempTable[66]  =  79;
    tempTable[67]  =  79;
    tempTable[68]  =  78;
    tempTable[69]  =  78;
    tempTable[70]  =  77;
    tempTable[71]  =  77;
    tempTable[72]  =  76;
    tempTable[73]  =  75;
    tempTable[74]  =  75;
    tempTable[75]  =  75;
    tempTable[76]  =  74;
    tempTable[77]  =  74;
    tempTable[78]  =  73;
    tempTable[79]  =  73;
    tempTable[80]  =  72;
    tempTable[81]  =  72;
    tempTable[82]  =  71;
    tempTable[83]  =  71;
    tempTable[84]  =  70;
    tempTable[85]  =  70;
    tempTable[86]  =  69;
    tempTable[87]  =  69;
    tempTable[88]  =  68;
    tempTable[89]  =  68;
    tempTable[90]  =  67;
    tempTable[91]  =  67;
    tempTable[92]  =  66;
    tempTable[93]  =  66;
    tempTable[94]  =  66;
    tempTable[95]  =  65;
    tempTable[96]  =  65;
    tempTable[97]  =  64;
    tempTable[98]  =  64;
    tempTable[99]  =  63;
    tempTable[100] =  63;
    tempTable[101] =  62;
    tempTable[102] =  62;
    tempTable[103] =  61;
    tempTable[104] =  61;
    tempTable[105] =  61;
    tempTable[106] =  60;
    tempTable[107] =  60;
    tempTable[108] =  59;
    tempTable[109] =  59;
    tempTable[110] =  58;
    tempTable[111] =  58;
    tempTable[112] =  58;
    tempTable[113] =  57;
    tempTable[114] =  57;
    tempTable[115] =  56;
    tempTable[116] =  56;
    tempTable[117] =  55;
    tempTable[118] =  55;
    tempTable[119] =  54;
    tempTable[120] =  54;
    tempTable[121] =  53;
    tempTable[122] =  53;
    tempTable[123] =  53;
    tempTable[124] =  52;
    tempTable[125] =  52;
    tempTable[126] =  51;
    tempTable[127] =  51;
    tempTable[128] =  50;
    tempTable[129] =  50;
    tempTable[130] =  50;
    tempTable[131] =  49;
    tempTable[132] =  49;
    tempTable[133] =  48;
    tempTable[134] =  48;
    tempTable[135] =  47;
    tempTable[136] =  47;
    tempTable[137] =  46;
    tempTable[138] =  46;
    tempTable[139] =  45;
    tempTable[140] =  45;
    tempTable[141] =  44;
    tempTable[142] =  44;
    tempTable[143] =  44;
    tempTable[144] =  43;
    tempTable[145] =  43;
    tempTable[146] =  42;
    tempTable[147] =  42;
    tempTable[148] =  41;
    tempTable[149] =  41;
    tempTable[150] =  40;
    tempTable[151] =  40;
    tempTable[152] =  39;
    tempTable[153] =  39;
    tempTable[154] =  38;
    tempTable[155] =  38;
    tempTable[156] =  37;
    tempTable[157] =  37;
    tempTable[158] =  36;
    tempTable[159] =  36;
    tempTable[160] =  35;
    tempTable[161] =  35;
    tempTable[162] =  34;
    tempTable[163] =  34;
    tempTable[164] =  33;
    tempTable[165] =  33;
    tempTable[166] =  32;
    tempTable[167] =  32;
    tempTable[168] =  31;
    tempTable[169] =  30;
    tempTable[170] =  30;
    tempTable[171] =  29;
    tempTable[172] =  29;
    tempTable[173] =  28;
    tempTable[174] =  28;
    tempTable[175] =  27;
    tempTable[176] =  26;
    tempTable[177] =  26;
    tempTable[178] =  25;
    tempTable[179] =  25;
    tempTable[180] =  24;
    tempTable[181] =  23;
    tempTable[182] =  23;
    tempTable[183] =  22;
    tempTable[184] =  21;
    tempTable[185] =  21;
    tempTable[186] =  20;
    tempTable[187] =  19;
    tempTable[188] =  19;
    tempTable[189] =  18;
    tempTable[190] =  17;
    tempTable[191] =  16;
    tempTable[192] =  16;
    tempTable[193] =  15;
    tempTable[194] =  14;
    tempTable[195] =  13;
    tempTable[196] =  12;
    tempTable[197] =  11;
    tempTable[198] =  10;
    tempTable[199] =   9;
    tempTable[200] =   8;
    tempTable[201] =   7;
    tempTable[202] =   6;
    tempTable[203] =   5;
    tempTable[204] =   4;
    tempTable[205] =   3;
    tempTable[206] =   2;
    tempTable[207] =   1;
    tempTable[208] =   0;

}