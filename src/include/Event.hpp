// Inspired by https://github.com/janekb04/glfwpp

#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <list>

template<typename... Args>
class Event {
private:
  std::function<void(Args...)> _handler;

public:
  template<typename CallbackT>
  void setCallback(CallbackT&& callback_) {
    _handler = std::forward<CallbackT>(callback_);
  }
  void operator()(Args... args_) {
    if (_handler) {
      _handler(args_...);
    }
  }
};

#endif
