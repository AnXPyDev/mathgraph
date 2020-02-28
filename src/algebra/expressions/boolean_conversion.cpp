#include <memory>
#include <iostream>

#include "algebra/expressions/base.hpp"
#include "algebra/scope.hpp"
#include "algebra/expression.hpp"
#include "algebra/types/boolean.hpp"
#include "algebra/expressions/boolean_conversion.hpp"

using namespace std;

namespace mathgraph::algebra::expressions {
  ostream& Boolean_conversion::output_to_stream(ostream& stream) {
    return stream << "B<" << this->_expression << ">";
  }
  shared_ptr<Expression> Boolean_conversion::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Boolean_conversion::_evaluate(this->_expression, scope);
  }
  shared_ptr<Expression> Boolean_conversion::reduce(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Boolean_conversion::_reduce(this->_expression, scope);
  }
  shared_ptr<Expression> Boolean_conversion::expression() { return this->_expression; }
  Boolean_conversion::Boolean_conversion(shared_ptr<Expression> expression) : _expression{ expression } {
    this->_type = "boolean_conversion";
  }
  shared_ptr<Expression> Boolean_conversion::construct(shared_ptr<Expression> expression) {
    return shared_ptr<Expression>(new Boolean_conversion(expression));
  }
  shared_ptr<Expression> Boolean_conversion::_reduce(shared_ptr<Expression> expression, shared_ptr<Scope> scope) {
    return Boolean_conversion::construct(Expression::_reduce(expression, scope));
  }
  shared_ptr<Expression> Boolean_conversion::_evaluate(shared_ptr<Expression> expression, shared_ptr<Scope> scope) {
    return types::Boolean::construct(Expression::_evaluate(expression, scope));
  }
}
