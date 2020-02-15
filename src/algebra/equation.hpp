#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Equation : public Expression {
  private:
    shared_ptr<Expression> left;
    shared_ptr<Expression> right;
  public:
    shared_ptr<Expression> get_left();
    shared_ptr<Expression> get_right();
    ostream& output_to_stream(ostream& os);
    shared_ptr<Expression> evaluate(shared_ptr<Scope> scope = empty_scope, shared_ptr<Expression> caller = undefined);
    Equation(shared_ptr<Expression> left, shared_ptr<Expression> right);
    static shared_ptr<Expression> construct(shared_ptr<Expression> left = undefined, shared_ptr<Expression> right = undefined);
    static shared_ptr<Expression> evaluate(shared_ptr<Expression> left = undefined, shared_ptr<Expression> right = undefined, shared_ptr<Scope> scope = empty_scope);
  };
}
