#ifndef DECEREALISER_H_
#define DECEREALISER_H_


#include "Cereal.hpp"
#include <algorithm>


class Decerealiser: public Cereal {
public:

    Decerealiser();

    virtual Type getType() const { return Cereal::Type::Read; }

    template<typename T> Decerealiser(const T& bytes):
        Cereal(bytes),
        _iterator(std::begin(_bytes)),
        _currentByte(),
        _bitIndex(),
        _originalBytes(std::begin(bytes), std::end(bytes)) {

    }

    template<typename T>
    Decerealiser& operator>>(T& val) {
        Cereal::grain(val);
        return *this;
    }

    template<typename T>
    T read() {
        T val = T();
        *this >> val;
        return val;
    }

    template<typename T> T value() { return read<T>(); }
    template<typename T, typename... A>
    T* create(A... args) {
        auto obj = new T(args...);
        *this >> *obj;
        return obj;
    }

    uint32_t readBits(int bits);
    void reset();

private:

    Bytes::const_iterator _iterator;
    uint8_t _currentByte;
    int _bitIndex;
    Bytes _originalBytes;

    virtual void grainByte(uint8_t& val) override;
    virtual void grainBitsImpl(uint32_t& val, int bits) override { val = readBits(bits); }
    virtual int bytesLeft() const override { return std::distance(_iterator, std::end(_bytes)); }

    uint32_t readBitsHelper(int bits);
};


using Decerealizer = Decerealiser; //for people who can't spell :P

#endif // DECEREALISER_H
