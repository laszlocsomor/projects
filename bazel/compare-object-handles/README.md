Demonstrate usage of [CompareObjectHandles](https://docs.microsoft.com/en-us/windows/desktop/api/handleapi/nf-handleapi-compareobjecthandles) and [GetFinalPathNameByHandleW](https://docs.microsoft.com/en-us/windows/desktop/api/FileAPI/nf-fileapi-getfinalpathnamebyhandlew).

`CompareObjectHandles` seems to be broken, it always reports that handles are different even for equal paths.
