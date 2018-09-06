import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {
  private static boolean CreateFile(Path p) {
    try (OutputStream os = Files.newOutputStream(p)) {
      os.write(new byte[] {'h', 'e', 'l', 'l', 'o', '\n'});
      return true;
    } catch (IOException e) {
      return false;
    }
  }

  public static void main(String[] args) throws IOException {
    if (args.length != 1) {
      System.out.println("usage: $0 <path-to-delete>");
      return;
    }

    Path path = FileSystems.getDefault().getPath(args[0]);

    System.out.printf("Opening \"%s\" with new FileInputStream%n", args[0]);
    try (FileInputStream is = new FileInputStream(path.toFile())) {
      System.out.println("  attempting to delete with Files.delete");
      try {
        Files.delete(path);
        System.out.println("  successfully deleted (this was not expected)");
        return;
      } catch (IOException e) {
        System.out.println("  cannot delete (this was expected)");
      }

      // Read from the file.
      byte[] data = new byte[4];
      int read = is.read(data);
      System.out.printf(
          "  read %d bytes from deleted file [%c, %c, %c, %c]%n",
          read, data[0], data[1], data[2], data[3]);
    }
    System.out.println("  closed FileInputStream");

    System.out.printf("Opening \"%s\" with Files.newInputStream%n", args[0]);
    try (InputStream is = Files.newInputStream(path)) {
      System.out.println("  attempting to delete with Files.delete");
      try {
        Files.delete(path);
        System.out.println("  successfully deleted");
      } catch (IOException e) {
        System.out.printf("  cannot delete: %s%n", e);
        return;
      }

      System.out.println("Read through open stream");
      byte[] data = new byte[4];
      int read = is.read(data);
      System.out.printf(
          "  read %d bytes from deleted file [%c, %c, %c, %c]%n",
          read, data[0], data[1], data[2], data[3]);

      System.out.println("Create a new file just to show that it's possible.");
      Path path2 = FileSystems.getDefault().getPath(args[0] + ".2");
      if (CreateFile(path2)) {
        System.out.printf("  successfully created new file \"%s\"%n", path2);
      } else {
        System.out.printf("  cannot create new file \"%s\"%n", path2);
        return;
      }

      System.out.println("Attempt to re-create the deleted file that we have a stream open for.");
      if (CreateFile(path)) {
        System.out.println("  successfully re-created deleted file while streams are open");
      } else {
        System.out.println("  cannot re-create deleted file while streams are open");
      }
    } catch (IOException e) {
      System.out.printf("  cannot open: %s%n", e);
    }

    System.out.println("Attempt to re-create the new deleted file, after streams are closed.");
    if (CreateFile(path)) {
      System.out.println("  successfully re-created file");
    } else {
      System.out.println("  cannot re-create file");
    }
  }
}
