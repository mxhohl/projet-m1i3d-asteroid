#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observer.hpp"

#include <memory>
#include <vector>
#include <algorithm>

template<class T>
class Subject {
public:
    void addObserver(std::shared_ptr<Observer<T>> observer) {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<Observer<T>> observer) {
        auto res = std::find(observers.begin(), observers.end(), observer);
        while (res != observers.end()) {
            observers.erase(res);
        }
    }

protected:
    void notify(const T& data) {
        for (auto observer : observers) {
            observer->update(data);
        }
    }

private:
    std::vector<std::shared_ptr<Observer<T>>> observers;

};

#endif // SUBJECT_HPP
