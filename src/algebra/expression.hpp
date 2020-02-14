#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "base.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Scope;
  struct Expression;
  extern shared_ptr<Expression> undefined;
  struct Expression {
    const string type = "undefined";
    virtual shared_ptr<Expression> evaluate(shared_ptr<Scope> scope, shared_ptr<Expression> caller = undefined);
    virtual ostream& output_to_stream(ostream& os);
  };
  ostream& operator<<(ostream& os, shared_ptr<Expression> expr);
}

