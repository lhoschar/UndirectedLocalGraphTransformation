#ifndef ULGTAlgo_h
#define ULGTAlgo_h

#include <set>
#include <algorithm>
#include <Graph.h>
#include <USFApprox.h>
#include <iostream>
#include <fstream>

void dfsConnectRootToLeaves(TreeNode* connectedNode, int rootNr, bool removeOldConnection, std::fstream &tgt);

void connectRootToLeaves(TreeNode* root, std::fstream &tgt);

void dfsRemoveLeaveConnectionsToRoot(TreeNode* node, TreeNode* parent, int rootNr, bool removeRootConnection, std::fstream &tgt);
void removeLeaveConnectionsToRoot(TreeNode* root, std::fstream &tgt);

void approxULGT(Graph &gs, Graph &gt, std::fstream &tgt);

#endif
