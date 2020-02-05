#include <iostream>

#include "../value/number.hpp"
#include "../enviroment.hpp"
#include "base.hpp"
#include "expression.hpp"

using namespace mathgraph::algebra;

value::Value* expression::Expression::get_value(Enviroment* enviroment, bool force_update) {
  if (enviroment == NULL) {
    enviroment = this->last_enviroment;
  }
  if (this->last_enviroment != enviroment || force_update) {
    this->update(enviroment, force_update);
  }
  return this->value;
}

void expression::Expression::update(Enviroment* enviroment, bool force_update) {
  if (enviroment == NULL) {
    enviroment = this->last_enviroment;
  }
  if (this->mute_next_update) {
    this->mute_next_update = false;
    return;
  }
  this->mute_next_update = true;
  this->update_value(enviroment, force_update);
  for (auto it = this->dependants.begin(); it < this->dependants.end(); ++it) {
    (*it)->update();
  }
}

void expression::Expression::update_value(Enviroment* enviroment, bool force_update) {};

void expression::Expression::add_member(expression::Expression* member) {
  this->members.push_back(member);
}

void expression::Expression::remove_member(expression::Expression* member) {
  for (auto it = this->members.begin(); it < this->members.end(); ++it) {
    if ((*it) == member) {
      this->members.erase(it--);
    }
  }
}

void expression::Expression::add_dependant(expression::Expression* dependant) {
  this->dependants.push_back(dependant);
}

void expression::Expression::remove_dependant(expression::Expression* dependant) {
  for (auto it = this->dependants.begin(); it < this->dependants.end(); ++it) {
    if ((*it) == dependant) {
      this->dependants.erase(it--);
    }
  }
}

expression::Expression::~Expression() {
  for (auto it = this->members.begin(); it < this->members.end(); ++it) {
    (*it)->remove_dependant(this);
  }
  for (auto it = this->dependants.begin(); it < this->dependants.end(); ++it) {
    (*it)->remove_member(this);
  }
}

expression::Expression::Expression() {
  this->type = "expression";
  value::Number num(0);
  this->value = &num;
  Enviroment env;
  this->last_enviroment = &env;
  this->mute_next_update = false;
}
