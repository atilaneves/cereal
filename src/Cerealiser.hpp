#ifndef CEREALISER_H_
#define CEREALISER_H_

#include "Cereal.hpp"
#include <type_traits>

class Cerealiser: public Cereal {
public:

    template<typename T>
    Cerealiser& operator<<(const T& val) {
        Cereal::cereal(const_cast<T&>(val)); //ok: cereal doesn't modify anything
        return *this;
    }

    template<typename T>
    void write(const T& val) {
        *this << val;
    }

    template<typename I, typename T, typename A>
    void cereal(const std::vector<T, A>& vector) {
        Cereal::cereal<I>(const_cast<std::vector<T, A>&>(vector)); //ok: cereal doesn't modify anything
    }


private:

    virtual void cerealByte(uint8_t& val) override;
};

using Cerealizer = Cerealiser; //for people who can't spell :P


#endif // CEREALIN_H
