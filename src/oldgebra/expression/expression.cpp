#include "base.hpp"
#include "number.hpp"
#include "expression.hpp"

using namespace mathgraph::algebra;

Value* Expression::evaluate() {
  return this->value;
}

void Expression::update() {
  this->update_value();
  for (auto it = this->dependants.begin; it < this->dependants.end(); ++it) {
    (*it)->update();
  }
}

void Expression::update_value() {};

void Expression::add_member(Expression* member) {
  this->members.push_back(member);
}

void Expression::remove_member(Expression* member) {
  for (auto it = this->members.begin(); it < this->members.end(); ++it) {
    if ((*it) == member) {
      this->members.erase(it--);
    }
  }
}

void Expression::add_dependant(Expression* dependant) {
  this->dependants.push_back(member);
}

void Expression::remove_member(Expression* dependant) {
  for (auto it = this->dependants.begin(); it < this->dependants.end(); ++it) {
    if ((*it) == dependant) {
      this->dependants.erase(it--);
    }
  }
}

Expression::~Expression() {
  for (auto it = this->members.begin(); it < this->members.end(); ++it) {
    (*it)->remove_dependant(this);
  }
  for (auto it = this->dependants.begin(); it < this->dependants.end(); ++it) {
    (*it)->remove_member(this);
  }
}

Expression::Expression() {
  this->type = "expression"
  this->value = new Number(0);
}
