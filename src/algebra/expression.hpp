#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "base.hpp"
#include "scope.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Expression;
  extern shared_ptr<Expression> undefined;
  struct Expression {
  protected:
    string type;
  public:
    virtual shared_ptr<Expression> evaluate(shared_ptr<Scope> scope = empty_scope, shared_ptr<Expression> caller = undefined);
    virtual shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined);
    virtual ostream& output_to_stream(ostream& os);
    virtual const string& get_type();
    Expression();
  };
  ostream& operator<<(ostream& os, shared_ptr<Expression> expr);
}


