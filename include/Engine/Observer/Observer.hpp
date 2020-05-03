#ifndef OBSERVER_HPP
#define OBSERVER_HPP

namespace engine {

class Renderer;
struct KeyboardEventData;

template<class T>
class Observer {
public:
    virtual ~Observer() = default;

    virtual void update(T) = 0;
};

using Updatable = Observer<double>;
using Renderable = Observer<Renderer &>;
using KeyboardObserver = Observer<const KeyboardEventData &>;

}

#endif // OBSERVER_HPP
