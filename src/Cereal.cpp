#include "Cereal.hpp"

Cereal::Cereal(const Bytes& bytes):_bytes(bytes) {
}

Cereal::Cereal() {
}

Cereal::~Cereal() {
}

void Cereal::handle(uint8_t& val) {
    handleByte(val);
}

void Cereal::handle(int8_t& val) {
    const auto uptr = reinterpret_cast<uint8_t*>(&val);
    handleByte(*uptr);
}
