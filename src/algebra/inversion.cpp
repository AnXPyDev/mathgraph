#include <vector>

#include "number.hpp"
#include "list.hpp"
#include "boolean.hpp"
#include "multiplication.hpp"
#include "inversion.hpp"

using namespace std;

namespace mathgraph::algebra {
  shared_ptr<Expression> Inversion::get() {
    return this->expr;
  }

  ostream& Inversion::output_to_stream(ostream& os) {
    os << "1/" << this->expr;
    return os;
  }

  Inversion::Inversion(shared_ptr<Expression> expr) : expr{ expr } {
    this->type = "inversion";
  }

  shared_ptr<Expression> Inversion::construct(shared_ptr<Expression> expr) {
    return Inversion::evaluate(expr);
  }

  shared_ptr<Expression> Inversion::evaluate(shared_ptr<Scope> scope, shared_ptr<Expression> caller) {
    return Inversion::evaluate(this->expr, scope);
  }

  shared_ptr<Expression> Inversion::evaluate(shared_ptr<Expression> expr, shared_ptr<Scope> scope) {
    expr = expr->evaluate(scope, expr);
    if (expr->get_type() == "undefined") {
      return undefined;
    } else if (expr->get_type() == "inversion") {
      return dynamic_cast<Inversion*>(expr.get())->get();
    } else if (expr->get_type() == "boolean") {
      return Boolean::construct(!dynamic_cast<Boolean*>(expr.get())->get());
    } else if (expr->get_type() == "number") {
      return Number::construct(1/dynamic_cast<Number*>(expr.get())->get());
    } else if (expr->get_type() == "list") {
      vector<shared_ptr<Expression>> new_elements;
      auto elements = dynamic_cast<List*>(expr.get())->get();
      for (auto element : elements) {
        new_elements.push_back(Inversion::evaluate(element->evaluate(scope, element)));
      }
      return List::construct(new_elements);
    } else if (expr->get_type() == "multiplication") {
      vector<shared_ptr<Expression>> new_elements;
      auto elements = dynamic_cast<List*>(expr.get())->get();
      for (auto element : elements) {
        new_elements.push_back(Inversion::evaluate(element->evaluate(scope, element)));
      }
      return Multiplication::construct(new_elements);
    }

    return shared_ptr<Expression>(new Inversion(expr));
  }
}
