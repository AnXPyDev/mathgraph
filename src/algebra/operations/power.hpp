#pragma once

#include <memory>

#include "../expression.hpp"
#include "base.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  shared_ptr<Expression> power(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b);
}
