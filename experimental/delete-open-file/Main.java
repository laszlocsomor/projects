import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {
  public static void main(String[] args) throws IOException {
    if (args.length != 1) {
      System.out.println("usage: $0 <path-to-delete>");
      return;
    }

    Path path = FileSystems.getDefault().getPath(args[0]);

    System.out.printf("opening \"%s\" with new FileInputStream%n", args[0]);
    try (FileInputStream is = new FileInputStream(path.toFile())) {
      try {
        Files.delete(path);
        System.out.printf("successfully deleted \"%s\" (this was not expected)%n", args[0]);
        return;
      } catch (IOException e) {
        System.out.printf("cannot delete \"%s\" (this was expected)%n", args[0]);
      }

      // Read from the file.
      byte[] data = new byte[4];
      int read = is.read(data);
      System.out.printf(
          "read %d bytes from deleted file [%c, %c, %c, %c]%n",
          read, data[0], data[1], data[2], data[3]);
    }

    System.out.printf("opening \"%s\" with Files.newInputStream%n", args[0]);
    try (InputStream is = Files.newInputStream(path)) {
      try {
        Files.delete(path);
        System.out.printf("successfully deleted \"%s\" (this was expected)%n", args[0]);
      } catch (IOException e) {
        System.out.printf("cannot delete \"%s\": %s%n", args[0], e);
        return;
      }

      // Read from the file.
      byte[] data = new byte[4];
      int read = is.read(data);
      System.out.printf(
          "read %d bytes from deleted file [%c, %c, %c, %c]%n",
          read, data[0], data[1], data[2], data[3]);
    } catch (IOException e) {
      System.out.printf("cannot open \"%s\": %s%n", args[0], e);
    }
  }

//  // Get attributes via GetFileAttributesA: returns INVALID_FILE_ATTRIBUTES.
//  DWORD attr = GetFileAttributesA(argv[1]);
//  printf("attributes: 0x%08x\n", attr);
//
//  // Get attributes via FindFirstFile: can retrieve the attributes.
//  WIN32_FIND_DATAA find;
//  HANDLE h2 = FindFirstFileA(argv[1], &find);
//  if (h2 != INVALID_HANDLE_VALUE) {
//    printf("attributes(find): 0x%08x\n", find.dwFileAttributes);
//    FindClose(h2);
//  }
//
//  // Read from the file.
//  DWORD data, read;
//  BOOL succ = ReadFile(h, &data, 4, &read, NULL);
//  if (succ != FALSE) {
//    printf("ReadFile: read %d bytes from deleted file [%c, %c, %c, %c]\n",
//        read, data & 0xff, (data >> 8) & 0xff, (data >> 16) & 0xff, (data >> 24) & 0xff);
//  } else {
//    printf("ReadFile: could not read from deleted file\n");
//  }
//  
//  printf("press any key to continue . . .\n");
//  ReadFile(GetStdHandle(STD_INPUT_HANDLE), &data, 1, &read, NULL);
//  CloseHandle(h);
//  return 0;
//  }
}
