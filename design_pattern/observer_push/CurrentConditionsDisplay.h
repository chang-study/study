#ifndef CURRENT_CONDITIONS_DISPLAY_H
#define CURRENT_CONDITIONS_DISPLAY_H

#include "Observer.h"
#include "DisplayElement.h"
#include "Subject.h"
#include <iostream>

class CurrentConditionsDisplay : public Observer, DisplayElement {
    public:
        CurrentConditionsDisplay() = default;
        CurrentConditionsDisplay(Subject *wd) : weatherdata(wd) 
                                    { weatherdata->registerObserver(this); }
        void update(double t, double h, double p) override;
        void display() const override;
    private:
        double temperature = 0.0f;
        double humidity = 0.0f;
        Subject *weatherdata = nullptr;
};

inline
void
CurrentConditionsDisplay::update(double t, double h, double p) {
    temperature = t;
    humidity = h;
    display();
}

inline
void
CurrentConditionsDisplay::display() const {
    std::cout << "Current Conditions: " << temperature
            << "F degree and " << humidity << "% humidity\n";
}



#endif /* ifndef CURRENT_CONDITIONS_DISPLAY_H */