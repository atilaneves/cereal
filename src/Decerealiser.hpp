#ifndef DECEREALISER_H_
#define DECEREALISER_H_


#include "Cereal.hpp"


class Decerealiser: public Cereal {
public:

    Decerealiser();

    virtual Type getType() const { return Cereal::Type::Read; }

    template<typename T> Decerealiser(const T& bytes):
        Cereal(bytes), _iterator(std::begin(bytes)) { }

    template<typename T>
    Decerealiser& operator>>(T& val) {
        Cereal::grain(val);
        return *this;
    }

    template<typename T>
    T read() {
        T val;
        *this >> val;
        return val;
    }

    uint32_t readBits(int bits);

private:

    Bytes::const_iterator _iterator;
    uint8_t _currentByte;
    int _bitIndex;

    virtual void grainByte(uint8_t& val) override;
    uint32_t readBitsHelper(int bits);
};


using Decerealizer = Decerealiser; //for people who can't spell :P

#endif // DECEREALISER_H
