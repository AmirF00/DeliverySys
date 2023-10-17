#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>

// Define the GeoLocation and Destination structs
struct GeoLocation {
    int degrees;
    int minutes;
    int seconds;
};

struct Destination {
    GeoLocation latitude;
    GeoLocation longitude;
};

// Function to generate a random integer within a specified range
int randomInt(int min, int max) {
    static std::mt19937 mt(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

// Function to generate random GeoLocation within the given edges
GeoLocation generateRandomGeoLocation(int minDegrees, int maxDegrees, int minMinutes, int maxMinutes, int minSeconds, int maxSeconds) {
    GeoLocation location;
    location.degrees = randomInt(minDegrees, maxDegrees);
    location.minutes = randomInt(minMinutes, maxMinutes);
    location.seconds = randomInt(minSeconds, maxSeconds);
    return location;
}

// Define the ZoneData struct based on GeoLocation
struct ZoneData {
    std::string name;
    GeoLocation minLatitude;
    GeoLocation maxLatitude;
    GeoLocation minLongitude;
    GeoLocation maxLongitude;
};

// Define the Zone enum
enum Zone {
    NE, // NorthEast
    NW, // NorthWest
    SW, // SouthWest
    SE  // SouthEast
};

// Function to categorize destinations into zones
std::vector<std::pair<Destination, Zone>> compareDestinationsToZones(const std::vector<Destination>& destinations, const std::vector<ZoneData>& zones) {
    std::vector<std::pair<Destination, Zone>> destinationZonePairs;

    for (const Destination& dest : destinations) {
        Zone zone = SE; // Default to SE zone

        // Check which zone the destination belongs to
        for (int i = 0; i < zones.size(); ++i) {
            const ZoneData& zoneData = zones[i];
            if (dest.latitude.degrees >= zoneData.minLatitude.degrees &&
                dest.latitude.degrees <= zoneData.maxLatitude.degrees &&
                dest.longitude.degrees >= zoneData.minLongitude.degrees &&
                dest.longitude.degrees <= zoneData.maxLongitude.degrees) {
                zone = static_cast<Zone>(i);
                break; // No need to check other zones
            }
        }

        destinationZonePairs.push_back(std::make_pair(dest, zone));
    }

    return destinationZonePairs;
}

// Function to generate 3500 random Destinations within the given edges
std::vector<Destination> generateRandomDestinations() {
    std::vector<Destination> destinations;
    const int minLatitudeDegrees = 40;
    const int maxLatitudeDegrees = 41;
    const int minLongitudeDegrees = -6;
    const int maxLongitudeDegrees = -5;

    for (int i = 0; i < 3500; ++i) {
        Destination destination;
        destination.latitude = generateRandomGeoLocation(minLatitudeDegrees, maxLatitudeDegrees, 0, 59, 0, 59);
        destination.longitude = generateRandomGeoLocation(minLongitudeDegrees, maxLongitudeDegrees, 0, 59, 0, 59);
        destinations.push_back(destination);
    }

    return destinations;
}


// Function to generate a random date in the "yyyymmdd" format
std::string randomDate() {
    int year = randomInt(2020, 2024);
    int month = randomInt(1, 12);
    int day = randomInt(1, 31); // Assuming all months have up to 31 days for simplicity
    char buffer[9];
    snprintf(buffer, sizeof(buffer), "%04d%02d%02d", year, month, day);
    return std::string(buffer);
}


// Function to generate 3500 random 3-digit numbers
std::vector<int> random3DigitNumbers(int count) {
    std::vector<int> numbers;
    for (int i = 0; i < count; ++i) {
        numbers.push_back(randomInt(100, 999)); // Generate random 3-digit numbers
    }
    return numbers;
}

// Function to generate a random letter
char randomLetter() {
    static std::mt19937 mt(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> dist(0, 25); // Generate a random index for A to Z (0 to 25)
    char randomChar = 'A' + dist(mt); // Convert the random index to a character from A to Z
    return randomChar;
}


int main() {
    std::vector<Destination> randomDestinations = generateRandomDestinations();

    std::vector<ZoneData> zones = {
        {"NE (NorthEast)", {40, 85, 4}, {41, 70, 9}, {5, 48, 3}, {5, 73, 37}},
        {"NW (NorthWest)", {40, 85, 4}, {41, 70, 9}, {5, 73, 37}, {5, 83, 73}},
        {"SW (SouthWest)", {40, 70, 8}, {40, 85, 4}, {5, 73, 37}, {5, 83, 73}},
        {"SE (SouthEast)", {40, 70, 8}, {40, 85, 4}, {5, 48, 3}, {5, 73, 37}}
    };

    std::vector<std::pair<Destination, Zone>> destinationZonePairs = compareDestinationsToZones(randomDestinations, zones);

    // Generate 3500 objects in the required format with destination coordinates and Client-ID
    std::vector<std::string> objects;
    for (int i = 0; i < 3500; ++i) {
        // Select a random destination and its corresponding zone
        const Destination& randomDestination = randomDestinations[i];
        Zone zone = SE; // Default to SE zone
        for (const auto& pair : destinationZonePairs) {
            if (pair.first.latitude.degrees == randomDestination.latitude.degrees &&
                pair.first.longitude.degrees == randomDestination.longitude.degrees) {
                zone = pair.second;
                break; // No need to check other destinations
            }
        }

        // Generate random date
        std::string randomDateStr = randomDate();

        // Generate random letter
        char randomChar = randomLetter();

        // Generate random 3-digit number
        int randomDigits = random3DigitNumbers(1)[0];

        // Generate a random Client-ID (8 random digits + 1 random letter)
        std::string clientId = std::to_string(randomInt(10000000, 99999999)) + randomLetter();

        // Create the object in the required format
        std::string object = 
            std::to_string(randomDestination.latitude.degrees) + " degree " +
            std::to_string(randomDestination.latitude.minutes) + " minutes " +
            std::to_string(randomDestination.latitude.seconds) + "." +
            std::to_string(randomInt(0, 99)) + " seconds, " +
            std::to_string(randomDestination.longitude.degrees) + " degree " +
            std::to_string(randomDestination.longitude.minutes) + " minutes " +
            std::to_string(randomDestination.longitude.seconds) + "." +
            std::to_string(randomInt(0, 99)) + " seconds, " +
            std::to_string(randomDigits) + randomChar + "-" + randomDateStr + "-" + (zone == NE ? "NE" : (zone == NW ? "NW" : (zone == SW ? "SW" : "SE"))) +
            ", " + clientId;
        objects.push_back(object);
    }

    // Print the objects
    for (const std::string& object : objects) {
        std::cout << object << std::endl;
    }

    return 0;
}





