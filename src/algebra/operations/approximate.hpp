#pragma once

#include <memory>

#include "../expression.hpp"
#include "base.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  shared_ptr<Expression> approximate(shared_ptr<Expression> expr);
}
