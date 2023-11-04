#include <iostream>
#include <thread>
#include <chrono>
//#include <cstdlib>  // For system function
//#include <fstream>  // Include this for std::ofstream
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
    
    // Redirect the output to a file
    //std::ofstream outputFile("result.txt");

    // Save the current state of the std::cout buffer
    //std::streambuf* coutBuffer = std::cout.rdbuf();

    // Redirect the output to the file
    //std::cout.rdbuf(outputFile.rdbuf());
    
    
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
    
    Queue<Label> deliveredQueueSWCopy;
    Queue<Label> deliveredQueueNECopy;
    Queue<Label> deliveredQueueNWCopy;
    Queue<Label> deliveredQueueSECopy;

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
        //Stack<Label> stacktestSE1 = vanSE1.loadedStack;
         // Create a copy of the stack
        //Stack<Label> stackCopySE1 = stacktestSE1;
        //while (!stackCopySE1.empty()) {
            //Label label = stackCopySE1.top();
            //stackCopySE1.pop();
             //Process the label or do whatever you need with the copy
          //  std::cout << "|| " << label.getID() << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        //        }
        vanNW1.loadVan(stackNW);
        std::cout << "van NW1 is loading..." << std::endl;
        // Access the loadedStack of the Van
        //Stack<Label> stacktestNW1 = vanNW1.loadedStack;
         // Create a copy of the stack
        //Stack<Label> stackCopyNW1 = stacktestNW1;
        //while (!stackCopyNW1.empty()) {
            //Label label = stackCopyNW1.top();
            //stackCopyNW1.pop();
             //Process the label or do whatever you need with the copy
           // std::cout << "|| " << label.getID() << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
         //       }
        vanNE1.loadVan(stackNE);
        std::cout << "van NE1 is loading..." << std::endl;
        // Access the loadedStack of the Van
        //Stack<Label> stacktestNE1 = vanNE1.loadedStack;
         // Create a copy of the stack
        //Stack<Label> stackCopyNE1 = stacktestNE1;
        //while (!stackCopyNE1.empty()) {
            //Label label = stackCopyNE1.top();
            //stackCopyNE1.pop();
             //Process the label or do whatever you need with the copy
            //std::cout << "|| " << label.getID() << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
              //  }
        vanSW1.loadVan(stackSW);
        std::cout << "van SW1 is loading..." << std::endl;
        // Access the loadedStack of the Van
        //Stack<Label> stacktestSW1 = vanSW1.loadedStack;
         // Create a copy of the stack
        //Stack<Label> stackCopySW1 = stacktestSW1;
        //while (!stackCopySW1.empty()) {
            //Label label = stackCopySW1.top();
            //stackCopySW1.pop();
             //Process the label or do whatever you need with the copy
            //std::cout << "|| " << label.getID() << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
              //  }
        
    
        if (vanNE1.isFull()) {
            vanNE1Trips = vanNE1Trips + 1;
            std::cout << "Van NE1 is leaving..." << std::endl;
            vanNE1.leave();
            std::cout << "Van NE1 is deliverying..." << std::endl;
            vanNE1.deliver();
            std::cout << "Van NE1 is emptying the packets..." << std::endl;
            vanNE1.emptyVan();
            std::cout << "Van NE1 is returning back..." << std::endl;
            vanNE1.returnToStation();
        } 
            
        if (vanNW1.isFull()) {
            vanNW1Trips = vanNW1Trips + 1;
            std::cout << "Van NW1 is leaving..." << std::endl;
            vanNW1.leave();
            std::cout << "Van Nw1 is deliverying..." << std::endl;
            vanNW1.deliver();
            std::cout << "Van NW1 is emptying..." << std::endl;
            vanNW1.emptyVan();
            std::cout << "Van NW1 is returning back..." << std::endl;
            vanNW1.returnToStation();
        }  
        if (vanSE1.isFull()) {
            vanSE1Trips = vanSE1Trips + 1;
            std::cout << "Van SE1 is leaving..." << std::endl;
            vanSE1.leave();
            std::cout << "Van SE1 is deliverying..." << std::endl;
            vanSE1.deliver();
            std::cout << "Van SE1 is emtying..." << std::endl;
            vanSE1.emptyVan();
            std::cout << "Van SE1 is returning back..." << std::endl;
            vanSE1.returnToStation();
        }  
        if (vanSW1.isFull()) {
            vanSW1Trips = vanSW1Trips + 1;
            std::cout << "Van SW1 is leaving..." << std::endl;
            vanSW1.leave();
            std::cout << "Van SW1 is deliverying..." << std::endl;
            vanSW1.deliver();
            std::cout << "Van SW1 is emptying..." << std::endl;
            vanSW1.emptyVan();
            std::cout << "Van SW1 is returning back..." << std::endl;
            vanSW1.returnToStation();
        }
                

        
        std::cout << "\nFinal State:" << std::endl;
        std::cout <<  "The Central Station Queue: " << initial.size() << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Simulation round: " << mainCount << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "vanNE1 Trips: " << vanNE1Trips << std::endl;
        std::cout << "vanNW1 Trips: " << vanNW1Trips << std::endl;
        std::cout << "vanSE1 Trips: " << vanSE1Trips << std::endl;
        std::cout << "vanSW1 Trips: " << vanSW1Trips << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        // Labels delivered to  NE
        std::cout << "Labels delivered to NE\n" << std::endl;
        Queue<Label>& deliveredQueueNE = vanNE1.getDeliveredQueue();
        //create copy
        
        // present the copy 
        while (!deliveredQueueNE.empty()) {
            Label label = deliveredQueueNE.dequeue(); // Dequeue a label from the original queue
            std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
            deliveredQueueNECopy.enqueue(label);
            }
        std::cout << "-----------------------------" << std::endl;
        std::cout << "-----------------------------" << std::endl;    
        // Labels delivered to NW
        std::cout << "Labels delivered to NW\n" << std::endl;
        Queue<Label>& deliveredQueueNW = vanNW1.getDeliveredQueue();
        //create copy
        
        // present the copy 
        while (!deliveredQueueNW.empty()) {
            Label label = deliveredQueueNW.dequeue(); // Dequeue a label from the original queue
            std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
            deliveredQueueNWCopy.enqueue(label);
            }
        std::cout << "-----------------------------" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        // Labels delivered to SE
        std::cout << "Labels delivered to SE\n" << std::endl;
        Queue<Label>& deliveredQueueSE = vanSE1.getDeliveredQueue();
        //create copy
       
        // present the copy 
        while (!deliveredQueueSE.empty()) {
            Label label = deliveredQueueSE.dequeue(); // Dequeue a label from the original queue
            std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
            deliveredQueueSECopy.enqueue(label);
            }
        std::cout << "-----------------------------" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        // Labels delivered to SW
        std::cout << "Labels delivered to SW\n" << std::endl;
        Queue<Label>& deliveredQueueSW = vanSW1.getDeliveredQueue();
        //create copy
        
        // present the copy 
        while (!deliveredQueueSW.empty()) {
            Label label = deliveredQueueSW.dequeue(); // Dequeue a label from the original queue
            std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
            deliveredQueueSWCopy.enqueue(label);
            }

    }
    
    size_t size1 = stackSE.size();
    std::cout << "size of the Stack SE" << size1 << std::endl;
    
    size_t size2 = stackSW.size();
    std::cout << "size of the Stack SW" << size2 << std::endl;
    
    size_t size3 = stackNE.size();
    std::cout << "size of the Stack NE" << size3 << std::endl;
    
    size_t size4 = stackNW.size();
    std::cout << "size of the Stack NW" << size4 << std::endl;

    if (!stackSE.empty()){
        vanSE1.loadVan(stackSE);
        }
    
    std::cout << "van SE1 is loading..." << std::endl;
    
    if (!stackNW.empty()){
        vanNW1.loadVan(stackNW);
        }
    std::cout << "van NW1 is loading..." << std::endl;
    
    if (!stackNE.empty()){
        vanNE1.loadVan(stackNE);
    }
    std::cout << "van NE1 is loading..." << std::endl;
    
    if (!stackSW.empty()){
        vanSW1.loadVan(stackSW);
    }
    std::cout << "van SW1 is loading..." << std::endl;
    
    vanNE1Trips = vanNE1Trips + 1;
    std::cout << "Van NE1 is leaving..." << std::endl;
    vanNE1.leaveLast();
    std::cout << "Van NE1 is deliverying..." << std::endl;
    vanNE1.deliver();
    std::cout << "Van NE1 is emptying the packets..." << std::endl;
    vanNE1.emptyVan();
    std::cout << "Van NE1 is returning back..." << std::endl;
    vanNE1.returnToStation();
    
    vanNW1Trips = vanNW1Trips + 1;
    std::cout << "Van NW1 is leaving..." << std::endl;
    vanNW1.leaveLast();
    std::cout << "Van Nw1 is deliverying..." << std::endl;
    vanNW1.deliver();
    std::cout << "Van NW1 is emptying..." << std::endl;
    vanNW1.emptyVan();
    std::cout << "Van NW1 is returning back..." << std::endl;
    vanNW1.returnToStation();
    
    vanSE1Trips = vanSE1Trips + 1;
    std::cout << "Van SE1 is leaving..." << std::endl;
    vanSE1.leaveLast();
    std::cout << "Van SE1 is deliverying..." << std::endl;
    vanSE1.deliver();
    std::cout << "Van SE1 is emtying..." << std::endl;
    vanSE1.emptyVan();
    std::cout << "Van SE1 is returning back..." << std::endl;
    vanSE1.returnToStation();
    
    vanSW1Trips = vanSW1Trips + 1;
    std::cout << "Van SW1 is leaving..." << std::endl;
    vanSW1.leaveLast();
    std::cout << "Van SW1 is deliverying..." << std::endl;
    vanSW1.deliver();
    std::cout << "Van SW1 is emptying..." << std::endl;
    vanSW1.emptyVan();
    std::cout << "Van SW1 is returning back..." << std::endl;
    vanSW1.returnToStation();
    
    std::cout << "\nFinal State:" << std::endl;
    std::cout <<  "The Central Station Queue: " << initial.size() << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Simulation round: " << mainCount << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "vanNE1 Trips: " << vanNE1Trips << std::endl;
    std::cout << "vanNW1 Trips: " << vanNW1Trips << std::endl;
    std::cout << "vanSE1 Trips: " << vanSE1Trips << std::endl;
    std::cout << "vanSW1 Trips: " << vanSW1Trips << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
        // Labels delivered to  NE
    std::cout << "Labels delivered to NE\n" << std::endl;
    Queue<Label>& deliveredQueueNE = vanNE1.getDeliveredQueue();
        //create copy
    
        // present the copy 
    while (!deliveredQueueNE.empty()) {
        Label label = deliveredQueueNE.dequeue(); // Dequeue a label from the original queue
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        deliveredQueueNECopy.enqueue(label);
        }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;    
        // Labels delivered to NW
    std::cout << "Labels delivered to NW\n" << std::endl;
    Queue<Label>& deliveredQueueNW = vanNW1.getDeliveredQueue();
        //create copy
    
        // present the copy 
    while (!deliveredQueueNW.empty()) {
        Label label = deliveredQueueNW.dequeue(); // Dequeue a label from the original queue
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        deliveredQueueNWCopy.enqueue(label);
        }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
        // Labels delivered to SE
    std::cout << "Labels delivered to SE\n" << std::endl;
    Queue<Label>& deliveredQueueSE = vanSE1.getDeliveredQueue();
        //create copy
    
        // present the copy 
    while (!deliveredQueueSE.empty()) {
        Label label = deliveredQueueSE.dequeue(); // Dequeue a label from the original queue
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        deliveredQueueSECopy.enqueue(label);
        }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
        // Labels delivered to SW
    std::cout << "Labels delivered to SW\n" << std::endl;
    Queue<Label>& deliveredQueueSW = vanSW1.getDeliveredQueue();
        //create copy
    
        // present the copy 
    while (!deliveredQueueSW.empty()) {
        Label label = deliveredQueueSW.dequeue(); // Dequeue a label from the original queue
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        deliveredQueueSWCopy.enqueue(label);
        }
        
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "FINAL DELIVERED RESULT" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Labels delivered to NE\n" << std::endl;
    while (!deliveredQueueNECopy.empty()) {
        Label label = deliveredQueueNECopy.dequeue();
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Labels delivered to NW\n" << std::endl;
    while (!deliveredQueueNWCopy.empty()){
        Label label = deliveredQueueNWCopy.dequeue();
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Labels delivered to SE\n" << std::endl;
    while (!deliveredQueueSECopy.empty()){
        Label label = deliveredQueueSECopy.dequeue();
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        }
    
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Labels delivered to SW\n" << std::endl;
    while (!deliveredQueueSWCopy.empty()) {
        Label label = deliveredQueueSWCopy.dequeue();
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        }
    
    // Restore the std::cout buffer
    //std::cout.rdbuf(coutBuffer);

    // Close the output file
    //outputFile.close();
    return 0;
}
// Queue<Label>& deliveredQueue = van.getDeliveredQueue(); for the prints