#include <memory>
#include <cmath>

#include "../base.hpp"
#include "../expression.hpp"
#include "../number.hpp"
#include "../fraction.hpp"
#include "../exponentiation.hpp"
#include "../multiplication.hpp"
#include "base.hpp"
#include "add.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  shared_ptr<Expression> power(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b) {
    // If the expressions have dependencies, return a complex Addition
    if (expr_a->dependencies().size() + expr_b->dependencies().size() != 0 || expr_b == "fraction") {
      return Exponentiation::_reduce(expr_a, expr_b);
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
        new_list_elements.push_back(power(element, expr_b));
      }
      return List::construct(new_list_elements);
    } else if (expr_b->type() == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto elements = dynamic_cast<List*>(expr_b.get())->elements();
      for (auto element : elements) {
        new_list_elements.push_back(power(expr_a, element));
      }
      return List::construct(new_list_elements);
    }    if (expr_a->type() == "undefined" || expr_b->type() == "undefined") {
      return undefined;
    }

    if (expr_a->type() == "error") {
      return expr_a;
    } else if (expr_b->type() == "error") {
      return expr_b;
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
    return Fraction::_reduce(Number::construct(pow(fraction_matrix[0][0], fraction_matrix[1][0])), Number::construct(pow(fraction_matrix[0][1], fraction_matrix[1][0])));
  }

}
