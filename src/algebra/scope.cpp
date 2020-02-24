#include <memory>

#include "base.hpp"
#include "expression.hpp"
#include "error.hpp"
#include "symbol.hpp"
#include "scope.hpp"

using namespace std;

namespace mathgraph::algebra {
  shared_ptr<Expression> Scope::set_key(string key, shared_ptr<Expression> expr) {
    if (!this->_locked) {
      this->key_map[key] = expr;
    }
    return expr;
  }
  shared_ptr<Expression> Scope::set_key(shared_ptr<Expression> key, shared_ptr<Expression> expr) {
    if (key == "symbol") {
      return this->set_key(dynamic_cast<Symbol*>(key.get())->value(), expr);
    } else {
      return Error::construct("scope can't assign to type: " + key->type());
    }
  }
  shared_ptr<Expression> Scope::get_key(string key) {
    if (this->key_map.find(key) == this->key_map.end()) {
      if (this->_parent != NULL) {
        return this->_parent->get_key(key);
      }
      return undefined;
    }
    return this->key_map[key];
  }
  shared_ptr<Expression> Scope::get_key(shared_ptr<Expression> key) {
    if (key == "symbol") {
      this->get_key(dynamic_cast<Symbol*>(key.get())->value());
    }
    return undefined;
  }
  void Scope::set_parent(shared_ptr<Scope> parent) {
    this->_parent = parent;
  }
  shared_ptr<Scope> Scope::parent() {
    return this->_parent;
  }
  void Scope::lock() {
    this->_locked = true;
  }
  void Scope::unlock() {
    this->_locked = false;
  }
  const bool& Scope::locked() {
    return this->_locked;
  }
  Scope::Scope(bool locked) : _locked{ locked } {
    this->_parent = NULL;
  }
  shared_ptr<Scope> Scope::construct(bool locked) {
    return shared_ptr<Scope>(new Scope(locked));
  }
  shared_ptr<Scope> empty_scope = shared_ptr<Scope>(new Scope(true));
}
