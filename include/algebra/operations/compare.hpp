#pragma once

#include <memory>

#include "algebra/operations/base.hpp"
#include "algebra/expression.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  expr_t less(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b);
  expr_t more(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b);
}
