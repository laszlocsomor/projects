1.  Download Bazel 0.18.0 and 0.21.0
1.  Check out https://github.com/bazelbuild/bazel-buildfarm/tree/ec7a05362d70b8074a29803d283f5ffeb2e33f28
1.  Build BuildFarm server + worker with Bazel 0.18.0
    
    ```
    bazel-0.18.0.exe build //src/main/java/build/buildfarm:buildfarm-worker //src/main/java/build/buildfarm:buildfarm-server
    ```

1.  Start the worker and the server in two separate consoles:

    ```
    <path>\<to>\buildfarm-server.exe <path>\<to>\server.config
    ```

    ```
    <path>\<to>\buildfarm-worker.exe <path>\<to>\server.config
    ```

    They don't print anything to stdout/stderr. This is fine.

1.  Build the targets in this workspace:

    ```
    bazel build --spawn_strategy=remote --remote_executor=localhost:8980 //:foo-bin
    ```

    The build fails with:

    ```
    ERROR: C:/src/my-projects/bazel/gh-7030-buildfarm-includecheck-fails/BUILD:1:1: undeclared inclusion(s) in rule '//:foo-bin':
    this rule is missing dependency declarations for the following files included by 'foo.cc':
      'D:/gh-7030/worker/default_memory_instance/operations/af056149-3fd3-4c74-9c8e-3f8880e89041/foo.h'
    Target //:foo-bin failed to build
    ```

1.  However, the build succeeds when built locally.
