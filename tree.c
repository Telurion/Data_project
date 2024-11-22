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

t_move *getMovesArray() {
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

p_node createNode(int idx, int cost, int nb_sons, t_move move, t_node *parent) {
    p_node my_node = (p_node)malloc(sizeof(t_node));
    my_node->idx = idx;
    my_node->cost = cost;
    my_node->nb_sons = nb_sons;
    my_node->move = move;
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
    p_node my_node = createNode(idx, map.costs[robot.pos.x][robot.pos.y], nb_possibilities, present_move, parent_node);
    if (map.costs[robot.pos.x][robot.pos.y] >= 1000 || map.costs[robot.pos.x][robot.pos.y] == 0) {
        nb_possibilities = 0;
    }
    if (idx == NB_MOVES) {
        nb_possibilities = 0;
    }
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

t_move *remove_current_move(int size, int index, t_move *possible_moves) {
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


















// trouver la minLeaf (si hors limite, pas pris en compte) //DONE//
// trouver la valeur minimum (de la leafmin)
// trouver le meilleur chemin
// faire une fonction qui permet de savoir sur quel type de terrain on est (Ensuite voir conditions en message sur discord)
// fonction qui dit si on arrive à la base (point d'arrivée) ou non

// MANDATORY

//TREE :
// Définition de la structure de l'arbre et des noeuds     //DONE//
// Création d'un noeud                                     //DONE//
// Construction d'un arbre n-aires                         //DONE//
// Recherche de la valeur minimale de tout l'arbre         //NOT DONE BUT EASY//

//NODE_QUEUE :
//Fonction de file pour les noeuds
// Création d'une file vide
// Ajout d'un noeud dans la file
// Retirer un noeud de la file

//PATH :
//Recherche de la feuille de valeur minimale            // DONE//
// Parcours en largeur pour trouver tous les noeuds ayant la valeur minimale
// Calcul du coût total du chemin pour arriver à chaque noeud minimal
// Choix du noeud ayant le coût optimal
//Définition du chemin optimal
// Définir les mouvements à effectuer pour avoir le parcours le plus optimal
//
