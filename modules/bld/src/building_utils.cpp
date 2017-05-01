#include <fstream>
#include <iostream>
#include <skyline/bld/building.h>
#include <vector>

namespace skyline {
namespace bld {
    /**
 * Read in building from a file into a vector of buildings
 */
    template <typename T>
    bool loadRecBuildings(std::vector<RecBuilding<T>>& bldVector, const std::string& inputFileName)
    {

        std::ifstream inputStream(inputFileName.c_str(), std::ifstream::in);

        if (!inputStream) {
            throw std::runtime_error("Failed to open building file" + inputFileName);
        }

        RecBuilding<T> bld;
        while (inputStream >> bld.leftBottom[0] >> bld.leftBottom[1] >> bld.buildingSize[0] >> bld.buildingSize[1]) {
            bldVector.push_back(bld);
        }

        std::cout << "Number of buildings: " << bldVector.size() << "\n";

        return true;
    }

    // initialize to generate the actual code for library
    template struct RecBuilding<int>;
    template bool loadRecBuildings(std::vector<RecBuilding<int>>& bldVector, const std::string& inputFileName);
}
}
