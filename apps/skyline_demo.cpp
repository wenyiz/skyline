// skyline_demo.cpp
// apps
//
// Created to demo building skyline giving a series of buildings

#include <iostream>
#include <ostream>
#include <skyline/bld/building.h>
#include <skyline/bld/skyline_vector.h>
#include <unistd.h>

using namespace std;

void printUsage()
{
    std::cout << "Usage : skyline_demo -b <BuildingListFile> -s <SkylineOutFile>"
              << "\n BuildingListFile - input file lists all buildings"
              << "\n SkylineOutFile   - output file lists the nodes on the skyline (left->right, up/down \n";
}

int main(int argc, char** argv)
{

    // Process command line arguments
    int option = 0;
    std::string BuildingListFile("building.txt");
    std::string SkylineOutFile("skyline.txt");

    while ((option = getopt(argc, argv, "b:s:")) != -1) {
        switch (option) {
        case 'b':
            BuildingListFile = optarg;
            break;
        case 's':
            SkylineOutFile = optarg;
            break;
        default:
            printUsage();
            exit(EXIT_FAILURE);
        }
    }

    std::vector<skyline::bld::RecBuilding<int>> bldVector;
    // Reading in a list of buildings
    loadRecBuildings(bldVector, BuildingListFile);

    // Building the skyline
    skyline::bld::Skyline<int> sky;

    for (const auto& bld : bldVector) {
        sky.updateSkyline(bld);

        // dynamically output skyline
        sky.printSkyline();
    }

    sky.saveSkyline(SkylineOutFile);
}
