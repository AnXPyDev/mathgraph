#include <memory>

#include "../base.hpp"
#include "../expression.hpp"
#include "../number.hpp"
#include "../fraction.hpp"
#include "../multiplication.hpp"
#include "base.hpp"
#include "add.hpp"

namespace mathgraph::algebra::operations {
  shared_ptr<Expression> multiply(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b) {
    // If the expressions have dependencies, return a complex Addition
    if (expr_a->dependencies().size() + expr_b->dependencies().size() != 0) {
      return Multiplication::_reduce({expr_a, expr_b});
    }

    if (expr_a->type() == "undefined" || expr_b->type() == "undefined") {
      return undefined;
    } else if (expr_a->type() == "error") {
      return expr_a;
    } else if (expr_b->type() == "error") {
      return expr_b;
    } else if (expr_a->type() == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto elements = dynamic_cast<List*>(expr_a.get())->elements();
      for (auto element : elements) {
        new_list_elements.push_back(multiply(element, expr_b));
      }
      return List::construct(new_list_elements);
    } else if (expr_b->type() == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto elements = dynamic_cast<List*>(expr_b.get())->elements();
      for (auto element : elements) {
        new_list_elements.push_back(multiply(expr_a, element));
      }
      return List::construct(new_list_elements);
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
    return Fraction::_reduce(Number::construct(fraction_matrix[0][0] * fraction_matrix[1][0]), Number::construct(fraction_matrix[0][1] * fraction_matrix[1][1]));
  }

}
