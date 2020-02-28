#pragma once

#include <iostream>
#include <memory>

#include "algebra/expressions/base.hpp"
#include "algebra/expression.hpp"
#include "algebra/types/list.hpp"

namespace mathgraph::algebra::expressions {
  struct Multiplication : public types::List {
    ostream& output_to_stream(ostream& stream);
    shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    shared_ptr<Expression> reduce(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    shared_ptr<Expression> known();
    vector<shared_ptr<Expression>> unknown();
    Multiplication(vector<shared_ptr<Expression>> elements);
    static shared_ptr<Expression> construct(vector<shared_ptr<Expression>> elements = {});
    static shared_ptr<Expression> _reduce(vector<shared_ptr<Expression>> elements = {}, shared_ptr<Scope> scope = empty_scope);
    static shared_ptr<Expression> _evaluate(vector<shared_ptr<Expression>> elements = {}, shared_ptr<Scope> scope = empty_scope);
  };
}
