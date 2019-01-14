Contents:

```
2019-01-14  15:28                66 BUILD
2019-01-14  15:39    <SYMLINKD>     dir.dangl [hello]
2019-01-14  14:33    <DIR>          examples
2019-01-14  15:39    <SYMLINK>      file.dangl [hello]
2019-01-14  15:25    <SYMLINKD>     foo.dir [examples\py_native]
2019-01-14  15:25    <SYMLINKD>     foo.dir.bad [examples\py_native\bin.py]
2019-01-14  14:35    <SYMLINK>      foo.sym [examples\py_native\bin.py]
2019-01-14  15:26    <SYMLINK>      foo.sym.bad [examples\py_native]
2019-01-14  15:48    <JUNCTION>     junc [D:\src\tmp\examples]
2019-01-14  15:38    <JUNCTION>     junc.dangl [D:\src\tmp\hello]
2019-01-14  15:49    <JUNCTION>     junc.file [D:\src\tmp\BUILD]
```

CreateFileW and attributes:

- open1: CreateFileW with `FILE_FLAG_BACKUP_SEMANTICS` (follows reparse points)
- open2: CreateFileW with `FILE_ATTRIBUTE_NORMAL`

```
\\?\D:\src\tmp\BUILD (regular file)
  open1: succeeded, attr: 0x00000020, info.attr: 0x00000020, is_dir: 0
  open2: succeeded, attr: 0x00000020, info.attr: 0x00000020, is_dir: 0
\\?\D:\src\tmp\examples (directory)
  open1: succeeded, attr: 0x00000010, info.attr: 0x00000010, is_dir: 1
  open2: failed, error: 5
\\?\D:\src\tmp\junc (junction)
  open1: succeeded, attr: 0x00000410, info.attr: 0x00000010, is_dir: 1
  open2: failed, error: 5
\\?\D:\src\tmp\foo.sym (file symlink)
  open1: succeeded, attr: 0x00000420, info.attr: 0x00000020, is_dir: 0
  open2: succeeded, attr: 0x00000420, info.attr: 0x00000020, is_dir: 0
\\?\D:\src\tmp\foo.dir (directory symlink)
  open1: succeeded, attr: 0x00000410, info.attr: 0x00000010, is_dir: 1
  open2: failed, error: 5
\\?\D:\src\tmp\foo.sym.bad (file symlink pointing to directory)
  open1: succeeded, attr: 0x00000420, info.attr: 0x00000010, is_dir: 1
  open2: failed, error: 5
\\?\D:\src\tmp\foo.dir.bad (directory symlink pointing to file)
  open1: succeeded, attr: 0x00000410, info.attr: 0x00000020, is_dir: 0
  open2: failed, error: 5
\\?\D:\src\tmp\junc.dangl (dangling junction)
  open1: failed, error: 2
  open2: failed, error: 5
\\?\D:\src\tmp\file.dangl (dangling file symlink)
  open1: failed, error: 2
  open2: failed, error: 2
\\?\D:\src\tmp\dir.dangl (dangling directory symlink)
  open1: failed, error: 2
  open2: failed, error: 5
\\?\D:\src\tmp\junc.file (junction pointing to file)
  open1: succeeded, attr: 0x00000410, info.attr: 0x00000020, is_dir: 0
  open2: failed, error: 5
```