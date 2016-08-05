#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

class MyClass {
public:
  virtual void someFunction() = 0;
};

//MyClass* makeMyClass(int, float); //Factory function.

EMSCRIPTEN_BINDINGS(external_constructors) {
  class_<MyClass>("MyClass")
    //.constructor(&makeMyClass, allow_raw_pointers())
    .function("someFunction", &MyClass::someFunction)
    ;
}