//
// Created by Corentin Monsallier on 21/11/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "stack.h"
#include "map.h"
#include "moves.h"

typedef struct s_node
{
    int idx;
    int cost;
    int nb_sons;
    t_move move;
    struct s_node **sons;           //pointeur tous ce qui suivent (sur le fils)
    struct s_node *parent;          //pointeur sur parent
} t_node;
typedef struct s_node t_node, *p_node;

typedef struct
{
    t_node *root;
} t_tree;

t_move *getMovesArray();
p_node createNode(int, int, int, t_move, t_node *);
t_tree createTree(int, int, t_localisation, t_map, t_move, t_move *);
p_node addNodesToTree(int, int, t_localisation, t_map, t_move, t_move *, p_node);
t_move *remove_current_move(int, int, t_move *);

#endif //UNTITLED1_TREE_H
