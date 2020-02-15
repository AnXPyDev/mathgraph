#pragma once

#include <memory>
#include <vector>
#include <string>

#include "base.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Expression;
  extern shared_ptr<Expression> undefined;
  struct Scope {
  private:
    vector<shared_ptr<Expression>> elements;
  public:
    shared_ptr<Expression> get(shared_ptr<Expression> expr = undefined);
    shared_ptr<Expression> get(string key = "");
  };
  extern shared_ptr<Scope> empty_scope;
}

