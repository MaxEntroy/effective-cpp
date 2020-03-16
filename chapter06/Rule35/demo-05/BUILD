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
    "under_attack_on_physical.cc",
    "under_attack_on_magic.cc",
    "game_character.cc"
  ],
  deps = []
)

cc_test(
  name = "under_attack_on_physical_test",
  srcs = [
    "under_attack_on_physical_test.cc"
  ],
  deps = [
    "//demo-05:main_lib"
  ]
)

cc_test(
  name = "under_attack_on_magic_test",
  srcs = [
    "under_attack_on_magic_test.cc"
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
