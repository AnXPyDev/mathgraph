#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "algebra.hpp"

using namespace mathgraph::algebra;

#define NUM(a) new expression::Constant(new value::Number(a))
#define REF(a) new expression::Reference(new Symbol(a))
#define ADD new expression::operations::Add
#define SUB new expression::operations::Subtract
#define MUL new expression::operations::Multiply
#define DIV new expression::operations::Division
#define MOD new expression::operations::Modulus
#define POW new expression::operations::Power
#define ROOT new expression::operations::Root
#define LOG new expression::operations::Logarithm
#define LIST new expression::List
#define SYM new Symbol

int main() {

  auto enviroment = new Enviroment();

  enviroment->set_value(SYM("PI"), NUM(3.14159265359));

  auto ret = MUL(LIST({NUM(1), NUM(2), NUM(3), NUM(4), NUM(5)}), REF("PI"));

  std::cout << ret->get_value(enviroment) << std::endl;

}
