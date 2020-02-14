#include <iostream>

#include "algebra.hpp"

using namespace mathgraph;

int main() {
  std::cout << algebra::Symbol::construct("x") << std::endl;
  std::cout << algebra::Number::construct(13.321321) << std::endl;
  std::cout << algebra::Boolean::construct(true) << std::endl;
}
