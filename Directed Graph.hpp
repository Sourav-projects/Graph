//
//  Directed Graph.hpp
//  Graph Library
//
//  Created by Sourav Kumar on 01/06/21.
//

#ifndef Directed_Graph_hpp
#define Directed_Graph_hpp

#include <stdio.h>
#include <stack>
#include "Graph.h"

using namespace std;

class DirectedGraph : public Graph
{
    public:
        DirectedGraph(int nodes) : Graph(nodes)
        {

        }

        virtual bool isCyclic();

        virtual void addEdge(int u, int v, long long w = 1)
        {
            adjacencyList[u].push_back({v, w});
        }
        vector<vector<int>> getStronglyConnectedComponents();
    
    private:
        
         vector<int> getFinishTimes();
         void finishTimeHelper(int src, vector<int>& finishTimes, vector<bool>& visited);
         DirectedGraph getReversal();
    bool detectCycle(int src, vector<int> &stack, vector<bool> &visited);

};

vector<vector<int>> DirectedGraph :: getStronglyConnectedComponents()
{
            vector<vector<int>> stronglyConnectedComponents;
            vector<int> finishTimes = this -> getFinishTimes();
            DirectedGraph reversedGraph = this -> getReversal();

            vector<bool> visited(this -> getNumberOfNodes() + 1, 0);

            for(int i = finishTimes.size() - 1; i >= 0; i--)
            {
                vector<int> SCC;
                if(!visited[finishTimes[i]])
                {
                  reversedGraph.dfsHelper(finishTimes[i], SCC, visited);
                  stronglyConnectedComponents.push_back(SCC);
                }
            }

            return stronglyConnectedComponents;
}

vector<int> DirectedGraph :: getFinishTimes()
{
             vector<int> finishTimes;
             vector<bool> visited(this -> getNumberOfNodes() + 1, 0);

             for(int src = 1; src <= this -> getNumberOfNodes(); src++)
             {
                 if(!visited[src])
                 {
                     finishTimeHelper(src, finishTimes, visited);
                 }
             }

             return finishTimes;
}


void DirectedGraph :: finishTimeHelper(int src, vector<int>& finishTimes, vector<bool>& visited)
{
             visited[src] = 1;

             for(auto neighbour : this -> adjacencyList[src])
             {
                 if(!visited[neighbour.first])
                    finishTimeHelper(neighbour.first, finishTimes, visited);
             }

             finishTimes.push_back(src);
}

DirectedGraph DirectedGraph :: getReversal()
{
             DirectedGraph gT(this -> getNumberOfNodes());

             for(int node = 1; node <= this -> getNumberOfNodes(); node++)
             {
                 for(auto edge : adjacencyList[node])
                 {
                     gT.addEdge(edge.first, node);
                 }
             }

             return gT;
}

bool DirectedGraph::detectCycle(int src, vector<int> &stack, vector<bool> &visited){
    stack[src]=true;
    if(!visited[src]){
        visited[src]=true;
        for(auto neighbor:this->adjacencyList[src]){
            if(!visited[neighbor.first]&&detectCycle(neighbor.first, stack, visited)) return true;
            if(stack[neighbor.first]) return true;
        }
    }
    stack[src]=false;
    return false;
}


bool DirectedGraph::isCyclic(){
    bool cycle=false;
    vector<int> stack(this->numNodes+1);
    vector<bool> visited(this->numNodes+1);
    for(int i=1;i<=numNodes;i++){
        if(!visited[i]&&detectCycle(i,stack,visited)){
            cycle=true;
            break;
        }
    }
    return cycle;
}



#endif /* Directed_Graph_hpp */
