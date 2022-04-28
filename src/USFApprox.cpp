#include "USFApprox.h"

void dfsBuildTree(std::unordered_map<int, std::unordered_set<int>> &adjMap, int rootNr, TreeNode* root, std::unordered_set<int> &seen) {
	if(seen.count(rootNr) != 0) return;
	root->nr = rootNr;
	seen.insert(rootNr);
	if(adjMap.find(rootNr) == adjMap.end()) return;
	for(int childNr : adjMap[rootNr]) {
		TreeNode* childNode;
		dfsBuildTree(adjMap, childNr, childNode, seen);
		root->children.push_back(childNode);
	}
}

std::vector<TreeNode*> buildForestFromMarkedEdges(std::unordered_map<int, std::unordered_set<int>> m) {
    std::unordered_set<int> seen;
    std::vector<TreeNode*> result;
    
    for(auto it = m.begin(); it != m.end(); it++) {
        int nodeNr = it->first;
	    if(seen.count(nodeNr) != 0) continue;
	    TreeNode* newNode;
	    dfsBuildTree(m, nodeNr, newNode, seen);
	    result.push_back(newNode);
    } 
    
	return result;
}

std::pair<std::vector<int>, int> getShortestPathBetween(Graph &g, std::unordered_map<int, std::unordered_set<int>> &zeroed, int s, int t) {
    int nrGraphNodes; //TODO
    std::vector<int> dist(nrGraphNodes, INT_MAX);
    std::vector<int> pred(nrGraphNodes, -1);
    dist[s] = 0;
    pred[s] = s;
    std::deque<int> q;
    q.push_front(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int neigh : g.getNeighboursOf(v)) {
            int weight = zeroed.find(v) == zeroed.end() || zeroed[v].count(neigh) == 0; 
            if (dist[v] + weight < dist[neigh]) {
                dist[neigh] = dist[v] + weight;
                if (weight == 1)
                    q.push_back(neigh);
                else
                    q.push_front(neigh);
            }
            if(neigh == t) break; //TODO confirm correctness            
        }
    }
	
	std::vector<int> path;
	for(int akt = t; akt != s; akt = pred[akt]) path.push_back(akt);
	path.push_back(s);
    return make_pair(path, dist[t]);
}

std::vector<TreeNode*> calculateUSFApproximation(Graph &g, std::vector<std::vector<int>> &terminals) {
	// impl Gupta & Kumar 2014
	int nrTerm = terminals.size();
	std::vector<bool> terminalProcessed(nrTerm, false);
	int nrTerminalsProcessed = 0;
	std::unordered_map<int, std::unordered_set<int>> zeroed;

	bool stop = false;
	while(stop == false) {
		//find terminal with shortest path
		int minTerm = -1;
		int minTermDist = INT_MAX;
		std::vector<int> minTermPath;
		for(int i = 0; i < nrTerm; i++) {
			if(terminalProcessed[i] == true) continue;
			
            std::pair<std::vector<int>, int> res = getShortestPathBetween(g, zeroed, terminals[i][0], terminals[i][1]);
			std::vector<int> currPath = res.first; 
			int currTerminalDistance = res.second; 
			if(currTerminalDistance < minTermDist) {
				minTerm = i;
				minTermDist = currTerminalDistance;
				minTermPath = currPath;
			}
		}
		
		// mark terminal as processed
		terminalProcessed[minTerm] = true;
		nrTerminalsProcessed++;
		
		// mark edges on path as zeroed out 
        //
		for(int i = 0; i < minTermPath.size() - 1; i++) {
	        zeroed[i].insert(i+1);
	        zeroed[i + 1].insert(i);
		}
		
		if(nrTerminalsProcessed == nrTerm) break;
	}
	
	return buildForestFromMarkedEdges(zeroed);
}
