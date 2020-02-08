#pragma once

#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"

namespace mathgraph::algebra::expression {
  class Operation;
  namespace operations {
    class Add;
    class Subtract;
    class Multiply;
    class Divide;
    class Modulus;
    class Power;
    class Root;
    class Logarithm;
  }
}

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Operation : public expression::Expression {
public:
  expression::Expression* expr_a;
  expression::Expression* expr_b;
  Operation(expression::Expression* expr_a = expression::undefined_expression, expression::Expression* expr_b = expression::undefined_expression);
};

class mathgraph::algebra::expression::operations::Add : public expression::Operation {
public:
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Subtract : public expression::Operation {
public:
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Multiply : public expression::Operation {
public:
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Divide : public expression::Operation {
public:
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Modulus : public expression::Operation {
public:
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Power : public expression::Operation {
public:
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Root : public expression::Operation {
public:
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Logarithm : public expression::Operation {
public:
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  using Operation::Operation;
};
