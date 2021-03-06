/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{

    /* Remember to handle the case if malloc returned NULL */
    queue_t *q = malloc(sizeof(queue_t));
    if(q){
        q->tail = NULL;
        q->head = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Remember to free the queue structue and list elements */
    if(q){
        list_ele_t *temp1,*temp2;
        temp1 = q->head;
        while(temp1!=q->tail){
            temp2 = temp1->next;
            free(temp1);
            temp1 = temp2;
        }
        if(q->tail){
            free(q->tail);
        }
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    /* What should you do if the q is NULL? */
    /* What if malloc returned NULL? */
    if(q){
        list_ele_t *p = malloc(sizeof(list_ele_t));
        if(p){
            if(q->size==0){
                q->tail = p;
            }
            p->next = q->head;
            p->value = v;
            q->size = q->size+1;
            q->head = p;
            return true;
        }
    }
    return false;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* Remember: It should operate in O(1) time */
    if(q){
        list_ele_t *p = malloc(sizeof(list_ele_t));
        if(p){
            if(q->size==0){
                q->head = p;
            }
            else{
                q->tail->next = p;
            }
            q->tail = p;
            p->value = v;
            p->next = NULL;
            q->size = q->size+1;
            return true;
        }
    }
        return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if(q==NULL||q->size==0||vp==NULL){
        return false;
    }
    list_ele_t *temp = q->head;
    *vp = temp->value;
    if(q->size == 1){
        free(temp);
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        return true;
    }
    q->head = temp->next;
    free(temp);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if(q){
        return q->size;
    }
    else{
        return 0;
    }
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if(q){
        int s = q->size;
        if(s>1){
            list_ele_t *temp1, *temp2,*temp3,*t;
            temp1 = q->head;
            temp2 = temp1->next;
            t = q->tail;
            int k;
            for(k=2;k<s;k++){
                temp3 = temp2->next;
                temp2->next = temp1;
                temp1 = temp2;
                temp2 = temp3;
            }
            temp2->next = temp1;
            q->head->next = NULL;
            q->tail = q->head;
            q->head = t;
        }
    }
}

