#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "stout/notification.h"

using std::string;

using stout::Notification;

using testing::_;
using testing::MockFunction;


TEST(NotificationTest, WatchBeforeNotify)
{
  Notification<string> notification;

  MockFunction<void(string)> mock;

  EXPECT_CALL(mock, Call(_))
    .Times(0);

  notification.Watch(mock.AsStdFunction());

  EXPECT_CALL(mock, Call("hello world"))
    .Times(1);

  notification.Notify("hello world");
}


TEST(NotificationTest, NotifyBeforeWatch)
{
  Notification<string> notification;

  notification.Notify("hello world");

  MockFunction<void(string)> mock;

  EXPECT_CALL(mock, Call("hello world"))
    .Times(1);

  notification.Watch(mock.AsStdFunction());
}
