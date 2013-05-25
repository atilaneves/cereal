#include "unit_thread.hpp"
#include <cereal_all>
#include <limits>


struct TestInU8: public TestCase {
    virtual void test() override final {
        std::vector<uint8_t> ins{4, 5, 6};
        Cerealiser cerealiser;
        for(const auto in: ins) cerealiser << in;
        checkEqual(cerealiser.getBytes(), ins);
    }
};
REGISTER_TEST(8, TestInU8)


template<typename T>
struct TestInOut: public TestCase {
    std::vector<T> _ins;
    TestInOut(const std::vector<T>& ins):_ins(ins) { }

    virtual void test() override {
        Cerealiser cerealiser;
        for(const auto in: _ins) cerealiser << in;

        Decerealiser decerealiser(cerealiser.getBytes());
        std::vector<T> outs(_ins.size());
        for(auto& out: outs) decerealiser >> out;

        checkEqual(_ins, outs);
    }
};


struct TestInOutU8: public TestInOut<uint8_t> {
    TestInOutU8():TestInOut<uint8_t>({2, 5, 7, 3}) { }
};
REGISTER_TEST(8, TestInOutU8)


struct TestInOutS8: public TestInOut<int8_t> {
    TestInOutS8():TestInOut<int8_t>({-2, -5, 7, 3, -9}) { }
};
REGISTER_TEST(8, TestInOutS8)


struct TestInOutU16: public TestInOut<uint16_t> {
    TestInOutU16():TestInOut<uint16_t>({2, 65000, 7, 0xffff}) { }
};
REGISTER_TEST(16, TestInOutU16)


struct TestInOutS16: public TestInOut<int16_t> {
    TestInOutS16():TestInOut<int16_t>({-2, -32000, 32000, 3, -9}) { }
};
REGISTER_TEST(16, TestInOutS16)

struct TestInOutU32: public TestInOut<uint32_t> {
    TestInOutU32():TestInOut<uint32_t>({std::numeric_limits<uint32_t>::max(), 5, 7, 3}) { }
};
REGISTER_TEST(32, TestInOutU32)


struct TestInOutS32: public TestInOut<int32_t> {
    TestInOutS32():TestInOut<int32_t>({-std::numeric_limits<uint32_t>::max(), -5, 7, 3, -1}) { }
};
REGISTER_TEST(32, TestInOutS32)
