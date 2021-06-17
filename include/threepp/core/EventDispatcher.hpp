// https://github.com/mrdoob/three.js/blob/r129/src/core/EventDispatcher.js

#ifndef THREEPP_EVENTDISPATCHER_HPP
#define THREEPP_EVENTDISPATCHER_HPP

#include <any>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace threepp {

    struct Event {
        const std::string type;
        const std::any &target;
    };

    using EventListener = std::function<void(Event)>;
    using EventListenerPtr = EventListener *;

    class EventDispatcher {

    public:
        void addEventListener(const std::string &type, EventListenerPtr listener) {
            listeners_[type].push_back(listener);
        }

        bool hasEventListener(const std::string &type, const EventListenerPtr &listener) {

            if (listeners_.count(type) == 0) return false;

            auto listenerArray = &listeners_.at(type);
            return std::find(listenerArray->begin(), listenerArray->end(), listener) != listenerArray->end();
        }

        void removeEventListener(const std::string &type, const EventListenerPtr &listener) {

            if (listeners_.count(type) == 0) return;

            auto listenerArray = &listeners_.at(type);
            auto find = std::find(listenerArray->begin(), listenerArray->end(), listener);
            if (find != listenerArray->end()) {
                listenerArray->erase(find);
            }
        }

        void dispatchEvent(const std::string &type, const std::any &target = {}) {

            if (listeners_.count(type)) {
                Event e{type, target};
                auto listeners = listeners_[type];
                for (auto &l : listeners) {
                    l->operator()(e);
                }
            }
        }

    private:
        std::unordered_map<std::string, std::vector<EventListenerPtr>> listeners_;
    };

}// namespace threepp

#endif//THREEPP_EVENTDISPATCHER_HPP