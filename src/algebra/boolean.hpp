#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Boolean : public Expression {
  private:
    bool value;
  public:
    const bool& get();
    ostream& output_to_stream(ostream& os);
    Boolean(bool value);
    static shared_ptr<Expression> construct(bool value = false);
  };
  extern shared_ptr<Expression> b_true;
  extern shared_ptr<Expression> b_false;
}
