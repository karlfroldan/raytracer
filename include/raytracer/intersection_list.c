#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "intersection_list.h"
#include "raytracer_utils.h"

struct intersections new_intersections()
{
    struct intersections its = {
        0, NULL 
    };

    return its;
}

void 
its_insert(struct intersections* lst, intersection_node* n)
{
    intersection_node* new_node = 
        (intersection_node*) malloc(sizeof(intersection_node));
    
    memcpy(new_node, n, sizeof(intersection_node));

    if (lst->count == 0)
    {
        lst->head = new_node;
    }
    else 
    {
        intersection_node* temp = lst->head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new_node;        
    }
    lst->count += 1;
}

intersection_node* 
its_get(struct intersections* lst, int idx)
{
    if (idx >= lst->count)
        return NULL;

    intersection_node* temp = lst->head;
    int i = 0;

    while (i++ != idx)
        temp = temp->next;

    return temp;     
}

/* Create a new intersection object. */
intersection_node 
intersection(double t_value, void* obj, int obj_type)
{
    intersection_node n = {
        NULL, t_value, obj_type, obj
    };

    return n;
}

/* Add a new intersection object */
void 
add_intersection_obj(struct intersections* lst, intersection_node* n)
{
    
}

void 
free_intersection_list(struct intersections* lst)
{
    intersection_node* current = lst->head;
    intersection_node* free_this;

    for (int i = 0; i < lst->count; ++i)
    {
        free_this = current;
        current = current->next;
        free(free_this);
    }
}

/* Two intersections are the same if and only if 
    they have the same t_value, object pointer, and object type.
*/
int same_intersection(intersection_node* n1, intersection_node* n2)
{
    return n1->obj_pntr == n2->obj_pntr && approx_d(n1->t_value, n2->t_value)
        && n1->obj_type == n2->obj_type;
}