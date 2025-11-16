#include <iostream>
#include <string>

#include "unique_ptr.h"

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
  cpp::UniquePtr<int> up1;
  std::cout << "Default UniquePtr created" << std::endl;

  // Constructor with pointer
  cpp::UniquePtr<int> up2(new int(42));
  std::cout << "UniquePtr<int>(42) value: " << *up2 << std::endl;

  // make_unique_ptr
  auto up3 = cpp::make_unique_ptr<int>(100);
  std::cout << "make_unique_ptr<int>(100) value: " << *up3 << std::endl;
}

void test_release() {
  std::cout << "\n=== Test 2: Release ===" << std::endl;

  auto up = cpp::make_unique_ptr<int>(50);
  std::cout << "Before release: value = " << *up << std::endl;

  int* raw_ptr = up.release();
  std::cout << "After release: raw_ptr value = " << *raw_ptr << std::endl;
  std::cout << "UniquePtr no longer owns the memory" << std::endl;

  // Must manually delete the released pointer
  delete raw_ptr;
  std::cout << "Manually deleted raw_ptr" << std::endl;
}

void test_reset() {
  std::cout << "\n=== Test 3: Reset ===" << std::endl;

  std::cout << "Creating UniquePtr<TestClass>(100):" << std::endl;
  auto up = cpp::make_unique_ptr<TestClass>(100);
  std::cout << "Value: " << up->getValue() << std::endl;

  std::cout << "Resetting with new TestClass(200):" << std::endl;
  up.reset(new TestClass(200));
  std::cout << "New value: " << up->getValue() << std::endl;

  std::cout << "Resetting to nullptr:" << std::endl;
  up.reset();
  std::cout << "UniquePtr is now empty" << std::endl;
}

void test_with_custom_class() {
  std::cout << "\n=== Test 4: Custom Class ===" << std::endl;

  std::cout << "Creating UniquePtr<TestClass>:" << std::endl;
  auto up = cpp::make_unique_ptr<TestClass>(123);

  std::cout << "Value via operator*: " << (*up).getValue() << std::endl;
  std::cout << "Value via operator->: " << up->getValue() << std::endl;

  up->setValue(456);
  std::cout << "After setValue(456): " << up->getValue() << std::endl;

  std::cout << "Leaving scope (object will be destroyed):" << std::endl;
}

void test_with_string() {
  std::cout << "\n=== Test 5: UniquePtr<std::string> ===" << std::endl;

  auto up = cpp::make_unique_ptr<std::string>("Hello, UniquePtr!");
  std::cout << "String value: " << *up << std::endl;
  std::cout << "String length: " << up->length() << std::endl;

  up->append(" - Modified");
  std::cout << "After append: " << *up << std::endl;
}

void test_ownership_transfer() {
  std::cout << "\n=== Test 6: Ownership Transfer (via release/reset) ===" << std::endl;

  std::cout << "Creating up1 with TestClass(111):" << std::endl;
  auto up1 = cpp::make_unique_ptr<TestClass>(111);
  std::cout << "up1 value: " << up1->getValue() << std::endl;

  std::cout << "Transferring ownership to up2:" << std::endl;
  cpp::UniquePtr<TestClass> up2;
  up2.reset(up1.release());
  std::cout << "up2 value: " << up2->getValue() << std::endl;
  std::cout << "up1 is now empty" << std::endl;

  std::cout << "Leaving scope (only up2 will destroy the object):" << std::endl;
}

void test_move_constructor() {
  std::cout << "\n=== Test 7: Move Constructor ===" << std::endl;

  std::cout << "Creating up1 with TestClass(222):" << std::endl;
  auto up1 = cpp::make_unique_ptr<TestClass>(222);
  std::cout << "up1 value: " << up1->getValue() << std::endl;
  std::cout << "up1 is valid: " << (up1 ? "true" : "false") << std::endl;

  std::cout << "Move constructing up2 from up1:" << std::endl;
  cpp::UniquePtr<TestClass> up2(std::move(up1));
  std::cout << "up2 value: " << up2->getValue() << std::endl;
  std::cout << "up1 is valid: " << (up1 ? "true" : "false") << std::endl;
  std::cout << "up2 is valid: " << (up2 ? "true" : "false") << std::endl;

  std::cout << "Leaving scope (only up2 will destroy the object):" << std::endl;
}

void test_move_assignment() {
  std::cout << "\n=== Test 8: Move Assignment ===" << std::endl;

  std::cout << "Creating up1 with TestClass(333):" << std::endl;
  auto up1 = cpp::make_unique_ptr<TestClass>(333);
  std::cout << "up1 value: " << up1->getValue() << std::endl;

  std::cout << "Creating up2 with TestClass(444):" << std::endl;
  auto up2 = cpp::make_unique_ptr<TestClass>(444);
  std::cout << "up2 value: " << up2->getValue() << std::endl;

  std::cout << "Move assigning up1 to up2 (up2 = std::move(up1)):" << std::endl;
  up2 = std::move(up1);
  std::cout << "up2 value: " << up2->getValue() << std::endl;
  std::cout << "up1 is valid: " << (up1 ? "true" : "false") << std::endl;
  std::cout << "up2 is valid: " << (up2 ? "true" : "false") << std::endl;
  std::cout << "TestClass(444) should have been destroyed above" << std::endl;

  std::cout << "Leaving scope:" << std::endl;
}

void test_get_and_bool() {
  std::cout << "\n=== Test 9: get() and bool conversion ===" << std::endl;

  auto up1 = cpp::make_unique_ptr<int>(100);
  std::cout << "up1 value: " << *up1 << std::endl;
  std::cout << "up1.get(): " << up1.get() << std::endl;
  std::cout << "up1 is valid (bool): " << (up1 ? "true" : "false") << std::endl;

  cpp::UniquePtr<int> up2;
  std::cout << "up2 (empty) is valid (bool): " << (up2 ? "true" : "false") << std::endl;
  std::cout << "up2.get(): " << up2.get() << std::endl;

  // Use in if statement
  if (up1) {
    std::cout << "up1 can be used in if statement" << std::endl;
  }
  if (!up2) {
    std::cout << "up2 is empty, !up2 is true" << std::endl;
  }
}

void test_reset_edge_cases() {
  std::cout << "\n=== Test 10: Reset Edge Cases ===" << std::endl;

  auto up = cpp::make_unique_ptr<int>(777);
  std::cout << "Initial value: " << *up << std::endl;

  // Reset with new value
  up.reset(new int(888));
  std::cout << "After reset(new int(888)): " << *up << std::endl;

  // Reset to empty
  up.reset(nullptr);
  std::cout << "After reset(nullptr): UniquePtr is empty" << std::endl;

  // Reset again (should be safe)
  up.reset();
  std::cout << "After reset(): Still empty (safe operation)" << std::endl;
}

void test_multiple_releases() {
  std::cout << "\n=== Test 11: Multiple Operations ===" << std::endl;

  cpp::UniquePtr<int> up;

  std::cout << "Empty UniquePtr created" << std::endl;

  up.reset(new int(10));
  std::cout << "After reset(new int(10)): " << *up << std::endl;

  up.reset(new int(20));
  std::cout << "After reset(new int(20)): " << *up << std::endl;

  int* ptr = up.release();
  std::cout << "After release: " << *ptr << std::endl;

  up.reset(new int(30));
  std::cout << "After reset(new int(30)): " << *up << std::endl;

  delete ptr;
  std::cout << "Cleaned up released pointer" << std::endl;
}

void test_destructor_behavior() {
  std::cout << "\n=== Test 12: Destructor Behavior ===" << std::endl;

  {
    std::cout << "Creating scope with TestClass(999):" << std::endl;
    auto up = cpp::make_unique_ptr<TestClass>(999);
    std::cout << "Value: " << up->getValue() << std::endl;
    std::cout << "Exiting scope..." << std::endl;
  }
  std::cout << "Object should have been destroyed" << std::endl;

  {
    std::cout << "\nCreating scope with released pointer:" << std::endl;
    auto up = cpp::make_unique_ptr<TestClass>(888);
    TestClass* raw = up.release();
    std::cout << "Released pointer, exiting scope..." << std::endl;
    // Destructor should not delete anything
    delete raw;
    std::cout << "Manually deleted raw pointer" << std::endl;
  }
}

// ============================================================================
// DANGEROUS USAGE EXAMPLES - DO NOT UNCOMMENT THESE!
// These examples demonstrate undefined behavior that will crash your program
// ============================================================================

/*
 * DANGER 1: Passing stack pointer to UniquePtr
 * This will cause undefined behavior when UniquePtr tries to delete stack memory
 */
void DANGER_stack_pointer() {
  int stack_var = 42;
  cpp::UniquePtr<int> up(&stack_var);  // DANGER: stack pointer!
  std::cout << "Value: " << *up << std::endl;
  // When up goes out of scope, it will call delete on stack memory = CRASH!
}

/*
 * DANGER 2: Passing 'this' pointer from stack-allocated object
 * This will cause undefined behavior
 */
class DangerousClass {
public:
  void bad_unique_from_this() {
    // DANGER: 'this' might be on stack or already managed
    cpp::UniquePtr<DangerousClass> up(this);
    // When up is destroyed, it will delete 'this' = CRASH!
  }

  void use() { std::cout << "Using object" << std::endl; }
};

void DANGER_this_pointer() {
  DangerousClass obj;          // stack allocated
  obj.bad_unique_from_this();  // DANGER: will try to delete stack object!
  // Program will likely crash here or exhibit undefined behavior
}

/*
 * DANGER 3: Multiple UniquePtrs managing same raw pointer
 * This causes double deletion (worse than SharedPtr because no ref counting)
 */
void DANGER_double_management() {
  int* raw = new int(100);
  cpp::UniquePtr<int> up1(raw);
  cpp::UniquePtr<int> up2(raw);  // DANGER: same raw pointer!
  // When up1 and up2 are destroyed, raw will be deleted twice = CRASH!
}

/*
 * DANGER 4: Reset with same pointer
 * This causes immediate double-free
 */
void DANGER_reset_same_pointer() {
  int* raw = new int(50);
  cpp::UniquePtr<int> up(raw);
  up.reset(raw);  // DANGER: deletes raw, then assigns raw (now dangling)!
  // *up is now undefined behavior - accessing freed memory
}

/*
 * DANGER 5: Using 'this' in heap-allocated object
 * Dangerous because of potential double-free
 */
void DANGER_heap_this_pointer() {
  DangerousClass* obj = new DangerousClass();
  obj->bad_unique_from_this();  // Creates UniquePtr that will delete obj
  // obj is now deleted by UniquePtr's destructor
  // obj->use();  // DANGER: use-after-free!
  // delete obj;  // DANGER: double-free if we try to delete again!
}

// ============================================================================
// SAFE ALTERNATIVES - Correct usage patterns
// ============================================================================

void demonstrate_safe_usage() {
  std::cout << "\n=== Test 13: Safe Usage Patterns ===" << std::endl;

  // SAFE 1: Always use make_unique_ptr or new
  std::cout << "Safe pattern 1: Use make_unique_ptr" << std::endl;
  auto up1 = cpp::make_unique_ptr<int>(42);
  std::cout << "  Value: " << *up1 << std::endl;

  // SAFE 2: Transfer ownership via release/reset
  std::cout << "Safe pattern 2: Transfer ownership correctly" << std::endl;
  cpp::UniquePtr<int> up2;
  up2.reset(up1.release());  // Correct: up1 gives up ownership, up2 takes it
  std::cout << "  up2 value: " << *up2 << std::endl;

  // SAFE 3: Use new directly in constructor
  std::cout << "Safe pattern 3: Use new in constructor" << std::endl;
  cpp::UniquePtr<TestClass> up3(new TestClass(999));
  std::cout << "  Value: " << up3->getValue() << std::endl;

  // SAFE 4: Reset with new allocation
  std::cout << "Safe pattern 4: Reset with new allocation" << std::endl;
  up2.reset(new int(100));
  std::cout << "  New value: " << *up2 << std::endl;

  std::cout << "Leaving scope - safe cleanup:" << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "===== UniquePtr Test Suite =====" << std::endl;

  test_basic_construction();
  test_release();
  test_reset();
  test_with_custom_class();
  test_with_string();
  test_ownership_transfer();
  test_move_constructor();
  test_move_assignment();
  test_get_and_bool();
  test_reset_edge_cases();
  test_multiple_releases();
  test_destructor_behavior();
  demonstrate_safe_usage();

  std::cout << "\n===== All Tests Completed =====" << std::endl;

  std::cout << "\n===== WARNING: Dangerous Usage Patterns =====" << std::endl;
  std::cout << "The following patterns cause UNDEFINED BEHAVIOR:" << std::endl;
  std::cout << "1. UniquePtr<T>(&stack_variable) - deleting stack memory" << std::endl;
  std::cout << "2. UniquePtr<T>(this) - deleting 'this' pointer" << std::endl;
  std::cout << "3. Multiple UniquePtrs from same raw pointer - double free" << std::endl;
  std::cout << "4. up.reset(up.get()) - self-reset causes double free" << std::endl;
  std::cout << "5. Using raw pointer after UniquePtr takes ownership" << std::endl;
  std::cout << "\nALWAYS use make_unique_ptr or pass 'new T(...)' directly!" << std::endl;
  std::cout << "Transfer ownership ONLY via release()/reset() pattern!" << std::endl;

  return 0;
}