package(
    default_visibility = ["//:__pkg__"],
)

cc_library(
    name = "action",
    hdrs = ["action.h"],
    deps = [
        ":cmd",
        ":env",
        ":path",
    ],
)

cc_library(
    name = "cmd",
    hdrs = ["cmd.h"],
    deps = [":path"],
)

cc_library(
    name = "env",
    hdrs = ["env.h"],
)

cc_library(
    name = "error",
    hdrs = ["error.h"],
)

cc_library(
    name = "executor",
    hdrs = ["executor.h"],
    deps = [
        ":error",
        ":sched",
    ],
)

cc_library(
    name = "path",
    hdrs = ["path.h"],
    srcs = ["path.cc"],
)

cc_library(
    name = "sched",
    hdrs = ["sched.h"],
    deps = [":action"],
)

cc_library(
    name = "timetype",
    hdrs = ["timetype.h"],
)
