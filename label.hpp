#ifndef LABEL_HPP
#define LABEL_HPP

#include <string>

struct GeoLocation {
    int degrees;
    int minutes;
    double seconds;
};

enum Zone { NE, NW, SW, SE };

class Label {
public:
    Label();
    std::string getDestination() const;
    std::string getPackageID() const;
    std::string getClientID() const;

private:
    GeoLocation latitude;
    GeoLocation longitude;
    Zone zone;
    int randomDigits;
    char randomChar;
    std::string randomDate;
    std::string clientID;

    int randomInt(int min, int max);
    char randomLetter();
    std::string generateRandomDate();
    int random3DigitNumber();
};

#endif
