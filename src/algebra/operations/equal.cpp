#include <string>
#include <vector>
#include <memory>

#include "algebra/expression.hpp"
#include "algebra/types/symbol.hpp"
#include "algebra/types/integer.hpp"
#include "algebra/types/float.hpp"
#include "algebra/types/fraction.hpp"
#include "algebra/expressions/exponentiation.hpp"
#include "algebra/types/list.hpp"
#include "algebra/operations/base.hpp"
#include "algebra/operations/equal.hpp"

using namespace std;


namespace mathgraph::algebra::operations {
  bool equal(types::Symbol* sym_a, types::Symbol* sym_b) {
    return sym_a->value() == sym_b->value();
  }

  bool equal(types::Integer* int_a, types::Integer* int_b) {
    return int_a->value() == int_b->value();
  }

  bool equal(types::Float* float_a, types::Float* float_b) {
    return float_a->value() == float_b->value();
  }

  bool equal(types::Float* float_a, types::Integer* integer_b) {
    return float_a->value() == integer_b->value();
  }

  bool equal(types::Fraction* frac_a, types::Fraction* frac_b) {
    return equal(frac_a->numerator(), frac_b->numerator()) && equal(frac_a->denominator(), frac_b->denominator());
  }

  bool equal(expressions::Exponentiation* exp_a, expressions::Exponentiation* exp_b) {
    return equal(exp_a->base(), exp_b->base()) && equal(exp_a->exponent(), exp_b->exponent());
  }

  bool equal(types::List* list_a, types::List* list_b) {
    auto elements_a = list_a->elements();
    auto elements_b = list_b->elements();
    if (elements_a.size() != elements_b.size()) return false;
    for (int i = 0; i < elements_a.size(); ++i) {
      if (!equal(elements_a[i], elements_b[i])) return false;
    }
    return true;
  }

  // compares expressions, returns true if they are equal
  // only expressions of the same type can be equal
  bool equal(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b) {
    if (expr_a->type() == expr_b->type()) {
      string type = expr_a->type();
      if (type == "undefined") {
        return true;
      } else if (type == "symbol") {
        return equal(dynamic_cast<types::Symbol*>(expr_a.get()), dynamic_cast<types::Symbol*>(expr_b.get()));
      } else if (type == "integer") {
        return equal(dynamic_cast<types::Integer*>(expr_a.get()), dynamic_cast<types::Integer*>(expr_b.get()));
      } else if (type == "float") {
        return equal(dynamic_cast<types::Float*>(expr_a.get()), dynamic_cast<types::Float*>(expr_b.get()));
      } else if (type == "fraction") {
        return equal(dynamic_cast<types::Fraction*>(expr_a.get()), dynamic_cast<types::Fraction*>(expr_b.get()));
      } else if (type == "exponentiation") {
        return equal(dynamic_cast<expressions::Exponentiation*>(expr_a.get()), dynamic_cast<expressions::Exponentiation*>(expr_b.get()));
      } else if (type == "list" || type == "addition" || type == "multiplication") {
        return equal(dynamic_cast<types::List*>(expr_a.get()), dynamic_cast<types::List*>(expr_b.get()));
      }
    } else if ((expr_a->type() == "float" || expr_a->type() == "integer") && (expr_b->type() == "float" || expr_b->type() == "integer")) {
      if (expr_a->type() == "float") {
        return equal(dynamic_cast<types::Float*>(expr_a.get()), dynamic_cast<types::Integer*>(expr_b.get()));
      }
      return equal(dynamic_cast<types::Float*>(expr_b.get()), dynamic_cast<types::Integer*>(expr_a.get()));
    }
    return false;
  }
}
