/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * Licensed under the MIT license (see LICENSE).
 */
#include <stdlib.h>
#include "../svalue.h"
#include "../symboltable.h"

namespace fnordmetric {
namespace query {

static void countExpr(void* scratchpad, int argc, SValue* argv, SValue* out) {
  uint64_t* count = (uint64_t*) scratchpad;
  *out = SValue((int64_t) ++(*count));
}

static SymbolTableEntry __count_symbol(
    "count",
    &countExpr,
    sizeof(uint64_t));

/**
 * SUM() expression
 */
union sum_expr_scratchpad {
  uint64_t t_integer;
  double t_float;
};

static void sumExpr(void* scratchpad, int argc, SValue* argv, SValue* out) {
  assert(argc == 1);
  SValue* val = argv;

  union sum_expr_scratchpad* data = (union sum_expr_scratchpad*) scratchpad;

  switch(val->getType()) {
    case SValue::T_INTEGER:
      data->t_integer += val->getInteger();
      *out = SValue((int64_t) data->t_integer);
      return;
    case SValue::T_FLOAT:
      data->t_float += val->getFloat();
      *out = SValue(data->t_float);
      return;
    default:
      break;
  }

  assert(0);
}

static SymbolTableEntry __sum_symbol(
    "sum",
    &sumExpr,
    sizeof(union sum_expr_scratchpad));


}
}