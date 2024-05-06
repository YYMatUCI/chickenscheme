/**
 * \mainpage COMP2012H Programming Assignment 2, Fall 2014
 *
 * \author **Put your name here**
 * \author **Your studentID**
 * \author **Your email**
 * \author **Your lab session**
 *
 * \date **Fill in the date**
 *
 * Instructor: <a href="http://www.cs.ust.hk/~dekai/">Dekai Wu</a>
 * Due: 2014.10.10 at 23:00 by CASS
 */

/**
 * \file Cell.hpp
 *
 * Encapsulates the abstract interface for a concrete class-based
 * implementation of cells for a cons list data structure.
 */

#ifndef CELL_HPP
#define CELL_HPP

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <math.h>


/**
 * \class Cell.
 * \brief Cell class which contains parsed data for multiple data types.
 */
class Cell {

public:

  /**
   * \brief Make a copy of this cell.
   * \return A new cell copy of this cell.
   */
  virtual Cell* clone() const;

  /**
   * \brief Check if this is an int cell.
   * \return True iff this is an int cell.
   */
  virtual bool is_int() const;

  /**
   * \brief Check if this is a double cell.
   * \return True iff this is a double cell.
   */
  virtual bool is_double() const;

  /**
   * \brief Check if this is a symbol cell.
   * \return True iff this is a symbol cell.
   */
  virtual bool is_symbol() const;

  /**
   * \brief Check if this is a cons cell.
   * \return True iff this is a cons cell.
   */
  virtual bool is_cons() const;

  /**
   * \brief Check if this is a nil cell.
   * \return True iff this is a nil cell.
   */
  virtual bool is_nil() const;

  /**
   * \brief Accessor (error if this is not an int cell).
   * \return The value in this int cell.
   */
  virtual int get_int() const;

  /**
   * \brief Accessor (error if this is not a double cell).
   * \return The value in this double cell.
   */
  virtual double get_double() const;

  /**
   * \brief Accessor (error if this is not a symbol cell).
   * \return The symbol name in this symbol cell.
   */
  virtual std::string get_symbol() const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return First child cell.
   */
  virtual Cell* get_car() const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return Rest child cell.
   */
  virtual Cell* get_cdr() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const;

  /**
   * \brief The plus cell function.
   * \param is_int Record the output type.
   * \param n The number be added.
   */
  virtual void plus_c(bool& is_int, double& n) const;

  /**
   * \brief The multiply cell function.
   * \param is_int Record the output type.
   * \param n The number be added.
   */
  virtual void multi_c(bool& is_int, double& n) const;

  /**
   * \brief The ceiling cell function.
   * \return The ceilinged number.
   */
  virtual Cell* ceiling_c() const;

  /**
   * \brief The floor cell function.
   * \return The floored number.
   */
  virtual Cell* floor_c() const;

  /**
   * \brief The less cell function.
   * \param b Record whether the passed in value is smaller.
   * \param n Pass in a value.
   */
  virtual void less_c(bool& b, double& n) const;

  /**
   * \brief The not cell function.
   * \return 1 if contains 0 or 0.0.
   */
  virtual int not_c() const;
};


/**
 * \class Int cell.
 * \brief A cell contains int.
 */
class IntCell: public Cell
{
private:

  /**
   * \brief The content.
   */
  int i;

public:

  /**
   * \brief Build IntCell
   */
  IntCell(int n);

  /**
   * \brief Make a copy of this cell.
   * \return A new cell copy of this cell.
   */
  IntCell* clone() const;

  /**
   * \brief Check if this is an int cell.
   * \return True iff this is an int cell.
   */
  bool is_int() const;

  /**
   * \brief Accessor (error if this is not an int cell).
   * \return The value in this int cell.
   */
  int get_int() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  void print(std::ostream& os = std::cout) const;

  /**
   * \brief The plus cell function.
   * \param is_int Record the output type.
   * \param n The number be added.
   */
  void plus_c(bool& is_int, double& n) const;

  /**
   * \brief The multiply cell function.
   * \param is_int Record the output type.
   * \param n The number be added.
   */
  void multi_c(bool& is_int, double& n) const;

  /**
   * \brief The ceiling cell function.
   * \return The ceilinged number.
   */
  Cell* ceiling_c() const;

  /**
   * \brief The floor cell function.
   * \return The floored number.
   */
  Cell* floor_c() const;

  /**
   * \brief The less cell function.
   * \param b Record whether the passed in value is smaller.
   * \param n Pass in a value.
   */
  void less_c(bool& b, double& n) const;

  /**
   * \brief The not cell function.
   * \return 1 if contains 0.
   */
  int not_c() const;

  /**
   * \brief The eval cell function.
   * \return The evaluated Cell pointer.
   */
  //    Cell* eval_c() const;

};


/**
 * \class Double cell.
 * \brief A cell contains double.
 */
class DoubleCell: public Cell
{
private:

  /**
   * \brief The content.
   */
  double d;

public:

  /**
   * \brief Build DoubleCell
   */
  DoubleCell(double n);

  /**
   * \brief Make a copy of this cell.
   * \return A new cell copy of this cell.
   */
  DoubleCell* clone() const;

  /**
   * \brief Check if this is a double cell.
   * \return True iff this is a double cell.
   */
  bool is_double() const;

  /**
   * \brief Accessor (error if this is not a double cell).
   * \return The value in this double cell.
   */
  double get_double() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  void print(std::ostream& os = std::cout) const;

  /**
   * \brief The plus cell function.
   * \param is_int Record the output type.
   * \param n The number be added.
   */
  void plus_c(bool& is_int, double& n) const;

  /**
   * \brief The multiply cell function.
   * \param is_int Record the output type.
   * \param n The number be added.
   */
  void multi_c(bool& is_int, double& n) const;

  /**
   * \brief The ceiling cell function.
   * \return The ceilinged number.
   */
  Cell* ceiling_c() const;

  /**
   * \brief The floor cell function.
   * \return The floored number.
   */
  Cell* floor_c() const;

  /**
   * \brief The less cell function.
   * \param b Record whether the passed in value is smaller.
   * \param n Pass in a value.
   */
  void less_c(bool& b, double& n) const;

  /**
   * \brief The not cell function.
   * \return 1 if contains 0.0.
   */
  int not_c() const;

  /**
   * \brief The eval cell function.
   * \return The evaluated Cell pointer.
   */
  //    Cell* eval_c() const;

};



class SymbolCell: public Cell
{
private:

  /**
   * \brief The content.
   */
  char* c;

public:

  /**
   * \brief Build SymbolCell
   */
 SymbolCell(const char* const s);

  /**
   * \brief Make a copy of this cell.
   * \return A new cell copy of this cell.
   */
  SymbolCell* clone() const;

  /**
   * \brief Check if this is a symbol cell.
   * \return True iff this is a symbol cell.
   */
  bool is_symbol() const;

  /**
   * \brief Accessor (error if this is not a symbol cell).
   * \return The value in this symbol cell.
   */
  std::string get_symbol() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  void print(std::ostream& os = std::cout) const;

  /**
   * \brief The eval cell function.
   * \return The evaluated Cell pointer.
   */
  //    Cell* eval_c() const;

};



class ConsCell: public Cell
{
private:

  /**
   * \brief The content.
   */
  Cell* car;

  Cell* cdr;

public:

  /**
   * \brief Build ConsCell
   */
  ConsCell(Cell* const my_car, Cell* const my_cdr);

  /**
   * \brief Make a copy of this cell.
   * \return A new cell copy of this cell.
   */
  ConsCell* clone() const;

  /**
   * \brief Check if this is a cons cell.
   * \return True iff this is a cons cell.
   */
  bool is_cons() const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return First child cell.
   */
  Cell* get_car() const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return Rest child cell.
   */
  Cell* get_cdr() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  void print(std::ostream& os = std::cout) const;

  /**
   * \brief The eval cell function.
   * \return The evaluated Cell pointer.
   */
  //    Cell* eval_c() const;
};


/**
 * \brief Nil cell, to handle nil.
 */
class NilCell: public Cell
{
public:

  /**
   * \brief Build ConsCell
   */
  NilCell();

  /**
   * \brief Make a copy of this cell.
   * \return A new cell copy of this cell.
   */
  NilCell* clone() const;

  /**
   * \brief Check if this is a nil cell.
   * \return True iff this is a nil cell.
   */
  bool is_nil() const;

  /**
   * \brief Print "()".
   */
  void print(std::ostream& os = std::cout) const;

};


extern Cell* const nil;

#endif // CELL_HPP