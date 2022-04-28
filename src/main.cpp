#include <USFApprox.h>
#include <Graph.h>
#include <RandomGraph.h>
#include <ULGTAlgo.h>

int main(int argc, char** argv) { 
    

    int N = 30;
    int E = 60;
    Graph gs; //fill random
    Graph gt; //fill random

   
    randomConnectedGraph(30, 30, gs);
    randomConnectedGraph(30, 30, gt);
    
    //for(int node : gs.getNodes()) {
    //    std::cout << std::to_string(node) + " -> [";
    //    for(int neigh : gs.getNeighboursOf(node)) std::cout << std::to_string(neigh) << " ";
    //    std::cout << std::endl;
    //}

    std::fstream mfile;
    mfile.open("/home/vagrant/bachelorThesisApproxAlgo/bachelorThesis/src/result");
    approxULGT(gs, gt, mfile);
    mfile.close();
    return 0; 
}
