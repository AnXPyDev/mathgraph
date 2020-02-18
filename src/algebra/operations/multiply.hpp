#pragma once

#include <memory>

#include "../expression.hpp"
#include "base.hpp"

namespace mathgraph::algebra::operations {
  shared_ptr<Expression> multiply(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b);
}
