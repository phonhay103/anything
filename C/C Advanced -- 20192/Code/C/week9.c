#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

typedef struct
{
    JRB edges; // Not sink vertex
    JRB vertices; // Các đỉnh
} Graph;

Graph createGraph();
void addVertex(Graph, int id, char* name);
char *getVertex(Graph, int id);
int hasEdge(Graph, int v1, int v2);
void addEdge(Graph, int v1, int v2);
int indegree(Graph, int v, int* output);
int outdegree(Graph, int v, int* output);
int isDAG(Graph);
void dropGraph(Graph);

int main()
{
    Graph G = createGraph();
    addVertex(G, 1, "A");
    addVertex(G, 2, "B");
    addVertex(G, 3, "C");
    addVertex(G, 4, "D");
    addVertex(G, 5, "E");
    addEdge(G, 1, 4);
    addEdge(G, 4, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 1);

    if (!isDAG(G))
        printf("\n!!!!DAG\n");
    return 0;
}

Graph createGraph()
{
    Graph G;
    G.edges = make_jrb();
    G.vertices = make_jrb();
    return G;
}

// Thêm định danh ID cho đỉnh
void addVertex(Graph G, int id, char* name)
{
    JRB node = jrb_find_int(G.vertices, id);
    if (!node)
        jrb_insert_int(G.vertices, id, new_jval_s(strdup(name)));
}

// Lấy đỉnh theo ID
char *getVertex(Graph G, int id)
{
    JRB isExist = jrb_find_int(G.vertices, id);
    if (!isExist)
        return NULL;
    return jval_s(isExist->val);
}

// Kiểm tra tồn tại liên kết v1->v2
int hasEdge(Graph G, int v1, int v2)
{
    JRB isExist = jrb_find_int(G.edges, v1);
    if (!isExist)
        return 0;
    if (jrb_find_int((JRB) jval_v(isExist->val), v2))
        return 1;
    else
        return 0;
}

// Thêm liên kết v1->v2
void addEdge(Graph G, int v1, int v2)
{
    JRB node, tree;
    if (!hasEdge(G, v1, v2)) // Nếu không tồn tại liên kết từ v1 -> v2
    {
        node = jrb_find_int(G.edges, v1);
        if(!node) // v1 là sink vertex (v1 không tồn tại trong G.edges)
        {
            tree = make_jrb(); // Thêm v1 vào G.edges
            jrb_insert_int(G.edges, v1, new_jval_v(tree));
        }
        else
            tree = (JRB) jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1)); // Thêm liên kết từ v1 -> v2
    }
}

// Liên kết từ v đến các đỉnh khác => Mảng và số phần tử
int outdegree(Graph G, int v, int* output)
{
    JRB node, tree;
    node = jrb_find_int(G.edges, v);
    if (!node)
        return 0;
    
    int total = 0;
    tree = (JRB) jval_v(node->val);
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}

// Liên kết từ các đỉnh khác đến v => Mảng và số phần tử
int indegree(Graph G, int v, int* output)
{
    JRB node, tree, iter;
    int total = 0;

    // Duyệt tất cả các đỉnh: Tìm liên kết từ đỉnh đến v
    jrb_traverse(iter, G.vertices)
    {
        node = jrb_find_int(G.edges, jval_i(iter->key));
        if (node) // Nếu đỉnh ko phải là sink vertex
        {
            tree = (JRB) jval_v(node->val);
            if (jrb_find_int(tree, v)) // Nếu đỉnh có liên kết đến v
            {
                output[total] = jval_i(node->key);
                total++;
            }
        }
    }
    return total;
}

// Kiểm tra DAG
int isDAG(Graph G)
{
    JRB iter;
    int n, output[100], visited[1000];
    Dllist stack = new_dllist();
    int vertice, start;

    // Duyệt theo chiều sâu bắt đầu từ từng đỉnh
    jrb_traverse(iter, G.vertices)
    {
        memset(visited, 0, sizeof(visited));
        start = jval_i(iter->key);
        dll_prepend(stack, new_jval_i(start));
        // printf("* VERTICE: %d\n", start);
        while (!dll_empty(stack))
        {
            vertice = jval_i(dll_first(stack)->val);
            dll_delete_node(dll_first(stack));
            // printf("- POP: %d\n", vertice);
            n = outdegree(G, vertice, output);
            // printf("- LINK: \n");
            for (int i = 0; i < n; ++i)
            {
                vertice = output[i];
                // printf("+ vertice: %d\n", vertice);
                if (vertice == start)
                {
                    // printf("==>Has cycle\n");
                    free_dllist(stack);
                    return 0;
                }
                if (!visited[vertice])
                {
                    // printf(" -> Stack: %d\n", vertice);
                    dll_prepend(stack, new_jval_i(vertice));
                }
                    
            }
        }
    }
    free_dllist(stack);
    return 1;
}
// Từ một đỉnh: duyệt qua tất cả đỉnh có liên kết từ đỉnh đó
// Nếu đỉnh liên kết có liên kết đến đỉnh bắt đầu => Không phải DAG => return 0;
// Nếu đỉnh liên kết không có liên kết đến đỉnh bắt đầu
// + Nếu đã visited => bỏ qua
// + Nếu chưa visited => Thêm vào stack

void dropGraph(Graph G)
{
    JRB iter;
    if (G.vertices != NULL)
        jrb_free_tree(G.vertices);

    if (G.edges != NULL)
    {
        jrb_traverse(iter, G.vertices)
            jrb_free_tree((JRB) jval_v(iter->val));
        jrb_free_tree(G.edges);
    }
}