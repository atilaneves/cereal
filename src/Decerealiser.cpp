#include "Decerealiser.hpp"

Decerealiser::Decerealiser(const Bytes& bytes):
    Cereal(bytes),
    _iterator(bytes.cbegin()) {

}

void Decerealiser::handleByte(uint8_t& val) {
    val = *_iterator++;
}
