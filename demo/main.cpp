#include <sharedptrtests.hpp>

int main() {
  int a = 1;
  SharedPtr<int> a_ptr;
  SharedPtr<int> a1_ptr(&a);
  SharedPtr<int> a2_ptr(&a);
  std::cout << *a1_ptr.get() << std::endl;
  SharedPtr<int> ex = a1_ptr;
}
