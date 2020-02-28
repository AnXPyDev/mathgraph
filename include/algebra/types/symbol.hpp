// symbol is an expression with no certain value until evaluated in a scope
// it represents a variable or function's name with a string

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "algebra/types/base.hpp"
#include "algebra/expression.hpp"

using namespace std;

namespace mathgraph::algebra::types {
  struct Symbol : public Expression {
    ostream& output_to_stream(ostream& stream);
    shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    vector<shared_ptr<Expression>> dependencies(shared_ptr<Expression> caller = undefined);
    // getter for _value
    const string& value();
    Symbol(string value);
    // constructs a new symbol as a shared pointer to Expression
    static shared_ptr<Expression> construct(string value = "nil");
  private:
    string _value;
  };
}
