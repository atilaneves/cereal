#ifndef DECEREALISER_H_
#define DECEREALISER_H_


#include "Cereal.hpp"


class Decerealiser: public Cereal {
public:

    Decerealiser(const Bytes& bytes);

    template<typename T>
    Decerealiser& operator>>(T& val) {
        Cereal::handle(val);
        return *this;
    }

private:

    Bytes::const_iterator _iterator;

    virtual void handleByte(uint8_t& val) override;

};


using Decerealizer = Decerealiser; //for people who can't spell :P

#endif // DECEREALISER_H
