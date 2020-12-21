#include<iostream>
#include<exception>
#include<functional>
#include<map>
#include<set>
#include<unordered_map>

template<class VertexType = int, class WeightType = int>
class Graph {
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

    private:
    using EdgeType = std::pair<VertexType, VertexType>;
    using NeighboursType = std::set<VertexType>;

    std::map<VertexType, NeighboursType> neighs;
    std::map<EdgeType, WeightType> weights;
    std::set<VertexType> vertices;
}; 
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
    return weights[std::make(first, second)]
}

template<class VertexType, class WeightType>
WeightType Graph<VertexType, WeightType>::getEdge(const VertexType& first, const VertexType& second) const {
    if(!hasEdge(v1,v2)) {
        throw std::invalid_argument("No edge present!");
    }

    return weights[std::make_pair(v1,v2)];
}

template<class VertexType, class WeightType>
std::set<VertexType> Graph<VertexType, WeightType>::neighbours(const VertexType& v) const {
    if(!hasVetrex(v)) {
        throw std::invalid_argument("No such vertex");
    }
    return neighs[v];
}


template<class VertexType = int, class WeightType = int>
class GraphM {
    std::vector<std::vector<std::optional<WeightType>>> neighMatrix;
    std::set<VertexType> vertices;
    std::map<VertexType, size_t> vertIndexes;

    public:
    WeightType getEdge(const VertexType& v1,const VertexType& v2) const;
};

template<class VertexType, class WeightType>
WeightType GraphM<VertexType, WeightType>::getEdge(const VertexType& v1,const VertexType& v2) const {
    // ...
    std::optional<WeightType> weight = neighMatrix[vertIndexes[v1]][vertIndexes[v2]];
    if(!weight.has_value()) {
        throw std::invalid_argument("No edge present!");
    }
    return weight.value();
}

int main() {
}