#include "CerealIn.hpp"


void CerealIn::handleUInt8(uint8_t val) {
    (void)val;
}

CerealIn& CerealIn::operator<<(uint8_t val) {
    handleUInt8(val);
    return *this;
}
