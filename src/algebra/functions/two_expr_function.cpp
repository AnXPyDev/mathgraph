#include <iostream>

#include "algebra/expression.hpp"
#include "algebra/functions/base.hpp"
#include "algebra/functions/two_expr_function.hpp"

namespace mathgraph::algebra::functions {
  expr_t Two_expr_function::expr_a() { return this->_expr_a; }
  expr_t Two_expr_function::expr_b() { return this->_expr_b; }
  Two_expr_function::Two_expr_function(expr_t expr_a, expr_t expr_b) : _expr_a{ expr_a }, _expr_b{ expr_b } {
    this->_type = "functions::Two_expr_function";
  }
}
