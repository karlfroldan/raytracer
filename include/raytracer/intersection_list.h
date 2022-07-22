#ifndef INTERSECTION_LIST_H
#define INTERSECTION_LIST_H

/* This file defines a singly-linked list of intersections */

typedef struct l_node
{
    struct l_node* next;
    double  data;

} l_node;

typedef struct intersections
{
    int count;
    l_node* head;
} intersections;

/* Create new intersection list. */
intersections new_intersections();

/* Insert new data into the linked list. */
void its_insert(intersections* lst, double data);

/* Get the intersection at index idx */
double its_get(intersections* lst, int idx);

#endif 