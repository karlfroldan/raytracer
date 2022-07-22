#include <stdlib.h>
#include <stdio.h>

#include "intersection_list.h"

intersections new_intersections()
{
    intersections its = {
        0, NULL 
    };

    return its;
}

void its_insert(intersections* lst, double data)
{
    l_node* new_node = (l_node*) malloc(sizeof(l_node));
    new_node->data = data;
    new_node->next = NULL;

    if (lst->count == 0)
    {
        lst->head = new_node;
    }
    else 
    {
        l_node* temp = lst->head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new_node;        
    }
    lst->count += 1;
}

double its_get(intersections* lst, int idx)
{
    l_node* temp = lst->head;
    int i = 0;

    while (i++ != idx)
        temp = temp->next;

    return temp->data;    
}