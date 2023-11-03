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
    
    // Create Vans with identifiers
    Van vanNE1("VanNE1");
    Van vanNW1("VanNW1");
    Van vanSE1("VanSE1");
    Van vanSW1("VanSW1");
    
    Van vanNE2("VanNE2");
    Van vanNW2("VanNW2");
    Van vanSE2("VanSE2");
    Van vanSW2("VanSW2");
    
    

    // Distribute labels into stacks in steps of 73 labels
    while (!initial.empty()) {
        distributeLabels(initial, stackSE, stackSW, stackNE, stackNW);
        
        // Load the vans with stacks
        vanNE1.loadVan(stackNE);
        vanNW1.loadVan(stackNW);
        vanSE1.loadVan(stackSE);
        vanSW1.loadVan(stackSW);
        
    
        if (vanNE1.isFull()) {
            vanNE2.loadVan(stackNE);
            if (vanNE2.isFull()) {
                vanNE2.leave();
                vanNE2.deliver();
                vanNE2.returnToStation();
                }
            vanNE1.leave();
            vanNE1.deliver();
            vanNE1.returnToStation();
        } else if (vanNW1.isFull()) {
            vanNW2.loadVan(stackNW);
            if (vanNW2.isFull()) {
                vanNW2.leave();
                vanNW2.deliver();
                vanNW2.returnToStation();
                }
            vanNW1.leave();
            vanNW1.deliver();
            vanNW1.returnToStation();
        } else if (vanSE1.isFull()) {
            vanSE2.loadVan(stackSE);
            if (vanSE2.isFull()) {
                vanSE2.leave();
                vanSE2.deliver();
                vanSE2.returnToStation();
                }
            vanSE1.leave();
            vanSE1.deliver();
            vanSE1.returnToStation();
        } else if (vanSW1.isFull()) {
            vanSW2.loadVan(stackSW);
            if (vanSW2.isFull()) {
                vanSW2.leave();
                vanSW2.deliver();
                vanSW2.returnToStation();
                }
            vanSW1.leave();
            vanSW1.deliver();
            vanSW1.returnToStation();
        }
        

    }

    

    return 0;
}

