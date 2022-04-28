#ifndef USFApprox_h
#define USFApprox_h

#include "Graph.h"
#include "limits.h"
#include <deque>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <map>
#include <utility>  

struct TreeNode {
    int nr;
    std::vector<TreeNode*> children;
};

std::pair<std::vector<int>, int> getShortestPathBetween(Graph &g, std::unordered_map<int, std::unordered_set<int>> &zeroed, int s, int t);

std::vector<TreeNode*> buildForestFromEdgeList(std::unordered_map<int, std::unordered_set<int>> &m);

std::vector<TreeNode*> calculateUSFApproximation(Graph &g, std::vector<std::vector<int>> &terminals);
#endif
