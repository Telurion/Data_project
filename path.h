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

int search_min_node(p_node);
p_node* tab_of_min(p_node, int *);
p_node min_leaf(t_tree); // finds the leaf containing minimum value for a tree
p_node min_leaf_node(p_node); // finds the leaf containing minimum value for a node
t_move* best_moves(t_tree);
int pathCost(p_node);

#endif //UNTITLED1_PATH_H
