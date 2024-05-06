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
Cell* const nil = new NilCell();

using namespace std;

/**
 * \brief Distructor
 */
Cell::~Cell() {};

/**
 * \brief Make a copy of this cell.
 * \return A new cell copy of this cell.
 */
Cell* Cell::clone() const
{
  throw runtime_error("ERROR: Clone not implemented for some type.\n");
}

/**
 * \brief Check if this is an int cell.
 * \return True iff this is an int cell.
 */
bool Cell::is_int() const
{
  return false;
}

/**
 * \brief Check if this is a double cell.
 * \return True iff this is a double cell.
 */
bool Cell::is_double() const
{
  return false;
}

/**
 * \brief Check if this is a symbol cell.
 * \return True iff this is a symbol cell.
 */
bool Cell::is_symbol() const
{
  return false;
}

/**
 * \brief Check if this is a cons cell.
 * \return True iff this is a cons cell.
 */
bool Cell::is_cons() const
{
  return false;
}

/**
 * \brief Check if this is a nil cell.
 * \return True iff this is a nil cell.
 */
bool Cell::is_nil() const
{
  return false;
}

/**
 * \brief Accessor (error if this is not an int cell).
 * \return The value in this int cell.
 */
int Cell::get_int() const
{
  throw runtime_error("ERROR: Get int for non-int cell.\n");
}

/**
 * \brief Accessor (error if this is not a double cell).
 * \return The value in this double cell.
 */
double Cell::get_double() const
{
  throw runtime_error("ERROR: Get double for non-double cell.\n");
}

/**
 * \brief Accessor (error if this is not a symbol cell).
 * \return The symbol name in this symbol cell.
 */
std::string Cell::get_symbol() const
{
  throw runtime_error("ERROR: Get symbol for non-symbol cell.\n");
}

/**
 * \brief Accessor (error if this is not a cons cell).
 * \return First child cell.
 */
Cell* Cell::get_car() const
{
  throw runtime_error("ERROR: Get car for non-cons cell.\n");
}

/**
 * \brief Accessor (error if this is not a cons cell).
 * \return Rest child cell.
 */
Cell* Cell::get_cdr() const
{
  throw runtime_error("ERROR: Get cdr for non-cons cell.\n");
}

/**
 * \brief Print the subtree rooted at this cell, in s-expression notation.
 * \param os The output stream to print to.
 */
void Cell::print(std::ostream& os) const {};

/**
 * \brief The plus cell function.
 * \param is_int Record the output type.
 * \param n The number to be added.
 */
void Cell::plus_c(bool& is_int, double& n) const
{
  throw runtime_error("ERROR: Plus on non-int or non-double cell.\n");
}

/**
 * \brief The multiply cell function.
 * \param is_int Record the output type.
 * \param n The number to be added.
 */
void Cell::multi_c(bool& is_int, double& n) const
{
  throw runtime_error("ERROR: Multi on non-int or non-double cell.\n");
}

/**
 * \brief The ceiling cell function.
 * \return The ceilinged number.
 */
Cell* Cell::ceiling_c() const
{
  throw runtime_error("ERROR: Ceiling on non-int or non-double cell.\n");
}

/**
 * \brief The floor cell function.
 * \return The floored number.
 */
Cell* Cell::floor_c() const
{
  throw runtime_error("ERROR: Floor on non-int or non-double cell.\n");
}

/**
 * \brief The less cell function.
 * \param b Record whether the passed in value is smaller.
 * \panam d Pass into  a value.
 */
void Cell::less_c(bool& b, double& n) const
{
  throw runtime_error("ERROR: Compare on non-int or non-double cell.\n");
}

/**
 * \brief The not cell function.
 * \return 1 if contains 0 or 0.0.
 */
int Cell::not_c() const
{
  return false;
}



//// IntCell

/**
 * \brief Build IntCell
 */
IntCell::IntCell(int n)
{
    i = n;
}

/**
 * \brief Make a copy of this cell.
 * \return A new cell copy of this cell.
 */
IntCell* IntCell::clone() const
{
  return new IntCell(i);
}

/**
 * \brief Check if this is an int cell.
 * \return True iff this is an int cell.
 */
bool IntCell::is_int() const 
{ 
  return true;
}

/**
 * \brief Accessor (error if this is not an int cell).
 * \return The value in this int cell.
 */
int IntCell::get_int() const
{
  return i;
}

/**
 * \brief Print the subtree rooted at this cell, in s-expression notation.
 * \param os The output stream to print to.
 */
void IntCell::print(std::ostream& os) const
{
  os << i;
}

/**
 * \brief The plus cell function.
 * \param is_int Record the output type.
 * \param n The number to be added.
 */
void IntCell::plus_c(bool& is_int, double& n) const
{
  n += i;
}

/**
 * \brief The multiply cell function.
 * \param is_int Record the output type.
 * \param n The number to be added.
 */
void IntCell::multi_c(bool& is_int, double& n) const
{
  n *= i;
}

/**
 * \brief The ceiling cell function.
 * \return The ceilinged number.
 */
Cell* IntCell::ceiling_c() const
{
  return new IntCell(i);
}

/**
 * \brief The floor cell function.
 * \return The floored number.
 */
Cell* IntCell::floor_c() const
{
  return new IntCell(i);
}

/**
 * \brief The less cell function.
 * \param b Record whether the passed in value is smaller.
 * \panam d Pass into  a value.
 */
void IntCell::less_c(bool& b, double& n) const
{
  b = b || n < i;
  n = i;
}

/**
 * \brief The not cell function.
 * \return 1 if contains 0.
 */
int IntCell::not_c() const
{
  return i == 0;
}



/// Double cell

/**
 * \brief Build DoubleCell
 */
DoubleCell::DoubleCell(double n)
{
    d = n;
}

/**
 * \brief Make a copy of this cell.
 * \return A new cell copy of this cell.
 */
DoubleCell* DoubleCell::clone() const
{
  return new DoubleCell(d);
}

/**
 * \brief Check if this is a double cell.
 * \return True iff this is a double cell.
 */
bool DoubleCell::is_double() const
{
  return true;
}

/**
 * \brief Accessor (error if this is not a double cell).
 * \return The value in this double cell.
 */
double DoubleCell::get_double() const
{
  return d;
}

/**
 * \brief Print the subtree rooted at this cell, in s-expression notation.
 * \param os The output stream to print to.
 */
void DoubleCell::print(std::ostream& os) const
{
  os << d;
}

/**
 * \brief The plus cell function.
 * \param is_int Record the output type.
 * \param n The number to be added.
 */
void DoubleCell::plus_c(bool& is_int, double& n) const
{
  is_int = false;
  n += d;
}

/**
 * \brief The multiply cell function.
 * \param is_int Record the output type.
 * \param n The number to be added.
 */
void DoubleCell::multi_c(bool& is_int, double& n) const
{
  is_int = false;
  n *= d;
}

/**
 * \brief The ceiling cell function.
 * \return The ceilinged number.
 */
Cell* DoubleCell::ceiling_c() const
{
  return new IntCell((int)ceil(d));
}

/**
 * \brief The floor cell function.
 * \return The floored number.
 */
Cell* DoubleCell::floor_c() const
{
  return new IntCell((int)floor(d));
}

/**
 * \brief The less cell function.
 * \param b Record whether the passed in value is smaller.
 * \param n Pass into a value.
 */
void DoubleCell::less_c(bool& b, double& n) const
{
  b = b || n < d;
  n = d;
}

/**
 * \brief The not cell function.
 * \return 1 if contains 0.0.
 */
int DoubleCell::not_c() const
{
  return d == 0;
}



/// SymbolCell

/**
 * \brief Build SymbolCell
 */
SymbolCell::SymbolCell(const char* const s)
{
  c = new char[strlen(s) + 1];
  strcpy(c, s);
}

/**
 * \brief Distructor
 */
SymbolCell::~SymbolCell()
{
    delete[] c;
}

/**
 * \brief Make a copy of this cell.
 * \return A new cell copy of this cell.
 */
SymbolCell* SymbolCell::clone() const
{
  return new SymbolCell(c);
}

/**
 * \brief Check if this is a symbol cell.
 * \return True iff this is a symbol cell.
 */
bool SymbolCell::is_symbol() const
{
  return true;
}

/**
 * \brief Accessor (error if this is not a symbol cell).
 * \return The value in this symbol cell.
 */
std::string SymbolCell::get_symbol() const
{
  return c;
}

/**
 * \brief Print the subtree rooted at this cell, in s-expression notation.
 * \param os The output stream to print to.
 */
void SymbolCell::print(std::ostream& os) const
{
  os << c;
}



/// ConsCell

/**
 * \brief Build SymbolCell
 */
ConsCell::ConsCell(Cell* const my_car, Cell* const my_cdr)
{
  car = my_car;
  cdr = my_cdr;
}

/**
 * \brief Make a copy of this cell.
 * \return A new cell copy of this cell.
 */
ConsCell* ConsCell::clone() const
{
  return new ConsCell(this->car->clone(), this->cdr->clone());
}

/**
 * \brief Check if this is a cons cell.
 * \return True iff this is a cons cell.
 */
bool ConsCell::is_cons() const
{
  return true;
}

/**
 * \brief Accessor (error if this is not a cons cell).
 * \return First child cell.
 */
Cell* ConsCell::get_car() const
{
  return car;
}

/**
 * \brief Accessor (error if this is not a cons cell).
 * \return Rest child cell.
 */
Cell* ConsCell::get_cdr() const
{
  return cdr;
}

/**
 * \brief Print the subtree rooted at this cell, in s-expression notation.
 * \param os The output stream to print to.
 */
void ConsCell::print(std::ostream& os) const
{
  os << "(";
  const Cell* cur = this;
  while (cur != nil) {
    cur->get_car()->print();
    os << " ";
    cur = cur->get_cdr();
  }
  os << ")";
}



/// NilCell


/**
 * \brief Build ConsCell
 */
NilCell::NilCell() {}

/**
 * \brief Make a copy of this cell.
 * \return A new cell copy of this cell.
 */
NilCell* NilCell::clone() const
{
  return new NilCell();
}

/**
 * \brief Check if this is a nil cell.
 * \return True iff this is a nil cell.
 */
bool NilCell::is_nil() const
{
  return true;
}

/**
 * \brief Print "()".
 */
void NilCell::print(std::ostream& os) const
{
  os << "()";
}