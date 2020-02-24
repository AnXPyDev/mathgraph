#include <memory>
#include <iostream>

#include "base.hpp"
#include "scope.hpp"
#include "expression.hpp"
#include "function.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Function::output_to_stream(ostream& stream) {
    return stream << "F<" << this->_argument_list << ", " << this->_expression << ">";
  }
  shared_ptr<Expression> Function::argument_list() { return this->_argument_list; }
  shared_ptr<Expression> Function::expression() { return this->_expression; }
  shared_ptr<Expression> Function::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return this->_expression->evaluate(this->_expression, scope);
  }
  shared_ptr<Expression> Function::reduce(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Function::_reduce(this->_argument_list, this->_expression, scope);
  }
  Function::Function(shared_ptr<Expression> argument_list, shared_ptr<Expression> expression) : _argument_list{ argument_list }, _expression{ expression } {
    this->_type = "function";
  }
  shared_ptr<Expression> Function::_reduce(shared_ptr<Expression> argument_list, shared_ptr<Expression> expression, shared_ptr<Scope> scope) {
    return Function::construct(Expression::_reduce(argument_list, scope), Expression::_reduce(expression, scope));
  }
  shared_ptr<Expression> Function::construct(shared_ptr<Expression> argument_list, shared_ptr<Expression> expression) {
    return shared_ptr<Expression>(new Function(argument_list, expression));
  }
}
