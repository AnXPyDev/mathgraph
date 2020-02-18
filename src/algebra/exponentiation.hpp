#pragma once

#include <iostream>
#include <memory>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Exponentiation : public Expression {
    ostream& output_to_stream(ostream& stream);
    // getter of _base
    shared_ptr<Expression> base();
    // getter of _exponent
    shared_ptr<Expression> exponent();
    vector<shared_ptr<Expression>> dependencies(shared_ptr<Expression> caller = undefined);
    shared_ptr<Expression> reduce(shared_ptr<Expression> caller = undefined);
    shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    Exponentiation(shared_ptr<Expression> base, shared_ptr<Expression> exponent);
    static shared_ptr<Expression> _reduce(shared_ptr<Expression> base, shared_ptr<Expression> exponent);
    static shared_ptr<Expression> _evaluate(shared_ptr<Expression> base, shared_ptr<Expression> exponent, shared_ptr<Scope> scope = empty_scope);
    // constructs new exponentiation as a shared pointer to Expression
    static shared_ptr<Expression> construct(shared_ptr<Expression> base = undefined, shared_ptr<Expression> exponent = undefined);
  private:
    shared_ptr<Expression> _base;
    shared_ptr<Expression> _exponent;
  };
}
