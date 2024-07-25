#ifndef STATISTICS_DISPLAY_H
#define STATISTICS_DISPLAY_H

#include "Observer.h"
#include "DisplayElement.h"
#include "Subject.h"
#include <iostream>

class StatisticsDisplay : public Observer, DisplayElement {
    public:
        StatisticsDisplay() = default;
        StatisticsDisplay(Subject *wd) : weatherdata(wd) 
                                { weatherdata->registerObserver(this); }
        void update(double t, double h, double p) override;
        void display() const override;
    private:
        double minTemp = 200.0f;
        double maxTemp = 0.0f;
        double tempSum = 0.0f;
        int numberOfReadings = 0;
        Subject *weatherdata = nullptr;
};

inline
void
StatisticsDisplay::update(double t, [[maybe_unused]] double h, [[maybe_unused]] double p) {
    tempSum += t;
    ++numberOfReadings;
    if (t < minTemp)
        minTemp = t;
    if (t > maxTemp)
        maxTemp = t;
    display();
}

inline
void
StatisticsDisplay::display() const {
    std::cout << "Avg/Max/Min Temperature = " <<
            tempSum / numberOfReadings << "/" << maxTemp << "/" << minTemp << '\n';
}

#endif /* ifndef STATISTICS_DISPLAY_H */