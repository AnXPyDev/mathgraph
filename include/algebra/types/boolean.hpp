#pragma once

#include <iostream>
#include <memory>

#include "algebra/types/base.hpp"
#include "algebra/expression.hpp"

using namespace std;

namespace mathgraph::algebra::types {
  struct Boolean : public Expression {
    ostream& output_to_stream(ostream& stream);
    const bool& value();
    Boolean(bool value);
    static shared_ptr<Expression> construct(bool value = false);
    static shared_ptr<Expression> construct(shared_ptr<Expression> expr = undefined);
  private:
    bool _value;
  };
  extern shared_ptr<Expression> b_true;
  extern shared_ptr<Expression> b_false;
}
