#pragma once
#include <iostream>
#include <vector>

namespace skyline {
namespace bld {
    /**
 * Data structure for rectangular building that has the following values looking from left to right
 * leftBottom[2] and buildingSize[2]
 */

    template <typename T>
    struct RecBuilding {

        T leftBottom[2]; // Left most bottom corner
        T buildingSize[2]; // Building size: width/x and height/y
    };

    // utilities function to read in buildings to a vector from a file
    template <typename T>
    bool loadRecBuildings(std::vector<RecBuilding<T>>& bldVector, const std::string& inputFileName);
}
}
