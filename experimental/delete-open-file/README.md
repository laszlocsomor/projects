## C++: deleting an open file with deletion sharing

Opening with `CreateFileA(..., FILE_SHARE_DELETE | ...)`.

Output from `main-cc`:
```
successfully deleted "foo.txt"
attributes: 0xffffffff
attributes(find): 0x00000020
ReadFile: read 4 bytes from deleted file [c, i, c, a]
cannot re-open deleted file: 5
press any key to continue . . .
```

## Java: deleting an open file

Opening first via `new FileInputStream` then via `Files.newInputStream`.

Output from `main-java`:
```
Opening "foo.txt" with new FileInputStream
  attempting to delete with Files.delete
  cannot delete (this was expected)
  read 4 bytes from deleted file [c, i, c, a]
  closed FileInputStream
Opening "foo.txt" with Files.newInputStream
  attempting to delete with Files.delete
  successfully deleted
Read through open stream
  read 4 bytes from deleted file [c, i, c, a]
Create a new file just to show that it's possible.
  successfully created new file "foo.txt.2"
Attempt to re-create the deleted file that we have a stream open for.
  cannot re-create deleted file while streams are open
Attempt to re-create the new deleted file, after streams are closed.
  successfully re-created file
```
