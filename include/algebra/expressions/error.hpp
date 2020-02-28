#pragma once

#include <string>
#include <memory>
#include <iostream>

#include "algebra/expressions/base.hpp"
#include "algebra/expression.hpp"

using namespace std;

namespace mathgraph::algebra::expressions {
  struct Error : public Expression {
    ostream& output_to_stream(ostream& stream);
    const string& message();
    Error(string message);
    static shared_ptr<Expression> construct(string message = "undefined error");
  private:
    string _message;
  };
}
