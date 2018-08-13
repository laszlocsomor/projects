public class Prof {
  private static final int ARRAY_SIZE = 50000000;
  private static final int RUNS = 10;

  public static void main(String[] args) {
    String[] a = new String[ARRAY_SIZE];
    System.out.println("Filling the array...");
    long start = System.currentTimeMillis();
    for (int i = 0; i < a.length; i++) {
      a[i] = new String(); // Integer.toString(i);
    }
    long end = System.currentTimeMillis();
    System.out.printf("Filling the array took %d ms%n", end - start);

    long[] results_loop = new long[RUNS];
    long[] results_iter = new long[RUNS];
    long[] results_stream = new long[RUNS];

    for (int i = 0; i < RUNS; i++) {
      long dummy = 0;
      System.out.printf("for-loop, run #%d%n", i);
      start = System.currentTimeMillis();
      for (int j = 0; j < a.length; j++) {
        dummy += a[j].length();
      }
      end = System.currentTimeMillis();
      results_loop[i] = end - start;

      dummy = 0;
      System.out.printf("iterator, run #%d%n", i);
      start = System.currentTimeMillis();
      for (String s : a) {
        dummy += s.length();
      }
      end = System.currentTimeMillis();
      results_iter[i] = end - start;

      dummy = 0;
      int dummy_arr[] = new int[] {0};
      System.out.printf("stream, run #%d%n", i);
      start = System.currentTimeMillis();
      java.util.Arrays.stream(a).forEach(s -> dummy_arr[0] += s.length());
      end = System.currentTimeMillis();
      results_stream[i] = end - start;
    }

    System.out.println("For-loop:");
    for (int i = 0; i < results_loop.length; i++) {
      System.out.printf("  %d ms%n", results_loop[i]);
    }

    System.out.println("Iterator:");
    for (int i = 0; i < results_iter.length; i++) {
      System.out.printf("  %d ms%n", results_iter[i]);
    }

    System.out.println("Stream forEach:");
    for (int i = 0; i < results_stream.length; i++) {
      System.out.printf("  %d ms%n", results_stream[i]);
    }
  }
}
