#include <memory>
#include <cmath>

#include "../base.hpp"
#include "../expression.hpp"
#include "../float.hpp"
#include "../integer.hpp"
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
        new_list_elements.push_back(power(element, expr_b));
      }
      return List::construct(new_list_elements);
    } else if (expr_b == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto elements = dynamic_cast<List*>(expr_b.get())->elements();
      for (auto element : elements) {
        new_list_elements.push_back(power(expr_a, element));
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
        return Float::construct(pow(a, b));
      }
      return Integer::construct(pow(a, b));
    } else if (expr_a == "fraction" && expr_b == "number") {
      auto frac = dynamic_cast<Fraction*>(expr_a.get());
      return Fraction::_reduce(power(frac->numerator(), expr_b), power(frac->denominator(), expr_b));
    }
    return undefined;
  }

}
