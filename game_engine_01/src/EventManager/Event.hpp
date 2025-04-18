#ifndef EVENT_HPP
#define EVENT_HPP

class Event {
public:
    Event() = default;
    virtual ~Event() = default;

    //virtual void execute() = 0;
    //virtual void undo() = 0;
    //virtual void redo() = 0;
};

#endif