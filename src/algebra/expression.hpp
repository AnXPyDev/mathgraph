// expression is a base for everything else in the algebra module

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "base.hpp"
#include "scope.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Expression;
  // undefined is going to be used instead of constructing new instances of basic Expression
  extern shared_ptr<Expression> undefined;
  struct Expression {
    // outputs the value of expression to stream (cout)
    virtual ostream& output_to_stream(ostream& stream);
    // will reduce an expression to it's base form using the rules of linear algebra
    virtual shared_ptr<Expression> reduce(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    // will evaluate an expression to an actual definite value
    virtual shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    // will return a vector of symbols that the expression needs to be defined to be evaluated
    virtual vector<shared_ptr<Expression>> dependencies(shared_ptr<Expression> caller = undefined);
    // returns reference to expression type
    const string& type();
    Expression();
    static shared_ptr<Expression> _reduce(shared_ptr<Expression> expr = undefined, shared_ptr<Scope> scope = empty_scope);
    static shared_ptr<Expression> _evaluate(shared_ptr<Expression> expr = undefined, shared_ptr<Scope> scope = empty_scope);
  protected:
    // type of expression (for example: number, list ...)
    string _type;
  };
  ostream& operator<<(ostream& stream, shared_ptr<Expression> expression);
  bool operator==(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b);
  bool operator==(shared_ptr<Expression> expr, string type);
}
