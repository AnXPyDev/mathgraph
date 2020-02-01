#include <cmath>
#include <vector>
#include <string>
#include <iostream>

#include "base.hpp"
#include "number.hpp"
#include "list.hpp"
#include "operations.hpp"

using namespace mathgraph::algebra;

Value* generic_operation(Value* a, Value* b, approximate_t (*operation)(approximate_t, approximate_t)) {
  if (a->type == "number" && b->type == "number") {
    return new Number((*operation)((dynamic_cast<Number*>(a))->get_value(), (dynamic_cast<Number*>(b))->get_value()));
  } else if (a->type == "list" || b->type == "list") {
    std::vector<Value*> new_list_elements;
    List* list; Value* other;
    if (a->type == "list") {
      list = dynamic_cast<List*>(a);
      other = b;
    } else if (b->type == "list") {
      list = dynamic_cast<List*>(b);
      other = a;
    }
    std::vector<Value*> list_elements = list->get_elements();
    for (auto it = list_elements.begin(); it < list_elements.end(); ++it) {
      new_list_elements.push_back(generic_operation(*it, other, operation));
    }
    return new List(new_list_elements);
  }
  return new Value();
}

std::ostream& operations::output_to_stream(std::ostream& stream, Value* a) {
  if (a->type == "number") {
    stream << (dynamic_cast<Number*>(a))->get_value();
  } else if (a->type == "list") {
    stream << "{";
    auto elements = (dynamic_cast<List*>(a))->get_elements();
    for (auto it = elements.begin(); it < elements.end() - 1; ++it) {
      operations::output_to_stream(stream, *it);
      stream << ", ";
    }
    operations::output_to_stream(stream, *(elements.end() - 1));
    stream << "}";
  }
  return stream;
}

approximate_t OP_add(approximate_t a, approximate_t b) { return a + b; }
approximate_t OP_subtract(approximate_t a, approximate_t b) { return a - b; }
approximate_t OP_multiply(approximate_t a, approximate_t b) { return a * b; }
approximate_t OP_divide(approximate_t a, approximate_t b) { return a / b; }
approximate_t OP_power(approximate_t a, approximate_t n) { return pow(a, n); }
approximate_t OP_root(approximate_t a, approximate_t n) { return pow(a, 1/n); }
approximate_t OP_logarithm(approximate_t a, approximate_t base) { return log(a) / log(base); }

Value* operations::add(Value* a, Value* b) { return generic_operation(a, b, &OP_add); }
Value* operations::subtract(Value* a, Value* b) { return generic_operation(a, b, &OP_subtract); }
Value* operations::multiply(Value* a, Value* b) { return generic_operation(a, b, &OP_multiply); }
Value* operations::divide(Value* a, Value* b) { return generic_operation(a, b, &OP_divide); }
Value* operations::power(Value* a, Value* b) { return generic_operation(a, b, &OP_power); }
Value* operations::root(Value* a, Value* b) { return generic_operation(a, b, &OP_root); }
Value* operations::logarithm(Value* a, Value* b) { return generic_operation(a, b, &OP_logarithm); }

// Value* operator+(Value* a, Value* b) { operations::add(a, b); }
// Value* operator-(Value* a, Value* b) { operations::subtract(a, b); }
// Value* operator*(Value* a, Value* b) { operations::multiply(a, b); }
// Value* operator/(Value* a, Value* b) { operations::divide(a, b); }
std::ostream& operator<<(std::ostream& stream, Value* a) { operations::output_to_stream(stream, a); }
