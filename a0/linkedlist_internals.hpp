/**
 * \file linkedlist_internals.hpp
 *
 * Encapsulates an abstract interface layer for a cons list ADT,
 * without using member functions. Makes no assumptions about what
 * kind of concrete type Cell will be defined to be.
 */

#ifndef LINKEDLIST_INTERNALS_HPP
#define LINKEDLIST_INTERNALS_HPP

#include "Node.hpp"
#include "Cell.hpp"
#include <string>
#include <iostream>

/**
 * \brief Make an int cell.
 * \param i The initial int value to be stored in the new cell.
 */
inline Cell* make_int(int i)
{
    Cell* cell = (Cell*) malloc(sizeof(Cell));
    cell->tag_m = type_int;
    cell->int_m = i;
    return cell;
}

/**
 * \brief Make a double cell.
 * \param d The initial double value to be stored in the new cell.
 */
inline Cell* make_double(double d)
{
    Cell* cell = (Cell*) malloc(sizeof(Cell));
    cell->tag_m = type_double;
    cell->double_m = d;
    return cell;
}

/**
 * \brief Make a symbol cell.
 * \param s The initial symbol name to be stored in the new cell.
 */
inline Cell* make_symbol(const char* s)
{
    Cell* cell = (Cell*) malloc(sizeof(Cell));
    cell->tag_m = type_symbol;
    cell->symbol_m = (char*) malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(cell->symbol_m, s);
    return cell;
}


/**
 * \brief Make a linked list node.
 * \param my_elem Pointer to the element to be held by this node.
 * \param my_next Pointer to the next node.
 */
inline Node* make_node(Cell* my_elem, Node* my_next)
{
    Node* node = (Node*) malloc(sizeof(Node));
    node->elem_m = my_elem;
    node->next_m = my_next;
    return node;
}

/**
 * \brief Check if d points to an int node.
 * \return True iff d points to an int node.
 */
inline bool intp(const Cell* c)
{
    return c->tag_m == type_int;
}

/**
 * \brief Check if d points to a double node.
 * \return True iff d points to a double node.
 */
inline bool doublep(const Cell* c)
{
    return c->tag_m == type_double;
}

/**
 * \brief Check if d points to a symbol node.
 * \return True iff d points to a symbol node.
 */
inline bool symbolp(const Cell* c)
{
    return c->tag_m == type_symbol;
}

/**
 * \brief Accessor (error if d is not an int node).
 * \return The value in the int node pointed to by c.
 */
inline int get_int(const Cell* c)
{
    if (!intp(c)) {
        std::cerr << "ERROR: get_int on non-int cell" << std::endl;
        exit(1);
    }
    return c->int_m;
}

/**
 * \brief Accessor (error if d is not a double node).
 * \return The value in the double node pointed to by c.
 */
inline double get_double(const Cell* c)
{
    if (!doublep(c)) {
        std::cerr << "ERROR: get_double on non-double cell" << std::endl;
        exit(1);
    }
    return c->double_m;
}

/**
 * \brief Retrieve the symbol name as a string (error if d is not a
 * symbol node).
 * \return The symbol name in the symbol node pointed to by c.
 */
inline char* get_symbol(const Cell* c)
{
    if (!symbolp(c)) {
        std::cerr << "ERROR: get_symbol on non-symbol cell" << std::endl;
        exit(1);
    }
    return c->symbol_m;
}

/**
 * \brief Accessor.
 * \return The elem pointer in the linked list node pointed to by c.
 */
inline Cell* get_elem(const Node* n)
{
    if (n == NULL) {
        std::cerr << "ERROR: null pointer" << std::endl;
        exit(1);
    }
    return n->elem_m;
}

/**
 * \brief Accessor.
 * \return The next pointer in the linked list node pointed to by c.
 */
inline Node* get_next(const Node* n)
{
    if (n == NULL) {
        std::cerr << "ERROR: null pointer" << std::endl;
        exit(1);
    }
    return n->next_m;
}

/**
 * \brief Print the cell n in parentheses.
 * \param os The output stream to print to.
 * \param c The cell to be printed.
 */
inline std::ostream& operator<<(std::ostream& os, Cell* c)
{
    switch (c->tag_m) {
        case type_int:
            os << get_int(c);
            break;
        case type_double:
            os << get_double(c);
            break;
        case type_symbol:
            os << get_symbol(c);
            break;
        default:
            std::cerr << "ERROR: Unknown type" <<std::endl;
            exit(1);
    }
    return os;
}

/**
 * \brief Print the linked list rooted at n in parentheses.
 * \param os The output stream to print to.
 * \param n The root node of the linked list to be printed.
 */
inline std::ostream& operator<<(std::ostream& os, const Node& n)
{
    const Node* node = &n;
    os << '(';
    while (true){
        os << node->elem_m;
        node = get_next(node);
        if (node == NULL){
            os << ')';
            break;
        }
        os << ' ';
    }
    return os;
}

#endif // LINKEDLIST_INTERNALS_HPP
