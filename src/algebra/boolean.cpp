#include <memory>
#include <iostream>

#include "base.hpp"
#include "scope.hpp"
#include "expression.hpp"
#include "boolean_constant.hpp"
#include "boolean.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Boolean::output_to_stream(ostream& stream) {
    return stream << "B<" << this->_expression << ">";
  }
  shared_ptr<Expression> Boolean::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Boolean::_evaluate(this->_expression, scope);
  }
  shared_ptr<Expression> Boolean::reduce(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Boolean::_reduce(this->_expression, scope);
  }
  shared_ptr<Expression> Boolean::expression() { return this->_expression; }
  Boolean::Boolean(shared_ptr<Expression> expression) : _expression{ expression } {
    this->_type = "boolean";
  }
  shared_ptr<Expression> Boolean::construct(shared_ptr<Expression> expression) {
    return shared_ptr<Expression>(new Boolean(expression));
  }
  shared_ptr<Expression> Boolean::_reduce(shared_ptr<Expression> expression, shared_ptr<Scope> scope) {
    return Boolean::construct(Expression::_reduce(expression, scope));
  }
  shared_ptr<Expression> Boolean::_evaluate(shared_ptr<Expression> expression, shared_ptr<Scope> scope) {
    return Boolean_Constant::construct(Expression::_evaluate(expression, scope));
  }
}
