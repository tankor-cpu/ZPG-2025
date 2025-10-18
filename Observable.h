#pragma once
#include <vector>
#include <algorithm>
#include "Observer.h"

class Observable {
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notifyObservers() {
        for (auto* obs : observers)
            obs->update();
    }

private:
    std::vector<Observer*> observers;
};
