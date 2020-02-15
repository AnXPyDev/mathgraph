#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "base.hpp"
#include "scope.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Symbol : public Expression {
  private:
    string value;
  public:
    const string& get();
    ostream& output_to_stream(ostream& os);
    shared_ptr<Expression> evaluate(shared_ptr<Scope> scope = empty_scope, shared_ptr<Expression> caller = undefined);
    Symbol(string value);
    static shared_ptr<Expression> construct(string value = "");
  };
}
