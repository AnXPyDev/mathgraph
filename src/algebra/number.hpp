#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Scope;
  struct Number : public Expression {
  private:
    approx_t value;
  public:
    const string type = "number";
    const approx_t& get();
    ostream& output_to_stream(ostream& os);
    Number(approx_t value);
    static shared_ptr<Expression> construct(approx_t value = 0);
  };
}
