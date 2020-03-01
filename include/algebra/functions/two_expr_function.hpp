#pragma once

#include "algebra/expression.hpp"
#include "algebra/functions/base.hpp"

using namespace std;

namespace mathgraph::algebra::functions {
  struct Two_expr_function : public Expression {
    expr_t expr_a();
    expr_t expr_b();
    Two_expr_function(expr_t expr_a, expr_t expr_b);
  protected:
    expr_t _expr_a;
    expr_t _expr_b;
  };
}
