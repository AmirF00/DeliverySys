// van.cpp
#include "van.hpp"

Van::Van(const std::string& identifier) : identifier(identifier), full(false) {
    // Constructor implementation
}

void Van::loadVan(Stack<Label>& stack) {
    while (!stack.empty() && loadedStack.size() < MAX_CAPACITY) {
        loadedStack.push(stack.top());
        stack.pop();
    }
    
    if (loadedStack.size() == MAX_CAPACITY) {
        full = true;
        
    }
}


void Van::leave() {
    while (!full) {
        // Keep loading labels until the van is full
        waitForSeconds(0.1);
    }
}

void Van::leaveLast() {
        waitForSeconds(0.1);
}

void Van::deliver() {
    waitForSeconds(0.5); // Simulate delivery time
    emptyVan();
}

void Van::emptyVan() {
    while (!loadedStack.empty()) {
        deliveredQueue.enqueue(loadedStack.top());
        loadedStack.pop();
    }
    full = false; // The van is now empty
}

void Van::returnToStation() {
    waitForSeconds(0.5); // Simulate return time
}

bool Van::isFull() const {
    return full;
}

void Van::simulateDelivery(Stack<Label>& stack) {
    loadVan(stack); // Load the van with the provided stack
    leave(); // Leave when the van is full
    deliver(); // Deliver labels
    returnToStation(); // Return to the station
}

void Van::waitForSeconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}