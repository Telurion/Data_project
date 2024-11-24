//
// Created by amine on 22/11/2024.
//

#include "path.h"
#define MAX 15120

int search_min_node(p_node node) {                              /// WORKS !!!
    if (node == NULL) {
        printf("Empty tree");
        return -1;
    }

    int min_val = node->cost;
    t_queue_tab q = createQueue2(1000);
    enqueue_node(&q, node);

    while (q.first != q.last) {
        p_node cur = dequeue_node(&q);
        if (cur->cost < min_val) {
            min_val = cur->cost;
        }

        for (int i = 0; i < cur->nb_sons; i++) {
            if (cur->sons[i] != NULL) {
                enqueue_node(&q, cur->sons[i]);
            }
        }
    }

    return min_val;
}


p_node* tab_of_min(p_node node, int* len){                /// WORKS
    int min_val = search_min_node(node);
    p_node* min_leaf = (p_node*) malloc(MAX * sizeof(p_node));
    t_queue_tab q  = createQueue2(1000);;
    p_node cur;
    enqueue_node(&q, node);
    while (q.first != q.last){
        cur = dequeue_node(&q);
        if (cur->cost == min_val) {
            min_leaf[*len] = cur;
            (*len)++;
        }
        if (cur->nb_sons != 0){
            for (int i = 0; i < cur->nb_sons; i++) {
                if (cur->sons[i] != NULL){
                    enqueue_node(&q,cur->sons[i]);
                }
            }
        }
    }
    return min_leaf;
}


p_node min_leaf_node(p_node node) {                             /// WORKS
    int len = 0, cost = 0, cheap = 10000, idx;
    p_node *tab_min = tab_of_min(node, &len);
    for (int i = 0; i < len; i++) {
        p_node cur = tab_min[i];
        while (cur != node) {
            cost += cur->cost;
            cur = cur->parent;
        }
        if (cost < cheap) {
            cheap = cost;
            idx = i;
        }
    }
    return tab_min[idx];
}


p_node min_leaf(t_tree t) {      /// WORKS
    return min_leaf_node(t.root);
}


t_move* best_path(t_tree t, int *len)
{

}

void display_min_leaf(t_tree t){
    p_node min = min_leaf(t);
    printf("%d", min->cost);
}


t_move *best_moves(p_node path) {                              /// WORKS !!!
    p_node curr = path;
    int depth = path->idx;

    t_move *pathArray = (t_move *) malloc((depth) * sizeof(t_move));
    while (curr != NULL) {
        pathArray[curr->idx] = curr->move;
        curr = curr->parent;
    }
    return pathArray;
}


int pathCost(p_node path) {                                 /// WORKS !!!
    int total_cost = 0;
    p_node curr = path;
    while (curr != NULL) {
        total_cost += curr->cost;
        curr = curr->parent;
    }
    return total_cost;
}


int soil_type_reg(p_node my_node) {                         ///WORkS BUT TO MODIFY !!!
    if (my_node->soil_type == REG) {
        return 1;
    }
    else {
        return 0;
    }
}


int soil_type_erg(p_node my_node) {                         /// WORKS !!!
    if (my_node->soil_type == ERG) {
        switch (my_node->move) {
            case F_10:
                my_node->move = NO_MOVE;
                break;
            case F_20:
                my_node->move = F_10;
                break;
            case F_30:
                my_node->move = F_20;
                break;
            case T_RIGHT:
                my_node->move = NO_MOVE;
                break;
            case T_LEFT:
                my_node->move = NO_MOVE;
                break;
            case U_TURN:
                my_node->move = T_RIGHT;
                break;
        }
        return 1;
    }
    else {
        return 0;
    }
}


int win(t_map map, t_localisation robot) {                  /// WORKS !!!
    if (map.costs[robot.pos.y][robot.pos.x] == 0) {
        return 1;
    }
    else {
        return 0;
    }
}


int lose(t_map map, t_localisation robot) {                 /// WORKS !!!
    if (isValidLocalisation(robot.pos, map.x_max, map.y_max) == 0 || map.costs[robot.pos.y][robot.pos.x] >= 10000) {
        return 1;
    }
    else {
        return 0;
    }
}