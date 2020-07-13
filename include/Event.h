//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_EVENT_H
#define EXPRESSIONEVALUATION_EVENT_H

class Event {
public:
    Event(int _numEvents, const struct epoll_event *_events) : numEvents(_numEvents), events(_events) {}
    int getNumEvents() const { return numEvents; }
    const struct epoll_event *getEvent() const { return events; }

private:
    int numEvents;
    const struct epoll_event *events;
};
#endif //EXPRESSIONEVALUATION_EVENT_H
