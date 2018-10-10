cc_binary(
  name = "my-bin",
  srcs = ["main.cc"],
  deps = [":lib1"],
  data = [
    "//my-data:data1.txt",
    "@ext_c//:imported_dlls",
  ],
)

cc_library(
  name = "lib1",
  srcs = ["@ext_c//:imported_ccs"],
)
