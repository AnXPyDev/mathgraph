// List is an expression that stores multiple expressions inside a vector

#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct List : public Expression {
    virtual ostream& output_to_stream(ostream& stream);
    vector<shared_ptr<Expression>> dependencies(shared_ptr<Expression> caller = undefined);
    virtual shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    const vector<shared_ptr<Expression>>& elements();
    List(vector<shared_ptr<Expression>> elements);
    static shared_ptr<Expression> construct(vector<shared_ptr<Expression>> elements = {});
    static shared_ptr<Expression> _evaluate(vector<shared_ptr<Expression>> elements = {}, shared_ptr<Scope> scope = empty_scope);
  protected:
    vector<shared_ptr<Expression>> _elements;
  };
}
