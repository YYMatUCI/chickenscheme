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
 * \return A constant cell which contains int/double. 0 if no parameters given.
 */
Cell* eval_plus(Cell* const c)
{
  double d = 0;
  bool is_int = true;
  Cell* cur = c;
  Cell* tmp;
  while (!nullp(cur)) {
    tmp = eval(car(cur));
    if (intp(tmp)) {
      d += get_int((tmp));
    } else if (doublep(tmp)) {
      d += get_double(tmp);
      is_int = false;
    } else {
      cerr << "ERROR: Only int and double cell can be added\n";
      exit(1);
    }
    cur = cdr(cur);
  }
  if (is_int) {
    return new Cell((int) d);
  } else {
    return new Cell(d);
  }
}

/**
 * \brief Evaluate ceiling cell.
 * \param c Head of cells to ceiling.
 * \return A constant cell which contains int/double.
 */
Cell* eval_ceiling(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    cerr << "ERROR: Exactly one parameter is needed for ceiling.\n";
    exit(1);
  }
  Cell* tmp = eval(car(c));
  if (intp(tmp)) {
    return tmp;
  } else {
    return new Cell((int)ceil(get_double(tmp)));
  }
}

/**
 * \brief Evaluate condition.
 * \param c Head of condition cell.
 * \return False if condition cell is int/double 0, otherwise true.
 */
bool eval_condition(Cell* const c)
{
  Cell* condition = eval(car(c));
  return !(intp(condition) && get_int(condition) == 0 || 
           doublep(condition) && get_double(condition) == 0.0);
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
    } else if (s == "ceiling") {
      cell = eval_ceiling(cdr(c));
    }  else if (s == "if") {
      cell = eval_if(cdr(c));
    } else {
      cerr << "ERROR: key word '" << s << "' not supported yet.\n";
      exit(1);
    }
  } else {
    cell = new Cell(c);
  } 
  return cell;
}
