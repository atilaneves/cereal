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

    void handleInt8(int8_t val);
    void handleUInt16(uint16_t val);
    void handleInt16(int16_t val);
    void handleUInt32(uint32_t val);
    const Bytes& getBytes() const { return _bytes; }

protected:

    Bytes _bytes;

    Cereal();
    Cereal(const Bytes& bytes);

private:


    virtual void handleUInt8(uint8_t val) = 0;
};


#endif // CEREAL_HPP_
