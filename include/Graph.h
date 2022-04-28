#ifndef Graph_h
#define Graph_h

#include <vector>
#include <unordered_map>

class Graph {
	private:
   	int N;
    std::vector<int> nodes;
	std::unordered_map<int, std::vector<int>> adj;
	
	public:
	int getSize();
    void setSize(int size);
    std::vector<int> getNodes();
    void setNodes(std::vector<int> newNodes);
    void addEdge(int u, int v);
	std::vector<int> getNeighboursOf(int v);
};

#endif
