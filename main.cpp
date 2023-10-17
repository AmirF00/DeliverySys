#include <iostream>
#include "label.hpp"
#include "queue.hpp"

int main() {
    // Create the initial queue with 3500 instances of Label
    Queue<Label> initial;
    for (int i = 0; i < 3500; ++i) {
        initial.enqueue(Label());
    }

    // Create separate queues for each zone
    Queue<Label> queueSE;
    Queue<Label> queueSW;
    Queue<Label> queueNE;
    Queue<Label> queueNW;

    // Dequeue from the initial queue and enqueue into zone-specific queues
    while (!initial.empty()) {
        Label label = initial.dequeue();
        std::string packageID = label.getPackageID();
        // Determine the zone based on the last two characters of the Package ID
        std::string zoneCode = packageID.substr(packageID.size() - 2);
        if (zoneCode == "SE") {
            queueSE.enqueue(label);
        } else if (zoneCode == "SW") {
            queueSW.enqueue(label);
        } else if (zoneCode == "NE") {
            queueNE.enqueue(label);
        } else if (zoneCode == "NW") {
            queueNW.enqueue(label);
        }
    }

    // You now have separate queues for each zone: queueSE, queueSW, queueNE, queueNW
    // You can perform operations on these queues as needed.
    while (!queueNE.empty()) {
        Label label = queueNE.dequeue();
        std::cout << "Destination: " << label.getDestination() << ", Package ID: " << label.getPackageID() << ", Client ID: " << label.getClientID() << std::endl;
    }
    return 0;
}

