#include "Graph.h"

int Graph::getSize() {
    return N;
}

void Graph::setSize(int size) {
    N = size;
}

std::vector<int> Graph::getNodes() {
    return nodes;
}

void Graph::setNodes(std::vector<int> newNodes) {
    nodes = newNodes;
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

std::vector<int> Graph::getNeighboursOf(int v) {
    if(adj.find(v) == adj.end()) return {};
    else return adj[v];
}
