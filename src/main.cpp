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
#define ASS Assignment::construct

int main() {
  auto global_scope = SCOPE();
  // auto expr = ADD({MULT({FLOAT(2.5), INT(2), SYM("x")}), LIST({FLOAT(5.132), INT(33)})});
  for (auto expr : {
      ASS(SYM("x"), LIST({FLOAT(5.51321), INT(3)})),
        ASS(SYM("y"), FLOAT(3.1341)),
        EXP(SYM("x"), SYM("y")),
    }) {
    cout << "---------------------" << endl;
    auto reduced_expr = Expression::_reduce(expr);
    auto evaluated_expr = Expression::_evaluate(reduced_expr, global_scope);
    auto straight_to_eval = Expression::_evaluate(expr, global_scope);
    cout << "base:                " << expr << endl;
    cout << "reduced:             " << reduced_expr << endl;
    cout << "evaluated:           " << evaluated_expr << endl;
    cout << "evaluated from base: " << straight_to_eval << endl;
  }
  return 0;
}
