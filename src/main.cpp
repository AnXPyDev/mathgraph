#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "algebra.hpp"

using namespace mathgraph::algebra;

int main() {

  auto enviroment = new Enviroment();

  enviroment->set_value(new Symbol("x"), new expression::Constant(new value::Number(3)));
  
  auto n1 = new expression::Reference(new Symbol("x"));
  auto n2 = new expression::Constant(new value::Number(2));
  auto n3 = new expression::Constant(new value::Number(3));
  auto n4 = new expression::Constant(new value::Number(4));

  auto l1 = new expression::List({n1, n2, n3, n4});

  std::cout << l1->get_value(enviroment, true) << std::endl;

  
}
