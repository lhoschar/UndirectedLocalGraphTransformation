#include <RandomGraph.h>

void randomConnectedGraph(int n, int e, Graph &g) {
    g.setSize(n);
    std::vector<int> graphNodes(n);
    std::iota(graphNodes.begin(), graphNodes.end(), 0);
    g.setNodes(graphNodes);

	// create random spanning tree
	std::vector<int> randomPerm(n);
    std::iota(randomPerm.begin(), randomPerm.end(), 0);
    std::shuffle(randomPerm.begin(), randomPerm.end(), std::mt19937{std::random_device{}()});

	for(int i = 1; i < n; i++) {
		int randomConnectionPoint = rand() % i;
	    g.addEdge(randomPerm[i], randomPerm[randomConnectionPoint]);	
	}

	// add leftover edges
	int addedEdges = n - 1;
	while(addedEdges < e) {
		int firstNode = rand() % n;
		int secondNode = rand() % n;

        if(firstNode == secondNode) continue;
        for(int n : g.getNeighboursOf(firstNode)) if(n == secondNode) continue; 

        g.addEdge(firstNode, secondNode);
        addedEdges++;
	}

	// write to file
	//for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(adjMatrix[i][j]) file << to_string(i) + "," + to_string(j) << endl;
}
