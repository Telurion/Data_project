//
// Created by Corentin Monsallier on 21/11/2024.
//

#include "tree.h"
#include "moves.h"
#include "map.h"
#include "loc.h"
#include <stdlib.h>
#include <stdio.h>

#define NB_MOVES 5
#define NUM_MOVEMENTS 7
#define PHASES 9

t_move *getMovesArray() {                                                                                               /// WORKS
    int prob[NUM_MOVEMENTS] = {22, 37, 44, 51, 72, 93, 100};
    t_move *moves;
    moves = (t_move*)malloc(PHASES * sizeof(t_move));
    if (!moves) {
        return NULL;
    }

    for (int i=0; i < PHASES; i++) {
        int val = rand() % prob[6] + 1;
        int temp=-1;

        if (val <= prob[0]) {
            moves[i] = F_10;
            temp = 0;
        } else if (val <= prob[1]) {
            moves[i] = F_20;
            temp = 1;
        } else if (val <= prob[2]) {
            moves[i] = F_30;
            temp = 2;
        } else if (val <= prob[3]) {
            moves[i] = B_10;
            temp = 3;
        } else if (val <= prob[4]) {
            moves[i] = T_LEFT;
            temp = 4;
        } else if (val <= prob[5]) {
            moves[i] = T_RIGHT;
            temp = 5;
        } else if (val <= prob[6]) {
            moves[i] = U_TURN;
            temp = 6;
        } else {
            free(moves);
            return NULL;
        }

        if (temp > 0) {
            for (int j = temp; j < NUM_MOVEMENTS; j++) {
                prob[j]--;
            }
        }
    }
    return moves;
}

p_node createNode(int idx, int cost, int nb_sons, t_move move, t_soil soil, t_node *parent) {                           /// WORKS
    p_node my_node = (p_node)malloc(sizeof(t_node));
    my_node->idx = idx;
    my_node->cost = cost;
    my_node->nb_sons = nb_sons;
    my_node->move = move;
    my_node->soil_type = soil;
    my_node->sons = (p_node *)malloc(nb_sons * sizeof(p_node));
    my_node->parent = parent;
    for (int i = 0; i < nb_sons; i++) {
        my_node->sons[i] = NULL;
    }
    return my_node;
}

t_tree createTree(int idx, int nb_possibilities, t_localisation robot, t_map map, t_move present_move, t_move *possible_moves) {
    t_tree t;
    t.root = addNodesToTree(idx, nb_possibilities, robot, map, present_move, possible_moves, NULL);
    return t;
}

p_node addNodesToTree(int idx, int nb_possibilities, t_localisation robot, t_map map, t_move present_move, t_move *possible_moves, p_node parent_node) {
    if (map.costs[robot.pos.y][robot.pos.x] >= 10000 || map.costs[robot.pos.y][robot.pos.x] == 0) {
        nb_possibilities = 0;
    }
    if (idx == NB_MOVES) {
        nb_possibilities = 0;
    }
    p_node my_node = createNode(idx, map.costs[robot.pos.x][robot.pos.y], nb_possibilities, present_move, map.soils[robot.pos.y][robot.pos.x], parent_node);
    for (int i = 0; i < nb_possibilities; i++) {
        t_localisation new_robot_loc = robot;
        updateLocalisation(&new_robot_loc, possible_moves[i]);
        if (isValidLocalisation(new_robot_loc.pos, map.x_max, map.y_max)) {
            t_move *new_possible_moves = remove_current_move(nb_possibilities, i, possible_moves);
            my_node->sons[i] = addNodesToTree(idx++, nb_possibilities--, new_robot_loc, map, possible_moves[i], new_possible_moves, my_node);
        }
        else {
            my_node->sons[i] = 0;
        }
    }
    return my_node;
}

t_move *remove_current_move(int size, int index, t_move *possible_moves) {                                              /// WORKS
    t_move *new_possible_moves = (t_move *) malloc((size - 1) * sizeof(t_move));
    int found = 0;
    for (int i = 0; i < size-1; ++i) {
        if (index == i) {
            found = 1;
        }
        new_possible_moves[i] = possible_moves[i + found];
    }
    return new_possible_moves;
}