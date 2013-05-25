#ifndef CEREALISER_H_
#define CEREALISER_H_

#include "Cereal.hpp"
#include <type_traits>

class Cerealiser: public Cereal {
public:

    template<typename T>
    Cerealiser& operator<<(const T& val) {
        handle(const_cast<T&>(val)); //ok: handle doesn't modify anything
        return *this;
    }

private:

    virtual void handle(uint8_t& val) override;
};



#endif // CEREALIN_H
