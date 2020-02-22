#include <string>
#include <memory>
#include <iostream>

#include "base.hpp"
#include "expression.hpp"
#include "error.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Error::output_to_stream(ostream& stream) {
    return stream << "E<" << this->_message << ">";
  }
  const string& Error::message() {
    return this->_message;
  }
  Error::Error(string message) : _message{ message } {
    this->_type = "error";
  }
  shared_ptr<Expression> Error::construct(string message) {
    return shared_ptr<Expression>(new Error(message));
  }
}
