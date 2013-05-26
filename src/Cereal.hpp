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

    void cereal(bool& val);
    void cereal(uint8_t& val);
    void cereal(int8_t& val);
    void cereal(uint16_t& val);
    void cereal(int16_t& val);
    void cereal(uint32_t& val);
    void cereal(int32_t& val);
    void cereal(uint64_t& val);
    void cereal(int64_t& val);
    void cereal(double& val);

    template<typename I, typename T, typename A>
    void cereal(std::vector<T, A>& vector);

    const Bytes& getBytes() const { return _bytes; }

protected:

    Bytes _bytes;

    Cereal();
    template<typename T> Cereal(const T& bytes):
        _bytes(std::begin(bytes), std::end(bytes)) { }

private:

    template<typename T>
    void cerealReinterpret(T& val) {
        const auto uptr = reinterpret_cast<typename CerealTraits::MakeUnsigned<T>::Type*>(&val);
        cereal(*uptr);
    }

    virtual void cerealByte(uint8_t& val) = 0;
};

template<typename I, typename V>
static void maybeResizeVector(Cereal& cereal, V& vec) {
    I num;
    cereal.cereal(num);
    if(vec.size() != num) { //writing to vector, resize it
        vec.resize(num);
    }
}

#include <iostream>
template<typename I, typename T, typename A>
void Cereal::cereal(std::vector<T, A>& vector) {
    I num = vector.size();
    cereal(num);
    if(vector.size() != num) { //writing to vector, resize it
        vector.resize(num);
    }
    for(auto& t: vector) {
        t.cerealise(*this);
    }
}


#endif // CEREAL_HPP_
