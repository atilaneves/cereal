#include "Cerealiser.hpp"


void Cerealiser::handleByte(uint8_t& val) {
    _bytes.push_back(val);
}
