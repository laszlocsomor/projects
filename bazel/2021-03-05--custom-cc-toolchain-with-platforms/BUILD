load("@bazel_tools//tools/cpp:unix_cc_toolchain_config.bzl", "cc_toolchain_config")

cc_binary(
    name = "hello",
    srcs = ["hello.cc"],
)

platform(
    name = "target-platform",
    constraint_values = [
        ":targetcpu",
        ":targetos",
    ],
)

platform(
    name = "exec-platform",
    constraint_values = [
        ":execcpu",
        ":execos",
    ],
)

constraint_value(
    name = "targetcpu",
    constraint_setting = "@platforms//cpu",
)

constraint_value(
    name = "execcpu",
    constraint_setting = "@platforms//cpu",
)

constraint_value(
    name = "targetos",
    constraint_setting = "@platforms//os",
)

constraint_value(
    name = "execos",
    constraint_setting = "@platforms//os",
)

toolchain(
    name = "my-cc-toolchain",
    exec_compatible_with = [
        ":execcpu",
        ":execos",
    ],
    target_compatible_with = [
        ":targetcpu",
        ":targetos",
    ],
    toolchain = ":my_toolchain",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
)

cc_toolchain(
    name = "my_toolchain",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
    toolchain_config = ":my_cc_toolchain_config",
    toolchain_identifier = "my-cc-toolchain",
)

cc_toolchain_config(
    name = "my_cc_toolchain_config",
    abi_libc_version = "1",
    abi_version = "1",
    compiler = "mycompiler",
    cpu = "targetcpu",
    host_system_name = "hostos",
    target_libc = "1",
    target_system_name = "targetos",
    tool_paths = {
        "gcc": "/dummy/tool/path",
        "ld": "/dummy/tool/path",
        "ar": "/dummy/tool/path",
        "cpp": "/dummy/tool/path",
        "gcov": "/dummy/tool/path",
        "nm": "/dummy/tool/path",
        "objdump": "/dummy/tool/path",
        "strip": "/dummy/tool/path",
        "llvm-cov": "/dummy/tool/path",
    },
    toolchain_identifier = "my-cc-toolchain",
)

filegroup(name = "empty")
