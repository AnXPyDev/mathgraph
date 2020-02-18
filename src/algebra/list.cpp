#include <iostream>
#include <vector>
#include <memory>

#include "base.hpp"
#include "expression.hpp"
#include "operations.hpp"
#include "list.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& List::output_to_stream(ostream& stream) {
    stream << "{";
    for (auto it = this->_elements.begin(); it < this->_elements.end() -1; ++it) {
      stream << *it << ", ";
    }
    return stream << *(this->_elements.end() - 1) << "}";
  }
  vector<shared_ptr<Expression>> List::dependencies(shared_ptr<Expression> caller) {
    vector<shared_ptr<Expression>> result = {};
    for (auto element : this->_elements) {
      for (auto dependency : element->dependencies(element)) {
        // only add unique dependencies
        bool is_unique = true;
        for (auto result_element : result) {
          if (operations::equal(result_element, dependency)) {
            is_unique = false;
            break;
          }
        }
        if (is_unique) result.push_back(dependency);
      }
    }
    return result;
  }
  shared_ptr<Expression> List::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return List::_evaluate(this->_elements, scope);
  }
  const vector<shared_ptr<Expression>>& List::elements() {
    return this->_elements;
  }
  List::List(vector<shared_ptr<Expression>> elements) : _elements{ elements } {
    this->_type = "list";
  }
  shared_ptr<Expression> List::construct(vector<shared_ptr<Expression>> elements) {
    return shared_ptr<Expression>(new List(elements));
  }
  shared_ptr<Expression> List::_evaluate(vector<shared_ptr<Expression>> elements, shared_ptr<Scope> scope) {
    vector<shared_ptr<Expression>> new_list_elements = {};
    for (auto element : elements) {
      new_list_elements.push_back(element->evaluate(element, scope));
    }
    return List::construct(new_list_elements);
  }
}
