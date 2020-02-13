# bazel build //:x --cpu=mycpu --compiler=mycomp --host_crosstool_top=//crosstool:toolchain --crosstool_top=//crosstool:toolchain

load("@bazel_tools//tools/cpp:cc_toolchain_config.bzl", "cc_toolchain_config")

cc_toolchain_suite(
  name = "toolchain",
  toolchains = {"mycpu|mycomp": ":cc-compiler-mycpu"},
  #"k8|compiler": "@local_config_cc//:cc-compiler-k8", "k8": "@local_config_cc//:cc-compiler-k8", "armeabi-v7a|compiler": "@local_config_cc//:cc-compiler-armeabi-v7a", "armeabi-v7a": "@local_config_cc//:cc-compiler-armeabi-v7a"},
)

cc_toolchain(
  name = "cc-compiler-mycpu",
  all_files = ":compiler_deps",
  compiler_files = ":compiler_deps",
  strip_files = ":empty",
  objcopy_files = ":empty",
#  as_files = "@local_config_cc//:compiler_deps",
#  ar_files = "@local_config_cc//:compiler_deps",
  linker_files = ":compiler_deps",
  dwp_files = ":empty",
#  supports_param_files = True,
#  toolchain_identifier = "local",
  toolchain_config = ":local",
)

filegroup(
  name = "empty",
  srcs = [],
)

filegroup(
  name = "compiler_deps",
#  srcs = ["@local_config_cc//:builtin_include_directory_paths"],
)

cc_toolchain_config(
  name = "local",
  cpu = "local",
#  compiler = "compiler",
#  toolchain_identifier = "local",
#  host_system_name = "local",
#  target_system_name = "local",
#  target_libc = "local",
#  abi_version = "local",
#  abi_libc_version = "local",
#  cxx_builtin_include_directories = ["/usr/lib/gcc/x86_64-linux-gnu/9/include", "/usr/local/include", "/usr/lib/gcc/x86_64-linux-gnu/9/include-fixed", "/usr/include/x86_64-linux-gnu", "/usr/include", "/usr/include/c++/9", "/usr/include/x86_64-linux-gnu/c++/9", "/usr/include/c++/9/backward"],
#  tool_paths = {"ar": "/usr/bin/ar", "ld": "/usr/bin/ld", "cpp": "/usr/bin/cpp", "gcc": "/usr/bin/gcc", "dwp": "/usr/bin/dwp", "gcov": "/usr/bin/gcov", "nm": "/usr/bin/nm", "objcopy": "/usr/bin/objcopy", "objdump": "/usr/bin/objdump", "strip": "/usr/bin/strip"},
#  compile_flags = ["-U_FORTIFY_SOURCE", "-fstack-protector", "-Wall", "-Wunused-but-set-parameter", "-Wno-free-nonheap-object", "-fno-omit-frame-pointer"],
#  dbg_compile_flags = ["-g"],
#  opt_compile_flags = ["-g0", "-O2", "-D_FORTIFY_SOURCE=1", "-DNDEBUG", "-ffunction-sections", "-fdata-sections"],
#  cxx_flags = ["-std=c++0x"],
#  link_flags = ["-fuse-ld=gold", "-Wl,-no-as-needed", "-Wl,-z,relro,-z,now", "-B/usr/bin", "-pass-exit-codes", "-lstdc++", "-lm"],
#  link_libs = [],
#  opt_link_flags = ["-Wl,--gc-sections"],
#  unfiltered_compile_flags = ["-fno-canonical-system-headers", "-Wno-builtin-macro-redefined", "-D__DATE__=\"redacted\"", "-D__TIMESTAMP__=\"redacted\"", "-D__TIME__=\"redacted\""],
#  coverage_compile_flags = ["--coverage"],
#  coverage_link_flags = ["--coverage"],
#  supports_start_end_lib = True,
)
