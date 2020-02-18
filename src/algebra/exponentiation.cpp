#include <iostream>
#include <memory>
#include <vector>

#include "base.hpp"
#include "expression.hpp"
#include "number.hpp"
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
  shared_ptr<Expression> Exponentiation::reduce(shared_ptr<Expression> caller) {
    return Exponentiation::_reduce(this->_base, this->_exponent);
  }
  shared_ptr<Expression> Exponentiation::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Exponentiation::_evaluate(this->_base, this->_exponent, scope);
  }
  Exponentiation::Exponentiation(shared_ptr<Expression> base, shared_ptr<Expression> exponent) : _base{ base }, _exponent{ exponent } {
    this->_type = "exponentiation";
  }
  shared_ptr<Expression> Exponentiation::_reduce(shared_ptr<Expression> base, shared_ptr<Expression> exponent) {
    if (base == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto list_elements = dynamic_cast<List*>(base.get())->elements();
      for (auto list_element : list_elements) {
        new_list_elements.push_back(Exponentiation::construct(list_element, exponent));
      }
      return List::construct(new_list_elements);
    } else if (base == "multiplication") {
      vector<shared_ptr<Expression>> new_mult_elements;
      auto mult_elements = dynamic_cast<Multiplication*>(base.get())->elements();
      for (auto mult_element : mult_elements) {
        new_mult_elements.push_back(Exponentiation::construct(mult_element, exponent));
      }
      return Multiplication::construct(new_mult_elements);
    } else if (exponent == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto list_elements = dynamic_cast<List*>(exponent.get())->elements();
      for (auto list_element : list_elements) {
        new_list_elements.push_back(Exponentiation::construct(base, list_element));
      }
      return List::construct(new_list_elements);
    } else if (base == Number::construct(1) || exponent == Number::construct(1)) {
      return base;
    } else if (exponent == Number::construct(0)) {
      return Number::construct(1);
    } else if (base == "exponentiation") {
      auto exp = dynamic_cast<Exponentiation*>(base.get());
      return Exponentiation::construct(exp->base(), Multiplication::construct({exp->exponent(), exponent}));
    } else if (base == "fraction") {
      auto frac = dynamic_cast<Fraction*>(base.get());
      return Fraction::construct(Exponentiation::construct(frac->numerator(), exponent), Exponentiation::construct(frac->denominator(), exponent));
    }
    return shared_ptr<Expression>(new Exponentiation(base, exponent));
  }
  shared_ptr<Expression> Exponentiation::_evaluate(shared_ptr<Expression> base, shared_ptr<Expression> exponent, shared_ptr<Scope> scope) {
    // TODO: implement exponentiation evaluation
    return undefined;
  }
  shared_ptr<Expression> Exponentiation::construct(shared_ptr<Expression> base, shared_ptr<Expression> exponent) {
    return Exponentiation::_reduce(base, exponent);
  }
}