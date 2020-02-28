#pragma once

#include <memory>

#include "algebra/operations/base.hpp"
#include "algebra/expression.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  bool equal(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b);
}
