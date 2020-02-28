#pragma once

#include <memory>
#include <iostream>

#include "algebra/functions/base.hpp"
#include "algebra/scope.hpp"
#include "algebra/expression.hpp"

using namespace std;

namespace mathgraph::algebra::functions {
  struct If : public Expression {
    ostream& output_to_stream(ostream& stream);
    shared_ptr<Expression> condition();
    shared_ptr<Expression> case_true();
    shared_ptr<Expression> case_false();
    shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    shared_ptr<Expression> reduce(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    If(shared_ptr<Expression> condition, shared_ptr<Expression> case_true, shared_ptr<Expression> case_false);
    static shared_ptr<Expression> _reduce(shared_ptr<Expression> condition = undefined, shared_ptr<Expression> case_true = undefined, shared_ptr<Expression> case_false = undefined, shared_ptr<Scope> scope = empty_scope);
    static shared_ptr<Expression> _evaluate(shared_ptr<Expression> condition = undefined, shared_ptr<Expression> case_true = undefined, shared_ptr<Expression> case_false = undefined, shared_ptr<Scope> scope = empty_scope);
    static shared_ptr<Expression> construct(shared_ptr<Expression> condition = undefined, shared_ptr<Expression> case_true = undefined, shared_ptr<Expression> case_false = undefined);
  private:
    shared_ptr<Expression> _condition;
    shared_ptr<Expression> _case_true;
    shared_ptr<Expression> _case_false;
  };
}
