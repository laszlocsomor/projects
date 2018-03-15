import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.FileSystem;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.attribute.FileTime;
import java.util.List;

public class Tool {
  public static void main(String[] args) throws Exception {
    if (args.length != 2) {
      throw new Exception("Usage: $0 <input> <output>");
    }
    FileSystem fs = FileSystems.getDefault();
    List<String> lines = Files.readAllLines(fs.getPath(args[0]), StandardCharsets.UTF_8);
    Path output = fs.getPath(args[1]);
    Files.write(output, lines, StandardCharsets.UTF_8);
    Files.setLastModifiedTime(output, FileTime.fromMillis(0L));
  }
}
