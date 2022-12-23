# Bazel demo: hermetic JDK from repo

## What

Demonstrate using JDK19 in target- and host-configuration. The JDK comes from an archive on disk, in
the source tree (not checked in), and it's newer than any JDK that Bazel supports by default.

## Why

Wanted to build Java 13 code using a custom JDK 19 (instead of one Bazel downloads for me), and it
was difficult to figure out how to set up the toolchains, so here's the result of my efforts.

## How

1. Download a JDK 19 archive (e.g. the [Zulu JDK](https://www.azul.com/downloads/?package=jdk#download-openjdk))
1. Put the file in the workspace root
1. Update the `WORKSPACE` file: `my_jdk.src` is the archive's name, `my_jdk.strip_prefix` is the
   directory name inside the archive (to strip)
1. Build (see `BUILD` for more examples):

   ```sh
   bazel build //:x  --java_language_version=19 --java_runtime_version=19 --tool_java_language_version=19 --tool_java_runtime_version=19
   ```
