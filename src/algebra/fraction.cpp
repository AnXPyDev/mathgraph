#include <iostream>
#include <memory>
#include <vector>

#include "base.hpp"
#include "scope.hpp"
#include "expression.hpp"
#include "integer.hpp"
#include "float.hpp"
#include "exponentiation.hpp"
#include "list.hpp"
#include "addition.hpp"
#include "multiplication.hpp"
#include "operations.hpp"
#include "fraction.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Fraction::output_to_stream(ostream& stream) {
    return stream << this->_numerator << "/" << this->_denominator;
  }
  shared_ptr<Expression> Fraction::numerator() { return this->_numerator; }
  shared_ptr<Expression> Fraction::denominator() { return this->_denominator; }
  vector<shared_ptr<Expression>> Fraction::dependencies(shared_ptr<Expression> caller) {
    vector<shared_ptr<Expression>> result = {};
    for (auto element : vector<shared_ptr<Expression>>({this->_numerator, this->_denominator})) {
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
  shared_ptr<Expression> Fraction::reduce(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Fraction::_reduce(this->_numerator, this->_denominator, scope);
  }
  shared_ptr<Expression> Fraction::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Fraction::_evaluate(this->_numerator, this->_denominator, scope);
  }
  Fraction::Fraction(shared_ptr<Expression> numerator, shared_ptr<Expression> denominator) : _numerator{ numerator }, _denominator{ denominator } {
    this->_type = "fraction";
  }
  shared_ptr<Expression> Fraction::_reduce(shared_ptr<Expression> numerator, shared_ptr<Expression> denominator, shared_ptr<Scope> scope) {
    numerator = Expression::_reduce(numerator, scope);
    denominator = Expression::_reduce(denominator, scope);
    if (numerator == "undefined" || denominator == "undefined") {
      return undefined;
    } else if (numerator == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      for (auto element : dynamic_cast<List*>(numerator.get())->elements()) {
        new_list_elements.push_back(Fraction::_reduce(element, denominator, scope));
      }
      return List::construct(new_list_elements);
    } else if (denominator == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      for (auto element : dynamic_cast<List*>(denominator.get())->elements()) {
        new_list_elements.push_back(Fraction::_reduce(numerator, element, scope));
      }
      return List::construct(new_list_elements);
      
    } else if (numerator == "multiplication" || denominator == "multiplication") {
      shared_ptr<Expression> numerator_known;
      shared_ptr<Expression> denominator_known;
      vector<shared_ptr<Expression>> numerator_rest;
      vector<shared_ptr<Expression>> denominator_rest;

      if (numerator == "multiplication") {
        auto mult = dynamic_cast<Multiplication*>(numerator.get());
        numerator_known = mult->known();
        numerator_rest = mult->unknown();
      } else if (numerator == "number" || numerator == "fraction") {
        numerator_known = numerator;
      }

      if (denominator == "multiplication") {
        auto mult = dynamic_cast<Multiplication*>(denominator.get());
        denominator_known = mult->known();
        denominator_rest = mult->unknown();
      } else if (denominator == "number" || denominator == "fraction") {
        denominator_known = denominator;
      }

      // Eliminate equal elements of numerator and denominator
      for (auto n_it = numerator_rest.begin(); n_it < numerator_rest.end(); ++n_it) {
        for (auto d_it = denominator_rest.begin(); d_it < denominator_rest.end(); ++d_it) {
          if (*n_it == *d_it) {
            numerator_rest.erase(n_it--);
            denominator_rest.erase(d_it--);
            break;
          }
        }
      }

      auto known = Fraction::_reduce(numerator_known, denominator_known, scope);
      if (known == "number") {
        numerator_rest.push_back(known);
      } else if (known == "fraction") {
        auto frac = dynamic_cast<Fraction*>(known.get());
        numerator_rest.push_back(frac->numerator());
        denominator_rest.push_back(frac->denominator());
      }

      if (denominator_rest.size() == 0) {
        return Multiplication::_reduce(numerator_rest, scope);
      }

      if (numerator_rest.size() == 0) {
        numerator_rest.push_back(Integer::construct(1));
      }

      numerator = Multiplication::_reduce(numerator_rest, scope);
      denominator = Multiplication::_reduce(denominator_rest, scope);
    } else if (denominator == Integer::construct(0)) {
      return undefined;
    } else if (numerator == Integer::construct(0) || denominator == Integer::construct(1)) {
      return numerator;
    } else if (numerator == denominator) {
      return Integer::construct(1);
    } else if (numerator == "fraction" || denominator == "fraction") {
      shared_ptr<Expression> fraction_matrix[2][2];
      int i = 0;
      for (auto element : {numerator, denominator}) {
        if (element == "fraction") {
          auto frac = dynamic_cast<Fraction*>(element.get());
          fraction_matrix[i][0] = frac->numerator();
          fraction_matrix[i][1] = frac->denominator();
        } else {
          fraction_matrix[i][0] = element;
          fraction_matrix[i][1] = Integer::construct(1);
        }
        ++i;
      }
      return Fraction::_reduce(Multiplication::_reduce({fraction_matrix[0][0], fraction_matrix[1][1]}, scope), Multiplication::_reduce({fraction_matrix[0][1], fraction_matrix[1][0]}, scope), scope);
    } else if (numerator == "integer" && denominator == "integer") {
      integer_t a = dynamic_cast<Integer*>(numerator.get())->value();
      integer_t b = dynamic_cast<Integer*>(denominator.get())->value();
      integer_t gcd = operations::gcd(a, b);
      return shared_ptr<Expression>(new Fraction(Integer::construct(a / gcd), Integer::construct(b / gcd)));
    } else if (numerator == "float" || denominator == "float") {
      return shared_ptr<Expression>(new Fraction(numerator, denominator));
    }
    vector<shared_ptr<Expression>> numerator_elements;
    vector<shared_ptr<Expression>> denominator_elements;

    if (numerator == "multiplicaton") {
      numerator_elements = dynamic_cast<Multiplication*>(numerator.get())->elements();
    } else {
      numerator_elements = {numerator};
    }

    if (denominator == "multiplicaton") {
      denominator_elements = dynamic_cast<Multiplication*>(denominator.get())->elements();
    } else {
      denominator_elements = {denominator};
    }

    {
      vector<shared_ptr<Expression>> reduced_elements;
      for (auto a_it = numerator_elements.begin(); a_it < numerator_elements.end(); ++a_it) {
        shared_ptr<Expression> base;
        shared_ptr<Expression> exponent;
        if (*a_it == "exponentiation") {
          auto exp = dynamic_cast<Exponentiation*>((*a_it).get());
          base = exp->base();
          exponent = exp->exponent();
        } else {
          base = *a_it;
          exponent = Integer::construct(1);
        }
        for (auto b_it = denominator_elements.begin(); b_it < denominator_elements.end(); ++b_it) {
          if (*b_it == "exponentiation") {
            auto exp = dynamic_cast<Exponentiation*>((*b_it).get());
            if (exp->base() == base) {
              exponent = Addition::_reduce({exponent, Multiplication::_reduce({Integer::construct(-1), exp->exponent()}, scope)}, scope);
              denominator_elements.erase(b_it--);
            }
          } else if (*b_it == base) {
            exponent = Addition::_reduce({exponent, Integer::construct(-1)}, scope);
            denominator_elements.erase(b_it--);
          }
        }
        reduced_elements.push_back(Exponentiation::_reduce(base, exponent, scope));
        numerator_elements.erase(a_it--);
      }
      numerator_elements = reduced_elements;
    }

    if (denominator_elements.size() == 0) {
      return Multiplication::_reduce(numerator_elements, scope);
    }

    if (numerator_elements.size() == 0) {
      numerator_elements.push_back(Integer::construct(1));
    }

    numerator = Multiplication::_reduce(numerator_elements, scope);
    denominator = Multiplication::_reduce(denominator_elements, scope);

    return shared_ptr<Expression>(new Fraction(numerator, denominator));
  }
  shared_ptr<Expression> Fraction::_evaluate(shared_ptr<Expression> numerator, shared_ptr<Expression> denominator, shared_ptr<Scope> scope) {
    return Fraction::construct(Expression::_evaluate(numerator, scope), Expression::_evaluate(denominator, scope));
  }
  shared_ptr<Expression> Fraction::construct(shared_ptr<Expression> numerator, shared_ptr<Expression> denominator) {
    return shared_ptr<Expression>(new Fraction(numerator, denominator));
  }
}
