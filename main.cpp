#include <iostream>
#include "label.hpp"
#include "queue.hpp"
#include "stack.hpp"


int main() {
    // Create the initial queue with 3500 instances of Label
    Queue<Label> initial;
    for (int i = 0; i < 3500; ++i) {
        initial.enqueue(Label());
    }

    // Create separate stacks for each zone
    Stack<Label> stackSE;
    Stack<Label> stackSW;
    Stack<Label> stackNE;
    Stack<Label> stackNW;

// Push onto the zone-specific stacks
    while (!initial.empty()) {
        Label label = initial.dequeue();
        std::string packageID = label.getPackageID();
        // Determine the zone based on the last two characters of the Package ID
        std::string zoneCode = packageID.substr(packageID.size() - 2);
        if (zoneCode == "SE") {
            stackSE.push(label);
        } else if (zoneCode == "SW") {
            stackSW.push(label);
        } else if (zoneCode == "NE") {
            stackNE.push(label);
        } else if (zoneCode == "NW") {
            stackNW.push(label);
        }
    }

// You now have separate stacks for each zone: stackSE, stackSW, stackNE, stackNW
// You can perform operations on these stacks as needed.

// For example, to print the labels in stackNE:
    while (!stackNE.empty()) {
        Label label = stackNE.top();
        std::cout << "Destination: " << label.getDestination() << ", Package ID: " << label.getPackageID() << ", Client ID: " << label.getClientID() << std::endl;
        stackNE.pop();
        }
    return 0;
}


