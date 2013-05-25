#include "Cereal.hpp"

Cereal::Cereal(const Bytes& bytes):_bytes(bytes) {
}

Cereal::Cereal() {
}

Cereal::~Cereal() {
}

void Cereal::handleInt8(int8_t val) {
    (void)val;
}

void Cereal::handleUInt16(uint16_t val) {
    (void)val;
}

void Cereal::handleInt16(int16_t val) {
    (void)val;
}

void Cereal::handleUInt32(uint32_t val) {
    (void)val;
}
