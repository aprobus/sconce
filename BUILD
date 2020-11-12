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

ino(
  name = "sconce",
  srcs = ["sconce.ino"],
  deps = [
    ":button",
    ":solid_led_effect",
    "@neopixel//:neopixel",
    "@neopixel//:neopixel_wrapper",
  ]
)
