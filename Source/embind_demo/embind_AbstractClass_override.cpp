#include <emscripten.h>
#include <emscripten/bind.h>


using namespace emscripten;

class AbstractClass {
public:
    virtual ~AbstractClass() {}
    virtual std::string abstractMethod() const = 0;
    virtual std::string abstractMethod2() const = 0;
};

class AbstractClassWrapper : public wrapper<AbstractClass> {
public:
    EMSCRIPTEN_WRAPPER(AbstractClassWrapper);

    std::string abstractMethod() const override {
        return call<std::string>("abstractMethod");
    }
};

class ConcreteClass : public AbstractClass {
    std::string abstractMethod() const {
        return "from concrete";
    }

    std::string abstractMethod2() const {
        return "from concrete2";
    }
};

EMSCRIPTEN_BINDINGS(AbstractClass_override) {
    class_<AbstractClass>("AbstractClass")
        //.smart_ptr<std::shared_ptr<AbstractClass>>("shared_ptr<AbstractClass>")
        .allow_subclass<AbstractClassWrapper>("AbstractClassWrapper")
        .function("abstractMethod", &AbstractClass::abstractMethod, pure_virtual())
        ;
}