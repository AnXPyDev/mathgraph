#pragma once

#include <iostream>

#include "algebra/expression.hpp"
#include "algebra/scope.hpp"
#include "algebra/functions/base.hpp"
#include "algebra/functions/two_expr_function.hpp"

using namespace std;

namespace mathgraph::algebra::functions {
  struct More : public Two_expr_function {
    ostream& output_to_stream(ostream& stream);
    expr_t evaluate(expr_t caller = undefined, scope_t scope = empty_scope);
    expr_t reduce(expr_t caller = undefined, scope_t scope = empty_scope);
    More(expr_t expr_a, expr_t expr_b);
    static expr_t _evaluate(expr_t expr_a = undefined, expr_t expr_b = undefined, scope_t scope = empty_scope);
    static expr_t _reduce(expr_t expr_a = undefined, expr_t expr_b = undefined, scope_t scope = empty_scope);
    static expr_t construct(expr_t expr_a = undefined, expr_t expr_b = undefined);
  };
}
