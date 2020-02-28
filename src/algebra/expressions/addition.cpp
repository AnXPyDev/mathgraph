#include <iostream>
#include <memory>
#include <vector>

#include "algebra/expressions/base.hpp"
#include "algebra/scope.hpp"
#include "algebra/expression.hpp"
#include "algebra/types/integer.hpp"
#include "algebra/types/float.hpp"
#include "algebra/types/fraction.hpp"
#include "algebra/types/list.hpp"
#include "algebra/expressions/multiplication.hpp"
#include "algebra/operations.hpp"
#include "algebra/expressions/addition.hpp"

namespace mathgraph::algebra::expressions {
  ostream& Addition::output_to_stream(ostream& stream) {
    stream << "(";
    for (auto it = this->_elements.begin(); it < this->_elements.end() -1; ++it) {
      stream << *it << " + ";
    }
    return stream << *(this->_elements.end() - 1) << ")";
  }
  shared_ptr<Expression> Addition::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Addition::_evaluate(this->_elements, scope);
  }
  shared_ptr<Expression> Addition::reduce(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Addition::_reduce(this->_elements, scope);
  }
  Addition::Addition(vector<shared_ptr<Expression>> elements) : List(elements) {
    this->_type = "addition";
  }
  shared_ptr<Expression> Addition::construct(vector<shared_ptr<Expression>> elements) {
    return shared_ptr<Expression>(new Addition(elements));
  }
  shared_ptr<Expression> Addition::_reduce(vector<shared_ptr<Expression>> elements, shared_ptr<Scope> scope) {
    {
      vector<shared_ptr<Expression>> reduced_elements;
      for (auto element : elements) {
        reduced_elements.push_back(Expression::_reduce(element, scope));
      }
      elements = reduced_elements;
    }

    if (elements.size() == 1) {
      return elements[0];
    } else if (elements.size() == 0) {
      return undefined;
    }

    {
      // If an element is an addition join it's elements to this one's
      vector<shared_ptr<Expression>> reduced_elements;
      for (auto element : elements) {
        if (element->type() == "addition") {
          for (auto sub_element : dynamic_cast<Addition*>(element.get())->elements()) {
            reduced_elements.push_back(sub_element);
          }
        } else {
          reduced_elements.push_back(element);
        }
      }
      elements = reduced_elements;
    }

    shared_ptr<Expression> known_sum = types::Integer::construct(0);
    {
      for (auto it = elements.begin(); it < elements.end(); ++it) {
        if ((*it)->dependencies().size() == 0 && (*it)->type() != "list") {
          known_sum = operations::add(known_sum, *it);
          elements.erase(it--);
        }
      }
    }

    {
      vector<shared_ptr<Expression>> reduced_elements;
      for (auto a_it = elements.begin(); a_it < elements.end(); ++a_it) {
        shared_ptr<Expression> base;
        shared_ptr<Expression> multiplier;
        if (*a_it == "multiplication") {
          auto mult = dynamic_cast<Multiplication*>((*a_it).get());
          base = Multiplication::construct(mult->unknown());
          multiplier = mult->known();
        } else {
          base = *a_it;
          multiplier = types::Integer::construct(1);
        }
        for (auto b_it = elements.begin(); b_it < elements.end(); ++b_it) {
          if (a_it == b_it) {
            continue;
          }
          if (*b_it == "multiplication") {
            auto mult = dynamic_cast<Multiplication*>((*b_it).get());
            if (Multiplication::construct(mult->unknown()) == base) {
              multiplier = Addition::_reduce({multiplier, mult->known()}, scope);
              elements.erase(b_it--);
            }
          } else if (*b_it == base) {
            multiplier = Addition::_reduce({multiplier, types::Integer::construct(1)}, scope);
            elements.erase(b_it--);
          }
        }
        reduced_elements.push_back(Multiplication::_reduce({multiplier, base}, scope));
        elements.erase(a_it--);
      }
      elements = reduced_elements;
    }

    if (!(known_sum == types::Integer::construct(0)) || elements.size() == 0) {
      elements.push_back(known_sum);
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
            auto addition_elements = elements;
            addition_elements[i] = list_elements[e];
            new_list_elements.push_back(Addition::_reduce(addition_elements, scope));
          }
          return List::construct(new_list_elements);
        }
      }
    }

    vector<shared_ptr<Expression>> denominator_elements = {types::Integer::construct(1)};

    for (auto element : elements) {
      if (element == "fraction") {
        auto frac = dynamic_cast<types::Fraction*>(element.get());
        denominator_elements.push_back(frac->denominator());
      }
    }

    shared_ptr<Expression> denominator = Multiplication::_reduce(denominator_elements, scope);

    if (denominator == types::Integer::construct(1)) {
      return shared_ptr<Expression>(new Addition(elements));
    }
    
    vector<shared_ptr<Expression>> numerator_elements;

    for (auto element : elements) {
      numerator_elements.push_back(Multiplication::_reduce({element, denominator}, scope));
    }

    shared_ptr<Expression> numerator = Addition::_reduce(numerator_elements, scope);

    return types::Fraction::_reduce(numerator, denominator, scope);
  }
  shared_ptr<Expression> Addition::_evaluate(vector<shared_ptr<Expression>> elements, shared_ptr<Scope> scope) {
    shared_ptr<Expression> result = types::Integer::construct(0);
    for (auto element : elements) {
      result = operations::add(result, element->evaluate(element, scope));
    }
    return result;
  }
}
