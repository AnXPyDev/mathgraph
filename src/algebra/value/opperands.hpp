#include <vector>

#include "../symbol.hpp"
#include "value.hpp"

namespace mathgraph::algebra::value {
  namespace opperands {
    class Unknown;
    class Sum;
    class Product;
    class Inverse;
  }
}

using namespace mathgraph::algebra;

class value::opperands::Unknown : public value::Value {
public:
  
  Unknown()
}
