#ifndef OBSERVER_HPP
#define OBSERVER_HPP

template<class T>
class Observer {
public:
    virtual void update(const T&) = 0;
};

#endif // OBSERVER_HPP
