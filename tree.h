//
// Created by Corentin Monsallier on 21/11/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "stack.h"
#include "map.h"
#include "moves.h"

/**
 * @brief Node structure
 */
typedef struct s_node
{
    int idx;
    int cost;
    int nb_sons;
    t_move move;
    t_soil soil_type;
    struct s_node **sons;
    struct s_node *parent;
} t_node;
typedef struct s_node t_node, *p_node;

/**
 * @brief Node structure
 */
typedef struct
{
    t_node *root;
} t_tree;

/**
 * @brief Function to get a random array of moves
 * @param none
 * @return the array
 */
t_move *getMovesArray();

/**
 * @brief Function to create a new node
 * @param index, cost, number_of_sons, applied_move, type_of_soil, parent
 * @return the node
 */
p_node createNode(int, int, int, t_move, t_soil, t_node *);

/**
 * @brief Function to create a new tree
 * @param index, number_of_possibilities, robot_localisation, used_map, applied_move, remaining_moves
 * @return the tree
 */
t_tree createTree(int, int, t_localisation, t_map, t_move, t_move *);

/**
 * @brief Function to add the nodes to the tree
 * @param index, number_of_possibilities, robot_localisation, used_map, applied_move, remaining_moves, parent
 * @return the nodes
 */
p_node addNodesToTree(int, int, t_localisation, t_map, t_move, t_move *, p_node);

/**
 * @brief Function to remove a certain move
 * @param index, size, remaining_moves
 * @return the remaining moves
 */
t_move *remove_current_move(int, int, t_move *);

#endif //UNTITLED1_TREE_H
