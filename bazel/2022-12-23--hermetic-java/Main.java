public class Main {
  // Sealed classes require Java 17
  public static abstract sealed class Foo permits Bar {
  }

  private static final class Bar extends Foo {
  }

	public static void main(String[] args) {
    // Switch expression requires Java 14 (or 12 / 13 with preview)
		var x = switch (args.length) {
			case 0 -> "no args";
			case 1 -> "one arg";
			default -> "many args";
		};
		System.out.println(x);
	}
}
