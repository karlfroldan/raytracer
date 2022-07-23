#ifndef INTERSECTION_LIST_H
#define INTERSECTION_LIST_H

#include "types.h"

#define OBJECT_SPHERE 0

/* TODO: Use a binary search tree later. */

/* This file defines a singly-linked list of intersections */

/**
 * The l_node aggregates the following things:
 * 
 * 1. the `t_value` of the intersection
 * 2. The object that was intersected.
 */
typedef struct intersection_node
{
    struct intersection_node* parent; /* Parent pointer of the binary search tree */
    struct intersection_node* left;   /* Left pointer of the tree */
    struct intersection_node* right;  /* Right pointer. */
    double t_value;       /* T-value of the intersection. */
    int    obj_type;      /* What kind of object does this
                             intersection belong to? */
    void*  obj_pntr;      /* Poiter to the object. */

} intersection_node;

struct intersections
{
    int count;
    intersection_node* root;
};

/* Create new intersection tree. */
struct intersections new_intersections();

/* Insert new data into the linked list. */
void its_insert(struct intersections* lst, intersection_node* n);

/* Get the node pointer at the intersection */
intersection_node* its_get(struct intersections* lst, int idx);

/* Create a new intersection object. */
intersection_node intersection(double t_value, void* obj, int obj_type);

/* Two intersections are the same if and only if 
    they have the same t_value, object pointer, and object type.
*/
int same_intersection(intersection_node* n1, intersection_node* n2);

void free_intersection_list(struct intersections* lst);

/* Get the smallest node. */
intersection_node* 
tree_minimum(intersection_node* n);

/* Get the largest node. */
intersection_node* 
tree_maximum(intersection_node* n);

intersection_node*
successor(intersection_node* n);

intersection_node*
predecessor(intersection_node* n);

#endif 