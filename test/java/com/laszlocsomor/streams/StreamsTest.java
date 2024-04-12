package com.laszlocsomor.streams;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public final class StreamsTest {
  @Test
  public void invalidArgumentsThrow() throws Exception {
    // negative max length
    try (InputStream s = new ByteArrayInputStream("".getBytes(StandardCharsets.UTF_8))) {
      Assert.assertThrows(
          IllegalArgumentException.class, () -> Streams.readStreamAsUtf8AndClose(s, -1, 10, ""));
    }

    // negative chunk size
    try (InputStream s = new ByteArrayInputStream("".getBytes(StandardCharsets.UTF_8))) {
      Assert.assertThrows(
          IllegalArgumentException.class, () -> Streams.readStreamAsUtf8AndClose(s, 10, -1, ""));
    }
  }

  @Test
  public void nullOrEmptyStreamOrZeroLimitYieldsEmptyString() throws Exception {
    // test that truncation suffix is appended correctly
    Assert.assertEquals(Streams.readStreamAsUtf8AndClose(null, 0, 10, null), "");
    Assert.assertEquals(Streams.readStreamAsUtf8AndClose(null, 0, 10, "x"), "x");

    Assert.assertEquals(Streams.readStreamAsUtf8AndClose(null, 5, 10, "x"), "x");
    Assert.assertEquals(Streams.readStreamAsUtf8AndClose(null, 0, 10, "x"), "x");
  }

  @Test
  public void fullyReadsOrLimitsUsingSingleChunk() throws Exception {
    Assert.assertEquals(createStreamAndRead("abcdef", 4, 10, null), "abcd");
    Assert.assertEquals(createStreamAndRead("abcdef", 4, 10, "..."), "abcd...");

    Assert.assertEquals(createStreamAndRead("abcdef", 6, 6, "..."), "abcdef");
    Assert.assertEquals(createStreamAndRead("abcdef", 6, 10, "..."), "abcdef");
    Assert.assertEquals(createStreamAndRead("abcdef", 10, 6, "..."), "abcdef");
    Assert.assertEquals(createStreamAndRead("abcdef", 10, 10, "..."), "abcdef");
  }

  @Test
  public void fullyReadsOrLimitsUsingMultipleChunks() throws Exception {
    Assert.assertEquals(createStreamAndRead("abcdef", 5, 4, "..."), "abcde...");
    Assert.assertEquals(createStreamAndRead("abcdef", 5, 3, "..."), "abcde...");
    Assert.assertEquals(createStreamAndRead("abcdef", 5, 2, "..."), "abcde...");

    Assert.assertEquals(createStreamAndRead("abcdef", 6, 4, "..."), "abcdef");
    Assert.assertEquals(createStreamAndRead("abcdef", 6, 3, "..."), "abcdef");
    Assert.assertEquals(createStreamAndRead("abcdef", 6, 2, "..."), "abcdef");
  }

  private static String createStreamAndRead(
      String input, int maxLen, int chunkSize, String truncationSuffix) throws IOException {
    try (InputStream s = new ByteArrayInputStream(input.getBytes(StandardCharsets.UTF_8))) {
      return Streams.readStreamAsUtf8AndClose(s, maxLen, chunkSize, truncationSuffix);
    }
  }
}
