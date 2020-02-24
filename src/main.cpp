#include <iostream>

#include "algebra.hpp"

using namespace std;
using namespace mathgraph;
using namespace mathgraph::algebra;

#define SYM Symbol::construct
#define INT Integer::construct
#define FLOAT Float::construct
#define FRAC Fraction::construct
#define EXP Exponentiation::construct
#define LIST List::construct
#define ADD Addition::construct
#define MULT Multiplication::construct
#define FUNC Function::construct
#define SCOPE Scope::construct

int main() {
  auto global_scope = SCOPE();
  global_scope->set_key(SYM("x"), INT(5));
  // auto expr = ADD({MULT({FLOAT(2.5), INT(2), SYM("x")}), LIST({FLOAT(5.132), INT(33)})});
  auto expr = FUNC(undefined, MULT({INT(5), INT(3)}));
  auto reduced_expr = Expression::_reduce(expr);
  auto evaluated_expr = Expression::_evaluate(reduced_expr, global_scope);
  auto straight_to_eval = Expression::_evaluate(expr, global_scope);
  cout << expr << endl;
  cout << reduced_expr << endl;
  cout << evaluated_expr << endl;
  cout << straight_to_eval << endl;

  return 0;
}
