//
// Created by amine on 22/11/2024.
//

#include "path.h"
#define MAX 15120

int search_min_node(p_node node) {
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


p_node* tab_of_min(p_node node, int* len){
    int min_val = search_min_node(node);
    p_node* min_leaf = (p_node*) malloc(MAX * sizeof(p_node));
    t_queue_tab q;
    p_node cur;
    q = createQueue2(1000);
    enqueue_node(&q, node);
    while (q.first != q.last){
        cur = dequeue_node(&q);
        if(cur->cost == min_val){
            int depth_of_min = cur->idx;
            while (cur->idx == depth_of_min && q.first != q.last){
                if(cur->cost == min_val){
                    min_leaf[*len] = cur;
                    (*len)++;
                }
                cur = dequeue_node(&q);
            }
            return min_leaf;
        }
        else if (cur->nb_sons != 0){
            for (int i = 0; i < cur->nb_sons; i++) {
                if (cur->sons[i] != NULL){
                    enqueue_node(&q,cur->sons[i]);
                }
            }
        }
    }
    return NULL;
}


p_node min_leaf_node(p_node node) {
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


p_node min_leaf(t_tree t) {
    return min_leaf_node(t.root);
}


t_move *best_moves(t_tree t) {
    p_node leaf = min_leaf(t);
    int depth = leaf->idx;

    t_move *pathArray = (t_move *) malloc((depth) * sizeof(t_move));

    for (int i = depth ; i > 0; i--)
    {
        pathArray[i]= leaf->move;
        leaf = leaf->parent;
    }
    return pathArray;
}


int pathCost(p_node path) {
    p_node curr = path;
    int depth = path->idx;
    int total_cost = 0;
    for (int i = depth; i > 0; i++) {
        total_cost += curr->cost;
        curr= curr->parent;
    }
    return total_cost;
}


int soil_type_reg(p_node my_node) {
    if (my_node->soil_type == REG) {
        return 1;
    }
    else {
        return 0;
    }
}


int soil_type_erg(p_node my_node) {
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


int win(t_map map, t_localisation robot) {
    if (map.costs[robot.pos.x][robot.pos.y] == 0) {
        return 1;
    }
    else {
        return 0;
    }
}


int lose(t_map map, t_localisation robot) {
    if (isValidLocalisation(robot.pos, map.x_max, map.y_max) == 0 || map.costs[robot.pos.x][robot.pos.y] >= 10000) {
        return 1;
    }
    else {
        return 0;
    }
}