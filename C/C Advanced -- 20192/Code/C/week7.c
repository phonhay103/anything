#include <stdio.h>
#include "jrb.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph, char*, char*);
int adjacent(Graph, char*, char*);
int getAdjacentVertices(Graph, char*, char** output);
void dropGraph(Graph);

int main()
{
    Graph G = createGraph();
    addEdge(G, "A", "B");
    addEdge(G, "A", "AB");
    addEdge(G, "B", "AB");
    addEdge(G, "C", "A");
    addEdge(G, "A", "AC");
    addEdge(G, "A", "ABC");
    addEdge(G, "AB", "AC");
    int n;
    char* A[50];
    Graph iter;
    jrb_traverse(iter, G)
    {
        n = getAdjacentVertices(G, jval_s(iter->key), A);
        printf("%s(%d): ", jval_s(iter->key), n);
        for (int i=0; i<n; ++i)
            printf("%s ", A[i]);
        puts("");
    }
    dropGraph(G);
    return 0;
}

Graph createGraph()
{
    return make_jrb();
}

void addEdge(Graph graph, char *v1, char *v2)
{
    JRB node, tree;
    if (!adjacent(graph, v1, v2))
    {
        node = jrb_find_str(graph, v1);
        if (!node)
        {
            tree = make_jrb();
            jrb_insert_str(graph, v1, new_jval_v(tree));
        }
        else
            tree = (JRB) jval_v(node->val);
        jrb_insert_str(tree, v2, new_jval_i(1));
    }

    if (!adjacent(graph, v2, v1))
    {
        node = jrb_find_str(graph, v2);
        if (!node)
        {
            tree = make_jrb();
            jrb_insert_str(graph, v2, new_jval_v(tree));
        }
        else
            tree = (JRB) jval_v(node->val);
        jrb_insert_str(tree, v1, new_jval_i(1));
    }
}

int adjacent(Graph graph, char *v1, char *v2)
{
    JRB tmp;
    tmp = jrb_find_str(graph, v1);
    if (!tmp)
        return 0;

    tmp = (JRB) jval_v(tmp->val);
    if (jrb_find_str(tmp, v2))
        return 1;
    else
        return 0;
}

int getAdjacentVertices(Graph graph, char *v, char **output)
{
    JRB node, tree, iter;
    int total;

    node = jrb_find_str(graph, v);
    if (!node)
        return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;

    jrb_traverse(iter, tree)
    {
        output[total] = jval_s(iter->key);
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