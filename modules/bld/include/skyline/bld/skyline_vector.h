#pragma once

#include "building.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

#define SKY_LEFT_END -1000000
#define SKY_RIGHT_END 1000000
#define SKY_BOTTOM_HEIGHT 0

namespace skyline {
namespace bld {

    template <typename T> //  Skyline Node
    struct Node {

        T location[2]; // x/width and y/height value
        bool isVisible;
    };

    // Skyline is a vector of nodes that is arranged from left to right (bottom to top OR top to bottom)
    // Class with template arguments but not function template, variable template, member function, member class, or static data member
    template <typename T>
    class Skyline {
    public:
        // default constructor and destrutor
        Skyline();
        ~Skyline();

        // initialize the skyline
        void initialize();

        // update skyline giving a building
        void updateSkyline(const RecBuilding<T>& bld);

        // insert a node a given position
        void insertNode(const Node<T>& node, const int pos)
        {

            mSkylineNodes.insert(mSkylineNodes.begin() + pos, 1, node);
        }

        // remove a node given position
        void removeNode(const int pos)
        {

            mSkylineNodes.erase(mSkylineNodes.begin() + pos);
        }

        // print out skyline nodes
        void printSkyline()
        {

            std::cout << "# Skyline: list of nodes"
                      << "\n"
                      << "# number of nodes: " << mSkylineNodes.size() << "\n"
                      << "# each node: index, [x, y], isVisible"
                      << "\n";

            int index = 0;
            for (const auto& node : mSkylineNodes) {

                std::cout << index << ","
                          << "[" << node.location[0] << ", " << node.location[1] << "]"
                          << ", " << node.isVisible << "\n";
                index++;
            }
            std::cout << "\n";
        }
        // save skyline nodes to file
        bool saveSkyline(const std::string& outFileName);

    private:
        // skyline is a vector
        std::vector<Node<T>> mSkylineNodes;
        int mBldNodesRange[2];
    };
}
}
