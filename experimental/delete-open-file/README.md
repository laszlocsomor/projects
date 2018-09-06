## C++: deleting an open file with deletion sharing

Opening with `CreateFileA(..., FILE_SHARE_DELETE | ...)`.

Output from `main-cc`:
```
successfully deleted "foo.txt"
attributes: 0xffffffff
attributes(find): 0x00000020
ReadFile: read 4 bytes from deleted file [c, i, c, a]
press any key to continue . . .
```

## Java: deleting an open file

Opening first via `new FileInputStream` then via `Files.newInputStream`.

Output from `main-java`:
```
opening "foo.txt" with new FileInputStream
cannot delete "foo.txt" (this was expected)
read 4 bytes from deleted file [c, i, c, a]
opening "foo.txt" with Files.newInputStream
successfully deleted "foo.txt" (this was expected)
read 4 bytes from deleted file [c, i, c, a]
```
