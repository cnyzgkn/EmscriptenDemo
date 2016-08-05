#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

class MyClass {
public:
  virtual std::string virtualFunc(MyClass& instance) = 0;
  virtual const char* FuncReturnConstChar() = 0;
  virtual void        FuncReference2Int(int& value) = 0; 
  virtual void        FuncReference2ConstInt(const int& value) = 0; 
  virtual void        FuncReference2Object(MyClass& instance) = 0; 
  virtual void        FuncReference2ConstObject(const MyClass& instance) = 0; 
  virtual void        FuncPointer2Pointer(MyClass** instance) = 0; 
  virtual MyClass&    FuncReturnReference2Object(MyClass& instance) = 0;
  virtual void        FuncReference2Pointer2Int(int*& body) = 0; 
  virtual void        FuncReference2Pointer2Object(MyClass*& body) = 0; 
};

// Binding code
EMSCRIPTEN_BINDINGS(my_class_example) {
  class_<MyClass>("MyClass")
    .function("virtualFunc", &MyClass::virtualFunc)
    .function("FuncReturnConstChar", &MyClass::FuncReturnConstChar, allow_raw_pointers())
    .function("FuncReference2Int", &MyClass::FuncReference2Int)
    .function("FuncReference2ConstInt", &MyClass::FuncReference2ConstInt)
    .function("FuncReference2Object", &MyClass::FuncReference2Object)
    .function("FuncReference2ConstObject", &MyClass::FuncReference2ConstObject)
    //.function("FuncPointer2Pointer", &MyClass::FuncPointer2Pointer, allow_raw_pointers())
    //.function("FuncReturnReference2Object", &MyClass::FuncReturnReference2Object)
    //.function("FuncReference2Pointer2Int", &MyClass::FuncReference2Pointer2Int)
    ;
}