def _impl(ctx):
  ctx.actions.write(
      output = ctx.outputs.out,
      content = """
#include <stdio.h>

int main(void) {
  printf("world\\n");
  return 0;
}
""")
  return [DefaultInfo(files = depset(direct = [ctx.outputs.out]))]

gen_cc = rule(
    implementation = _impl,
    outputs = {"out": "%{name}-1.cc"},
)
