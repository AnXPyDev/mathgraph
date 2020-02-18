#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Fraction : public Expression {
    ostream& output_to_stream(ostream& stream);
    // getter of _numerator
    shared_ptr<Expression> numerator();
    // getter of _denominator
    shared_ptr<Expression> denominator();
    vector<shared_ptr<Expression>> dependencies(shared_ptr<Expression> caller = undefined);
    shared_ptr<Expression> reduce(shared_ptr<Expression> caller = undefined);
    shared_ptr<Expression> evaluate(shared_ptr<Expression> caller = undefined, shared_ptr<Scope> scope = empty_scope);
    Fraction(shared_ptr<Expression> numerator, shared_ptr<Expression> denominator);
    static shared_ptr<Expression> _reduce(shared_ptr<Expression> numerator, shared_ptr<Expression> denominator);
    static shared_ptr<Expression> _evaluate(shared_ptr<Expression> numerator, shared_ptr<Expression> denominator, shared_ptr<Scope> scope = empty_scope);
    // constructs new fraction as a shared pointer to Expression
    static shared_ptr<Expression> construct(shared_ptr<Expression> numerator = undefined, shared_ptr<Expression> denominator = undefined);
  private:
    shared_ptr<Expression> _numerator;
    shared_ptr<Expression> _denominator;
  };
}
