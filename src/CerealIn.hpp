#ifndef CEREALIN_H_
#define CEREALIN_H_

#include "Cereal.hpp"

class CerealIn: public Cereal {
public:

    template<typename T>
    CerealIn& operator<<(const T& val); //TODO: implement

    CerealIn& operator<<(uint8_t val);

private:
    virtual void handleUInt8(uint8_t val) override;
};



#endif // CEREALIN_H
