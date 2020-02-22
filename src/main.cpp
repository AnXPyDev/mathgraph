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
#define SCOPE Scope::construct

int main() {
  auto global_scope = SCOPE();
  global_scope->set_key(SYM("x"), LIST({NUM(5), NUM(10), NUM(15)}));
  auto expr = EXP(LIST({NUM(2), SYM("x")}), NUM(2));
  auto reduced_expr = Expression::_reduce(expr);
  auto evaluated_expr = Expression::_evaluate(reduced_expr, global_scope);
  cout << expr << endl;
  cout << reduced_expr << endl;
  cout << evaluated_expr << endl;
  return 0;
}
