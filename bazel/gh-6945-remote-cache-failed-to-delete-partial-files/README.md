# Repro for https://github.com/bazelbuild/bazel/issues/6945

Repro for Bazel 0.20.0 failing to delete partically-downloaded files from a remote cache on Windows.

Instructions:

1.  git clone @buchgr's Bazel Remote Cache from https://github.com/buchgr/bazel-remote into another
    directory

1.  build and run the cache server:

        bazel --output_user_root=c:\tmp1 run //:bazel-remote -- --host localhost --port 8000 --dir c:\tmp2 --max_size 1

1.  keep this cmd.exe window open, we'll need it soon again

1.  in a new cmd.exe session, in *this* directory, build with remote caching enabled:

        bazel build //:x --remote_http_cache=http://localhost:8000 --spawn_strategy=standalone

1.  clean the local output tree, so the next build will try and download cached outputs

        bazel clean

1.  start the build again with `-s`; be ready to quickly switch to the other cmd.exe window

        bazel build //:x --remote_http_cache=http://localhost:8000 --spawn_strategy=standalone -s

1.  as soon as you see Bazel starting execution, kill the cache server process with Ctrl+C

1.  if you were lucky, you'll see the build fail like so:

        SUBCOMMAND: # //:big-file2 [action 'Executing genrule //:big-file2']
        cd C:/_bazel/v3e7w5ym/execroot/__main__
          SET PATH=C:\msys64\usr\bin;C:\msys64\bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Users\Administrator\AppData\Local\Microsoft\WindowsApps;C:\python_27_amd64\files\lib\site-packages\pywin32_system32;C:\python_27_amd64\files;C:\ProgramData\GooGet;C:\Program Files (x86)\Corp SSH Helper;C:\Windows\corpam;C:\ProgramData\Diagnose_me;C:\Program Files\Google\gNetStatus;C:\gnubby\bin;C:\Program Files\Puppet Labs\Puppet\bin;C:\Program Files\gWindows-Updater;C:\Program Files (x86)\Google\gWindowsInformation;C:\Windows\mrmagoo;C:\Program Files (x86)\Google\Cert Installer\;C:\Windows\ccmsetup;C:\Program Files (x86)\Bit9\Parity Agent;C:\Program Files (x86)\Google\Cert Installer;C:\Windows\CCM\;C:\Windows\System32\WindowsPowerShell\v1.0;C:\Program Files\PuTTY\;%GooGetRoot%;c:\src\bazel-releases\current;C:\vscode\bin;C:\Python37;
          C:/msys64/usr/bin/bash.exe -c source external/bazel_tools/tools/genrule/genrule-setup.sh; dd if=/dev/zero ibs=1000 count=200000 iflag=binary oflag=binary conv=notrunc of=bazel-out/x64_windows-fastbuild/bin/big-file-200MB.txt >&/dev/null
        SUBCOMMAND: # //:big-file1 [action 'Executing genrule //:big-file1']
        cd C:/_bazel/v3e7w5ym/execroot/__main__
          SET PATH=C:\msys64\usr\bin;C:\msys64\bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Users\Administrator\AppData\Local\Microsoft\WindowsApps;C:\python_27_amd64\files\lib\site-packages\pywin32_system32;C:\python_27_amd64\files;C:\ProgramData\GooGet;C:\Program Files (x86)\Corp SSH Helper;C:\Windows\corpam;C:\ProgramData\Diagnose_me;C:\Program Files\Google\gNetStatus;C:\gnubby\bin;C:\Program Files\Puppet Labs\Puppet\bin;C:\Program Files\gWindows-Updater;C:\Program Files (x86)\Google\gWindowsInformation;C:\Windows\mrmagoo;C:\Program Files (x86)\Google\Cert Installer\;C:\Windows\ccmsetup;C:\Program Files (x86)\Bit9\Parity Agent;C:\Program Files (x86)\Google\Cert Installer;C:\Windows\CCM\;C:\Windows\System32\WindowsPowerShell\v1.0;C:\Program Files\PuTTY\;%GooGetRoot%;c:\src\bazel-releases\current;C:\vscode\bin;C:\Python37;
          C:/msys64/usr/bin/bash.exe -c source external/bazel_tools/tools/genrule/genrule-setup.sh; dd if=/dev/zero ibs=1000 count=100000 iflag=binary oflag=binary conv=notrunc of=bazel-out/x64_windows-fastbuild/bin/big-file-100MB.txt >&/dev/null
        ERROR: C:/src/my-projects/bazel/gh-6945-remote-cache-failed-to-delete-partial-files/BUILD:11:1: Executing genrule //:big-file1 failed: Failed to delete output files after incomplete download. Cannot continue with local execution.: C:/_bazel/v3e7w5ym/execroot/__main__/bazel-out/x64_windows-fastbuild/bin/big-file-100MB.txt (Permission denied)
