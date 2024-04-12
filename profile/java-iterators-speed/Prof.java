import java.time.Duration;
import java.time.Instant;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public final class Prof {
  private static final int ARRAY_SIZE = 50_000_000;
  private static final int RUNS = 10;

  public static void main(String[] args) {
    String[] a = new String[ARRAY_SIZE];
    System.out.println("Filling the array...");
    Instant start = Instant.now();
    for (int i = 0; i < a.length; i++) {
      a[i] = new String(); // Integer.toString(i);
    }
    System.out.printf("Filling the array took %s%n", Duration.between(start, Instant.now()));

    Duration[] results_loop = new Duration[RUNS];
    Duration[] results_iter = new Duration[RUNS];
    Duration[] results_stream = new Duration[RUNS];

    for (int i = 0; i < RUNS; i++) {
      long dummy = 0;
      System.out.printf("for-loop, run #%d%n", i);
      start = Instant.now();
      for (int j = 0; j < a.length; j++) {
        dummy += a[j].length();
      }
      results_loop[i] = Duration.between(start, Instant.now());

      dummy = 0;
      System.out.printf("iterator, run #%d%n", i);
      start = Instant.now();
      for (String s : a) {
        dummy += s.length();
      }
      results_iter[i] = Duration.between(start, Instant.now());

      dummy = 0;
      int dummy_arr[] = new int[] {0};
      System.out.printf("stream, run #%d%n", i);
      start = Instant.now();
      java.util.Arrays.stream(a).forEach(s -> dummy_arr[0] += s.length());
      results_stream[i] = Duration.between(start, Instant.now());
    }

    System.out.println("\t\t| Min\t\t| Max\t\t| Median");
    System.out.printf(
        "For-loop:\t| %s\t| %s\t| %s%n",
        findMin(results_loop), findMax(results_loop), findMedian(results_loop));
    System.out.printf(
        "Iterator:\t| %s\t| %s\t| %s%n",
        findMin(results_iter), findMax(results_iter), findMedian(results_iter));
    System.out.printf(
        "Stream-ForEach:\t| %s\t| %s\t| %s%n",
        findMin(results_stream), findMax(results_stream), findMedian(results_stream));
  }

  private static Duration findMin(Duration... samples) {
    return Arrays.stream(samples).min(Duration::compareTo).get();
  }

  private static Duration findMax(Duration... samples) {
    return Arrays.stream(samples).max(Duration::compareTo).get();
  }

  private static Duration findMedian(Duration... samples) {
    List<Duration> result = Arrays.stream(samples).sorted().collect(Collectors.toList());
    return result.get(result.size() / 2);
  }
}
