#include <stdio.h>
#include "jrb.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph, int v1, int v2);
int adjacent(Graph, int v1, int v2);
int getAdjacentVertices(Graph, int v, int* output);
void dropGraph(Graph);

int main()
{
    Graph G = createGraph();
    addEdge(G, 3, 5);
    addEdge(G, 3, 8);
    addEdge(G, 5, 8);
    addEdge(G, 7, 1);
    addEdge(G, 6, 4);
    addEdge(G, 1, 3);
    addEdge(G, 3, 2);
    int n, A[50];
    Graph iter;
    jrb_traverse(iter, G)
    {
        n = getAdjacentVertices(G, jval_i(iter->key), A);
        printf("%d(%d): ", jval_i(iter->key), n);
        for (int i=0; i<n; ++i)
            printf("%d ", A[i]);
        puts("");
    }
    dropGraph(G);
    return 0;
}

Graph createGraph()
{
    return make_jrb();
}

void addEdge(Graph graph, int v1, int v2)
{
    JRB node, tree;
    // Thêm v2 vào v1
    if (!adjacent(graph, v1, v2))
    {
        // Tìm v1 trong graph: không tìm thấy => Tạo mới, tìm thấy => lấy val v1 | => Thêm v2
        node = jrb_find_int(graph, v1);
        if (!node)
        {
            tree = make_jrb();
            jrb_insert_int(graph, v1, new_jval_v(tree));
        }
        else
            tree = (JRB) jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1)); // new_jval_i dùng để chứa trọng số, chưa dùng đến 
    }

    // Thêm v1 vào v2: tương tự
    if (!adjacent(graph, v2, v1))
    {
        node = jrb_find_int(graph, v2);
        if (!node)
        {
            tree = make_jrb();
            jrb_insert_int(graph, v2, new_jval_v(tree));
        }
        else
            tree = (JRB) jval_v(node->val);
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
}

int adjacent(Graph graph, int v1, int v2)
{
    JRB tmp;
    // Tìm v1 trong graph: không tìm thấy => 0, tìm thấy => tìm v2 trong v1
    tmp = jrb_find_int(graph, v1);
    if (!tmp)
        return 0;

    // Tìm v2 trong miền liền kề v1
    tmp = (JRB) jval_v(tmp->val);
    if (jrb_find_int(tmp, v2))
        return 1;
    else
        return 0;
}

int getAdjacentVertices(Graph graph, int v, int *output)
{
    /* Lấy list key các đỉnh kết nối và trả về tổng số đỉnh kết nối */

    // Tìm v trong graph: không tìm thấy => NULL, tìm thấy => duyệt tree
    JRB node, tree, iter;
    int total;

    node = jrb_find_int(graph, v);
    if (!node)
        return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;

    // Duyệt val v (tree): lưu key vào output mỗi lần lặp qua
    jrb_traverse(iter, tree)
    {
        output[total] = jval_i(iter->key);
        total++;
    }
    return total;
}

void dropGraph(Graph graph)
{
    JRB iter;
    jrb_traverse(iter, graph)
        jrb_free_tree((JRB) jval_v(iter->val));
    jrb_free_tree(graph);
}