#pragma once

#include <memory>

#include "../expression.hpp"
#include "base.hpp"


namespace mathgraph::algebra::operations {
  bool equal(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b);
}
