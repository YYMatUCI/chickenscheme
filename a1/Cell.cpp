/**
 * \file Cell.cpp
 *
 * A partial dummy implementation of the Cell.hpp interface for
 * example purposes, to support the cons list ADT interface specified
 * in cons.hpp.  Just barely enough is implemented to allow the parser
 * to run.  None of the accessor member functions are implemented.
 *
 * You need to replace this with a real implementation that actually
 * builds a tree data structure and then lets the user access the tree.
 *
 * You don't necessarily need to understand the ugly details of this
 * dummy implementation, which you'll throw away anyhow.
 */

#include "Cell.hpp"
// Reminder: cons.hpp expects nil to be defined somewhere.  For this
// implementation, this is the logical place to define it.
Cell* const nil = NULL;

using namespace std;

Cell::Cell(const int i) 
{
  type_m = type_int;
  my_int = i;
}

Cell::Cell(const double d)
{
  type_m = type_double;
  my_double = d;
}

Cell::Cell(const char* s)
{
  type_m = type_symbol;
  my_symbol = new char[strlen(s) + 1];
  strcpy(my_symbol, s);
}

Cell::Cell(Cell* const my_car, Cell* const my_cdr)
{
  type_m = type_cons;
  my_cons.my_car = my_car;
  my_cons.my_cdr = my_cdr;
}

/**
 * \brief Check if this is an int cell.
 * \return True iff this is an int cell.
 */
bool Cell::is_int() const
{
  return type_m == type_int;
}

/**
 * \brief Check if this is a double cell.
 * \return True iff this is a double cell.
 */
bool Cell::is_double() const
{
  return type_m == type_double;
}

/**
 * \brief Check if this is a symbol cell.
 * \return True iff this is a symbol cell.
 */
bool Cell::is_symbol() const
{
  return type_m == type_symbol;
}

/**
 * \brief Check if this is a cons cell.
 * \return True iff this is a cons cell.
 */
bool Cell::is_cons() const
{
  return type_m == type_cons;
}

/**
 * \brief Accessor (error if this is not an int cell).
 * \return The value in this int cell.
 */
int Cell::get_int() const
{
  if (!Cell::is_int()){
  	cerr << "Error: The cell is not an int cell." << endl;
  	exit(1);
  }
  return my_int;
}

/**
 * \brief Accessor (error if this is not a double cell).
 * \return The value in this double cell.
 */
double Cell::get_double() const
{
  if (!Cell::is_double()){
  	cerr << "Error: The cell is not a double cell." << endl;
  	exit(1);
  }
  return my_double;
}

/**
 * \brief Accessor (error if this is not a symbol cell).
 * \return The value in this symbol cell.
 */
std::string Cell::get_symbol() const
{
  if (!Cell::is_symbol()){
  	cerr << "Error: The cell is not a symbol cell." << endl;
  	exit(1);
  }
  return my_symbol;
}

/**
 * \brief Accessor (error if this is not a cons cell).
 * \return The first child cell.
 */
Cell* Cell::get_car() const
{
  if (!Cell::is_cons()){
  	cerr << "Error: The cell is not a cons cell." << endl;
  	exit(1);
  }
  return my_cons.my_car;
}

/**
 * \brief Accessor (error if this is not a cons cell).
 * \return The second child cell.
 */
Cell* Cell::get_cdr() const
{
  if (!Cell::is_cons()){
  	cerr << "Error: The cell is not a cons cell." << endl;
  	exit(1);
  }
  return my_cons.my_cdr;
}

/**
 * \brief Print the subtree rooted at this cell, in s-expression notation.
 * \param os The output stream to print to.
 */
void Cell::print(ostream& os) const
{
  switch (type_m)
  {
    case type_int:
      os << my_int;
      break;
    case type_double:
      os << my_double;
      break;
    case type_symbol:
      os << my_symbol;
      break;
    case type_cons:
      bool need_bracket = false;
      if (my_cons.my_car != nil) {
        if (my_cons.my_car->is_symbol()) {
          need_bracket = true;
          os << "(";
        }
        my_cons.my_car->print(os);
      } else {
        // Assume car always non-empty
        cerr << "ERROR: empty car for cons Cell" << endl;
        exit(1);
      }
      if (my_cons.my_cdr != nil) {
        os << " ";
        my_cons.my_cdr->print(os);
      }
      if (need_bracket) {
        os << ")";
      }
  }
}
