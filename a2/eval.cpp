/**
 * \file eval.cpp
 *
 * A dummy implementation for example purposes.  Just barely enough is
 * implemented to allow the parser to run.  Merely returns the input
 * expression without evaluating it.
 */

#include "eval.hpp"
#include <cmath>
#include <map>

/**
 * \brief Create a string-Cell* symbol map for `define` function
 */
map<string, Cell*> smap = {};

/**
 * \brief To reduce if-else for pre-defined function.
 */
typedef Cell* (*CellEvalFunction)(Cell *);

/**
 * \brief string-function map for pre-defined function.
 */
map<string, CellEvalFunction> cefmap;

/**
 * \brief A boolean record whether cefmap is initialized.
 */
bool cefmap_initialized = false;

/**
 * \brief Evaluate plus cell.
 * \param c Head of cells to plus.
 * \param is_minus True if would like to calculate minus.
 * \return A constant cell which contains int/double. 0 if no parameters given.
 */
Cell* eval_plusminus(Cell* const c, bool is_minus=false)
{
  if (is_minus && (nullp(c) || nullp(cdr(c)))) {
    throw runtime_error("ERROR: At least two parameters are needed for minus operator.");
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
 * \brief Evaluate plus cell.
 * \param c Head of cells to plus.
 * \return A constant cell which contains int/double.
 */
Cell* eval_plus(Cell* const c)
{
  return eval_plusminus(c, false);
}

/**
 * \brief Evaluate minus cell.
 * \param c Head of cells to minus.
 * \return A constant cell which contains int/double.
 */
Cell* eval_minus(Cell* const c)
{
  return eval_plusminus(c, true);
}

/**
 * \brief Evaluate multi cell. Early stopping when 0 founded.
 * \param c Head of cells to multi.
 * \param is_divide
 * \return A constant cell which contains int/double. 1 if no parameters given.
 */
Cell* eval_multidivide(Cell* const c, bool is_divide=false)
{
  if (is_divide && (nullp(c) || nullp(cdr(c)))) {
    throw runtime_error("ERROR: At least two parameters are needed for minus operator.");
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
      throw runtime_error("ERROR: The divisor cannot be zero.");
    }
    d = n / d;
  }
  return make_num(is_int, d);
}

/**
 * \brief Evaluate multi cell.
 * \param c Head of cells to multi.
 * \return A constant cell which contains int/double.
 */
Cell* eval_multi(Cell* const c)
{
  return eval_multidivide(c, false);
}

/**
 * \brief Evaluate divide cell.
 * \param c Head of cells to divide.
 * \return A constant cell which contains int/double.
 */
Cell* eval_divide(Cell* const c)
{
  return eval_multidivide(c, true);
}

/**
 * \brief Evaluate ceiling cell.
 * \param c Head of cells to ceiling.
 * \return An int cell which contains int.
 */
Cell* eval_ceiling(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    throw runtime_error("ERROR: Exactly one parameter is needed for ceiling.");
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
    throw runtime_error("ERROR: Exactly one parameter is needed for floor.");
  }
  return eval(car(c))->floor_c();
}

/**
 * \brief Evaluate less cell.
 * \param c Head of cells to less.
 * \return A constant cell which contains int/double. 0 if no parameters given.
 */
Cell* eval_less(Cell* const c)
{
  bool is_less = true;
  double d = 0;
  Cell* cur = c;
  if (!nullp(cur)) {
    eval(car(cur))->less_c(is_less, d);
    cur = cdr(cur);
    is_less = true;
  }
  while (!nullp(cur)) {
    eval(car(cur))->less_c(is_less, d);
    cur = cdr(cur);
    if (!is_less) {
      break;
    }
  }
  return is_less ? make_int(1) : make_int(0);
}

/**
 * \brief Evaluate not.
 * \param c Head of cells to not.
 * \return An int cell. 1 if conatins int/double 0, otherwise 1;
*/
Cell* eval_not(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    throw runtime_error("ERROR: Exactly one parameter is needed for not.");
  }
  return eval(car(c))->not_c() ? make_int(1) : make_int(0);
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
    throw runtime_error("ERROR: Missing condition part for if statement.");
  }
  Cell* tmp = cdr(c);
  if (nullp(tmp)) {
    throw runtime_error("ERROR: Missing first part of if.");
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
    throw runtime_error("ERROR: Exactly one parameter is needed for quote.");
  }
  return car(c);
}

/**
 * \brief Evalute cons.
 * \param c cons cell.
 * \return The new cell generated by cons.
*/
Cell* eval_cons(Cell* const c)
{
  if (nullp(c) || nullp(cdr(c)) || !nullp(cdr(cdr(c)))) {
    throw runtime_error("ERROR: Exactly two parameter is needed for cons.");
  }
  Cell* second = eval(car(cdr(c)));
  if (!listp(second)) {
    throw runtime_error("ERROR: Second parameter should be list after eval for cons.");
  }
  return cons(eval(car(c)), second);
}

/**
 * \brief Evalute car.
 * \param c car cell.
 * \return The car result.
*/
Cell* eval_car(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    throw runtime_error("ERROR: Exactly one parameter is needed for car.");
  }
  Cell* first = eval(car(c));
  if (!listp(first)) {
    throw runtime_error("ERROR: first parameter should be list after eval for car.");
  }
  return car(first);
}

/**
 * \brief Evalute cdr.
 * \param c cdr cell.
 * \return The car of c's cdr.
*/
Cell* eval_cdr(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    throw runtime_error("ERROR: Exactly one parameter is needed for cdr.");
  }
  Cell* first = eval(car(c));
  if (!listp(first)) {
    throw runtime_error("ERROR: first parameter should be list after eval for cdr.");
  }
  return cdr(first);
}

/**
 * \brief Evalute nullp.
 * \param c nullp cell.
 * \return The car of c's nullp.
*/
Cell* eval_nullp(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    throw runtime_error("ERROR: Exactly one parameter is needed for nullp.");
  }
  return nullp(eval(car(c))) ? make_int(1) : make_int(0);
}

/**
 * \brief Evaluate define.
 * \param c define cell.
 * \return nil if successed. Cannot override pre-defined symbols.
 */
Cell* eval_define(Cell* const c)
{
  if (nullp(c) || nullp(cdr(c)) || !nullp(cdr(cdr(c)))) {
    throw runtime_error("ERROR: Exactly two parameters are needed for define.");
  }
  if (!symbolp(car(c))) {
    throw runtime_error("ERROR: The first parameter for define should be a symbol.");
  }
  string s = get_symbol(car(c));
  map<string, CellEvalFunction>::iterator it = cefmap.find(s);
  if (it == cefmap.end()) {
    smap[s] = eval(car(cdr(c)))->clone();
  } else {
    throw runtime_error("Predefined symbol \"" + s + "\" cannot be redefined.");
  }
  return nil;
}

/**
 * \brief Evalute print.
 * \param c print cell.
 * \return nil.
*/
Cell* eval_print(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    throw runtime_error("ERROR: Exactly one parameter is needed for eval.");
  }
  eval(car(c))->print();
  cout << endl;
  return nil;
}

/**
 * \brief Evalute eval.
 * \param c eval cell.
 * \return Evaluated c.
*/
Cell* eval_eval(Cell* const c)
{
  if (nullp(c) || !nullp(cdr(c))) {
    throw runtime_error("ERROR: Exactly one parameter is needed for eval.");
  }
  return eval(eval(car(c)));
}

/**
 * \brief Evaluate symbol type.
 * \param c The symbol cell.
 * \return A cell that previous defined associated with the symbol.
 */
Cell* eval_symbol_cell(Cell* const c)
{
  string s = get_symbol(c);
  map<string, Cell*>::iterator it;
  it = smap.find(s);
  if (it != smap.end()) {
    return smap[s]->clone();
  } else {
    throw runtime_error("ERROR: attempt to reference an undefined symbol \"" + s + "\"");
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
  string s;
  map<string, CellEvalFunction>::iterator cefit;

  // always initiated on the first eval call
  if (!cefmap_initialized) {
    cefmap["+"] = &eval_plus;
    cefmap["-"] = &eval_minus;
    cefmap["*"] = &eval_multi;
    cefmap["/"] = &eval_divide;
    cefmap["ceiling"] = &eval_ceiling;
    cefmap["floor"] = &eval_floor;
    cefmap["<"] = &eval_less;
    cefmap["not"] = &eval_not;
    cefmap["if"] = &eval_if;
    cefmap["quote"] = &eval_quote;
    cefmap["cons"] = &eval_cons;
    cefmap["car"] = &eval_car;
    cefmap["cdr"] = &eval_cdr;
    cefmap["nullp"] = &eval_nullp;
    cefmap["define"] = &eval_define;
    cefmap["print"] = &eval_print;
    cefmap["eval"] = &eval_eval;
    cefmap_initialized = true;
  }
  
  try {
    if (listp(c) && !nullp(c)) {
      if (!symbolp(car(c))) {
        throw runtime_error("ERROR: The first element should be a symble when evaluating a list.");
      }
      s = get_symbol(car(c));
      cefit = cefmap.find(s);
      if (cefit != cefmap.end()) {
        cell = cefmap[s](cdr(c));
      } else {
        throw runtime_error("ERROR: key word '" + s + "' not supported yet.");
      }
    } else if (symbolp(c)) {
      cell = eval_symbol_cell(c);
    } else {
      cell = c->clone();
    } 
  } catch (runtime_error e) {
    cerr << e.what();
    cell = nil;
  }
  return cell;
}
