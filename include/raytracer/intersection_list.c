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
        lst->root = new_node;
    }
    else 
    {
        intersection_node* temp, *z;
        temp = lst->root;

        /* Ordering is on t_value. */
        while (temp != NULL)
        {
            z = temp;

            if (temp->t_value >= new_node->t_value)
                temp = temp->left;
            else 
                temp = temp->right;
        }

        /* z is now our parent node. */
        if (z->t_value >= new_node->t_value)
            z->left = new_node;
        else
            z->right = new_node;
        
        new_node->parent = z;   
    }

    lst->count += 1;
}

/* Get the smallest node. */
intersection_node* 
tree_minimum(intersection_node* n)
{
    while (n->left != NULL)
        n = n->left;
    return n;
}

/* Get the largest node. */
intersection_node* 
tree_maximum(intersection_node* n)
{
    while (n->right != NULL)
        n = n->right;
    return n;
}

intersection_node*
successor(intersection_node* n)
{
    if (n->right != NULL)
    {
        return tree_minimum(n->right);
    }

    intersection_node* parent = n->parent;

    while (parent != NULL && n == parent->right)
    {
        n = parent;
        parent = parent->parent;
    }
    return parent;
}

intersection_node*
predecessor(intersection_node* n)
{
    if (n->left != NULL)
    {
        return tree_maximum(n->left);
    }

    intersection_node* parent = n->parent;

    while (parent != NULL && n == parent->left)
    {
        n = parent;
        parent = parent->parent;
    }
    return parent;
}

intersection_node* 
its_get(struct intersections* lst, int idx)
{
    if (idx >= lst->count)
        return NULL;

    /* This is index 0. */
    intersection_node* temp = tree_minimum(lst->root);
    int i = 0;

    while (i++ != idx)
        temp = successor(temp);

    return temp;     
}

/* Create a new intersection object. */
intersection_node 
intersection(double t_value, void* obj, int obj_type)
{
    intersection_node n = {
        NULL, NULL, NULL, t_value, obj_type, obj
    };

    return n;
}


void free_node(intersection_node* n)
{
    if (n != NULL)
    {
            n->parent = NULL;

        intersection_node *right, *left;

        right = n->right;
        left = n->left;

        free(n);

        free_node(right);
        free_node(left);
    }
}

void 
free_intersection_list(struct intersections* lst)
{
    free_node(lst->root);
}

/* Two intersections are the same if and only if 
    they have the same t_value, object pointer, and object type.
*/
int same_intersection(intersection_node* n1, intersection_node* n2)
{
    return n1->obj_pntr == n2->obj_pntr && approx_d(n1->t_value, n2->t_value)
        && n1->obj_type == n2->obj_type;
}