#ifndef PROJETPROGAVANCEE_KEYBOARDEVENTDATA_HPP
#define PROJETPROGAVANCEE_KEYBOARDEVENTDATA_HPP

#include <SDL.h>

namespace engine {

struct KeyboardEventData {
    enum Type {
        Press,
        Release
    };

    KeyboardEventData(Type type, SDL_Scancode scancode, SDL_Keycode keycode) :
            type(type), scancode(scancode),
            keycode(keycode) {}

    Type type;
    SDL_Scancode scancode;
    SDL_Keycode keycode;
};

}

#endif //PROJETPROGAVANCEE_KEYBOARDEVENTDATA_HPP
