cc_binary(
  name = "main",
  srcs = [
    "main.cc"
  ],
  deps = [
    "//demo-05:main_lib"
  ]
)

cc_library(
  name = "main_lib",
  srcs = [
    "game_character.cc",
    "under_attack_wrapper.cc"
  ],
  deps = []
)

cc_test(
  name = "under_attack_wrapper_test",
  srcs = [
    "under_attack_wrapper_test.cc"
  ],
  deps = [
    "//demo-05:main_lib"
  ]
)

cc_test(
  name = "warrior_test",
  srcs = [
    "warrior_test.cc",
  ],
  deps = [
    "//demo-05:main_lib"
  ]
)

cc_test(
  name = "warlock_test",
  srcs = [
    "warlock_test.cc",
  ],
  deps = [
    "//demo-05:main_lib"
  ]
)
