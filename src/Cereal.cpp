#include "Cereal.hpp"


Cereal::Cereal() {
}

Cereal::~Cereal() {
}

void Cereal::handle(bool& val) {
    handleReinterpret(val);
}

void Cereal::handle(uint8_t& val) {
    handleByte(val);
}

void Cereal::handle(int8_t& val) {
    handleReinterpret(val);
}

void Cereal::handle(uint16_t& val) {
    uint8_t valh = (val >> 8);
    uint8_t vall = val & 0xff;
    handleByte(valh);
    handleByte(vall);
    val = (valh << 8) + vall;
}

void Cereal::handle(int16_t& val) {
    handleReinterpret(val);
}

void Cereal::handle(uint32_t& val) {
    uint8_t val0 = (val >> 24);
    uint8_t val1 = (val >> 16);
    uint8_t val2 = (val >> 8);
    uint8_t val3 = val & 0xff;
    handleByte(val0);
    handleByte(val1);
    handleByte(val2);
    handleByte(val3);
    val = (val0 << 24) + (val1 << 16) + (val2 << 8) + val3;
}

void Cereal::handle(int32_t& val) {
    handleReinterpret(val);
}
