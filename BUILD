load("ino.bzl", "ino")

cc_library(
  name = "button",
  hdrs = ["button.h"],
  srcs = ["button.cpp"]
)

ino(
  name = "sconce",
  srcs = ["sconce.ino"],
  deps = [
    ":button",
    "@neopixel//:neopixel",
    "@neopixel//:neopixel_wrapper",
  ]
)
