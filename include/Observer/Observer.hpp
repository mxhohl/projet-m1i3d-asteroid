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
using KeyboardListener = Observer<KeyboardEventData>;

#endif // OBSERVER_HPP
