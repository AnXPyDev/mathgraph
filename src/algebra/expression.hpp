// expression is a base for everything else in the algebra module

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "base.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Scope;
  struct Expression;
  extern shared_ptr<Scope> empty_scope;
  // undefined is going to be used instead of constructing new instances of basic Expression
  extern shared_ptr<Expression> undefined;
  struct Expression {
    // outputs the value of expression to stream (cout)
    virtual ostream& output_to_stream(ostream& stream);
    // will reduce an expression to it's base form using the rules of linear algebra
    virtual shared_ptr<Expression> reduce(shared_ptr<Expression> caller = undefined);
    // will evaluate an expression to an actual definite value
    virtual shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    // will return a vector of symbols that the expression needs to be defined to be evaluated
    virtual vector<shared_ptr<Expression>> dependencies(shared_ptr<Expression> caller = undefined);
    // returns reference to expression type
    const string& type();
    Expression();
  protected:
    // type of expression (for example: number, list ...)
    string _type;
  };
  ostream& operator<<(ostream& stream, shared_ptr<Expression> expression);
  bool operator==(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b);
  bool operator==(shared_ptr<Expression> expr, string type);
}
