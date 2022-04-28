#include "ULGTAlgo.h"

void dfsConnectRootToLeaves(TreeNode* connectedNode, int rootNr, bool removeOldConnection, std::fstream &tgt) {
	for(auto it = connectedNode->children.begin(); it != connectedNode->children.end(); it++) {
	    TreeNode* child = *it;
		if(removeOldConnection and (it + 1 == connectedNode->children.end())) {
		    tgt << "DELEGATION " + std::to_string(connectedNode->nr) + " " + std::to_string(rootNr) + " " + std::to_string(child->nr) << std::endl;
		} else
		    tgt << "INTRODUCTION " + std::to_string(connectedNode->nr) + " " + std::to_string(rootNr) + " " + std::to_string(child->nr) << std::endl;
		dfsConnectRootToLeaves(child, rootNr, true, tgt);
	}
}

void connectRootToLeaves(TreeNode* root, std::fstream &tgt) {
	for(TreeNode* child : root->children) dfsConnectRootToLeaves(child, root->nr, false, tgt);
}

void dfsRemoveLeaveConnectionsToRoot(TreeNode* node, TreeNode* parent, int rootNr, bool removeRootConnection, std::fstream &tgt) {
	for(TreeNode* child : node->children) dfsRemoveLeaveConnectionsToRoot(child, node, rootNr, true, tgt);
	for(int i = 0; i < node->children.size() - 1; i++) tgt << "FUSION " + std::to_string(node->nr) + " " + std::to_string(rootNr) << std::endl;
	tgt << "DELEGATION " + std::to_string(node->nr) + " " + std::to_string(rootNr) + " " + std::to_string(parent->nr) << std::endl;
}

void removeLeaveConnectionsToRoot(TreeNode* root, std::fstream &tgt) {
	for(TreeNode* child : root->children) dfsRemoveLeaveConnectionsToRoot(child, root, root->nr, false, tgt);
}

void approxULGT(Graph &gs, Graph &gt, std::fstream &tgt) {
	
	std::vector<std::vector<int>> ePlus;

    std::cout << "1" << std::endl;
    for(int node : gt.getNodes()) {
        for(int neigh : gt.getNeighboursOf(node)) {
            if(node < neigh) continue; //avooid dublicates
            bool flag = false;
            for(int neighSrc : gs.getNeighboursOf(node)) {
                if(neigh == neighSrc) {
                    flag = true;
                    break;
                }
                if(flag) ePlus.push_back({node, neigh});
            }
        }
    }

	std::vector<std::vector<int>> eMinus;


    std::cout << "1" << std::endl;
	std::vector<TreeNode*> usForest = calculateUSFApproximation(gs, ePlus); // assume no useless tree branches
	
    std::cout << "1" << std::endl;
	// create edges between treeNodes and ePlus endnodes
	for(TreeNode* akt : usForest) connectRootToLeaves(akt, tgt);
	
	// introduce eplus edges
	for(std::vector<int> aktEdge : ePlus) tgt << "INTRODUCTION " + std::to_string(aktEdge[0]) + " 0 " + std::to_string(aktEdge[1]) << std::endl; //zero placeholder for rT
	
	// remove edges created in step 2
	for(TreeNode* akt : usForest) removeLeaveConnectionsToRoot(akt, tgt);
    std::cout << "1" << std::endl;
}
