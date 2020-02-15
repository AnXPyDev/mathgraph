#include <vector>

#include "number.hpp"
#include "list.hpp"
#include "boolean.hpp"
#include "addition.hpp"
#include "multiplication.hpp"
#include "negation.hpp"

using namespace std;

namespace mathgraph::algebra {

  shared_ptr<Expression> Negation::get() {
    return this->expr;
  }

  ostream& Negation::output_to_stream(ostream& os) {
    os << "(0 - " << this->expr << ")";
    return os;
  }

  Negation::Negation(shared_ptr<Expression> expr) : expr{ expr } {
    this->type = "negation";
  }

  shared_ptr<Expression> Negation::construct(shared_ptr<Expression> expr) {
    return Negation::evaluate(expr);
  }

  shared_ptr<Expression> Negation::evaluate(shared_ptr<Scope> scope, shared_ptr<Expression> caller) {
    return Negation::evaluate(this->expr, scope);
  }

  shared_ptr<Expression> Negation::evaluate(shared_ptr<Expression> expr, shared_ptr<Scope> scope) {
    expr = expr->evaluate(scope, expr);
    if (expr->get_type() == "undefined") {
      return undefined;
    } else if (expr->get_type() == "inversion") {
      return dynamic_cast<Negation*>(expr.get())->get();
    } else if (expr->get_type() == "boolean") {
      return Boolean::construct(!dynamic_cast<Boolean*>(expr.get())->get());
    } else if (expr->get_type() == "number") {
      return Number::construct(0 - dynamic_cast<Number*>(expr.get())->get());
    } else if (expr->get_type() == "list") {
      vector<shared_ptr<Expression>> new_elements;
      auto elements = dynamic_cast<List*>(expr.get())->get();
      for (auto element : elements) {
        new_elements.push_back(Negation::evaluate(element->evaluate(scope, element)));
      }
      return List::construct(new_elements);
    } else if (expr->get_type() == "addition") {
      vector<shared_ptr<Expression>> new_elements;
      auto elements = dynamic_cast<List*>(expr.get())->get();
      for (auto element : elements) {
        new_elements.push_back(Negation::evaluate(element->evaluate(scope, element)));
      }
      return Addition::construct(new_elements);
    } else if (expr->get_type() == "multiplication") {
      return Multiplication::construct({expr, Number::construct(-1)});
    }

    return shared_ptr<Expression>(new Negation(expr));
  }
}
