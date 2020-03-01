#include <iostream>

#include "algebra.hpp"

using namespace std;
using namespace mathgraph;
using namespace mathgraph::algebra;

#define SYM types::Symbol::construct
#define INT types::Integer::construct
#define FLOAT types::Float::construct
#define FRAC types::Fraction::construct
#define EXP expressions::Exponentiation::construct
#define LIST types::List::construct
#define ADD expressions::Addition::construct
#define MULT expressions::Multiplication::construct
#define FUNC types::Function::construct
#define SCOPE Scope::construct
#define ASS expressions::Assignment::construct
#define CALL expressions::Call::construct
#define EVAL Expression::_evaluate
#define REDUCE Expression::_reduce
#define BOOL_CONV expressions::Boolean_conversion::construct
#define BOOL types::Boolean::construct
#define IF functions::If::construct
#define OR functions::Or::construct
#define AND functions::And::construct

int main() {
  //bruh
  auto global_scope = SCOPE();
  vector<shared_ptr<Expression>> exprs;
  exprs.push_back(ASS(SYM("f"), FUNC(ADD({MULT({INT(2), SYM("x")}), INT(2)}), LIST({SYM("x")}))));
  exprs.push_back(CALL(SYM("f"), LIST({LIST({INT(1), INT(2), INT(3), INT(4)})})));
  exprs.push_back(CALL(SYM("f"), LIST({LIST({INT(1), INT(2), INT(3), INT(4)})})));
  exprs.push_back(IF(BOOL(true), INT(5), INT(2)));
  exprs.push_back(ASS(SYM("x"), INT(5)));
  exprs.push_back(ASS(SYM("y"), INT(6)));
  exprs.push_back(AND(SYM("x"), SYM("y")));
  exprs.push_back(OR(SYM("x"), SYM("y")));
  for (auto expr : exprs) {
    auto reduced_expr = Expression::_reduce(expr);
    auto evaluated_expr = Expression::_evaluate(expr, global_scope);
    auto evaluated_from_reduced_expr = Expression::_evaluate(reduced_expr, global_scope);
    cout << "--------------------------" << endl;
    cout << "base:                     " << expr << endl;
    cout << "reduced:                  " << reduced_expr << endl;
    cout << "evaluated from base:      " << evaluated_expr << endl;
    cout << "evaluated from reduction: " << evaluated_from_reduced_expr << endl;
  }
  
}
