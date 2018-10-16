## Platform-independent `--workspace_status_command`

Demonstrate how to use `--workspace_status_command` in a platform-independent manner from
`tools/bazel.rc`, using a Python script.

Important points:

- the status script can be in a subdirectory, does not have to reside in the workspace root
- the `--workspace_status_command` uses "python" from the PATH
- the `--workspace_status_command` uses a workspace-relative path for the script

## Example

On Windows:

```
bazel build //:x
type bazel-genfiles\x.txt
```

On Linux:

```
bazel build //:x
cat bazel-genfiles/x.txt
```

The `STABLE_PY_BAR1` and `PY_FOO1` lines should show up in the output.
