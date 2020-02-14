#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "base.hpp"
#include "number.hpp"
#include "list.hpp"
#include "bool.hpp"
#include "operations.hpp"

using namespace mathgraph::algebra;

bool value::operations::to_boolean(value::Value_ptr a) {
  if (a->type == "value::bool") {
    return (dynamic_cast<value::Bool*>(a.get()))->evaluate();
  } else if (a->type == "value::number") {
    return true;
  }
  return false;
}

value::Value_ptr numerical_operation(value::Value_ptr a, value::Value_ptr b, approximate_t (*operation)(approximate_t, approximate_t)) {
  if (a->type == "value::bool") {
    a = value::Value_ptr(new value::Number(dynamic_cast<value::Bool*>(a.get())->evaluate() ? 1 : 0));
  }
  if (b->type == "value::bool") {
    b = value::Value_ptr(new value::Number(dynamic_cast<value::Bool*>(b.get())->evaluate() ? 1 : 0));
  }
  if (a->type == "value::number" && b->type == "value::number") {
    return value::Value_ptr(new Number(operation((dynamic_cast<value::Number*>(a.get()))->evaluate(), (dynamic_cast<value::Number*>(b.get()))->evaluate())));
  } else if (a->type == "value::list" || b->type == "value::list") {
    std::vector<value::Value_ptr> new_list_elements;
    value::List* list; value::Value_ptr other;
    if (a->type == "value::list") {
      list = dynamic_cast<value::List*>(a.get());
      other = b;
    } else {
      list = dynamic_cast<value::List*>(b.get());
      other = a;
    }
    std::vector<value::Value_ptr> list_elements = list->get_elements();
    for (auto it = list_elements.begin(); it < list_elements.end(); ++it) {
      new_list_elements.push_back(numerical_operation(*it, other, operation));
    }
    return value::Value_ptr(new value::List(new_list_elements));
  }
  return undefined_value;
}

value::Value_ptr boolean_operation(value::Value_ptr a, value::Value_ptr b, bool (*operation)(approximate_t, approximate_t)) {
  if (a->type == "value::number" && b->type == "value::number") {
    return value::Value_ptr(new value::Bool(operation((dynamic_cast<value::Number*>(a.get()))->evaluate(), (dynamic_cast<value::Number*>(b.get()))->evaluate())));
  } else if (a->type == "value::list" || b->type == "value::list") {
    std::vector<value::Value_ptr> new_list_elements;
    List* list; Value_ptr other;
    if (a->type == "value::list") {
      list = dynamic_cast<value::List*>(a.get());
      other = b;
    } else {
      list = dynamic_cast<value::List*>(b.get());
      other = a;
    }
    std::vector<value::Value_ptr> list_elements = list->get_elements();
    for (auto it = list_elements.begin(); it < list_elements.end(); ++it) {
      new_list_elements.push_back(boolean_operation(*it, other, operation));
    }
    return value::Value_ptr(new value::List(new_list_elements));
  }
  return value::undefined_value;
}

value::Value_ptr binary_operation(value::Value_ptr a, value::Value_ptr b, bool (*operation)(bool, bool)) {
  if (a->type == "value::list" || b->type == "value::list") {
    std::vector<value::Value_ptr> new_list_elements;
    List* list; Value_ptr other;
    if (a->type == "value::list") {
      list = dynamic_cast<value::List*>(a.get());
      other = b;
    } else {
      list = dynamic_cast<value::List*>(b.get());
      other = a;
    }
    std::vector<value::Value_ptr> list_elements = list->get_elements();
    for (auto it = list_elements.begin(); it < list_elements.end(); ++it) {
      new_list_elements.push_back(binary_operation(*it, other, operation));
    }
    return value::Value_ptr(new value::List(new_list_elements));
  } else {
    return value::Value_ptr(new value::Bool(operation(value::operations::to_boolean(a), value::operations::to_boolean(b))));
  }
}

std::ostream& value::operations::output_to_stream(std::ostream& stream, value::Value_ptr a) {
  if (a->type == "value::number") {
    stream << (dynamic_cast<value::Number*>(a.get()))->evaluate();
  } else if (a->type == "value::list") {
    stream << "{";
    auto elements = (dynamic_cast<value::List*>(a.get()))->get_elements();
    for (auto it = elements.begin(); it < elements.end(); ++it) {
      operations::output_to_stream(stream, *it);
      if (it < elements.end() - 1) {
        stream << ", ";
      }
    }
    stream << "}";
  } else if (a->type == "value::bool") {
    stream << ((dynamic_cast<value::Bool*>(a.get()))->evaluate() ? "True" : "False");
  } else {
    stream << "undefined";
  }
  return stream;
}

approximate_t OP_add(approximate_t a, approximate_t b) { return a + b; }
approximate_t OP_subtract(approximate_t a, approximate_t b) { return a - b; }
approximate_t OP_multiply(approximate_t a, approximate_t b) { return a * b; }
approximate_t OP_divide(approximate_t a, approximate_t b) { return a / b; }
approximate_t OP_modulus(approximate_t a, approximate_t b) { return a / b; }
approximate_t OP_power(approximate_t a, approximate_t n) { return pow(a, n); }
approximate_t OP_root(approximate_t a, approximate_t n) { return pow(a, 1/n); }
approximate_t OP_logarithm(approximate_t a, approximate_t base) { return log(a) / log(base); }

bool OP_equal(approximate_t a, approximate_t b) { return a == b; }
bool OP_less(approximate_t a, approximate_t b) { return a < b; }
bool OP_more(approximate_t a, approximate_t b) { return a > b; }
bool OP_less_or_equal(approximate_t a, approximate_t b) { return a <= b; }
bool OP_more_or_equal(approximate_t a, approximate_t b) { return a >= b; }

bool OP_and(bool a, bool b) { return a && b; }
bool OP_or(bool a, bool b) { return a || b; }

value::Value_ptr value::operations::add(value::Value_ptr a, value::Value_ptr b) { return numerical_operation(a, b, &OP_add); }
value::Value_ptr value::operations::subtract(value::Value_ptr a, value::Value_ptr b) { return numerical_operation(a, b, &OP_subtract); }
value::Value_ptr value::operations::multiply(value::Value_ptr a, value::Value_ptr b) { return numerical_operation(a, b, &OP_multiply); }
value::Value_ptr value::operations::divide(value::Value_ptr a, value::Value_ptr b) { return numerical_operation(a, b, &OP_divide); }
value::Value_ptr value::operations::modulus(value::Value_ptr a, value::Value_ptr b) { return numerical_operation(a, b, &OP_modulus); }
value::Value_ptr value::operations::power(value::Value_ptr a, value::Value_ptr b) { return numerical_operation(a, b, &OP_power); }
value::Value_ptr value::operations::root(value::Value_ptr a, value::Value_ptr b) { return numerical_operation(a, b, &OP_root); }
value::Value_ptr value::operations::logarithm(value::Value_ptr a, value::Value_ptr b) { return numerical_operation(a, b, &OP_logarithm); }

value::Value_ptr value::operations::equal(value::Value_ptr a, value::Value_ptr b) { return boolean_operation(a, b, &OP_equal); }
value::Value_ptr value::operations::less(value::Value_ptr a, value::Value_ptr b) { return boolean_operation(a, b, &OP_less); }
value::Value_ptr value::operations::more(value::Value_ptr a, value::Value_ptr b) { return boolean_operation(a, b, &OP_more); }
value::Value_ptr value::operations::less_or_equal(value::Value_ptr a, value::Value_ptr b) { return boolean_operation(a, b, &OP_less_or_equal); }
value::Value_ptr value::operations::more_or_equal(value::Value_ptr a, value::Value_ptr b) { return boolean_operation(a, b, &OP_more_or_equal); }

value::Value_ptr value::operations::conjunction(value::Value_ptr a, value::Value_ptr b) { return binary_operation(a, b, &OP_and); }
value::Value_ptr value::operations::disjunction(value::Value_ptr a, value::Value_ptr b) { return binary_operation(a, b, &OP_or); }

value::Value_ptr value::operations::negate(value::Value_ptr a) {
  if (a->type == "value::list") {
    std::vector<value::Value_ptr> new_list_elements;
    List* list = dynamic_cast<value::List*>(a.get());
    std::vector<value::Value_ptr> list_elements = list->get_elements();
    for (auto it = list_elements.begin(); it < list_elements.end(); ++it) {
      new_list_elements.push_back(value::operations::negate(*it));
    }
    return value::Value_ptr(new value::List(new_list_elements));
  } else {
    return value::Value_ptr(new value::Bool(!value::operations::to_boolean(a)));
  }
}

std::ostream& operator<<(std::ostream& stream, Value_ptr a) { return operations::output_to_stream(stream, a); }
