#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "tree.h"
#include "path.h"
#include "moves.h"
#include "loc.h"

#define NUM_MOVEMENTS 7
#define PHASES 9

int main() {
    t_map map;
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif


    ///     MAP DISPLAY     ///
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);


    ///     DRAW RANDOM MOVES     ///
    t_move *moves = getMovesArray();
    for (int i = 0; i < PHASES; i++) {
        printf("Move %d : %s\n", i+1, getMoveAsString(moves[i]));
    }


    ///     RANDOM ROBOT CREATION     ///
    int x = rand() % map.x_max;
    int y = rand() % map.y_max;
    t_orientation ori= rand() % 4;
    t_localisation robot = loc_init(x, y, ori);


    ///     TREE CREATION     ///
    //t_tree tree = createTree(0, PHASES, robot, map, NO_MOVE, moves);  createNode(int idx, int cost, int nb_sons, t_move move, t_soil soil, t_node *parent)
    p_node my_node1 = createNode(0,3, 2, F_10, REG, NULL);
    p_node my_node2 = createNode(1,5, 1, T_RIGHT, PLAIN, my_node1);
    p_node my_node3 = createNode(2,7, 4, F_20, PLAIN, my_node2);
    p_node my_node3_2 = createNode(2,6, 0, T_LEFT, PLAIN, my_node2);
    p_node my_node4 = createNode(3,8, 3, B_10, ERG, my_node3);


    ///     GET THE BEST PATH     ///
    //t_move* best_path_of_moves= best_moves(tree);
    //p_node min = min_leaf(tree);
    return 0;
}
