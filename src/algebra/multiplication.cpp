#include <iostream>
#include <memory>

#include "base.hpp"
#include "expression.hpp"
#include "number.hpp"
#include "fraction.hpp"
#include "exponentiation.hpp"
#include "list.hpp"
#include "operations.hpp"
#include "addition.hpp"
#include "multiplication.hpp"

namespace mathgraph::algebra {
  ostream& Multiplication::output_to_stream(ostream& stream) {
    stream << "(";
    for (auto it = this->_elements.begin(); it < this->_elements.end() -1; ++it) {
      stream << *it << " * ";
    }
    return stream << *(this->_elements.end() - 1) << ")";
  }
  shared_ptr<Expression> Multiplication::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Multiplication::_evaluate(this->_elements, scope);
  }
  shared_ptr<Expression> Multiplication::known() {
    for (auto element : this->_elements) {
      if ((element->type() == "number" || element->type() == "fraction") && element->dependencies().size() == 0) {
        return element;
      }
    }
    return Number::construct(1);
  }
  vector<shared_ptr<Expression>> Multiplication::unknown() {
    auto known = this->known();
    auto result = this->_elements;
    for (auto it = result.begin(); it < result.end(); ++it) {
      if (*it == known) {
        result.erase(it--);
        break;
      }
    }
    return result;
  }
  Multiplication::Multiplication(vector<shared_ptr<Expression>> elements) : List(elements) {
    this->_type = "multiplication";
  }
  shared_ptr<Expression> Multiplication::construct(vector<shared_ptr<Expression>> elements) {
    return Multiplication::_reduce(elements);
  }
  shared_ptr<Expression> Multiplication::_reduce(vector<shared_ptr<Expression>> elements) {
    if (elements.size() == 1) {
      return elements[0];
    } else if (elements.size() == 0) {
      return undefined;
    }

    {
      // If an element is a multiplication join it's elements to this one's
      vector<shared_ptr<Expression>> reduced_elements;
      for (auto element : elements) {
        if (element->type() == "multiplication") {
          for (auto sub_element : dynamic_cast<Multiplication*>(element.get())->elements()) {
            reduced_elements.push_back(sub_element);
          }
        } else {
          reduced_elements.push_back(element);
        }
      }
      elements = reduced_elements;
    }

    shared_ptr<Expression> known_product = Number::construct(1);
    {
      for (auto it = elements.begin(); it < elements.end(); ++it) {
        if ((*it)->dependencies().size() == 0 && (*it)->type() != "list") {
          known_product = operations::multiply(known_product, *it);
          elements.erase(it--);
        }
      }
    }

    {
      vector<shared_ptr<Expression>> reduced_elements;
      for (auto a_it = elements.begin(); a_it < elements.end(); ++a_it) {
        shared_ptr<Expression> base;
        shared_ptr<Expression> exponent;
        if (*a_it == "exponentiation") {
          auto exp = dynamic_cast<Exponentiation*>((*a_it).get());
          base = exp->base();
          exponent = exp->exponent();
        } else {
          base = *a_it;
          exponent = Number::construct(1);
        }
        for (auto b_it = elements.begin(); b_it < elements.end(); ++b_it) {
          if (a_it == b_it) {
            continue;
          }
          if (*b_it == "exponentiation") {
            auto exp = dynamic_cast<Exponentiation*>((*b_it).get());
            if (exp->base() == base) {
              exponent = Addition::construct({exponent, exp->exponent()});
              elements.erase(b_it--);
            }
          } else if (*b_it == base) {
            exponent = Addition::construct({exponent, Number::construct(1)});
            elements.erase(b_it--);
          }
        }
        reduced_elements.push_back(Exponentiation::construct(base, exponent));
        elements.erase(a_it--);
      }
      elements = reduced_elements;
    }

    if (!(known_product == Number::construct(1)) || elements.size() == 0) {
      elements.push_back(known_product);
    }

    if (elements.size() == 1) {
      return elements[0];
    }

    {
      for (int i = 0; i < elements.size(); ++i) {
        auto element = elements[i];
        if (element == "list") {
          vector<shared_ptr<Expression>> new_list_elements;
          auto list_elements = dynamic_cast<List*>(element.get())->elements();
          for (int e = 0; e < list_elements.size(); ++e) {
            auto multiplication = elements;
            multiplication[i] = list_elements[e];
            new_list_elements.push_back(Multiplication::construct(multiplication));
          }
          return List::construct(new_list_elements);
        }
      }
    }

    vector<shared_ptr<Expression>> numerator;
    vector<shared_ptr<Expression>> denominator;

    for (auto element : elements) {
      if (element == "fraction") {
        auto frac = dynamic_cast<Fraction*>(element.get());
        numerator.push_back(frac->numerator());
        denominator.push_back(frac->denominator());
      } else {
        numerator.push_back(element);
      }
    }

    if (denominator.size() == 0) {
      return shared_ptr<Expression>(new Multiplication(numerator));
    }

    return Fraction::construct(shared_ptr<Expression>(new Multiplication(numerator)), shared_ptr<Expression>(new Multiplication(denominator)));
    
  }
  shared_ptr<Expression> Multiplication::_evaluate(vector<shared_ptr<Expression>> elements, shared_ptr<Scope> scope) {
    return undefined;
  }
}