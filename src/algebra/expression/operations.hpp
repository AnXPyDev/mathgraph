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
    class If;
    class And;
    class Or;
    class Negate;
    class Equal;
    class Less;
    class Less_or_equal;
    class More;
    class More_or_equal;
  }
}

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Operation : public expression::Expression {
public:
  expression::Expression_ptr expr_a;
  expression::Expression_ptr expr_b;
  Operation(expression::Expression_ptr expr_a = expression::undefined_expression, expression::Expression_ptr expr_b = expression::undefined_expression);
};

class mathgraph::algebra::expression::operations::Add : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Subtract : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Multiply : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Divide : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Modulus : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Power : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Root : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Logarithm : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::And : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};


class mathgraph::algebra::expression::operations::Or : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Equal : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Less : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::Less_or_equal : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::More : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::More_or_equal : public expression::Operation {
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  using Operation::Operation;
};

class mathgraph::algebra::expression::operations::If : public expression::Expression {
public:
  expression::Expression_ptr condition;
  expression::Expression_ptr case_true;
  expression::Expression_ptr case_false;
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  //expression::Expression_ptr get_expression(Enviroment_ptr env = undefined_enviroment, expression::Expression_ptr caller = NULL);
  If(expression::Expression_ptr condition = expression::undefined_expression, expression::Expression_ptr case_true = expression::undefined_expression, expression::Expression_ptr case_false = expression::undefined_expression);
};

class mathgraph::algebra::expression::operations::Negate : public expression::Expression {
public:
  Expression_ptr expression;
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  expression::Expression_ptr get_expression(Enviroment_ptr env = undefined_enviroment, expression::Expression_ptr caller = NULL);
  Negate(expression::Expression_ptr expression = expression::undefined_expression);
};
