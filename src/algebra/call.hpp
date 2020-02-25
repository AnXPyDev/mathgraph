#pragma once

#include <memory>
#include <iostream>

#include "base.hpp"
#include "scope.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Call : public Expression {
    ostream& output_to_stream(ostream& stream);
    shared_ptr<Expression> reduce(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    shared_ptr<Expression> expression();
    shared_ptr<Expression> arguments();
    Call(shared_ptr<Expression> expression, shared_ptr<Expression> arguments);
    static shared_ptr<Expression> construct(shared_ptr<Expression> expression = undefined, shared_ptr<Expression> arguments = undefined);
    static shared_ptr<Expression> _reduce(shared_ptr<Expression> expression = undefined, shared_ptr<Expression> arguments = undefined, shared_ptr<Scope> scope = empty_scope);
    static shared_ptr<Expression> _evaluate(shared_ptr<Expression> expression = undefined, shared_ptr<Expression> arguments = undefined, shared_ptr<Scope> scope = empty_scope);
  private:
    shared_ptr<Expression> _expression;
    shared_ptr<Expression> _arguments;
  };
}
