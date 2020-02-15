#include "expression.hpp"
#include "symbol.hpp"
#include "scope.hpp"

using namespace std;

namespace mathgraph::algebra {
  shared_ptr<Expression> Scope::get(shared_ptr<Expression> expr) {
    if (expr->get_type() == "symbol") {
      return this->get(dynamic_cast<Symbol*>(expr.get())->get());
    }
    return expr;
  }

  shared_ptr<Expression> Scope::get(string key) {
    return undefined;
  }

  shared_ptr<Scope> empty_scope = shared_ptr<Scope>(new Scope);
}

