load("ino.bzl", "ino")

cc_library(
  name = "button",
  hdrs = ["button.h"],
  srcs = ["button.cpp"]
)

cc_library(
  name = "solid_led_effect",
  hdrs = ["solid_led_effect.h"],
  srcs = ["solid_led_effect.cpp"],
  deps = [
    "@aurora//:led_effect",
    "@aurora//:led_strip",
  ]
)

cc_test(
    name = "solid_led_effect_test",
    srcs = ["solid_led_effect_test.cpp"],
    size = "small",
    deps = [
      ":solid_led_effect",
      "@googletest//:gtest",
      "@aurora//:led_strip",
      "@aurora//:mock_led_strip",
    ]
)

cc_library(
  name = "moving_led_effect",
  hdrs = ["moving_led_effect.h"],
  srcs = ["moving_led_effect.cpp"],
  deps = [
    "@aurora//:led_effect",
    "@aurora//:led_strip",
  ]
)

cc_test(
    name = "moving_led_effect_test",
    srcs = ["moving_led_effect_test.cpp"],
    size = "small",
    deps = [
      ":moving_led_effect",
      "@googletest//:gtest",
      "@aurora//:led_strip",
      "@aurora//:mock_led_strip",
    ]
)

cc_library(
  name = "interleaved_led_effect",
  hdrs = ["interleaved_led_effect.h"],
  srcs = ["interleaved_led_effect.cpp"],
  deps = [
    "@aurora//:color_function",
    "@aurora//:led_effect",
    "@aurora//:led_strip",
  ]
)

cc_test(
    name = "interleaved_led_effect_test",
    srcs = ["interleaved_led_effect_test.cpp"],
    size = "small",
    deps = [
      ":interleaved_led_effect",
      "@aurora//:led_strip",
      "@aurora//:mock_led_effect",
      "@aurora//:mock_led_strip",
      "@googletest//:gtest",
    ]
)

cc_library(
    name = "led_effect_driver",
    hdrs = ["led_effect_driver.h"],
    srcs = ["led_effect_driver.cpp"],
    deps = ["@aurora//:led_effect"]
)

cc_test(
    name = "led_effect_driver_test",
    srcs = ["led_effect_driver_test.cpp"],
    size = "small",
    deps = [
      ":led_effect_driver",
      "@aurora//:led_effect",
      "@googletest//:gtest",
    ]
)

ino(
  name = "sconce",
  srcs = ["sconce.ino"],
  deps = [
    ":button",
    ":interleaved_led_effect",
    ":led_effect_driver",
    ":moving_led_effect",
    ":solid_led_effect",
    "@aurora//:led_strip",
    "@aurora//:neopixel_strip",
    "@aurora//:pulse_color_function",
    "@aurora//:repeated_led_effect",
    "@aurora//:sequential_led_effect",
  ]
)
