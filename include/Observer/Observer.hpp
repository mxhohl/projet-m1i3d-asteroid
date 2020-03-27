#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Renderer;
class KeyboardEventData;

template<class T>
class Observer {
public:
    virtual void update(T&) = 0;
};

using Updatable = Observer<double>;
using Renderable = Observer<Renderer>;
using KeyboardObserver = Observer<KeyboardEventData>;
using ScoreObserver = Observer<int>;

#endif // OBSERVER_HPP
