#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct List : public Expression {
  protected:
    vector<shared_ptr<Expression>> elements;
  public:
    const vector<shared_ptr<Expression>>& get();
    virtual ostream& output_to_stream(ostream& os);
    List(vector<shared_ptr<Expression>> elements);
    static shared_ptr<Expression> construct(vector<shared_ptr<Expression>> elements = {});
  };
}
