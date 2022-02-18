load("@io_bazel_rules_docker//container:container.bzl", "container_image")

container_image(
    name = "my-image",
    base = "@debian-gcr//image",
    entrypoint = [
        "bash",
        "-c",
        "ls /data* ; cat /etc/*release",
    ],
    files = glob(["foo/**"]),
    # exec_properties is ignored, so we use --remote_default_exec_properties
)
