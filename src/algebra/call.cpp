#include <memory>
#include <iostream>
#include <vector>

#include "base.hpp"
#include "scope.hpp"
#include "expression.hpp"
#include "list.hpp"
#include "function.hpp"
#include "assignment.hpp"
#include "call.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Call::output_to_stream(ostream& stream) {
    return stream << "C<" << this->_expression << ", " << this->_arguments << ">";
  }
  shared_ptr<Expression> Call::reduce(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Call::_reduce(this->_expression, this->_arguments, scope);
  }
  shared_ptr<Expression> Call::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    return Call::_evaluate(this->_expression, this->_arguments, scope);
  }
  shared_ptr<Expression> Call::expression() { return this->_expression; }
  shared_ptr<Expression> Call::arguments() { return this->_arguments; }
  Call::Call(shared_ptr<Expression> expression, shared_ptr<Expression> arguments) : _expression{ expression }, _arguments{ arguments } {
    this->_type = "call";
  }
  shared_ptr<Expression> Call::construct(shared_ptr<Expression> expression, shared_ptr<Expression> arguments) {
    return shared_ptr<Expression>(new Call(expression, arguments));
  }
  shared_ptr<Expression> Call::_reduce(shared_ptr<Expression> expression, shared_ptr<Expression> arguments, shared_ptr<Scope> scope) {
    return Call::construct(Expression::_reduce(expression, scope), Expression::_reduce(arguments, scope));
  }
  shared_ptr<Expression> Call::_evaluate(shared_ptr<Expression> expression, shared_ptr<Expression> arguments, shared_ptr<Scope> scope) {
    if (arguments == "undefined") {
      return Expression::_evaluate(expression, scope);
    } else if (expression == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto list_elements = dynamic_cast<List*>(expression.get())->elements();
      for (auto element : list_elements) {
        new_list_elements.push_back(Call::_evaluate(element, arguments, scope));
      }
      return List::construct(new_list_elements);
    }
    shared_ptr<Scope> sub_scope = Scope::construct();
    sub_scope->set_parent(scope);
    shared_ptr<Expression> argument_names = undefined;
    if (expression == "symbol") {
      auto refered_expr = scope->get_key(expression);
      if (refered_expr == "function") {
        argument_names = dynamic_cast<Function*>(refered_expr.get())->arguments();
      }
    }
    Assignment::_evaluate(argument_names, Expression::_evaluate(arguments, sub_scope), sub_scope);
    return Expression::_evaluate(expression, sub_scope);
  }
}
