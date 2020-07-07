#include "EWDigraph.h"

using namespace std;

EWDigraph::EWDigraph(const int vex, const int edge, const vector<tuple<char, char, double>>& v)
    :m_nVertex(vex),m_nEdge(edge)
{
    for (int i = 0; i < m_nEdge; i++)
        m_mapEWD[get<0>(v[i])].push_back(make_pair(get<1>(v[i]), get<2>(v[i])));
}

void EWDigraph::Print() {
    for (auto a : m_mapEWD) {
        cout << a.first << "|";
        for (auto it : m_mapEWD[a.first])
            cout << a.first << "->" << it.first << ":" << it.second << "  ";
        cout << endl;
    }
    cout << endl;
}

vector<char> EWDigraph::GetNodes() const {
    vector<char> vRet;
    for (auto it : m_mapEWD)
        vRet.push_back(it.first);
    return vRet;
}

void EWDigraph::BFST(const char start) {
    std::deque<char> q;
    map<char, bool> vVisited;
    for (auto i : GetNodes()) {
        vVisited[i] = false;
    }
    q.push_front(start);
    cout << "BFST(" << start << "):" << endl;
    while (!q.empty()) {
        char node = q.front();
        q.pop_front();
        if (!vVisited[node]) {
            vVisited[node] = true;
            cout << node << "-";
        }
        for (auto j : m_mapEWD[node]) {
            if (!vVisited[j.first]) {
                q.push_back(j.first);
            }
        }
        if (q.empty()) {
            for (auto i : GetNodes()) {
                if (!vVisited[i]) {
                    q.push_back(i);
                    break;
                }
            }
        }
    }
    cout << "end";
    cout << endl;
}

void EWDigraph::DFST(const char start) {

    std::stack<char> s;
    map<char, bool> vVisited;
    for (auto i : GetNodes()) {
        vVisited[i] = false;
        s.push(i);
    }
    s.push(start);
    cout << "DFST(" << start << "):" << endl;
    while (!s.empty()) {
        char node = s.top();
        s.pop();
        if (!vVisited[node]) {
            vVisited[node] = true;
            cout << node << "-";
        }
        for (auto i : m_mapEWD[node]) {
            if (!vVisited[i.first]) {
                s.push(i.first);
            }
        }
    }
    cout << "end";
    cout << endl;
}

void EWDigraph::InitVecs() {
    for (auto i : GetNodes()) {
        //map<char, char> m_mapPath
        m_mapPath[i] = '0';
        //map<char, bool> m_mapVertexInQueue
        m_mapVertexInQueue[i] = false;
        //DBL_MAX = 2^1024
        m_mapDistance[i] = DBL_MAX;
    }
}

void EWDigraph::Dijkstra(const char start) {
    InitVecs();
    cout << "Start Point:" << start << endl;
    m_mapDistance[start] = 0;
    std::queue<char> q;
    q.push(start);
    m_mapVertexInQueue[start] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        m_mapVertexInQueue[node] = false;
        for (auto it : m_mapEWD[node]) {
            if (m_mapDistance[it.first] > m_mapDistance[node] + it.second) {
                m_mapDistance[it.first] = m_mapDistance[node] + it.second;
                m_mapPath[it.first] = node;
                if (!m_mapVertexInQueue[it.first]) {

                    q.push(it.first);
                    m_mapVertexInQueue[it.first] = true;
                }
            }
        }
    }
    PrintDij(start);
}

void EWDigraph::PrintDij(const char start) {
    for (auto im : m_mapEWD) {
        cout << im.first << ":" << m_mapDistance[im.first] << "  |  Path = ";
        std::stack<char> spath;
        for (int j = im.first; j != start; j = m_mapPath[j]) {
            if (j == '0') {
                cout << "unreachable ";
                break;
            }
            else {
                spath.push(j);
            }
        }
        spath.push(start);
        while (spath.size() > 0) {
            cout << spath.top();
            if (spath.top() != im.first)
                cout << "->";
            spath.pop();
        }
        cout << endl;
    }
    cout << endl;
}

void EWDigraph::Dijkstra(const char start, const char end) {
    InitVecs();
    cout << start << "->" << end << ":";
    m_mapDistance[start] = 0;
    std::queue<char> q;
    q.push(start);
    m_mapVertexInQueue[start] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        m_mapVertexInQueue[node] = false;
        for (auto it : m_mapEWD[node]) {
            if (m_mapDistance[it.first] > m_mapDistance[node] + it.second) {
                m_mapDistance[it.first] = m_mapDistance[node] + it.second;
                m_mapPath[it.first] = node;
                if (!m_mapVertexInQueue[it.first]) {
                    q.push(it.first);
                    m_mapVertexInQueue[it.first] = true;
                }
            }
        }
    }
    PrintDij(start, end);
}

void EWDigraph::PrintDij(const char start, const char end) {
    cout << m_mapDistance[end] << "  |  Path = ";
    std::stack<char> spath;
    for (int j = end; j != start; j = m_mapPath[j]) {
        if (j == '0') {
            cout << "unreachable";
            break;
        }
        else {
            spath.push(j);
        }
    }
    spath.push(start);

    while (spath.size() > 0) {
        cout << spath.top();
        if (spath.top() != end)
            cout << "->";
        spath.pop();
    }
    cout << endl;
    cout << endl;
}

bool EWDigraph::IsValidVex(const char vex) const {
    return (m_mapEWD.find(vex) != m_mapEWD.end());
}