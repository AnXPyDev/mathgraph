#include <iostream>

#include "algebra.hpp"

using namespace std;
using namespace mathgraph;
using namespace mathgraph::algebra;

#define SYM Symbol::construct
#define NUM Number::construct
#define FRAC Fraction::construct
#define EXP Exponentiation::construct
#define LIST List::construct
#define ADD Addition::construct
#define MULT Multiplication::construct

int main() {
  auto expr = EXP(NUM(3), NUM(2));
  cout << expr << endl;
  cout << Expression::_reduce(expr) << endl;
  return 0;
}
