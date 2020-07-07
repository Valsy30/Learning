#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <tuple>
#include <map>
#include <stack>

class EWDigraph
{
private:
    int m_nVertex;
    int m_nEdge;
    std::map<char, bool> m_mapVertexInQueue;
    std::map<char, double> m_mapDistance;
    std::map<char, char> m_mapPath;
    std::map<char, std::vector<std::pair<char, double>>> m_mapEWD;

public:
    EWDigraph(const int vex, const int edge, const std::vector<std::tuple<char, char, double>>&);
    void Print();
    void Dijkstra(const char start);
    void Dijkstra(const char start, const char end);
    std::vector<char> GetNodes() const;
    bool IsValidVex(const char vex) const;
    void BFST(const char start);
    void DFST(const char start);

private:
    void InitVecs();
    void PrintDij(const char start);
    void PrintDij(const char start, const char end);
};