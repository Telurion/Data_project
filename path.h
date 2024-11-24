//
// Created by amine on 22/11/2024.
//

#ifndef UNTITLED1_PATH_H
#define UNTITLED1_PATH_H

#include "tree.h"
#include "moves.h"
#include "map.h"
#include "loc.h"
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
 * @brief Function to find the minimal node (0)
 * @param node
 * @return the minimum value
 */
int search_min_node(p_node);

/**
 * @brief Function to find the nodes that have the minimal value
 * @param node, length
 * @return array of moves array
 */
p_node* tab_of_min(p_node, int *);

/**
 * @brief Function to find the leaf containing minimum value for a node
 * @param node
 * @return the node
 */
p_node min_leaf_node(p_node);

/**
 * @brief Function to find the leaf containing minimum value for a tree
 * @param node
 * @return the node
 */
p_node min_leaf(t_tree);

/**
 * @brief Function to find the array of moves for the best path
 * @param node
 * @return the moves array
 */
t_move* best_moves(p_node);

/**
 * @brief Function to find the cost of the best path
 * @param node
 * @return the cost
 */
int pathCost(p_node);

/**
 * @brief Function to find if the robot is on a reg ground
 * @param node
 * @return True / False
 */
int soil_type_reg(p_node);

/**
 * @brief Function to find if the robot is on a erg ground
 * @param node
 * @return True / False
 */
int soil_type_erg(p_node);

/**
 * @brief Function to find if the robot is at the base
 * @param map, robot_localisation
 * @return True / False
 */
int win(t_map, t_localisation);

/**
 * @brief Function to find if the robot is out of  the map or on a crevasse
 * @param map, robot_localisation
 * @return True / False
 */
int lose(t_map, t_localisation);

/**
 * @brief Function to display the leaf with the minimal final cost
 * @param tree
 * @return none
 */
void display_min_leaf(t_tree);

#endif //UNTITLED1_PATH_H
