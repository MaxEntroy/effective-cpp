cc_binary(
  name = "main",
  srcs = [
    "main.cc"
  ],
  deps = [
    "//demo-03:main_lib"
  ]
)

cc_library(
  name = "main_lib",
  srcs = [
    "game_character.cc",
  ],
  deps = []
)

cc_test(
  name = "warrior_test",
  srcs = [
    "warrior_test.cc",
  ],
  deps = [
    "//demo-03:main_lib"
  ]
)

cc_test(
  name = "warlock_test",
  srcs = [
    "warlock_test.cc",
  ],
  deps = [
    "//demo-03:main_lib"
  ]
)
