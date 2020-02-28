#include <memory>
#include <iostream>

#include "algebra/types/base.hpp"
#include "algebra/scope.hpp"
#include "algebra/expression.hpp"
#include "algebra/types/function.hpp"

using namespace std;

namespace mathgraph::algebra::types {
  ostream& Function::output_to_stream(ostream& stream) {
    return stream << "F<" << this->_expression << ", " << this->_arguments << ">";
  }
  shared_ptr<Expression> Function::arguments() { return this->_arguments; }
  shared_ptr<Expression> Function::expression() { return this->_expression; }
  shared_ptr<Expression> Function::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Expression::_evaluate(this->_expression, scope);
  }
  shared_ptr<Expression> Function::reduce(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Function::_reduce(this->_expression, this->_arguments, scope);
  }
  Function::Function(shared_ptr<Expression> expression, shared_ptr<Expression> arguments) : _arguments{ arguments }, _expression{ expression } {
    this->_type = "function";
  }
  shared_ptr<Expression> Function::_reduce(shared_ptr<Expression> expression, shared_ptr<Expression> arguments, shared_ptr<Scope> scope) {
    return Function::construct(Expression::_reduce(expression, scope), Expression::_reduce(arguments, scope));
  }
  shared_ptr<Expression> Function::construct(shared_ptr<Expression> expression, shared_ptr<Expression> arguments) {
    return shared_ptr<Expression>(new Function(expression, arguments));
  }
}
