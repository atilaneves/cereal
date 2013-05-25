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

template<typename T>
struct TestInOut: public TestCase {
    std::vector<T> _ins;
    TestInOut(const std::vector<T>& ins):_ins(ins) { }

    virtual void test() override {
        Cerealiser cerealiser;
        for(const auto in: _ins) cerealiser << in;
        Decerealiser decerealiser(cerealiser.getBytes());
        std::vector<T> outs(_ins.size());
        for(auto& out: outs) {
            decerealiser >> out;
        }
        checkEqual(_ins, outs);
    }
};


struct TestInOutU8: public TestInOut<uint8_t> {
    TestInOutU8():TestInOut<uint8_t>({2, 5, 7, 3}) { }
};
REGISTER_TEST(inout, TestInOutU8)


struct TestInOutS8: public TestInOut<int8_t> {
    TestInOutS8():TestInOut<int8_t>({-2, -5, 7, 3, -9}) { }
};
REGISTER_TEST(inout, TestInOutS8)
