#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Inversion : public Expression {
  private:
    shared_ptr<Expression> expr;
  public:
    shared_ptr<Expression> get();
    ostream& output_to_stream(ostream& os);
    shared_ptr<Expression> evaluate(shared_ptr<Scope> scope = empty_scope, shared_ptr<Expression> caller = undefined);
    Inversion(shared_ptr<Expression> expr);
    static shared_ptr<Expression> construct(shared_ptr<Expression> expr = undefined);
    static shared_ptr<Expression> evaluate(shared_ptr<Expression> expr = undefined, shared_ptr<Scope> scope = empty_scope);
  };
}
