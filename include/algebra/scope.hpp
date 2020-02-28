#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

#include "algebra/base.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Expression;
  extern shared_ptr<Expression> undefined;
  struct Scope;
  extern shared_ptr<Scope> empty_scope;
  struct Scope {
    shared_ptr<Expression> set_key(string key, shared_ptr<Expression> expr = undefined);
    shared_ptr<Expression> set_key(shared_ptr<Expression> key, shared_ptr<Expression> expr = undefined);
    shared_ptr<Expression> get_key(string key);
    shared_ptr<Expression> get_key(shared_ptr<Expression> key);
    void set_parent(shared_ptr<Scope> parent = empty_scope);
    shared_ptr<Scope> parent();
    void lock();
    void unlock();
    const bool& locked();
    Scope(bool locked);
    static shared_ptr<Scope> construct(bool locked = false);
  private:
    map<string, shared_ptr<Expression>> key_map;
    shared_ptr<Scope> _parent;
    // locking the scope prevents writing to it
    bool _locked;
  };
}
