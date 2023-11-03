#include <iostream>
#include "label.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "van.hpp"


// Function to distribute labels into stacks in steps of 73 labels
void distributeLabels(Queue<Label>& initial, Stack<Label>& stackSE, Stack<Label>& stackSW, Stack<Label>& stackNE, Stack<Label>& stackNW) {
    for (int i = 0; i < 73 && !initial.empty(); ++i) {
        Label label = initial.dequeue();
        std::string packageID = label.getPackageID();
        std::string zoneCode = packageID.substr(packageID.size() - 2);

        // Determine the zone and push the label onto the appropriate stack
        if (zoneCode == "SE") {
            stackSE.push(label);
        } else if (zoneCode == "SW") {
            stackSW.push(label);
        } else if (zoneCode == "NE") {
            stackNE.push(label);
        } else if (zoneCode == "NW") {
            stackNW.push(label);
        }
        // Add conditions for other zones (SW, NE, NW) if needed
    }
}



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

    // Distribute labels into stacks in steps of 73 labels
    while (!initial.empty()) {
        distributeLabels(initial, stackSE, stackSW, stackNE, stackNW);
    }

    // Create a Van with an identifier
    Van van("Van1"); // Replace "Van1" with an appropriate identifier

    return 0;
}

