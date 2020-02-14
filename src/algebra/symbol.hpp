#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Scope;
  struct Symbol : public Expression {
  private:
    string value;
  public:
    const string type = "symbol";
    const string& get();
    ostream& output_to_stream(ostream& os);
    Symbol(string value);
    static shared_ptr<Expression> construct(string value = "");
  };
}
