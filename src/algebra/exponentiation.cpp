#include <memory>
#include <vector>
#include <cmath>
#include <iostream>

#include "number.hpp"
#include "list.hpp"
#include "boolean.hpp"
#include "inversion.hpp"
#include "negation.hpp"
#include "multiplication.hpp"
#include "exponentiation.hpp"

using namespace std;

namespace mathgraph::algebra {
  shared_ptr<Expression> Exponentiation::get_base() {
    return this->base;
  }

  shared_ptr<Expression> Exponentiation::get_exponent() {
    return this->exponent;
  }

  ostream& Exponentiation::output_to_stream(ostream& os) {
    os << this->base << "^" << this->exponent;
    return os;
  }

  Exponentiation::Exponentiation(shared_ptr<Expression> base, shared_ptr<Expression> exponent) : base{ base }, exponent{ exponent } {
    this->type = "exponentiation";
  }

  shared_ptr<Expression> Exponentiation::construct(shared_ptr<Expression> base, shared_ptr<Expression> exponent) {
    return Exponentiation::evaluate(base, exponent);
  }

  shared_ptr<Expression> Exponentiation::evaluate(shared_ptr<Scope> scope, shared_ptr<Expression> caller) {
    return Exponentiation::evaluate(this->base, this->exponent, scope);
  }

  shared_ptr<Expression> Exponentiation::evaluate(shared_ptr<Expression> base, shared_ptr<Expression> exponent, shared_ptr<Scope> scope) {
    base = base->evaluate(scope, base);
    exponent = exponent->evaluate(scope, exponent);
    if (exponent->get_type() == "number") {
      auto n = dynamic_cast<Number*>(exponent.get())->get();
      if (n == 0) {
        return Number::construct(1);
      } else if (n == 1) {
        return base;
      } else if (n < 0) {
        return Inversion::construct(Exponentiation::construct(base, Negation::construct(exponent)));
      }
    }
    if (base->get_type() == "number") {
      auto n = dynamic_cast<Number*>(base.get())->get();
      if (n == 0) {
        return base;
      } else if (n == 1) {
        return base;
      }
    }
    if (exponent->get_type() == "number" && base->get_type() == "number") {
      return Number::construct(pow(dynamic_cast<Number*>(base.get())->get(), dynamic_cast<Number*>(exponent.get())->get()));
    } else if (base->get_type() == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto list_elements = dynamic_cast<List*>(base.get())->get();
      for (auto list_element : list_elements) {
        new_list_elements.push_back(Exponentiation::construct(list_element, exponent));
      }
      return List::construct(new_list_elements);
    } else if (exponent->get_type() == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto list_elements = dynamic_cast<List*>(exponent.get())->get();
      for (auto list_element : list_elements) {
        new_list_elements.push_back(Exponentiation::construct(base, list_element));
      }
      return List::construct(new_list_elements);
    } else if (base->get_type() == "exponentiation") {
      auto temp = dynamic_cast<Exponentiation*>(base.get());
      base = temp->get_base();
      exponent = Multiplication::construct({temp->get_exponent(), exponent});
    }
    return shared_ptr<Expression>(new Exponentiation(base, exponent));
  }
}
