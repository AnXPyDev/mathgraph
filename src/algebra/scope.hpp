#pragma once

#include <memory>
#include <vector>

#include "base.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Scope;
}

#include "expression.hpp"
#include "symbol.hpp"

namespace mathgraph::algebra {
  struct Scope {
    vector<shared_ptr<Expression>> elements;
  };
}

