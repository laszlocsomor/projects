def _impl(repository_ctx):
  print("start repo rule, sleep %d" % repository_ctx.attr.delay_sec)
  repository_ctx.execute(
      [repository_ctx.attr.sleep_bin,
       str(repository_ctx.attr.delay_sec),
       repository_ctx.attr.slept_txt],
      quiet = False)
  print("end repo rule")
  repository_ctx.file("BUILD", content = "exports_files(['BUILD'])")

slow_repo = repository_rule(
    implementation = _impl,
    attrs = {
        "delay_sec": attr.int(mandatory = True),
        "sleep_bin": attr.string(mandatory = True),
        "slept_txt": attr.string(mandatory = True),
    },
)
