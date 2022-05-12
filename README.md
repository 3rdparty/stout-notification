[![status: archive](https://github.com/GIScience/badges/raw/master/status/archive.svg)](https://github.com/GIScience/badges#archive) [![No Maintenance Intended](http://unmaintained.tech/badge.svg)](http://unmaintained.tech/)

# DEPRECATED - migrated into [`3rdparty/stout`](https://github.com/3rdparty/stout).

# `stout::Notification`

Provides a simple mechanism to receive notifications as callbacks. This is in contrast to something like [`absl::Notification`](https://abseil.io/docs/cpp/guides/synchronization#notification) that blocks the calling thread which isn't productve in asynchronous environments where the current thread shouldn't be blocked (or creating a new thread is unnecessarily expensive).

> **Callbacks are executed in reverse order that they were added! This is an explicit design goal that can be relied on rather than treated as an implementation detail. It's intended to mimic the semantics of how destructors are called for allocations on the stack, i.e., in reverse order of what got constructed.**

## Usage

Watch the notification by calling `Watch()` and passing a callback:

```cpp
stout::Notification<std::string> notification;

notification.Watch([](const std::string& s) {
  // Invoked when 'Notification::Notify()' gets invoked.
});

notification.Notify("hello world");
```

Block the current thread (***bewarned***) for the notification:

```cpp
stout::Notification<std::string> notification;

// Thread 1:
auto s = notification.Wait();

// Thread 2:
notification.Notify("hello world");
```
