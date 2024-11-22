//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_QUEUE_H
#define UNTITLED1_QUEUE_H
#include "loc.h"
#include "tree.h"
/**
 * @brief Structure for the queue of integers
 */
typedef struct s_queue
{
    t_position *values;
    int size;
    int last;
    int first;
} t_queue;

/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */
t_queue createQueue(int);

/**
 * @brief Function to enqueue a value in the queue
 * @param p_queue : pointer to the queue
 * @param value : the position to enqueue
 * @return none
 */
void enqueue(t_queue *,t_position);

/**
 * @brief Function to dequeue a value from the queue
 * @param p_queue : pointer to the queue
 * @return the value dequeued
 */
t_position dequeue(t_queue *);


//BY AMINE//
typedef struct {
    int size;      // Maximum size of the queue
    int first;     // Index of the first element
    int last;      // Index of the next available slot
    p_node *values; // Array of pointers to tree nodes (p_node)
} t_queue_tab;

void enqueue_node(t_queue_tab *, p_node);
p_node dequeue_node(t_queue_tab *);
t_queue_tab createQueue2(int);

#endif //UNTITLED1_QUEUE_H
