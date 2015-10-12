#ifndef DECEREALISER_H_
#define DECEREALISER_H_


#include "Cereal.hpp"
#include <algorithm>
#include <memory>

class Decerealiser: public Cereal {
public:

    Decerealiser();

    virtual Type getType() const override { return Cereal::Type::Read; }

    template<typename T> explicit Decerealiser(const T& bytes):
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
    std::unique_ptr<T> createPtr(A... args) {
        auto obj = new T(args...);
        *this >> *obj;
        return std::unique_ptr<T>{obj};
    }

    template<typename T, typename... A>
    T create(A... args) {
        T obj(args...);
        *this >> obj;
        return obj;
    }

    template<typename T>
    void create(T& obj) {
        *this >> obj;
    }

    uint32_t readBits(int bits);
    void reset();

    //const Bytes& getBytes() const { return _bytes; }

private:

    //Bytes _bytes;
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
