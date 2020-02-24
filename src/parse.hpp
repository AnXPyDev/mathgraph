#pragma once

#include <memory>
#include <string>
#include <vector>

#include "algebra/expression.hpp"

using namespace std;

namespace mathgraph {
  namespace parse {}
}

namespace mathgraph::parse {
  shared_ptr<algebra::Expression> expression(string input);
}
