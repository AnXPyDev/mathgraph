#include <iostream>
#include <memory>
#include <vector>

#include "base.hpp"
#include "scope.hpp"
#include "expression.hpp"
#include "integer.hpp"
#include "float.hpp"
#include "fraction.hpp"
#include "addition.hpp"
#include "multiplication.hpp"
#include "operations.hpp"
#include "exponentiation.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Exponentiation::output_to_stream(ostream& stream) {
    return stream << this->_base << "^" << this->_exponent;
  }
  shared_ptr<Expression> Exponentiation::base() { return this->_base; }
  shared_ptr<Expression> Exponentiation::exponent() { return this->_exponent; }
  vector<shared_ptr<Expression>> Exponentiation::dependencies(shared_ptr<Expression> caller) {
    vector<shared_ptr<Expression>> result = {};
    for (auto element : vector<shared_ptr<Expression>>({this->_base, this->_exponent})) {
      for (auto dependency : element->dependencies(element)) {
        // only add unique dependencies
        bool is_unique = true;
        for (auto result_element : result) {
          if (operations::equal(result_element, dependency)) {
            is_unique = false;
            break;
          }
        }
        if (is_unique) result.push_back(dependency);
      }
    }
    return result;
  }
  shared_ptr<Expression> Exponentiation::reduce(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Exponentiation::_reduce(this->_base, this->_exponent, scope);
  }
  shared_ptr<Expression> Exponentiation::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Exponentiation::_evaluate(this->_base, this->_exponent, scope);
  }
  Exponentiation::Exponentiation(shared_ptr<Expression> base, shared_ptr<Expression> exponent) : _base{ base }, _exponent{ exponent } {
    this->_type = "exponentiation";
  }
  shared_ptr<Expression> Exponentiation::_reduce(shared_ptr<Expression> base, shared_ptr<Expression> exponent, shared_ptr<Scope> scope) {
    base = Expression::_reduce(base, scope);
    exponent = Expression::_reduce(exponent, scope);
    if (base == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto list_elements = dynamic_cast<List*>(base.get())->elements();
      for (auto list_element : list_elements) {
        new_list_elements.push_back(Exponentiation::_reduce(list_element, exponent, scope));
      }
      return List::construct(new_list_elements);
    } else if (base == "multiplication") {
      vector<shared_ptr<Expression>> new_mult_elements;
      auto mult_elements = dynamic_cast<Multiplication*>(base.get())->elements();
      for (auto mult_element : mult_elements) {
        new_mult_elements.push_back(Exponentiation::_reduce(mult_element, exponent, scope));
      }
      return Multiplication::_reduce(new_mult_elements, scope);
    } else if (exponent == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto list_elements = dynamic_cast<List*>(exponent.get())->elements();
      for (auto list_element : list_elements) {
        new_list_elements.push_back(Exponentiation::_reduce(base, list_element, scope));
      }
      return List::construct(new_list_elements);
    } else if (base == Integer::construct(1) || exponent == Integer::construct(1)) {
      return base;
    } else if (exponent == Integer::construct(0)) {
      return Integer::construct(1);
    } else if (base == "exponentiation") {
      auto exp = dynamic_cast<Exponentiation*>(base.get());
      return Exponentiation::_reduce(exp->base(), Multiplication::_reduce({exp->exponent(), exponent}, scope), scope);
    } else if (base->dependencies().size() + exponent->dependencies().size() == 0 && exponent == "integer") {
      return operations::power(base, exponent);
    } else if (base == "fraction") {
      auto frac = dynamic_cast<Fraction*>(base.get());
      return Fraction::_reduce(Exponentiation::_reduce(frac->numerator(), exponent, scope), Exponentiation::_reduce(frac->denominator(), exponent), scope);
    }
    return shared_ptr<Expression>(new Exponentiation(base, exponent));
  }
  shared_ptr<Expression> Exponentiation::_evaluate(shared_ptr<Expression> base, shared_ptr<Expression> exponent, shared_ptr<Scope> scope) {
    return operations::power(base->evaluate(base, scope), exponent->evaluate(exponent, scope));
  }
  shared_ptr<Expression> Exponentiation::construct(shared_ptr<Expression> base, shared_ptr<Expression> exponent) {
    return shared_ptr<Expression>(new Exponentiation(base, exponent));
  }
}
