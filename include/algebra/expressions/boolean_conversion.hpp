#pragma once

#include <memory>
#include <iostream>

#include "algebra/expressions/base.hpp"
#include "algebra/scope.hpp"
#include "algebra/expression.hpp"

using namespace std;

namespace mathgraph::algebra::expressions {
  struct Boolean_conversion : public Expression {
    ostream& output_to_stream(ostream& stream);
    shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    shared_ptr<Expression> reduce(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    shared_ptr<Expression> expression();
    Boolean_conversion(shared_ptr<Expression> expression);
    static shared_ptr<Expression> construct(shared_ptr<Expression> expression = undefined);
    static shared_ptr<Expression> _reduce(shared_ptr<Expression> expression = undefined, shared_ptr<Scope> scope = empty_scope);
    static shared_ptr<Expression> _evaluate(shared_ptr<Expression> expression = undefined, shared_ptr<Scope> scope = empty_scope);
  private:
    shared_ptr<Expression> _expression;
  };
}
