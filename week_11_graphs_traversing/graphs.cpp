#include "graphs.hpp"

int main() {
    Graph<int, int> gr{{
        { {1,2}, 5 },
        { {2,1}, 5 },
        { {2,6}, 5 },
        { {1,3}, 5 },
        { {3,4}, 5 },
        { {4,5}, 5 },
        { {5,3}, 5 },
        { {4,7}, 5 },
        { {6,7}, 5 },
        { {7,7}, 5 },
        { {7,5}, 5 },
        { {7,9}, 5 },
        { {9,8}, 5 },
        { {6,8}, 5 },
        { {8,7}, 5 },
        { {8,6}, 5 },
        { {6,2}, 5 },
        { {5,10}, 5 },
        { {10,11}, 5 },
    }};
    // gr.printDFS();
    // gr.printBFS(1);
    // std::cout << std::boolalpha << gr.hasPath(10,7);
    std::vector<int> path = gr.findPath(3,11);
    for(auto elem : path) {
        std::cout << elem << " ";
    }
}