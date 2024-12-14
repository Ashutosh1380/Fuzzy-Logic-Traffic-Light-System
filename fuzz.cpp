#include <iostream>
#include <algorithm>
using namespace std;

float low(float x) {
    return (x <= 10) ? 1 : (x >= 30) ? 0 : (30 - x) / 20.0;
}

float medium(float x) {
    if (x <= 10 || x >= 50)
        return 0;
    else if (x >= 20 && x <= 40)
        return 1;
    else if (x > 10 && x < 20)
        return (x - 10) / 10.0;
    else
        return (50 - x) / 10.0;
}

float high(float x) {
    return (x >= 50) ? 1 : (x <= 30) ? 0 : (x - 30) / 20.0;
}

float fogLow(float x) {
    return (x <= 10) ? 1 : (x >= 30) ? 0 : (30 - x) / 20.0;
}

float fogMedium(float x) {
    if (x <= 10 || x >= 50)
        return 0;
    else if (x >= 20 && x <= 40)
        return 1;
    else if (x > 10 && x < 20)
        return (x - 10) / 10.0;
    else
        return (50 - x) / 10.0;
}

float fogHigh(float x) {
    return (x >= 50) ? 1 : (x <= 30) ? 0 : (x - 30) / 20.0;
}

// Rule-Based Evaluation with Defuzzification
float greenLightDuration(float arrivingVehicles, float queuingVehicles, float fogLevel) {
    float arriveLow = low(arrivingVehicles);
    float arriveMedium = medium(arrivingVehicles);
    float arriveHigh = high(arrivingVehicles);

    float queueLow = low(queuingVehicles);
    float queueMedium = medium(queuingVehicles);
    float queueHigh = high(queuingVehicles);

    float fogLowMem = fogLow(fogLevel);
    float fogMediumMem = fogMedium(fogLevel);
    float fogHighMem = fogHigh(fogLevel);

    // Replace std::min({a, b, c}) with nested std::min calls
    float rule1 = std::min(std::min(arriveLow, queueLow), fogLowMem) * 10;  
    float rule2 = std::min(std::min(arriveMedium, queueMedium), fogMediumMem) * 30; 
    float rule3 = std::min(std::min(arriveHigh, queueHigh), fogHighMem) * 50; 

    float totalWeight = (std::min(std::min(arriveLow, queueLow), fogLowMem) +
                         std::min(std::min(arriveMedium, queueMedium), fogMediumMem) +
                         std::min(std::min(arriveHigh, queueHigh), fogHighMem));

    if (totalWeight == 0) return 0;

    float defuzzifiedOutput = (rule1 + rule2 + rule3) / totalWeight;

    return defuzzifiedOutput;
}

int main() {
    float arrivingVehicles, queuingVehicles, fogLevel;

    cout << "Enter arriving vehicle count: ";
    cin >> arrivingVehicles;

    cout << "Enter queuing vehicle count: ";
    cin >> queuingVehicles;

    cout << "Enter fog level (0-50): ";
    cin >> fogLevel;

    float greenDuration = greenLightDuration(arrivingVehicles, queuingVehicles, fogLevel);

    cout << "Suggested green light duration: " << greenDuration << " seconds" << endl;

    return 0;
}
