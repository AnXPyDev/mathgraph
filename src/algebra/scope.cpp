#include <memory>

#include "base.hpp"
#include "scope.hpp"

using namespace std;

namespace mathgraph::algebra {
  Scope::Scope() {}
  shared_ptr<Scope> empty_scope = shared_ptr<Scope>(new Scope());
}
