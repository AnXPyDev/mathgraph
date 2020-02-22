#include <memory>
#include <vector>

#include "../base.hpp"
#include "../expression.hpp"
#include "../integer.hpp"
#include "../float.hpp"
#include "../fraction.hpp"
#include "../list.hpp"
#include "../multiplication.hpp"
#include "base.hpp"
#include "multiply.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  shared_ptr<Expression> multiply(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b) {
    // If the expressions have dependencies, return a complex Addition
    if (expr_a->dependencies().size() + expr_b->dependencies().size() != 0) {
      return Multiplication::_reduce({expr_a, expr_b});
    }

    if (expr_a == "undefined" || expr_b == "undefined") {
      return undefined;
    } else if (expr_a == "error") {
      return expr_a;
    } else if (expr_b == "error") {
      return expr_b;
    } else if (expr_a == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto elements = dynamic_cast<List*>(expr_a.get())->elements();
      for (auto element : elements) {
        new_list_elements.push_back(multiply(element, expr_b));
      }
      return List::construct(new_list_elements);
    } else if (expr_b == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto elements = dynamic_cast<List*>(expr_b.get())->elements();
      for (auto element : elements) {
        new_list_elements.push_back(multiply(expr_a, element));
      }
      return List::construct(new_list_elements);
    } else if (expr_a == "number" && expr_b == "number") {
      float_t a;
      float_t b;
      if (expr_a == "float") {
        a = dynamic_cast<Float*>(expr_a.get())->value();
      } else {
        a = dynamic_cast<Integer*>(expr_a.get())->value();
      }
      if (expr_b == "float") {
        b = dynamic_cast<Float*>(expr_b.get())->value();
      } else {
        b = dynamic_cast<Integer*>(expr_b.get())->value();
      }

      if (expr_a == "float" || expr_b == "float") {
        return Float::construct(a * b);
      }
      return Integer::construct(a * b);
    } else if (expr_a == "fraction" || expr_b == "fraction") {
      shared_ptr<Expression> fraction_matrix[2][2];
      short int i = 0;
      for (auto expr : {expr_a, expr_b}) {
        if (expr == "fraction") {
          auto frac = dynamic_cast<Fraction*>(expr.get());
          fraction_matrix[i][0] = frac->numerator();
          fraction_matrix[i][1] = frac->denominator();
        } else {
          fraction_matrix[i][0] = expr;
          fraction_matrix[i][1] = Integer::construct(1);
        }
        ++i;
      }
      return Fraction::_reduce(multiply(fraction_matrix[0][0], fraction_matrix[1][0]), multiply(fraction_matrix[0][1], fraction_matrix[1][1]));
    }

    return undefined;
  }

}
