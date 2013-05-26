#include "Decerealiser.hpp"

void Decerealiser::cerealByte(uint8_t& val) {
    val = *_iterator++;
}
