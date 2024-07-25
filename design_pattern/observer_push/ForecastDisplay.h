#ifndef FORECAST_DISPLAY_H
#define FORECAST_DISPLAY_H

#include "Observer.h"
#include "DisplayElement.h"
#include "Subject.h"
#include <iostream>

class ForecastDisplay : public Observer, DisplayElement {
    public:
        ForecastDisplay() = default;
        ForecastDisplay(Subject *wd) : weatherdata(wd) 
                                { weatherdata->registerObserver(this); }
        void update(double t, double h, double p) override;
        void display() const override;
    private:
        double currentPressure = 29.92f;
        double prevPressure = 0.0f;
        Subject *weatherdata = nullptr;
};

inline
void
ForecastDisplay::update([[maybe_unused]] double t, [[maybe_unused]] double h, double p) {
    prevPressure = currentPressure;
    currentPressure = p;
    display();
}

inline
void
ForecastDisplay::display() const {
    if (currentPressure > prevPressure)
        std::cout << "Improving weather on the way!\n";
    else if (currentPressure == prevPressure)
        std::cout << "Forcast : More of the same\n"
    else if (currentPressure < prevPressure)
        std::cout << "Forcast : "
}

#endif /* ifndef FORECAST_DISPLAY_H */
