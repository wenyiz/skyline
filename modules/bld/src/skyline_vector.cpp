#include <fstream>
#include <skyline/bld/building.h>
#include <skyline/bld/skyline_vector.h>

namespace skyline {
namespace bld {

    template <typename T>
    Skyline<T>::Skyline()
    {

        initialize();
    }

    template <typename T>
    Skyline<T>::~Skyline() {}

    // initialze the class with left extreme and right extreme
    template <typename T>
    void Skyline<T>::initialize()
    {

        Node<T> node;

        // left end node
        node.location[0] = SKY_LEFT_END;
        node.location[1] = SKY_BOTTOM_HEIGHT;
        node.isVisible = true;
        insertNode(node, 0);

        // right end node
        node.location[0] = SKY_RIGHT_END;
        node.location[1] = SKY_BOTTOM_HEIGHT;
        node.isVisible = true;
        insertNode(node, 1);

        // BldNodes of interest
        mBldNodesRange[0] = 0;
        mBldNodesRange[1] = 1;
    }

    // update skyline giving a building after blocked nodes are detected
    template <typename T>
    void Skyline<T>::updateSkyline(const RecBuilding<T>& bld)
    {

        // scan and add bld corner as node when there are transitions
        // 1) from valid to invalid, and
        // 2) invalid to valid

        // Go through all nodes relevant to the four corners of the new building
        int i = mBldNodesRange[0];

        T bldRight = bld.leftBottom[0] + bld.buildingSize[0];
        T bldHeight = bld.leftBottom[1] + bld.buildingSize[1];

        // index to insert after existing node
        int indexLeftBottom = -1;
        int indexLeftTop = -1;
        int indexRightBottom = -1;
        int indexRightTop = -1;

        Node<T> node;
        for (; i < mBldNodesRange[1]; i++) {

            // 1) for leftBottom Corner: add if lie between two bottom nodes (horizontal projection) or left most and remove right node
            // otherwise, not add corner and keep the right node
            // 2) for leftTop Corner: add if above two nodes (vertical projection and remove right node
            // otherwise, not add corner and keep the right node

            // Check two nodes surrouding corners along horizontal line: left node and right node

            /******  Left side: bottom --> top (crossing horizonal line) ******/
            if ((bld.leftBottom[0] > mSkylineNodes[i].location[0]) && (bld.leftBottom[0] < mSkylineNodes[i + 1].location[0])) {

                // adding leftBottom
                if ((bld.leftBottom[1] >= mSkylineNodes[i].location[1]) && (bld.leftBottom[1] >= mSkylineNodes[i + 1].location[1])) {
                    // for leftBottom Corner to be visible, this leads to that leftTop must be visible

                    node.location[0] = bld.leftBottom[0];
                    node.location[1] = bld.leftBottom[1];
                    node.isVisible = true;
                    i++;
                    insertNode(node, i);
                    mBldNodesRange[1]++;
                    indexLeftBottom = i;

                    node.location[0] = bld.leftBottom[0];
                    node.location[1] = bldHeight;
                    node.isVisible = true;
                    i++;
                    insertNode(node, i);
                    mBldNodesRange[1]++;
                    indexLeftTop = i;
                } else { // leftBottom hidden --> LeftTop visible needs to create additional node

                    if ((bldHeight > mSkylineNodes[i].location[1]) && (bldHeight > mSkylineNodes[i + 1].location[1])) { // for leftTop Corner

                        // additional node
                        node.location[0] = bld.leftBottom[0];
                        node.location[1] = mSkylineNodes[i].location[1];
                        node.isVisible = true;
                        i++;
                        insertNode(node, i);
                        mBldNodesRange[1]++;

                        // adding leftTop
                        node.location[0] = bld.leftBottom[0];
                        node.location[1] = bldHeight;
                        node.isVisible = true;
                        i++;
                        insertNode(node, i);
                        mBldNodesRange[1]++;
                        indexLeftTop = i;
                    }
                }

                break;
            }
        }

        /******  Top side: Left --> Right to create additional nodes during visibility transition (crossing vertical lines) ******/
        for (; (i < mBldNodesRange[1]) && (mSkylineNodes[i].location[0] <= bldRight); i++) {

            if (mSkylineNodes[i].location[1] < bldHeight) { // invisible node to next

                mSkylineNodes[i].isVisible = false;

                // next node is visible
                if ((mSkylineNodes[i + 1].location[1] > bldHeight) && (mSkylineNodes[i].location[0] == mSkylineNodes[i + 1].location[0])) {
                    // create additional node
                    node.location[0] = mSkylineNodes[i].location[0];
                    node.location[1] = bldHeight;
                    node.isVisible = true;
                    i++;
                    insertNode(node, i);
                    mBldNodesRange[1]++;
                }
            } else { // visible node to next

                // next node is invisible
                if ((mSkylineNodes[i + 1].location[1] < bldHeight) && (mSkylineNodes[i].location[0] == mSkylineNodes[i + 1].location[0])) {
                    // create additional node
                    node.location[0] = mSkylineNodes[i].location[0];
                    node.location[1] = bldHeight;
                    node.isVisible = true;
                    i++;
                    insertNode(node, i);
                    mBldNodesRange[1]++;
                }
            }
        }

        /******  Right side: top --> bottom (crossing horizontal line) ******/
        for (i--; (i < mBldNodesRange[1]) && (mSkylineNodes[i].location[0] <= bldRight); i++) {
            if ((mSkylineNodes[i].location[0]) <= bldRight && (mSkylineNodes[i + 1].location[0]) > bldRight) {

                // add RightTop node
                if ((bldHeight >= mSkylineNodes[i].location[1]) && (bldHeight >= mSkylineNodes[i + 1].location[1])) {

                    node.location[0] = bldRight;
                    node.location[1] = bldHeight;
                    node.isVisible = true;
                    i++;
                    insertNode(node, i);
                    mBldNodesRange[1]++;
                    indexRightTop = i;

                    // add RightBottom node
                    if (bld.leftBottom[1] >= mSkylineNodes[i + 1].location[1]) {

                        node.location[0] = bldRight;
                        node.location[1] = bld.leftBottom[1];
                        node.isVisible = true;
                        i++;
                        insertNode(node, i);
                        mBldNodesRange[1]++;
                        indexRightBottom = i;
                    } else {
                        // create additional node between visible rightTop and invisible rightBottom
                        node.location[0] = bldRight;
                        node.location[1] = mSkylineNodes[i + 1].location[1];
                        node.isVisible = true;
                        i++;
                        insertNode(node, i);
                        mBldNodesRange[1]++;
                        i++;
                    }
                }

                break;
            }
        }

        // Update SkylineNodes: remove invalid/blocked Nodes
        for (auto it = mSkylineNodes.cbegin(); it != mSkylineNodes.cend(); ++it) {

            if (it->isVisible == false) {

                mSkylineNodes.erase(it);

                // need to account for the removed element
                --it;
            }
        }
    }

    // save skyline to file
    template <typename T>
    bool Skyline<T>::saveSkyline(const std::string& outFileName)
    {
        std::ofstream outputStream(outFileName.c_str(), std::ifstream::out);

        if (!outputStream) {
            throw std::runtime_error("Failed to open skyline file" + outFileName);
        }

        outputStream << "# Skyline: list of nodes"
                     << "\n"
                     << "# number of nodes: " << mSkylineNodes.size() << "\n"
                     << "# each node: index, [x, y], isVisible"
                     << "\n";

        int index = 0;
        for (const auto& node : mSkylineNodes) {

            outputStream << index << ","
                         << "[" << node.location[0] << ", " << node.location[1] << "]"
                         << ", " << node.isVisible << "\n";

            index++;
        }

        return true;
    }

    // initiate to generate actual code for the library
    Skyline<int> skyline;
    // initialize the member functions
    template void Skyline<int>::updateSkyline(const RecBuilding<int>& bld);
    template bool Skyline<int>::saveSkyline(const std::string& outFileName);
}
}
