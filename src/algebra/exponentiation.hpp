#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Exponentiation : public Expression {
  private:
    shared_ptr<Expression> base;
    shared_ptr<Expression> exponent;
  public:
    shared_ptr<Expression> get_base();
    shared_ptr<Expression> get_exponent();
    ostream& output_to_stream(ostream& os);
    shared_ptr<Expression> evaluate(shared_ptr<Scope> scope = empty_scope, shared_ptr<Expression> caller = undefined);
    Exponentiation(shared_ptr<Expression> base, shared_ptr<Expression> exponent);
    static shared_ptr<Expression> construct(shared_ptr<Expression> base = undefined, shared_ptr<Expression> exponent = undefined);
    static shared_ptr<Expression> evaluate(shared_ptr<Expression> expr = undefined, shared_ptr<Expression> exponent = undefined, shared_ptr<Scope> scope = empty_scope);
  };
}
