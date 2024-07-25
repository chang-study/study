#ifndef DISPLAY_ELEMENT_H
#define DISPLAY_ELEMENT_H

class DisplayElement {
    public:
        virtual ~DisplayElement() = default;
        virtual void display() const = 0;
};

#endif /* ifndef DISPLAY_ELEMENT_H */