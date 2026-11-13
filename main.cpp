#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }
};

void DFS(Graph);
void BFS(Graph, int);
bool find(vector<int>, int);

bool find(vector<int> List, int Int) {
    bool found = false;
    for (int i = 0; i < List.size(); ++i)
        if (List[i] == Int)
            found = true;

    return found;
}

void BFS(Graph graph, int vertex = 0) {
    static vector<int> searched;
    static bool hasOutput = false; 
    searched.push_back(vertex);
    for (Pair v : graph.adjList[vertex]) {
        if (!find(searched, v.first)) {
            BFS(graph, v.first);
        }
    }
    // check if all nodes have been visited
    if (searched.size() == SIZE && !hasOutput) {
        hasOutput = true;
        cout << "BFS starting from vertex 0:\n";
        for (int i = 0; i < searched.size(); ++i) {
            cout << searched[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();
    BFS(graph);

    return 0;
}
