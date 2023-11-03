#include <iostream>
#include <thread>
#include <chrono>
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

void wait() {
        std::this_thread::sleep_for(std::chrono::seconds(5));
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
    
    int vanNE1Trips = 0;
    int vanNW1Trips = 0;
    int vanSE1Trips = 0;
    int vanSW1Trips = 0;
    int vanNE2Trips = 0;
    int vanNW2Trips = 0;
    int vanSE2Trips = 0;
    int vanSW2Trips = 0;
    
    
    

    // Distribute labels into stacks in steps of 73 labels
    while (!initial.empty()) {
        wait();
        distributeLabels(initial, stackSE, stackSW, stackNE, stackNW);
        
        // Load the vans with stacks
        vanNE1.loadVan(stackNE);
        vanNW1.loadVan(stackNW);
        vanSE1.loadVan(stackSE);
        vanSW1.loadVan(stackSW);
        
    
        if (vanNE1.isFull()) {
            vanNE1Trips = vanNE1Trips + 1;
            vanNE2.loadVan(stackNE);
            if (vanNE2.isFull()) {
                vanNE2Trips = vanNE2Trips + 1;
                vanNE2.leave();
                vanNE2.deliver();
                vanNE2.emptyVan();
                vanNE2.returnToStation();
                }
            vanNE1.leave();
            vanNE1.deliver();
            vanNE1.emptyVan();
            vanNE1.returnToStation();
        } else if (vanNW1.isFull()) {
            vanNW1Trips = vanNW1Trips + 1;
            vanNW2.loadVan(stackNW);
            if (vanNW2.isFull()) {
                vanNW2Trips = vanNW2Trips + 1;
                vanNW2.leave();
                vanNW2.deliver();
                vanNW2.emptyVan();
                vanNW2.returnToStation();
                }
            vanNW1.leave();
            vanNW1.deliver();
            vanNW1.emptyVan();
            vanNW1.returnToStation();
        } else if (vanSE1.isFull()) {
            vanSE1Trips = vanSE1Trips + 1;
            vanSE2.loadVan(stackSE);
            if (vanSE2.isFull()) {
                vanSE2Trips = vanSE2Trips + 1;
                vanSE2.leave();
                vanSE2.deliver();
                vanSE2.emptyVan();
                vanSE2.returnToStation();
                }
            vanSE1.leave();
            vanSE1.deliver();
            vanSE1.emptyVan();
            vanSE1.returnToStation();
        } else if (vanSW1.isFull()) {
            vanSW1Trips = vanSW1Trips + 1;
            vanSW2.loadVan(stackSW);
            if (vanSW2.isFull()) {
                vanSW2Trips = vanSW2Trips + 1;
                vanSW2.leave();
                vanSW2.deliver();
                vanSW2.emptyVan();
                vanSW2.returnToStation();
                }
            vanSW1.leave();
            vanSW1.deliver();
            vanSW1.emptyVan();
            vanSW1.returnToStation();
        }
        
        std::cout << "\nFinal State:" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        

    }
    
    

    return 0;
}
// Queue<Label>& deliveredQueue = van.getDeliveredQueue(); for the prints