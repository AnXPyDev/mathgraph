#include <iostream>

#include "algebra.hpp"

using namespace std;
using namespace mathgraph;

#define SYM algebra::Symbol::construct
#define NUM algebra::Number::construct
#define FRAC algebra::Fraction::construct
#define EXP algebra::Exponentiation::construct
#define LIST algebra::List::construct
#define ADD algebra::Addition::construct
#define MULT algebra::Multiplication::construct

int main() {
  cout << FRAC(EXP(SYM("x"), NUM(3)), SYM("x")) << endl;
  return 0;
}
