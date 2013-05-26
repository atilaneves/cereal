#include "Decerealiser.hpp"

void Decerealiser::handleByte(uint8_t& val) {
    val = *_iterator++;
}
