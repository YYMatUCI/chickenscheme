/**
 * \file eval.cpp
 *
 * A dummy implementation for example purposes.  Just barely enough is
 * implemented to allow the parser to run.  Merely returns the input
 * expression without evaluating it.
 */

#include "eval.hpp"
#include<cmath>

/**
 * \brief Evaluate plus cell.
 * \param c Head of cells to plus.
 * \param is_minus True if would like to calculate minus.
 * \return A constant cell which contains int/double. 0 if no parameters given.
 */
Cell* eval_plus(Cell* const c, bool is_minus=false)
{
  if (is_minus && (nullp(c) || nullp(cdr(c)))) {
    cerr << "ERROR: At least two parameters are needed for minus operator.\n";
    exit(1);
  }
  bool is_int = true;
  double d = 0;
  Cell* cur = c;
  // Case minus would be a - b - c - ... = - (-a + b + c + ...)
  if (is_minus) {
    eval(car(cur))->plus_c(is_int, d);
    cur = cdr(cur);
    d = -d;
  }
  while (!nullp(cur)) {
    eval(car(cur))->plus_c(is_int, d);
    cur = cdr(cur);
  }
  if (is_minus) {
    d = -d;
  }
  return make_num(is_int, d);
}

/**
 * \brief Evaluate minus cell.
 * \param c Head of cells to minus.
 * \return A constant cell which contains int/double.
 */
Cell* eval_minus(Cell* const c)
{
  return eval_plus(c, true);
}

/**
 * \brief Evaluate multi cell. Early stopping when 0 founded.
 * \param c Head of cells to multi.
 * \param is_divide
 * \return A constant cell which contains int/double. 1 if no parameters given.
 */
Cell* eval_multi(Cell* const c, bool is_divide=false)
{
  if (is_divide && (nullp(c) || nullp(cdr(c)))) {
    cerr << "ERROR: At least two parameters are needed for minus operator.\n";
    exit(1);
  }
  bool is_int = true;
  double d = 1;
  double n = 1;
  Cell* cur = c;
  if (is_divide) {
    eval(car(cur))->multi_c(is_int, n);
    cur = cdr(cur);
  }
  while (!nullp(cur)) {
    eval(car(cur))->multi_c(is_int, d);
    if (d == 0) break;
    cur = cdr(cur);
  }
  if (is_divide) {
    if (d == 0) {
      cerr << "ERROR: The divisor cannot be zero.\n";
      exit(1);
    }
    d = n / d;
  }
  return make_num(is_int, d);
}

/**
 * \brief Evaluate divide cell.
 * \param c Head of cells to divide.
 * \return A constant cell which contains int/double.
 */
Cell* eval_divide(Cell* const c)
{
  return eval_multi(c, true);
}

/**
 * \brief Evaluate ceiling cell.
 * \param c Head of cells to ceiling.
 * \return An int cell which contains int.
 */
Cell* eval_ceiling(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    cerr << "ERROR: Exactly one parameter is needed for ceiling.\n";
    exit(1);
  }
  return eval(car(c))->ceiling_c();
}

/**
 * \brief Evaluate floor cell.
 * \param c Head of cells to floor.
 * \return An int cell which contains int.
 */
Cell* eval_floor(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    cerr << "ERROR: Exactly one parameter is needed for floor.\n";
    exit(1);
  }
  return eval(car(c))->floor_c();
}

/**
 * \brief Evaluate condition.
 * \param c Head of condition cell.
 * \return False if condition cell is int/double 0, otherwise true.
 */
bool eval_condition(Cell* const c)
{
  Cell* condition = eval(car(c));
  return !( (intp(condition) && get_int(condition) == 0) || 
            (doublep(condition) && get_double(condition) == 0.0) );
}

/**
 * \brief Evaluate if cell.
 * \param c If cell.
 * \return A constant cell which contains int/double.
 */
Cell* eval_if(Cell* const c)
{
  if (nullp(c)) {
    cerr << "ERROR: Missing condition part for if statement.\n";
    exit(1);
  }
  Cell* tmp = cdr(c);
  if (nullp(tmp)) {
    cerr << "ERROR: Missing first part of if.\n";
    exit(1);
  }
  if (eval_condition(c)) {
    return eval(car(tmp));
  } else {
    if (nullp(cdr(tmp))) {
      return nil;
    } else {
      return eval(car(cdr(tmp)));
    }
  }
}

/**
 * \brief Evalute quote.
 * \param c Quote cell.
 * \return The car of c's cdr.
*/
Cell* eval_quote(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    cerr << "ERROR: Exactly one parameter is needed for quote.\n";
    exit(1);
  }
  return car(c);
}

/**
 * \brief Evaluate cell c.
 * \param c The evaluated cell.
 * \return A constant cell which contains int/double.
 */
Cell* eval(Cell* const c)
{
  Cell* cell;
  if (listp(c) && !nullp(c)) {
    string s = get_symbol(eval(car(c)));
    if (s == "+") {
      cell = eval_plus(cdr(c));
    } else if (s == "-") {
      cell = eval_minus(cdr(c));
    } else if (s == "*") {
      cell = eval_multi(cdr(c));
    } else if (s == "/") {
      cell = eval_divide(cdr(c));
    } else if (s == "ceiling") {
      cell = eval_ceiling(cdr(c));
    } else if (s == "floor") {
      cell = eval_floor(cdr(c));
    } else if (s == "if") {
      cell = eval_if(cdr(c));
    } else if (s == "quote") {
      cell = eval_quote(cdr(c));
    } else {
      cerr << "ERROR: key word '" << s << "' not supported yet.\n";
      exit(1);
    }
  } else {
    cell = c->clone();
  } 
  return cell;
}
