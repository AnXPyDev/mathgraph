#include "algebra/expression.hpp"
#include "algebra/types/boolean.hpp"
#include "algebra/types/integer.hpp"
#include "algebra/types/float.hpp"
#include "algebra/types/fraction.hpp"
#include "algebra/functions/less.hpp"
#include "algebra/functions/more.hpp"
#include "algebra/operations/base.hpp"
#include "algebra/operations/compare.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  float_t* to_float_list(expr_t expr) {
    float_t result[2] = {0, 1};
    if (expr == "integer") {
      result[0] = dynamic_cast<types::Integer*>(expr.get())->value();
    } else if (expr == "float") {
      result[0] = dynamic_cast<types::Float*>(expr.get())->value();
    } else if (expr == "fraction") {
      auto frac = dynamic_cast<types::Fraction*>(expr.get());
      auto numerator = frac->numerator();
      auto denominator = frac->numerator();
      result[0] = to_float_list(numerator)[0];
      result[1] = to_float_list(numerator)[0];
    }
    return result;
  }
  expr_t less(expr_t expr_a, expr_t expr_b) {
    if (expr_a->dependencies().size() != 0 || expr_b->dependencies().size() != 0) {
      return functions::Less::construct(expr_a, expr_b);
    }
    float_t* fraction_matrix[2] = {};
    int i = 0;
    for (auto expr : {expr_a, expr_b}) {
      fraction_matrix[i] = to_float_list(expr);
      ++i;
    }
    if (fraction_matrix[0][0] * fraction_matrix[1][1] < fraction_matrix[0][1] * fraction_matrix[1][0]) {
      return types::b_true;
    }
    return types::b_false;
  }
}
