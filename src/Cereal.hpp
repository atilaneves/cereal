#ifndef CEREAL_HPP_
#define CEREAL_HPP_

#include "CerealTraits.hpp"
#include <vector>
#include <stdint.h>
#include <algorithm>


class Cereal {
public:

    using Byte = unsigned char;
    using Bytes = std::vector<Byte>;

    Cereal(const Cereal&) = delete;
    Cereal& operator=(const Cereal&) = delete;
    virtual ~Cereal();

    void handle(bool& val);
    void handle(uint8_t& val);
    void handle(int8_t& val);
    void handle(uint16_t& val);
    void handle(int16_t& val);
    void handle(uint32_t& val);
    void handle(int32_t& val);

    const Bytes& getBytes() const { return _bytes; }

protected:

    Bytes _bytes;

    Cereal();
    template<typename T> Cereal(const T& bytes):
        _bytes(std::begin(bytes), std::end(bytes)) { }

private:

    template<typename T>
    void handleReinterpret(T& val) {
        const auto uptr = reinterpret_cast<typename CerealTraits::MakeUnsigned<T>::Type*>(&val);
        handle(*uptr);
    }

    virtual void handleByte(uint8_t& val) = 0;
};


#endif // CEREAL_HPP_
