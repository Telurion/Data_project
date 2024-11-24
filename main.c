#include <stdio.h>
#include <stdlib.h>
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



    ///     RANDOM ROBOT CREATION     ///
    int x = rand() % map.x_max;
    int y = rand() % map.y_max;
    t_orientation ori = rand() % 4;
    t_localisation robot = loc_init(x, y, ori);
    printf("The robot can be found at these coordinates : y = %d, x = %d", y, x);



    while (win(map, robot) != 1 || lose(map, robot) != 1) {
        ///     DRAW RANDOM MOVES     ///
        t_move *moves = getMovesArray();
        printf("Here are the moves that our robot is going to be able to use : \n");
        for (int i = 0; i < PHASES; i++) {
            printf("Move %d : %s\n", i+1, getMoveAsString(moves[i]));
        }
        printf("-------------\n");



        ///     TREE CREATION USING THE DRAWN MOVEMENTS     ///
        t_tree tree = createTree(0, PHASES, robot, map, NO_MOVE, moves);
        //p_node my_root_node = createNode(0,5, 1, NO_MOVE, PLAIN, NULL);
        //p_node my_node1 = createNode(1,3, 2, F_10, REG, my_root_node);
        //p_node my_node2 = createNode(2,5, 1, T_RIGHT, PLAIN, my_node1);
        //p_node my_node3 = createNode(3,7, 4, F_20, PLAIN, my_node2);
        //p_node my_node4_1 = createNode(4,0, 3, F_10, ERG, my_node3);
        //p_node my_node4_2 = createNode(4,10002, 3, F_20, CREVASSE, my_node3);
        //t_tree t;
        //t.root = my_root_node;


        ///     GET THE BEST PATH     ///
        //p_node my_node = min_leaf(tree);
        //printf("Here is the minimal leaf : \n");
        //display_min_leaf(tree);
        printf("Here are the moves that are made in the best path :\n");
        t_move *my_best = best_moves(tree.root);
        for (int i = 0; i < tree.root->idx+1; i++) {
            printf("Move %d : %s\n", i+1, getMoveAsString(my_best[i]));
        }
        printf("Here is the total cost of the best path : %d\n", pathCost(tree.root));


        ///     UPDATE OF THE ROBOT LOCALISATION     ///
        for (int i = 0; i < tree.root->idx+1; i++) {
            updateLocalisation(&robot, my_best[i]);
        }
        printf("New robot location : y = %d, x = %d\n", robot.pos.y, robot.pos.x);
    }

    return 0;
}

// To fix :
//  - createTree
//  - addNodesToTree