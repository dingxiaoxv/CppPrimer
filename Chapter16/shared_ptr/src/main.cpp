#include <iostream>
#include <string>
#include <vector>

#include "shared_ptr.h"

// Test class to track construction and destruction
class TestClass {
public:
  TestClass(int val) : value(val) {
    std::cout << "  TestClass(" << value << ") constructed" << std::endl;
  }
  ~TestClass() {
    std::cout << "  TestClass(" << value << ") destructed" << std::endl;
  }
  int getValue() const { return value; }
  void setValue(int val) { value = val; }

private:
  int value;
};

void test_basic_construction() {
  std::cout << "\n=== Test 1: Basic Construction ===" << std::endl;

  // Default constructor
  cpp::SharedPtr<int> sp1;
  std::cout << "Default SharedPtr use_count: " << sp1.use_count() << std::endl;

  // Constructor with pointer
  cpp::SharedPtr<int> sp2(new int(42));
  std::cout << "SharedPtr<int>(42) value: " << *sp2
            << ", use_count: " << sp2.use_count() << std::endl;

  // make_shared_ptr
  auto sp3 = cpp::make_shared_ptr<int>(100);
  std::cout << "make_shared_ptr<int>(100) value: " << *sp3
            << ", use_count: " << sp3.use_count() << std::endl;
}

void test_copy_constructor() {
  std::cout << "\n=== Test 2: Copy Constructor ===" << std::endl;

  auto sp1 = cpp::make_shared_ptr<int>(50);
  std::cout << "sp1 value: " << *sp1 << ", use_count: " << sp1.use_count() << std::endl;

  cpp::SharedPtr<int> sp2(sp1);
  std::cout << "After copy: sp1 use_count: " << sp1.use_count()
            << ", sp2 use_count: " << sp2.use_count() << std::endl;
  std::cout << "sp2 value: " << *sp2 << std::endl;

  // Modify through sp2
  *sp2 = 99;
  std::cout << "After *sp2 = 99: sp1 value: " << *sp1
            << ", sp2 value: " << *sp2 << std::endl;
}

void test_assignment_operator() {
  std::cout << "\n=== Test 3: Assignment Operator ===" << std::endl;

  auto sp1 = cpp::make_shared_ptr<int>(10);
  auto sp2 = cpp::make_shared_ptr<int>(20);

  std::cout << "Before assignment:" << std::endl;
  std::cout << "  sp1: value=" << *sp1 << ", use_count=" << sp1.use_count() << std::endl;
  std::cout << "  sp2: value=" << *sp2 << ", use_count=" << sp2.use_count() << std::endl;

  sp2 = sp1;
  std::cout << "After sp2 = sp1:" << std::endl;
  std::cout << "  sp1: value=" << *sp1 << ", use_count=" << sp1.use_count() << std::endl;
  std::cout << "  sp2: value=" << *sp2 << ", use_count=" << sp2.use_count() << std::endl;
}

void test_reference_counting() {
  std::cout << "\n=== Test 4: Reference Counting ===" << std::endl;

  auto sp1 = cpp::make_shared_ptr<int>(777);
  std::cout << "sp1 created, use_count: " << sp1.use_count() << std::endl;

  {
    auto sp2 = sp1;
    std::cout << "sp2 copied from sp1, use_count: " << sp1.use_count() << std::endl;

    {
      auto sp3 = sp1;
      std::cout << "sp3 copied from sp1, use_count: " << sp1.use_count() << std::endl;

      auto sp4 = sp2;
      std::cout << "sp4 copied from sp2, use_count: " << sp1.use_count() << std::endl;
    }
    std::cout << "sp3 and sp4 destroyed, use_count: " << sp1.use_count() << std::endl;
  }
  std::cout << "sp2 destroyed, use_count: " << sp1.use_count() << std::endl;
}

void test_with_custom_class() {
  std::cout << "\n=== Test 5: Custom Class ===" << std::endl;

  std::cout << "Creating SharedPtr<TestClass>:" << std::endl;
  auto sp1 = cpp::make_shared_ptr<TestClass>(123);

  std::cout << "Value via operator*: " << (*sp1).getValue() << std::endl;
  std::cout << "Value via operator->: " << sp1->getValue() << std::endl;

  std::cout << "Creating copy:" << std::endl;
  auto sp2 = sp1;
  std::cout << "use_count: " << sp1.use_count() << std::endl;

  sp2->setValue(456);
  std::cout << "After sp2->setValue(456):" << std::endl;
  std::cout << "  sp1->getValue(): " << sp1->getValue() << std::endl;
  std::cout << "  sp2->getValue(): " << sp2->getValue() << std::endl;

  std::cout << "Leaving scope (objects will be destroyed):" << std::endl;
}

void test_with_string() {
  std::cout << "\n=== Test 6: SharedPtr<std::string> ===" << std::endl;

  auto sp1 = cpp::make_shared_ptr<std::string>("Hello, SharedPtr!");
  std::cout << "String value: " << *sp1 << std::endl;
  std::cout << "String length: " << sp1->length() << std::endl;

  auto sp2 = sp1;
  sp2->append(" - Modified");
  std::cout << "After append: " << *sp1 << std::endl;
  std::cout << "use_count: " << sp1.use_count() << std::endl;
}

void test_self_assignment() {
  std::cout << "\n=== Test 7: Self Assignment ===" << std::endl;

  auto sp1 = cpp::make_shared_ptr<int>(888);
  std::cout << "Before self-assignment: value=" << *sp1
            << ", use_count=" << sp1.use_count() << std::endl;

  sp1 = sp1;
  std::cout << "After self-assignment: value=" << *sp1
            << ", use_count=" << sp1.use_count() << std::endl;
}

void test_vector_of_shared_ptr() {
  std::cout << "\n=== Test 8: Vector of SharedPtr ===" << std::endl;

  std::vector<cpp::SharedPtr<int>> vec;

  auto sp = cpp::make_shared_ptr<int>(555);
  std::cout << "Initial use_count: " << sp.use_count() << std::endl;

  vec.push_back(sp);
  std::cout << "After push_back, use_count: " << sp.use_count() << std::endl;

  vec.push_back(sp);
  std::cout << "After second push_back, use_count: " << sp.use_count() << std::endl;

  vec.clear();
  std::cout << "After vec.clear(), use_count: " << sp.use_count() << std::endl;
}

void test_move_constructor() {
  std::cout << "\n=== Test 9: Move Constructor ===" << std::endl;

  std::cout << "Creating sp1 with TestClass(222):" << std::endl;
  auto sp1 = cpp::make_shared_ptr<TestClass>(222);
  std::cout << "sp1 value: " << sp1->getValue() << ", use_count: " << sp1.use_count() << std::endl;
  std::cout << "sp1 is valid: " << (sp1 ? "true" : "false") << std::endl;

  std::cout << "Move constructing sp2 from sp1:" << std::endl;
  cpp::SharedPtr<TestClass> sp2(std::move(sp1));
  std::cout << "sp2 value: " << sp2->getValue() << ", use_count: " << sp2.use_count() << std::endl;
  std::cout << "sp1 is valid: " << (sp1 ? "true" : "false") << std::endl;
  std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
  std::cout << "sp2 is valid: " << (sp2 ? "true" : "false") << std::endl;

  std::cout << "Note: Move doesn't change reference count (still 1)" << std::endl;
  std::cout << "Leaving scope (only sp2 will destroy the object):" << std::endl;
}

void test_move_assignment() {
  std::cout << "\n=== Test 10: Move Assignment ===" << std::endl;

  std::cout << "Creating sp1 with TestClass(333):" << std::endl;
  auto sp1 = cpp::make_shared_ptr<TestClass>(333);
  std::cout << "sp1 value: " << sp1->getValue() << ", use_count: " << sp1.use_count() << std::endl;

  std::cout << "Creating sp2 with TestClass(444):" << std::endl;
  auto sp2 = cpp::make_shared_ptr<TestClass>(444);
  std::cout << "sp2 value: " << sp2->getValue() << ", use_count: " << sp2.use_count() << std::endl;

  std::cout << "Move assigning sp1 to sp2 (sp2 = std::move(sp1)):" << std::endl;
  sp2 = std::move(sp1);
  std::cout << "sp2 value: " << sp2->getValue() << ", use_count: " << sp2.use_count() << std::endl;
  std::cout << "sp1 is valid: " << (sp1 ? "true" : "false") << std::endl;
  std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
  std::cout << "sp2 is valid: " << (sp2 ? "true" : "false") << std::endl;
  std::cout << "TestClass(444) should have been destroyed above" << std::endl;

  std::cout << "Leaving scope:" << std::endl;
}

void test_get_and_bool() {
  std::cout << "\n=== Test 11: get() and bool conversion ===" << std::endl;

  auto sp1 = cpp::make_shared_ptr<int>(100);
  std::cout << "sp1 value: " << *sp1 << std::endl;
  std::cout << "sp1.get(): " << sp1.get() << std::endl;
  std::cout << "sp1 is valid (bool): " << (sp1 ? "true" : "false") << std::endl;

  cpp::SharedPtr<int> sp2;
  std::cout << "sp2 (empty) is valid (bool): " << (sp2 ? "true" : "false") << std::endl;
  std::cout << "sp2.get(): " << sp2.get() << std::endl;
  std::cout << "sp2.use_count(): " << sp2.use_count() << std::endl;

  // Use in if statement
  if (sp1) {
    std::cout << "sp1 can be used in if statement" << std::endl;
  }
  if (!sp2) {
    std::cout << "sp2 is empty, !sp2 is true" << std::endl;
  }
}

void test_reset_method() {
  std::cout << "\n=== Test 12: reset() method ===" << std::endl;

  std::cout << "Creating sp with TestClass(500):" << std::endl;
  auto sp = cpp::make_shared_ptr<TestClass>(500);
  std::cout << "sp value: " << sp->getValue() << ", use_count: " << sp.use_count() << std::endl;

  std::cout << "Creating sp2 as copy of sp:" << std::endl;
  auto sp2 = sp;
  std::cout << "sp use_count: " << sp.use_count() << std::endl;

  std::cout << "Resetting sp with new TestClass(600):" << std::endl;
  sp.reset(new TestClass(600));
  std::cout << "sp value: " << sp->getValue() << ", use_count: " << sp.use_count() << std::endl;
  std::cout << "sp2 value: " << sp2->getValue() << ", use_count: " << sp2.use_count() << std::endl;
  std::cout << "Note: sp2 still owns TestClass(500)" << std::endl;

  std::cout << "Resetting sp to nullptr:" << std::endl;
  sp.reset();
  std::cout << "sp is valid: " << (sp ? "true" : "false") << std::endl;
  std::cout << "sp use_count: " << sp.use_count() << std::endl;

  std::cout << "Leaving scope:" << std::endl;
}

// ============================================================================
// DANGEROUS USAGE EXAMPLES - DO NOT UNCOMMENT THESE!
// These examples demonstrate undefined behavior that will crash your program
// ============================================================================

/*
 * DANGER 1: Passing stack pointer to SharedPtr
 * This will cause undefined behavior when SharedPtr tries to delete stack memory
 */
void DANGER_stack_pointer() {
  int stack_var = 42;
  cpp::SharedPtr<int> sp(&stack_var);  // DANGER: stack pointer!
  std::cout << "Value: " << *sp << std::endl;
  // When sp goes out of scope, it will call delete on stack memory = CRASH!
}

/*
 * DANGER 2: Passing 'this' pointer from stack-allocated object
 * This will cause undefined behavior
 */
class DangerousClass {
public:
  void bad_shared_from_this() {
    // DANGER: 'this' might be on stack or already managed by another smart ptr
    cpp::SharedPtr<DangerousClass> sp(this);
    // When sp is destroyed, it will delete 'this' = CRASH or double-free!
  }

  void use() { std::cout << "Using object" << std::endl; }
};

void DANGER_this_pointer() {
  DangerousClass obj;           // stack allocated
  obj.bad_shared_from_this();  // DANGER: will try to delete stack object!
  // Program will likely crash here or exhibit undefined behavior
}

/*
 * DANGER 3: Multiple SharedPtrs managing same raw pointer
 * This causes double deletion
 */
void DANGER_double_management() {
  int* raw = new int(100);
  cpp::SharedPtr<int> sp1(raw);
  cpp::SharedPtr<int> sp2(raw);  // DANGER: same raw pointer, separate ref count!
  // When sp1 and sp2 are destroyed, raw will be deleted twice = CRASH!
}

/*
 * DANGER 4: Using 'this' in heap-allocated object
 * Still dangerous because of potential double-free
 */
void DANGER_heap_this_pointer() {
  DangerousClass* obj = new DangerousClass();
  obj->bad_shared_from_this();  // Creates SharedPtr that will delete obj
  // obj is now deleted by SharedPtr's destructor
  // obj->use();  // DANGER: use-after-free!
  // delete obj;  // DANGER: double-free if we try to delete again!
}

// ============================================================================
// SAFE ALTERNATIVES - Correct usage patterns
// ============================================================================

void demonstrate_safe_usage() {
  std::cout << "\n=== Test 13: Safe Usage Patterns ===" << std::endl;

  // SAFE 1: Always use make_shared_ptr or new
  std::cout << "Safe pattern 1: Use make_shared_ptr" << std::endl;
  auto sp1 = cpp::make_shared_ptr<int>(42);
  std::cout << "  Value: " << *sp1 << ", use_count: " << sp1.use_count() << std::endl;

  // SAFE 2: Copy SharedPtr, don't create from same raw pointer
  std::cout << "Safe pattern 2: Copy SharedPtr for shared ownership" << std::endl;
  auto sp2 = sp1;  // Correct: shares ownership
  std::cout << "  sp1 use_count: " << sp1.use_count()
            << ", sp2 use_count: " << sp2.use_count() << std::endl;

  // SAFE 3: Use new directly in constructor
  std::cout << "Safe pattern 3: Use new in constructor" << std::endl;
  cpp::SharedPtr<TestClass> sp3(new TestClass(999));
  std::cout << "  Value: " << sp3->getValue() << std::endl;

  std::cout << "Leaving scope - safe cleanup:" << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "===== SharedPtr Test Suite =====" << std::endl;

  test_basic_construction();
  test_copy_constructor();
  test_assignment_operator();
  test_reference_counting();
  test_with_custom_class();
  test_with_string();
  test_self_assignment();
  test_vector_of_shared_ptr();
  test_move_constructor();
  test_move_assignment();
  test_get_and_bool();
  test_reset_method();
  demonstrate_safe_usage();

  std::cout << "\n===== All Tests Completed =====" << std::endl;

  std::cout << "\n===== WARNING: Dangerous Usage Patterns =====" << std::endl;
  std::cout << "The following patterns cause UNDEFINED BEHAVIOR:" << std::endl;
  std::cout << "1. SharedPtr<T>(&stack_variable) - deleting stack memory" << std::endl;
  std::cout << "2. SharedPtr<T>(this) - deleting 'this' pointer" << std::endl;
  std::cout << "3. Multiple SharedPtrs from same raw pointer - double free" << std::endl;
  std::cout << "4. SharedPtr from already-managed pointer - double free" << std::endl;
  std::cout << "\nALWAYS use make_shared_ptr or pass 'new T(...)' directly!" << std::endl;

  return 0;
}