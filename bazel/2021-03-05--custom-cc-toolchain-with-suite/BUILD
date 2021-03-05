load("@bazel_tools//tools/cpp:unix_cc_toolchain_config.bzl", "cc_toolchain_config")

cc_binary(
    name = "hello",
    srcs = ["hello.cc"],
)

cc_toolchain_suite(
    name = "my-suite",
    toolchains = {
        "targetcpu": ":my_toolchain",
    },
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
