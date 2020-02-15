#include <vector>
#include <iostream>

#include "operations.hpp"
#include "number.hpp"
#include "list.hpp"
#include "inversion.hpp"
#include "addition.hpp"
#include "exponentiation.hpp"
#include "multiplication.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Multiplication::output_to_stream(ostream& os) {
    os << "(";
    for (auto it = this->elements.begin(); it < this->elements.end() - 1; ++it) {
      os << *it << " * ";
    }
    if (this->elements.size() > 0) {
      os << *(this->elements.end() - 1);
    }
    os << ")";
    return os;
  }

  shared_ptr<Expression> Multiplication::evaluate(shared_ptr<Scope> scope, shared_ptr<Expression> caller) {
    return Multiplication::evaluate(this->elements, scope);
  }

  shared_ptr<Expression> Multiplication::get_multiplier() {
    for (auto it = this->elements.begin(); it < this->elements.end(); ++it) {
      if ((*it)->get_type() == "number") {
        return *it;
      }
    }
    return Number::construct(1);
  }

  shared_ptr<Expression> Multiplication::get_unknown() {
    auto new_elements = this->elements;
    for (auto it = new_elements.begin(); it < new_elements.end(); ++it) {
      if ((*it)->get_type() == "number") {
        new_elements.erase(it--);
      }
    }
    return List::construct(new_elements);
  }

  Multiplication::Multiplication(vector<shared_ptr<Expression>> elements) : List(elements) {
    this->type = "multiplication";
  }

  shared_ptr<Expression> Multiplication::construct(vector<shared_ptr<Expression>> elements) {
    return Multiplication::evaluate(elements);
  }

  shared_ptr<Expression> Multiplication::evaluate(vector<shared_ptr<Expression>> elements, shared_ptr<Scope> scope) {
    {
      vector<shared_ptr<Expression>> evaluated_elements;
      for (auto element : elements) {
        element = element->evaluate(scope, element);
        if (element->get_type() == "multiplication") {
          for (auto sub_element : dynamic_cast<List*>(element.get())->get()) {
            evaluated_elements.push_back(sub_element);
          }
        } else {
          evaluated_elements.push_back(element->evaluate(scope, element));
        }
      }
      elements = evaluated_elements;
    }

    approx_t known_product = 1;

    {
      vector<shared_ptr<Expression>> simplified_elements;
      for (auto element : elements) {
        if (element->get_type() == "number") {
          known_product *= dynamic_cast<Number*>(element.get())->get();
        } else {
          simplified_elements.push_back(element);
        }
      }
      elements = simplified_elements;
    }

    if (known_product == 0) {
      return Number::construct(0);
    }

    {
      vector<shared_ptr<Expression>> simplified_elements;
      for (auto a = elements.begin(); a < elements.end(); ++a) {
        auto expr_a = *a;
        shared_ptr<Expression> base;
        shared_ptr<Expression> exponent;

        if (expr_a->get_type() == "exponentiation") {
          auto temp = dynamic_cast<Exponentiation*>(expr_a.get());
          base = temp->get_base();
          exponent = temp->get_exponent();
        } else if (expr_a->get_type() == "inversion") {
          auto temp = dynamic_cast<Inversion*>(expr_a.get());
          base = temp->get();
          exponent = Number::construct(-1);
        } else {
          base = expr_a;
          exponent = Number::construct(1);
        }

        for (auto b = elements.begin(); b < elements.end(); ++b) {
          if (a == b) {
            continue;
          }
          
          auto expr_b = *b;
          shared_ptr<Expression> b_base;
          shared_ptr<Expression> b_exponent;

          if (expr_b->get_type() == "exponentiation") {
            auto temp = dynamic_cast<Exponentiation*>(expr_b.get());
            b_base = temp->get_base();
            b_exponent = temp->get_exponent();
          } else if (expr_b->get_type() == "inversion") {
            auto temp = dynamic_cast<Inversion*>(expr_b.get());
            b_base = temp->get();
            b_exponent = Number::construct(-1);
          } else {
            b_base = expr_b;
            b_exponent = Number::construct(1);
          }       

          if (operations::equal(base, b_base)) {
            exponent = Addition::construct({exponent, b_exponent});
            elements.erase(b--);
          }
          
        }
        simplified_elements.push_back(Exponentiation::construct(base, exponent));
        elements.erase(a--);
      }
      elements = simplified_elements;
    }
    
    if (known_product != 1 || elements.size() == 0) {
      elements.push_back(Number::construct(known_product));
    }

    if (elements.size() == 0) {
      return undefined;
    } else if (elements.size() == 1) {
      return elements[0];
    }

    for (int i = 0; i < elements.size(); ++i) {
      auto element = elements[i];
      if (element->get_type() == "list" || element->get_type() == "addition") {
        auto list_elements = dynamic_cast<List*>(element.get())->get();
        vector<shared_ptr<Expression>> new_list_elements;
        for (auto list_element : list_elements) {
          auto multiplication_elements = elements;
          multiplication_elements[i] = list_element;
          new_list_elements.push_back(Multiplication::construct(multiplication_elements));
        }
        if (element->get_type() == "addition") {
          return Addition::construct(new_list_elements);
        }
        return List::construct(new_list_elements);
      }
    }

    return shared_ptr<Expression>(new Multiplication(elements));
  }
}
