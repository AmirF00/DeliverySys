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
    
    
    int vanNE1Trips = 0;
    int vanNW1Trips = 0;
    int vanSE1Trips = 0;
    int vanSW1Trips = 0;
    
    int mainCount = 0;
    

    // Distribute labels into stacks in steps of 73 labels
    while (!initial.empty()) {
        //wait();
        mainCount = mainCount + 1;
        distributeLabels(initial, stackSE, stackSW, stackNE, stackNW);
        size_t size1 = stackSE.size();
        std::cout << "size of the Stack SE" << size1 << std::endl;
    
        size_t size2 = stackSW.size();
        std::cout << "size of the Stack SW" << size2 << std::endl;
    
        size_t size3 = stackNE.size();
        std::cout << "size of the Stack NE" << size3 << std::endl;
    
        size_t size4 = stackNW.size();
        std::cout << "size of the Stack NW" << size4 << std::endl;
        // Load the vans with stacks
        
        vanSE1.loadVan(stackSE);
        std::cout << "van SE1 is loading..." << std::endl;
        // Access the loadedStack of the Van
        Stack<Label> stacktestSE1 = vanSE1.loadedStack;
         // Create a copy of the stack
        Stack<Label> stackCopySE1 = stacktestSE1;
        while (!stackCopySE1.empty()) {
            Label label = stackCopySE1.top();
            stackCopySE1.pop();
             //Process the label or do whatever you need with the copy
            std::cout << "|| " << label.getID() << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
                }
        vanNW1.loadVan(stackNW);
        std::cout << "van NW1 is loading..." << std::endl;
        // Access the loadedStack of the Van
        Stack<Label> stacktestNW1 = vanNW1.loadedStack;
         // Create a copy of the stack
        Stack<Label> stackCopyNW1 = stacktestNW1;
        while (!stackCopyNW1.empty()) {
            Label label = stackCopyNW1.top();
            stackCopyNW1.pop();
             //Process the label or do whatever you need with the copy
            std::cout << "|| " << label.getID() << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
                }
        vanNE1.loadVan(stackNE);
        std::cout << "van NE1 is loading..." << std::endl;
        // Access the loadedStack of the Van
        Stack<Label> stacktestNE1 = vanNE1.loadedStack;
         // Create a copy of the stack
        Stack<Label> stackCopyNE1 = stacktestNE1;
        while (!stackCopyNE1.empty()) {
            Label label = stackCopyNE1.top();
            stackCopyNE1.pop();
             //Process the label or do whatever you need with the copy
            std::cout << "|| " << label.getID() << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
                }
        vanSW1.loadVan(stackSW);
        std::cout << "van SW1 is loading..." << std::endl;
        // Access the loadedStack of the Van
        Stack<Label> stacktestSW1 = vanSW1.loadedStack;
         // Create a copy of the stack
        Stack<Label> stackCopySW1 = stacktestSW1;
        while (!stackCopySW1.empty()) {
            Label label = stackCopySW1.top();
            stackCopySW1.pop();
             //Process the label or do whatever you need with the copy
            std::cout << "|| " << label.getID() << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
                }
        
    
        if (vanNE1.isFull()) {
            vanNE1Trips = vanNE1Trips + 1;
            vanNE1.leave();
            vanNE1.deliver();
            vanNE1.emptyVan();
            vanNE1.returnToStation();
        } 
            
        if (vanNW1.isFull()) {
            vanNW1Trips = vanNW1Trips + 1;
            vanNW1.leave();
            vanNW1.deliver();
            vanNW1.emptyVan();
            vanNW1.returnToStation();
        }  
        if (vanSE1.isFull()) {
            vanSE1Trips = vanSE1Trips + 1;
            vanSE1.leave();
            vanSE1.deliver();
            vanSE1.emptyVan();
            vanSE1.returnToStation();
        }  
        if (vanSW1.isFull()) {
            vanSW1Trips = vanSW1Trips + 1;
            vanSW1.leave();
            vanSW1.deliver();
            vanSW1.emptyVan();
            vanSW1.returnToStation();
        }
                

        
        std::cout << "\nFinal State:" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Simulation round: " << mainCount << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "vanNE1 Trips: " << vanNE1Trips << std::endl;
        std::cout << "vanNW1 Trips: " << vanNW1Trips << std::endl;
        std::cout << "vanSE1 Trips: " << vanSE1Trips << std::endl;
        std::cout << "vanSW1 Trips: " << vanSW1Trips << std::endl;
        std::cout << "-----------------------------" << std::endl;

    }

    
    
    

    
    

    return 0;
}
// Queue<Label>& deliveredQueue = van.getDeliveredQueue(); for the prints