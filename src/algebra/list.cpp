#include "list.hpp"

namespace mathgraph::algebra {
  const vector<shared_ptr<Expression>>& List::get() {
    return this->elements;
  }

  ostream& List::output_to_stream(ostream& os) {
    os << "{";
    for (auto it = this->elements.begin(); it < this->elements.end() - 1; ++it) {
      os << *it << ", ";
    }
    if (this->elements.size() > 0) {
      os << *(this->elements.end() - 1);
    }
    os << "}";
    return os;
  }

  List::List(vector<shared_ptr<Expression>> elements) : elements{ elements } {
    this->type = "list";
  }

  shared_ptr<Expression> List::construct(vector<shared_ptr<Expression>> elements) {
    if (elements.size() == 1) {
      return elements[0];
    }
    return shared_ptr<Expression>(new List(elements));
  }
}
