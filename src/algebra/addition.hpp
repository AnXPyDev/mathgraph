#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "scope.hpp"
#include "base.hpp"
#include "expression.hpp"
#include "list.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Addition : public List {
  public:
    ostream& output_to_stream(ostream& os);
    shared_ptr<Expression> evaluate(shared_ptr<Scope> scope = empty_scope, shared_ptr<Expression> caller = undefined);
    Addition(vector<shared_ptr<Expression>> elements);
    static shared_ptr<Expression> construct(vector<shared_ptr<Expression>> elements = {});
    static shared_ptr<Expression> evaluate(vector<shared_ptr<Expression>> elements = {}, shared_ptr<Scope> scope = empty_scope);
  };
}
