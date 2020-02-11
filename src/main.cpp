#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "algebra.hpp"

using namespace mathgraph::algebra;

#define NIL expression::undefined_expression
#define NUM(a) expression::Expression_ptr(new expression::Constant(value::Value_ptr(new value::Number(a))))
#define BOOL(a) expression::Expression_ptr(new expression::Constant(value::Value_ptr(new value::Bool(a))))
#define LIST(a) expression::Expression_ptr(new expression::List(a))
#define VEC std::vector<expression::Expression_ptr>
#define ADD(a, b) expression::Expression_ptr(new expression::operations::Add(a, b))
#define SUB(a, b) expression::Expression_ptr(new expression::operations::Subtract(a, b))
#define MUL(a, b) expression::Expression_ptr(new expression::operations::Multiply(a, b))
#define DIV(a, b) expression::Expression_ptr(new expression::operations::Divide(a, b))
#define MOD(a, b) expression::Expression_ptr(new expression::operations::Modulus(a, b))
#define POW(a, b) expression::Expression_ptr(new expression::operations::Power(a, b))
#define ROOT(a, b) expression::Expression_ptr(new expression::operations::Root(a, b))
#define LOG(a, b) expression::Expression_ptr(new expression::operations::Logarithm(a, b))
#define LOG(a, b) expression::Expression_ptr(new expression::operations::Logarithm(a, b))
#define EQ(a, b) expression::Expression_ptr(new expression::operations::Equal(a, b))
#define NOT(a) expression::Expression_ptr(new expression::operations::Negate(a))
#define IF(a, b, c) expression::Expression_ptr(new expression::operations::If(a, b, c))
#define AND(a, b) expression::Expression_ptr(new expression::operations::And(a, b))
#define OR(a, b) expression::Expression_ptr(new expression::operations::Or(a, b))
#define LESS(a, b) expression::Expression_ptr(new expression::operations::Less(a, b))
#define MORE(a, b) expression::Expression_ptr(new expression::operations::More(a, b))
#define LESSEQ(a, b) expression::Expression_ptr(new expression::operations::Less_or_equal(a, b))
#define MOREEQ(a, b) expression::Expression_ptr(new expression::operations::More_or_equal(a, b))
#define REF(a) expression::Expression_ptr(new expression::Reference(Symbol_ptr(new Symbol(a))))
#define SYM(a) Symbol_ptr(new Symbol(a))
#define ENVIROMENT() Enviroment_ptr(new Enviroment())
#define CALL(a, b) expression::Expression_ptr(new expression::Call(a, b))
#define FUNC(a, b) expression::Expression_ptr(new expression::Function(a, b))

int main() {
  auto env = ENVIROMENT();
  env->set_value(SYM("ret"), CALL(REF("fac"), {NUM(5)}));

  std::cout << REF("ret")->get_value(env) << std::endl;
  
}
