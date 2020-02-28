#include <memory>
#include <cmath>

#include "algebra/expression.hpp"
#include "algebra/types/float.hpp"
#include "algebra/types/integer.hpp"
#include "algebra/types/fraction.hpp"
#include "algebra/expressions/exponentiation.hpp"
#include "algebra/expressions/multiplication.hpp"
#include "algebra/operations/base.hpp"
#include "algebra/operations/add.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  shared_ptr<Expression> power(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b) {
    // If the expressions have dependencies, return a complex Addition
    if (expr_a->dependencies().size() + expr_b->dependencies().size() != 0 || expr_b == "fraction") {
      return expressions::Exponentiation::_reduce(expr_a, expr_b);
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
        new_list_elements.push_back(power(element, expr_b));
      }
      return types::List::construct(new_list_elements);
    } else if (expr_b == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto elements = dynamic_cast<types::List*>(expr_b.get())->elements();
      for (auto element : elements) {
        new_list_elements.push_back(power(expr_a, element));
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
        return types::Float::construct(pow(a, b));
      }
      return types::Integer::construct(pow(a, b));
    } else if (expr_a == "fraction" && expr_b == "number") {
      auto frac = dynamic_cast<types::Fraction*>(expr_a.get());
      return types::Fraction::_reduce(power(frac->numerator(), expr_b), power(frac->denominator(), expr_b));
    }
    return undefined;
  }

}
