#include "Cereal.hpp"


Cereal::Cereal() {
}

Cereal::~Cereal() {
}

void Cereal::cereal(bool& val) {
    cerealReinterpret(val);
}

void Cereal::cereal(uint8_t& val) {
    cerealByte(val);
}

void Cereal::cereal(int8_t& val) {
    cerealReinterpret(val);
}

void Cereal::cereal(uint16_t& val) {
    uint8_t valh = (val >> 8);
    uint8_t vall = val & 0xff;
    cerealByte(valh);
    cerealByte(vall);
    val = (valh << 8) + vall;
}

void Cereal::cereal(int16_t& val) {
    cerealReinterpret(val);
}

void Cereal::cereal(uint32_t& val) {
    uint8_t val0 = (val >> 24);
    uint8_t val1 = (val >> 16);
    uint8_t val2 = (val >> 8);
    uint8_t val3 = val & 0xff;
    cerealByte(val0);
    cerealByte(val1);
    cerealByte(val2);
    cerealByte(val3);
    val = (val0 << 24) + (val1 << 16) + (val2 << 8) + val3;
}

void Cereal::cereal(int32_t& val) {
    cerealReinterpret(val);
}

void Cereal::cereal(uint64_t& val) {
    const auto ptr = reinterpret_cast<uint8_t*>(&val);
    for(int i = 7; i >= 0; --i) {
        cerealByte(ptr[i]);
    }
    uint64_t newVal = 0;
    for(int i = 7; i >= 0; --i) {
        newVal += (ptr[i] << (i * 8));
    }
}

void Cereal::cereal(int64_t& val) {
    cerealReinterpret(val);
}


void Cereal::cereal(double& val) {
    cerealReinterpret(val);
}
