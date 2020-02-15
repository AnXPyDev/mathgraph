#include <iostream>

#include "algebra.hpp"

using namespace mathgraph;

#define SYM algebra::Symbol::construct
#define NUM algebra::Number::construct
#define BOOL algebra::Boolean::construct
#define LIST algebra::List::construct
#define ADD algebra::Addition::construct
#define MULT algebra::Multiplication::construct
#define INV algebra::Inversion::construct
#define NEG algebra::Negation::construct
#define EXP algebra::Exponentiation::construct

int main() {
  std::cout << ADD({SYM("x"), SYM("x"), MULT({SYM("x"), NUM(2)}), MULT({SYM("x"), NUM(2)}), MULT({SYM("x"), NUM(2)})}) << std::endl;
}
