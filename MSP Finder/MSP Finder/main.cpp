//
//  main.cpp
//  MSP Finder
//
//  Created by Alexander Ley on 09/03/2024.
//


#include <iostream>
#include <vector>
#include <set>
using namespace std;

class graph
{
private:
    int numOfVertices = 0;
    vector<vector<int>> matrix;
    set<vector<int>> outputTree;
    set<int> visited;
    
    void createMatrix()
    {
        //looks weird but just makes a 2d vector to act as an adjacency matrix
        matrix = vector<vector<int>>(numOfVertices, vector<int>(numOfVertices, 0));
    }
    
    void removeEdge(int v1, int v2)
    {
        matrix[v1][v2] = 0;
        matrix[v2][v1] = 0;
    }
    
    vector<int> getConnectedVertices (int vertex) //returns vector of all vertices connected to a given one
    {
        vector<int> connectedVertices;
        int i = 0;
        
        for (int edge : matrix[vertex])
        {
            if (edge == 1)
            {
                connectedVertices.push_back(i);
            }
            i++;
        }
        
        
        return connectedVertices;
    }
    
    bool isVisited (int vertex)
    {
        bool returnVal = false;
        
        for (int currentV : visited)
        {
            if (currentV == vertex)
            {
                returnVal = true;
            }
        }
       
        
        return returnVal;
    }
    
    void visitVertex (int vertex, int parent)
    {
        vector<int> bufferVec;
        
        bufferVec.push_back(parent);
        bufferVec.push_back(vertex);
        
        visited.insert(vertex);
        outputTree.insert(bufferVec);
        
    }
    
    void getMSTInternal(int startV) //recursive MST function
    {
        vector<int> connections = getConnectedVertices(startV);
        
        
        for (int currentV : connections)
        {
            if (isVisited(currentV) == false)
            {
                visitVertex(currentV, startV);
                removeEdge(currentV, startV);
            }
        }
        
        for (int currentV : connections)
        {
            getMSTInternal(currentV);
        }
        
    }
    
    
    
    
    
public:
    void setupGraph (int numOfNodes) //sets up the adjacency matrix
    {
        numOfVertices = numOfNodes;
        createMatrix();
    }
    
    void addEdge (int v1, int v2)
    {
        matrix[v1][v2] = 1;
        matrix[v2][v1] = 1;
    }
    
    set<vector<int>> getMST(int startV) //just here to compartmentalise everything a little more
    {
        getMSTInternal(startV);
        return outputTree;
    }
    
    
    
};


int main(int argc, const char * argv[]) {
    graph g1;
    
    g1.setupGraph(6);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(0, 5);
    g1.addEdge(5, 3);
    g1.addEdge(2, 4);
    
    
    set<vector<int>> MST = g1.getMST(0);
    
    cout << "Minimum spanning tree : \n";
    for (vector<int> i : MST)
    {
        cout << i[0] << " -> " << i[1] << "\n";
        
    }
    
    
    
    
    return 0;
}
