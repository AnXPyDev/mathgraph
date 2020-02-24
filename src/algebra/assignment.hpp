#pragma once

#include <memory>
#include <iostream>

#include "base.hpp"
#include "scope.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Assignment : public Expression {
    ostream& output_to_stream(ostream& stream);
    shared_ptr<Expression> reduce(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    shared_ptr<Expression> left();
    shared_ptr<Expression> right();
    Assignment(shared_ptr<Expression> left, shared_ptr<Expression> right);
    static shared_ptr<Expression> _reduce(shared_ptr<Expression> left = undefined, shared_ptr<Expression> right = undefined, shared_ptr<Scope> scope = empty_scope);
    static shared_ptr<Expression> _evaluate(shared_ptr<Expression> left = undefined, shared_ptr<Expression> right = undefined, shared_ptr<Scope> scope = empty_scope);
    static shared_ptr<Expression> construct(shared_ptr<Expression> left = undefined, shared_ptr<Expression> right = undefined);
  private:
    shared_ptr<Expression> _left;
    shared_ptr<Expression> _right;
  };
}
