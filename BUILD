cc_library(
    name = "tinyspa",
    hdrs = glob(["include/**/*.h"]),
    includes = ["include"],
    strip_include_prefix = "include",
)

cc_test(
    name = "tinyspa_unit_tests",
    srcs = glob([
        "test/**/*.cpp",
        "test/**/*.hpp",
    ]),
    deps = [
        ":tinyspa",
        "@catch2",
    ],
)
