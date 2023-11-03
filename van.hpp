// van.hpp
#ifndef VAN_HPP
#define VAN_HPP

#include "stack.hpp"
#include "queue.hpp"
#include "label.hpp"
#include <string>
#include <chrono>
#include <thread>

class Van {
private:
    const std::string identifier;
    static const int MAX_CAPACITY = 24;
    Stack<Label> loadedStack;
    Queue<Label> deliveredQueue; // Member variable to store delivered labels
    bool full;

public:
    Van(const std::string& identifier);
    void loadVan(const Stack<Label>& stack);
    void leave();
    void deliver();
    void emptyVan();
    void returnToStation();
    bool isFull() const;
    void simulateDelivery(Stack<Label>& stack);
    void waitForSeconds(int seconds);
};

#endif
