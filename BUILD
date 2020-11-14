load("ino.bzl", "ino")

cc_library(
  name = "button",
  hdrs = ["button.h"],
  srcs = ["button.cpp"]
)

cc_library(
  name = "led_effect",
  hdrs = ["led_effect.h"]
)

cc_library(
  name = "solid_led_effect",
  hdrs = ["solid_led_effect.h"],
  srcs = ["solid_led_effect.cpp"],
  deps = [
    ":led_effect",
    "@neopixel//:neopixel",
  ]
)

cc_test(
    name = "solid_led_effect_test",
    srcs = ["solid_led_effect_test.cpp"],
    size = "small",
    deps = [
      ":solid_led_effect",
      "@googletest//:gtest",
      "@neopixel//:neopixel",
      "@neopixel//:mock_neopixel",
    ]
)

cc_library(
  name = "moving_led_effect",
  hdrs = ["moving_led_effect.h"],
  srcs = ["moving_led_effect.cpp"],
  deps = [
    ":led_effect",
    "@neopixel//:neopixel",
  ]
)

cc_test(
    name = "moving_led_effect_test",
    srcs = ["moving_led_effect_test.cpp"],
    size = "small",
    deps = [
      ":moving_led_effect",
      "@googletest//:gtest",
      "@neopixel//:neopixel",
      "@neopixel//:mock_neopixel",
    ]
)

cc_library(
    name = "led_effect_driver",
    hdrs = ["led_effect_driver.h"],
    srcs = ["led_effect_driver.cpp"],
    deps = [":led_effect"]
)

cc_test(
    name = "led_effect_driver_test",
    srcs = ["led_effect_driver_test.cpp"],
    size = "small",
    deps = [
      ":led_effect_driver",
      ":led_effect",
      "@googletest//:gtest",
    ]
)

ino(
  name = "sconce",
  srcs = ["sconce.ino"],
  deps = [
    ":button",
    ":led_effect_driver",
    ":moving_led_effect",
    ":solid_led_effect",
    "@neopixel//:neopixel",
    "@neopixel//:neopixel_wrapper",
  ]
)
