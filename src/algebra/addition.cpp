#include <vector>

#include "number.hpp"
#include "negation.hpp"
#include "operations.hpp"
#include "list.hpp"
#include "inversion.hpp"
#include "exponentiation.hpp"
#include "multiplication.hpp"
#include "addition.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Addition::output_to_stream(ostream& os) {
    os << "(";
    for (auto it = this->elements.begin(); it < this->elements.end() - 1; ++it) {
      os << *it << " + ";
    }
    if (this->elements.size() > 0) {
      os << *(this->elements.end() - 1);
    }
    os << ")";
    return os;
  }

  shared_ptr<Expression> Addition::evaluate(shared_ptr<Scope> scope, shared_ptr<Expression> caller) {
    return Addition::evaluate(this->elements, scope);
  }

  Addition::Addition(vector<shared_ptr<Expression>> elements) : List(elements) {
    this->type = "addition";
  }

  shared_ptr<Expression> Addition::construct(vector<shared_ptr<Expression>> elements) {
    return Addition::evaluate(elements);
  }

  shared_ptr<Expression> Addition::evaluate(vector<shared_ptr<Expression>> elements, shared_ptr<Scope> scope) {
    {
      vector<shared_ptr<Expression>> evaluated_elements;
      for (auto element : elements) {
        element = element->evaluate(scope, element);
        if (element->get_type() == "addition") {
          for (auto sub_element : dynamic_cast<List*>(element.get())->get()) {
            evaluated_elements.push_back(sub_element);
          }
        } else {
          evaluated_elements.push_back(element->evaluate(scope, element));
        }
      }
      elements = evaluated_elements;
    }

    approx_t known_sum = 0;

    {
      vector<shared_ptr<Expression>> simplified_elements;
      for (auto element : elements) {
        if (element->get_type() == "number") {
          known_sum += dynamic_cast<Number*>(element.get())->get();
        } else {
          simplified_elements.push_back(element);
        }
      }
      elements = simplified_elements;
    }

    {
      vector<shared_ptr<Expression>> simplified_elements;
      for (auto a = elements.begin(); a < elements.end(); ++a) {
        approx_t mul = 1;
        for (auto b = elements.begin(); b < elements.end(); ++b) {
          bool match = false;
          if (a != b) {
            if (operations::equal(*a, *b)) {
              ++mul;
              match = true;
            } else if (operations::equal(Negation::construct(*a), *b)) {
              --mul;
              match = true;
            }
          }
          if (match) {
            elements.erase(b--);
          }
        }
        simplified_elements.push_back(Multiplication::construct({*a, Number::construct(mul)}));
        elements.erase(a--);
      }
      elements = simplified_elements;
    }

    {
      vector<shared_ptr<Expression>> simplified_elements;
      for (auto a = elements.begin(); a < elements.end(); ++a) {
        auto expr_a = *a;
        shared_ptr<Expression> unknown;
        shared_ptr<Expression> multiplier;

        if (expr_a->get_type() == "multiplication") {
          auto temp = dynamic_cast<Multiplication*>(expr_a.get());
          unknown = temp->get_unknown();
          multiplier = temp->get_multiplier();
        } else if (expr_a->get_type() == "negation") {
          auto temp = dynamic_cast<Negation*>(expr_a.get());
          unknown = temp->get();
          multiplier = Number::construct(-1);
        } else {
          unknown = expr_a;
          multiplier = Number::construct(1);
        }

        for (auto b = elements.begin(); b < elements.end(); ++b) {
          if (a == b) {
            continue;
          }
          
          auto expr_b = *b;
          shared_ptr<Expression> b_unknown;
          shared_ptr<Expression> b_multiplier;

          if (expr_b->get_type() == "multiplication") {
            auto temp = dynamic_cast<Multiplication*>(expr_b.get());
            b_unknown = temp->get_unknown();
            b_multiplier = temp->get_multiplier();
          } else if (expr_b->get_type() == "negation") {
            auto temp = dynamic_cast<Negation*>(expr_b.get());
            b_unknown = temp->get();
            b_multiplier = Number::construct(-1);
          } else {
            b_unknown = expr_b;
            b_multiplier = Number::construct(1);
          }       

          if (operations::equal(unknown, b_unknown)) {
            multiplier = Addition::construct({multiplier, b_multiplier});
            elements.erase(b--);
          }
          
        }
        simplified_elements.push_back(Multiplication::construct({unknown, multiplier}));
        elements.erase(a--);
      }
      elements = simplified_elements;
    }

    if (known_sum != 0 || elements.size() == 0) {
      elements.push_back(Number::construct(known_sum));
    }

    if (elements.size() == 0) {
      return undefined;
    } else if (elements.size() == 1) {
      return elements[0];
    }

    for (int i = 0; i < elements.size(); ++i) {
      auto element = elements[i];
      if (element->get_type() == "list") {
        auto list_elements = dynamic_cast<List*>(element.get())->get();
        vector<shared_ptr<Expression>> new_list_elements;
        for (auto list_element : list_elements) {
          auto addition_elements = elements;
          addition_elements[i] = list_element;
          new_list_elements.push_back(Addition::construct(addition_elements));
        }
        return List::construct(new_list_elements);
      }
    }

    return shared_ptr<Expression>(new Addition(elements));
  }
}
