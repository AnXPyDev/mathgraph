#pragma once

#include <iostream>
#include <memory>

#include "base.hpp"
#include "expression.hpp"
#include "list.hpp"

namespace mathgraph::algebra {
  struct Addition : public List {
    ostream& output_to_stream(ostream& stream);
    shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    Addition(vector<shared_ptr<Expression>> elements);
    static shared_ptr<Expression> construct(vector<shared_ptr<Expression>> elements = {});
    static shared_ptr<Expression> _reduce(vector<shared_ptr<Expression>> elements = {});
    static shared_ptr<Expression> _evaluate(vector<shared_ptr<Expression>> elements = {}, shared_ptr<Scope> scope = empty_scope);
  };
}
