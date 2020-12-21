#include<iostream>
#include<exception>
#include<functional>
#include<map>
#include<set>
#include<unordered_map>
#include<vector>
#include<stack>
#include<queue>

template<class VertexType = int, class WeightType = int>
class Graph {
    using EdgeType = std::pair<VertexType, VertexType>;
    using NeighboursType = std::set<VertexType>;
    public:
    Graph() = default;
    Graph(std::vector< std::pair<EdgeType, WeightType>>);
    void addVertex(const VertexType&);
    void addEdge(const VertexType&, const VertexType&, const WeightType&);
    bool hasVertex(const VertexType&) const;
    bool hasEdge(const VertexType&, const VertexType&) const;
    WeightType& getEdge(const VertexType&, const VertexType&);
    WeightType getEdge(const VertexType&, const VertexType&) const;
    std::set<VertexType> neighbours(const VertexType&) const;
    void printDFS(const VertexType) const;
    void printBFS(const VertexType) const;
    bool hasPath(const VertexType&, const VertexType&) const;
    std::vector<VertexType> findPath(const VertexType&, const VertexType&) const;

    private:
    std::map<VertexType, NeighboursType> neighs;
    std::map<EdgeType, WeightType> weights;
    std::set<VertexType> vertices;
};

template<class VertexType, class WeightType>
Graph<VertexType, WeightType>::Graph(std::vector<std::pair<EdgeType, WeightType>> v) {
    for(std::pair<EdgeType, WeightType> element : v)
    {
        auto [edge, weight] = element;
        auto [startVertex, endVertex] = edge;
        addEdge(startVertex, endVertex, weight);
    }
}

template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::printDFS(const VertexType start) const {
	std::stack<VertexType> dfsStack;
	std::set<VertexType> visitedVertices;

	VertexType current = start;

	dfsStack.push(current);
	visitedVertices.insert(current);

    while(!dfsStack.empty())
    {
        VertexType top = dfsStack.top();
        dfsStack.pop();

        for (VertexType vert : neighbours(top)) {
            if (visitedVertices.count(vert) == 0) {
                dfsStack.push(vert);
                visitedVertices.insert(vert);
            }
        }

        std::cout << top << " ";
	}
}
template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::printBFS(const VertexType start) const {
    std::queue<VertexType> bfsQueue;
	std::set<VertexType> visitedVertices;

	VertexType current = start;

	bfsQueue.push(current);
	visitedVertices.insert(current);

    while(!bfsQueue.empty())
    {
        VertexType top = bfsQueue.front();
        bfsQueue.pop();

        for (VertexType vert : neighbours(top)) {
            if (visitedVertices.count(vert) == 0) {
                bfsQueue.push(vert);
                visitedVertices.insert(vert);
            }
        }

        std::cout << top << " ";
	}

}

template<class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::hasPath(const VertexType& start, const VertexType& end) const {
    if(!hasVertex(start) || !hasVertex(end)) {
        return false;
    }
    std::stack<VertexType> dfsStack;
	std::set<VertexType> visitedVertices;

	VertexType current = start;

	dfsStack.push(current);
	visitedVertices.insert(current);

    while(!dfsStack.empty())
    {
        VertexType top = dfsStack.top();
        dfsStack.pop();

        for (VertexType vert : neighbours(top)) {
            if (visitedVertices.count(vert) == 0) {
                dfsStack.push(vert);
                visitedVertices.insert(vert);
            }
        }

        if(visitedVertices.count(end) == 1) {
            return true;
        }
        // if (top == end) {
        //     return true;
        // }
	}
    return false;
}

template<class VertexType, class WeightType>
std::vector<VertexType> Graph<VertexType, WeightType>::findPath(const VertexType& start, const VertexType& end) const {
    std::vector<VertexType> path;
    if(!hasVertex(start) || !hasVertex(end)) {
        return path;
    }
    std::stack<std::pair<VertexType, VertexType>> dfsStack;
	std::set<VertexType> visitedVertices;

	VertexType current = start;

	dfsStack.push({current, current});
	visitedVertices.insert(current);
    

    while(!dfsStack.empty())
    {
        auto [parentVertex, currentVertex] = dfsStack.top();
        dfsStack.pop();

        if (currentVertex == end) {
            path.push_back(currentVertex);
            return path;
        }

        while(!path.empty() && path[path.size()-1] != parentVertex) {
            path.pop_back();
        }

        path.push_back(currentVertex);
        int currentVisitedVertexes = visitedVertices.size();
        for (VertexType vert : neighbours(currentVertex)) {
            if (visitedVertices.count(vert) == 0) {
                dfsStack.push({currentVertex,vert});
                visitedVertices.insert(vert);
            }
        }
	}
    return path;
}

template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::addVertex(const VertexType& v)
{
    vertices.insert(v);
    neighs[v];
}

template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::addEdge(const VertexType& first, const VertexType& second, const WeightType& weight)
{
    vertices.insert(first);
    vertices.insert(second);
    neighs[first].insert(second);
    neighs[second];
    weights[std::make_pair(first, second)] = weight;
}

template<class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::hasVertex(const VertexType& v) const {
    return vertices.count(v) == 1;
}

template<class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::hasEdge(const VertexType& first, const VertexType& second) const {
   return vertices.count(first) && neighs[first].count(second) == 1;
}

template<class VertexType, class WeightType>
WeightType& Graph<VertexType, WeightType>::getEdge(const VertexType& first, const VertexType& second) {
    if (!hasEdge(first, second)) {
        throw std::invalid_argument("No such edge!");
    }
    return weights[std::make_pair(first, second)];
}

template<class VertexType, class WeightType>
WeightType Graph<VertexType, WeightType>::getEdge(const VertexType& first, const VertexType& second) const {
    if(!hasEdge(first,second)) {
        throw std::invalid_argument("No edge present!");
    }

    return weights[std::make_pair(first,second)];
}

template<class VertexType, class WeightType>
std::set<VertexType> Graph<VertexType, WeightType>::neighbours(const VertexType& v) const {
    if(!hasVertex(v)) {
        throw std::invalid_argument("No such vertex");
    }
    return neighs.at(v);
}
