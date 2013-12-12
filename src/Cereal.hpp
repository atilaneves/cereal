#ifndef CEREAL_HPP_
#define CEREAL_HPP_

#include "CerealTraits.hpp"
#include <vector>
#include <string>
#include <stdint.h>
#include <algorithm>


class Cereal {
public:

    enum class Type { Write, Read };

    using Byte = unsigned char;
    using Bytes = std::vector<Byte>;

    Cereal(const Cereal&) = delete;
    Cereal& operator=(const Cereal&) = delete;
    virtual ~Cereal();

    virtual Type getType() const = 0;
    virtual void grainBits(uint32_t& val, int bits) = 0;

    void grain(bool& val);
    void grain(uint8_t& val);
    void grain(int8_t& val);
    void grain(char& val);
    void grain(uint16_t& val);
    void grain(int16_t& val);
    void grain(uint32_t& val);
    void grain(int32_t& val);
    void grain(uint64_t& val);
    void grain(int64_t& val);
    void grain(double& val);

    template<typename I = uint16_t, typename T, typename A>
    void grain(std::vector<T, A>& vector);

    template<typename I = uint16_t>
    void grain(std::string& val);

    template<typename T>
    void grain(T& t) {
        t.cerealise(*this);
    }

    const Bytes& getBytes() const { return _bytes; }

protected:

    Bytes _bytes;

    Cereal();
    template<typename T> Cereal(const T& bytes):
        _bytes(std::begin(bytes), std::end(bytes)) { }

private:

    template<typename T>
    void grainReinterpret(T& val) {
        const auto uptr = reinterpret_cast<typename CerealTraits::MakeUnsigned<T>::Type*>(&val);
        grain(*uptr);
    }

    virtual void grainByte(uint8_t& val) = 0;
};

template<typename I, typename V>
static void maybeResizeVector(Cereal& cereal, V& vec) {
    I num;
    cereal.grain(num);
    if(vec.size() != num) { //writing to vector, resize it
        vec.resize(num);
    }
}

template<typename I, typename T, typename A>
void Cereal::grain(std::vector<T, A>& val) {
    I num = val.size();
    grain(num);
    if(val.size() != num) { //writing to val, resize it
        val.resize(num);
    }
    for(auto& t: val) {
        t.cerealise(*this);
    }
}


template<typename I>
void Cereal::grain(std::string& val) {
    I num = val.size();
    grain(num);
    if(val.size() != num) { //writing to val, resize it
        val.resize(num);
    }
    for(auto& t: val) {
        grain(t);
    }
}


#endif // CEREAL_HPP_
