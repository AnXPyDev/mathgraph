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
#define BOOL expressions::Boolean_conversion::construct

int main() {
  auto global_scope = SCOPE();
  EVAL(ASS(SYM("f"), FUNC(MULT({INT(2), SYM("x"), SYM("y")}), LIST({SYM("x"), SYM("y")}))), global_scope);

  for (int i = 1; i <= 1000; ++i) {
    EVAL(CALL(SYM("f"), INT(i)), global_scope);
  }
  
}
