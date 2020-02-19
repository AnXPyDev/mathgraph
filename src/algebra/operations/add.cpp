#include <memory>

#include "../base.hpp"
#include "../expression.hpp"
#include "../number.hpp"
#include "../fraction.hpp"
#include "../addition.hpp"
#include "base.hpp"
#include "add.hpp"

namespace mathgraph::algebra::operations {
  shared_ptr<Expression> add(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b) {
    // If the expressions have dependencies, return a complex Addition
    if (expr_a->dependencies().size() + expr_b->dependencies().size() != 0) {
      return Addition::_reduce({expr_a, expr_b});
    }

    if (expr_a->type() == "undefined" || expr_b->type() == "undefined") {
      return undefined;
    }

    number_t fraction_matrix[2][2] = {{0,1}, {0,1}};

    int i = 0;
    for (auto expr : {expr_a, expr_b}) {
      if (expr->type() == "number") {
        fraction_matrix[i][0] = dynamic_cast<Number*>(expr.get())->value();
      } else if (expr->type() == "fraction") {
        auto frac = dynamic_cast<Fraction*>(expr.get());
        fraction_matrix[i][0] = dynamic_cast<Number*>(frac->numerator().get())->value();
        fraction_matrix[i][1] = dynamic_cast<Number*>(frac->denominator().get())->value();
      }
      ++i;
    }
    return Fraction::_reduce(Number::construct(fraction_matrix[0][0] * fraction_matrix[1][1] + fraction_matrix[1][0] * fraction_matrix[0][1]), Number::construct(fraction_matrix[0][1] * fraction_matrix[1][1]));
  }

}
