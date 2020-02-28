#include <memory>
#include <vector>

#include "algebra/operations/base.hpp"
#include "algebra/expression.hpp"
#include "algebra/types/integer.hpp"
#include "algebra/types/float.hpp"
#include "algebra/types/fraction.hpp"
#include "algebra/types/list.hpp"
#include "algebra/expressions/addition.hpp"
#include "algebra/operations/multiply.hpp"
#include "algebra/operations/add.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  shared_ptr<Expression> add(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b) {
    // If the expressions have dependencies, return a complex Addition
    if (expr_a->dependencies().size() + expr_b->dependencies().size() != 0) {
      return expressions::Addition::_reduce({expr_a, expr_b});
    }

    if (expr_a == "undefined" || expr_b == "undefined") {
      return undefined;
    } else if (expr_a == "error") {
      return expr_a;
    } else if (expr_b == "error") {
      return expr_b;
    } else if (expr_a == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto elements = dynamic_cast<types::List*>(expr_a.get())->elements();
      for (auto element : elements) {
        new_list_elements.push_back(add(element, expr_b));
      }
      return types::List::construct(new_list_elements);
    } else if (expr_b == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto elements = dynamic_cast<types::List*>(expr_b.get())->elements();
      for (auto element : elements) {
        new_list_elements.push_back(add(expr_a, element));
      }
      return types::List::construct(new_list_elements);
    } else if (expr_a == "number" && expr_b == "number") {
      float_t a;
      float_t b;
      if (expr_a == "float") {
        a = dynamic_cast<types::Float*>(expr_a.get())->value();
      } else {
        a = dynamic_cast<types::Integer*>(expr_a.get())->value();
      }
      if (expr_b == "float") {
        b = dynamic_cast<types::Float*>(expr_b.get())->value();
      } else {
        b = dynamic_cast<types::Integer*>(expr_b.get())->value();
      }

      if (expr_a == "float" || expr_b == "float") {
        return types::Float::construct(a + b);
      }
      return types::Integer::construct(a + b);
    } else if (expr_a == "fraction" || expr_b == "fraction") {
      shared_ptr<Expression> fraction_matrix[2][2];
      short int i = 0;
      for (auto expr : {expr_a, expr_b}) {
        if (expr == "fraction") {
          auto frac = dynamic_cast<types::Fraction*>(expr.get());
          fraction_matrix[i][0] = frac->numerator();
          fraction_matrix[i][1] = frac->denominator();
        } else {
          fraction_matrix[i][0] = expr;
          fraction_matrix[i][1] = types::Integer::construct(1);
        }
        ++i;
      }
      return types::Fraction::_reduce(add(multiply(fraction_matrix[0][0], fraction_matrix[1][1]), multiply(fraction_matrix[1][0], fraction_matrix[0][1])), multiply(fraction_matrix[0][1], fraction_matrix[1][1]));
    }

    return undefined;
  }

}
