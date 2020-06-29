# `stout::Notification`

Provides a simple mechanism to receive notifications as callbacks. This is in contrast to something like [`absl::Notification`](https://abseil.io/docs/cpp/guides/synchronization#notification) that blocks the calling thread which isn't productve in asynchronous environments where the current thread shouldn't be blocked (or creating a new thread is unnecessarily expensive).

## Usage

Watch the notification by calling `Watch()` and passing a callback:

```cpp
stout::Notification<std::string> notification;

notification.Watch([](const std::string& s) {
  // Invoked when 'Notification::Notify()' gets invoked.
});

notification.Notify("hello world");
```