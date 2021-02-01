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
  name = "color_function",
  hdrs = ["color_function.h"],
  deps = ["@aurora//:led_strip"],
)

cc_library(
  name = "repeated_led_effect",
  hdrs = ["repeated_led_effect.h"],
  deps = [":led_effect"]
)

cc_test(
  name = "repeated_led_effect_test",
  srcs = ["repeated_led_effect_test.cpp"],
  deps = [
    ":mock_led_effect",
    ":repeated_led_effect",
    "@googletest//:gtest",
  ]
)

cc_library(
  name = "mock_led_effect",
  hdrs = ["mock_led_effect.h"],
  deps = [
    ":led_effect",
    ":color_function",
    "@aurora//:led_strip",
  ],
  testonly = True
)

cc_library(
  name = "sequential_led_effect",
  hdrs = ["sequential_led_effect.h"],
  srcs = ["sequential_led_effect.cpp"],
  deps = [":led_effect"]
)

cc_test(
  name = "sequential_led_effect_test",
  srcs = ["sequential_led_effect_test.cpp"],
  deps = [
    ":sequential_led_effect",
    ":mock_led_effect",
    "@aurora//:led_strip",
    "@googletest//:gtest",
  ]
)

cc_library(
  name = "solid_led_effect",
  hdrs = ["solid_led_effect.h"],
  srcs = ["solid_led_effect.cpp"],
  deps = [
    ":led_effect",
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
    ":led_effect",
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
    ":led_effect",
    ":color_function",
    "@aurora//:led_strip",
  ]
)

cc_test(
    name = "interleaved_led_effect_test",
    srcs = ["interleaved_led_effect_test.cpp"],
    size = "small",
    deps = [
      ":interleaved_led_effect",
      ":mock_led_effect",
      "@googletest//:gtest",
      "@aurora//:led_strip",
      "@aurora//:mock_led_strip",
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

cc_library(
    name = "pulse_color_function",
    hdrs = ["pulse_color_function.h"],
    srcs = ["pulse_color_function.cpp"],
    deps = [
      ":color_function",
      "@aurora//:led_strip"
    ]
)

cc_test(
    name = "pulse_color_function_test",
    srcs = ["pulse_color_function_test.cpp"],
    size = "small",
    deps = [
      ":pulse_color_function",
      "@aurora//:led_strip",
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
    ":pulse_color_function",
    ":repeated_led_effect",
    ":sequential_led_effect",
    ":solid_led_effect",
    "@aurora//:led_strip",
    "@aurora//:neopixel_strip",
  ]
)
