#include "Cerealiser.hpp"


void Cerealiser::handle(uint8_t& val) {
    _bytes.push_back(val);
}
