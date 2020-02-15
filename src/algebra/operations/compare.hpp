#pragma once

#include <memory>

#include "base.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  bool equal(shared_ptr<Expression> a = undefined, shared_ptr<Expression> b = undefined);
  bool equal(Expression* a, Expression* b);
  bool equal(Number* a, Number* b);
  bool equal(Boolean* a, Boolean* b);
  bool equal(List* a, List* b);
  bool equal(Symbol* a, Symbol* b);
  bool equal(Interval* a, Interval* b);
  bool equal(Point* a, Point* b);
  bool equal(Vector* a, Vector* b);
  bool equal(Addition* a, Addition* b);
  bool equal(Multiplication* a, Multiplication* b);
  bool equal(Exponentiation* a, Exponentiation* b);
  bool equal(Negation* a, Negation* b);
  bool equal(Inversion* a, Inversion* b);
  bool equal(Conjunction* a, Conjunction* b);
  bool equal(Disjunction* a, Disjunction* b);
}
