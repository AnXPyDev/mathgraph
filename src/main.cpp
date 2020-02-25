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
#define CALL Call::construct
#define EVAL Expression::_evaluate

int main() {
  auto global_scope = SCOPE();
  EVAL(ASS(SYM("f"), FUNC(MULT({INT(2), SYM("x"), SYM("y")}), LIST({SYM("x"), SYM("y")}))), global_scope);

  for (int i = 1; i <= 100000; ++i) {
    EVAL(CALL(SYM("f"), INT(i)), global_scope);
  }
  
}
