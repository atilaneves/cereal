#include "unit_thread.hpp"
#include <cereal_all>


struct TestInU8: public TestCase {
    virtual void test() override {
        Cerealiser cerealiser;
        const uint8_t val1 = 4, val2 = 5, val3 = 6;
        cerealiser << val1 << val2 << val3;
        Cereal::Bytes bytes{val1, val2, val3};
        checkEqual(cerealiser.getBytes(), bytes);
    }
};
REGISTER_TEST(in, TestInU8)


struct TestInOutU8: public TestCase {
    virtual void test() override {
        Cerealiser cerealiser;
        const std::vector<uint8_t> ins{2, 5, 7, 3};
        for(const auto in: ins) cerealiser << in;
        Decerealiser decerealiser(cerealiser.getBytes());
        std::vector<uint8_t> outs(4);
        decerealiser >> outs[0] >> outs[1] >> outs[2] >> outs[3];
        checkEqual(ins, outs);
    }
};
REGISTER_TEST(inout, TestInOutU8)


struct TestInOutS8: public TestCase {
    virtual void test() override {
        Cerealiser cerealiser;
        const std::vector<int8_t> ins{-2, -5, -7, 3};
        for(const auto in: ins) cerealiser << in;
        Decerealiser decerealiser(cerealiser.getBytes());
        std::vector<int8_t> outs(4);
        decerealiser >> outs[0] >> outs[1] >> outs[2] >> outs[3];
        checkEqual(ins, outs);
    }
};
REGISTER_TEST(inout, TestInOutS8)
