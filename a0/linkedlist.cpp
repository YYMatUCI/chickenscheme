#include "linkedlist.hpp"

/**
 * \brief Return the size of linked list starting from Node n.
 * \param n The head of desired linked list.
 * \return The length of linked list.
 */
int list_size(const Node* n) {
    int i = 0;
    while (n != NULL) {
        n = get_next(n);
        i++;
    }
    return i;
}

/**
 * \brief Return the ith node's cell of linked list if exist.
 * \param n The head of linked list.
 * \param i The desired position.
 * \return The ith node if exist.
 */
Cell* list_ith(Node* n, unsigned int i) {
    Node* cur_n = n;
    int cnt = 0;
    while (cnt < i) {
        cur_n = get_next(cur_n);
        cnt++;
    }
    return get_elem(cur_n);
}

/**
 * \brief Erase target node if it exist. Assume the linked list does not contain loop. TODO: the node erase should be put in Node and Cell file.
 * \param n The head of linked list.
 * \param pos The target node.
 * \return The new head of linked list.
 */
Node* list_erase(Node* n, Node* pos) {
    Node* head = make_node(NULL, n);
    Node* cur = head;
    Node* nxt = n;
    // find pos in linked list
    while (nxt != NULL) {
        if (nxt == pos) {
            cur->next_m = get_next(nxt);
            Cell* c = get_elem(nxt);
            if (symbolp(c)) {
                free(c->symbol_m);
            }
            free(c);
            free(nxt);
            break;
        }
        cur = nxt;
        nxt = get_next(cur);
    }
    cur = get_next(head);
    free(head);
    return cur;
}

/**
 * \brief Insert new cell to the position and let the position to be the next.
 * \param n The head of linked list.
 * \param pos The desired position for insert. NULL pos means append to the end. If pos not found, it would not insert.
 * \param c The cell to insert.
 * \return The new head of linked list.
 */
Node* list_insert(Node* n, Node* pos, Cell* c) {
    Node* ins = make_node(c, pos);
    // Case insert at first
    if (n == pos) {
        ins->next_m = n->next_m;
        ins->elem_m = n->elem_m;
        n->next_m = ins;
        n->elem_m = c;
        return n;
    } else {
        while (n->next_m != pos && n->next_m != NULL) {
            n = n->next_m;
        }
        if (n->next_m == pos) {
            n->next_m = ins;
        }
    }
    return n;
}

/**
 * \brief Insert new int cell to the position and let the position to be the next.
 * \param n The head of linked list.
 * \param pos The desired position for insert. NULL pos means append to the end.
 * \param value The int to insert.
 * \return The new head of linked list.
 */
Node* list_insert_int(Node* n, Node* pos, const int value) {
    return list_insert(n, pos, make_int(value));
}

/**
 * \brief Insert new double cell to the position and let the position to be the next.
 * \param n The head of linked list.
 * \param pos The desired position for insert. NULL pos means append to the end.
 * \param value The double to insert.
 * \return The new head of linked list.
 */
Node* list_insert_double(Node* n, Node* pos, const double value) {
    return list_insert(n, pos, make_double(value));
}

/**
 * \brief Insert new symbol cell to the position and let the position to be the next.
 * \param n The head of linked list.
 * \param pos The desired position for insert. NULL pos means append to the end.
 * \param value The symbol to insert.
 * \return The new head of linked list.
 */
Node* list_insert_symbol(Node* n, Node* pos, const char* value) {
    return list_insert(n, pos, make_symbol(value));
}
