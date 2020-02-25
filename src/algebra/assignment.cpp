#include <memory>
#include <vector>
#include <iostream>

#include "base.hpp"
#include "scope.hpp"
#include "expression.hpp"
#include "list.hpp"
#include "assignment.hpp"

using namespace std;

#define CLAMP(x, min, max) (x < min ? min : (x > max ? max : x))

namespace mathgraph::algebra {
  ostream& Assignment::output_to_stream(ostream& stream) {
    return stream << "A<" << this->_left << " = " << this->_right << ">";
  }
  shared_ptr<Expression> Assignment::reduce(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Assignment::_reduce(this->_left, this->_right, scope);
  }
  shared_ptr<Expression> Assignment::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Assignment::_evaluate(this->_left, this->_right, scope);
  }
  shared_ptr<Expression> Assignment::left() { return this->_left; }
  shared_ptr<Expression> Assignment::right() { return this->_right; }
  Assignment::Assignment(shared_ptr<Expression> left, shared_ptr<Expression> right) : _left{ left }, _right{ right } {
    this->_type = "assignment";
  }

  shared_ptr<Expression> Assignment::_reduce(shared_ptr<Expression> left, shared_ptr<Expression> right, shared_ptr<Scope> scope) {
    return Assignment::construct(Expression::_reduce(left, scope), Expression::_reduce(right, scope));
  }

  shared_ptr<Expression> Assignment::_evaluate(shared_ptr<Expression> left, shared_ptr<Expression> right, shared_ptr<Scope> scope) {
    if (left == "list") {
      vector<shared_ptr<Expression>> return_elements;
      auto left_elements = dynamic_cast<List*>(left.get())->elements();
      vector<shared_ptr<Expression>> right_elements = {right};
      if (right == "list") {
        right_elements = dynamic_cast<List*>(right.get())->elements();
      }
      for (int i = 0; i < left_elements.size(); ++i) {
        return_elements.push_back(Assignment::_evaluate(left_elements[i], right_elements[CLAMP(i, 0, right_elements.size() - 1)], scope));
      }
      return List::construct(return_elements);
    }
    return scope->set_key(left, right);
  }

  shared_ptr<Expression> Assignment::construct(shared_ptr<Expression> left, shared_ptr<Expression> right) {
    return shared_ptr<Expression>(new Assignment(left, right));
  }
}
