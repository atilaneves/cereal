#ifndef CEREAL_HPP_
#define CEREAL_HPP_

#include <vector>
#include <stdint.h>

class Cereal {
public:

    using Byte = unsigned char;
    using Bytes = std::vector<Byte>;

    Cereal(const Cereal&) = delete;
    Cereal& operator=(const Cereal&) = delete;
    virtual ~Cereal();

    const Bytes& getBytes() const { return _bytes; }

protected:

    Bytes _bytes;

    Cereal();
    Cereal(const Bytes& bytes);

    void handle(uint8_t& val);
    void handle(int8_t& val);
    virtual void handleByte(uint8_t& val) = 0;
};


#endif // CEREAL_HPP_
