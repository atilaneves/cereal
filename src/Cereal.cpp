#include "Cereal.hpp"

Cereal::Cereal(const Bytes& bytes):_bytes(bytes) {
}

Cereal::Cereal() {
}

Cereal::~Cereal() {
}

void Cereal::handle(int8_t& val) {
    (void)val;
}
