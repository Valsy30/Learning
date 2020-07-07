// Testing.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "EWDigraph.h"
using namespace std;
int main()
{
    vector<tuple<char, char, double>> arrVertex = {
        make_tuple('E', 'F', 0.35),
        make_tuple('F', 'E', 0.35),
        make_tuple('E', 'H', 0.37),
        make_tuple('F', 'H', 0.28),
        make_tuple('H', 'F', 0.28),
        make_tuple('F', 'B', 0.32),
        make_tuple('A', 'E', 0.38),
        make_tuple('A', 'C', 0.26),
        make_tuple('H', 'D', 0.39),
        make_tuple('B', 'D', 0.29),
        make_tuple('C', 'H', 0.34),
        make_tuple('G', 'C', 0.40),
        make_tuple('D', 'G', 0.52),
        make_tuple('G', 'A', 0.58),
        make_tuple('G', 'E', 0.93),
        make_tuple('I', 'J', 0.5),
        make_tuple('J', 'J', 0)
    };

    auto ewd = make_unique<EWDigraph>(10, 17, arrVertex);
    ewd->Print();
    
    //BFS
    for (auto it : ewd->GetNodes()) {
        ewd->BFST(it);
        cout << endl;
    }

    //DFS
    for (auto it : ewd->GetNodes()) {
        ewd->DFST(it);
        cout << endl;
    }

    //Dijkstra
    for (auto it : ewd->GetNodes()) {
        ewd->Dijkstra(it);
        cout << endl;
    }

    return 0;
}