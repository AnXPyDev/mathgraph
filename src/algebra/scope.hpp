#pragma once

#include <memory>

#include "base.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Scope {
    Scope();
  };
  extern shared_ptr<Scope> empty_scope;
}
