#pragma once

#include <iostream>
#include <memory>

#include "base.hpp"
#include "scope.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Function : public Expression {
    ostream& output_to_stream(ostream& stream);
    shared_ptr<Expression> argument_list();
    shared_ptr<Expression> expression();
    shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    shared_ptr<Expression> reduce(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    Function(shared_ptr<Expression> argument_list, shared_ptr<Expression> expression);
    static shared_ptr<Expression> _reduce(shared_ptr<Expression> argument_list = undefined, shared_ptr<Expression> expression = undefined, shared_ptr<Scope> scope = empty_scope);
    static shared_ptr<Expression> construct(shared_ptr<Expression> argument_list = undefined, shared_ptr<Expression> expression = undefined);
  private:
    shared_ptr<Expression> _argument_list;
    shared_ptr<Expression> _expression;
  };
}
