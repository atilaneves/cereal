#include "unit_thread.hpp"
#include <cereal_all>


struct TestInU8: public TestCase {
    virtual void test() override {
        CerealIn cerealIn;
        const uint8_t val1 = 4, val2 = 5, val3 = 6;
        cerealIn << val1 << val2 << val3;
        Cereal::Bytes bytes{val1, val2, val3};
        checkEqual(cerealIn.getBytes(), bytes);
    }
};
REGISTER_TEST(in, TestInU8)
