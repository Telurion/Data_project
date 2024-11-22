//
// Created by amine on 22/11/2024.
//

#include "path.h"

int search_min_node(p_node node) {
    if (node == NULL) {
        printf("Empty tree");
        return -1;
    }

    int min_val = node->cost;
    t_queue_tab q = createQueue(1000);
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
        while (cur != NULL) {
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
