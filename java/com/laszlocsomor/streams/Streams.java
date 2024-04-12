package com.laszlocsomor.streams;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

public final class Streams {
  private Streams() {}

  /**
   * Reads a stream as UTF-8, returns at most the requested many characters, then closes the stream.
   *
   * <p>The method may read more characters from the stream than {@code maxLen}, partly because this
   * is how it decides whether to truncate the result.
   *
   * <p>If there were more characters in the input stream than {@code maxLen}, the method appends an
   * optional {@code truncationSuffix}.
   *
   * @param source the stream to read characters from; the method closes it
   * @param maxLen maximum number of characters to return; the number of bytes read may be greater,
   *     due to character encoding
   * @param chunkLen maximum number of characters to read at once
   * @param truncationSuffix optional; a suffix to append if there were more characters left in the
   *     input stream than {@code maxLen}
   * @return
   * @throws IOException
   * @throws IllegalArgumentException if {@code maxLen} or {@code chunkLen} are negative
   */
  public static String readStreamAsUtf8AndClose(
      InputStream source, int maxLen, int chunkLen, String truncationSuffix) throws IOException {
    if (maxLen < 0 || chunkLen < 0) {
      throw new IllegalArgumentException();
    }
    if (source == null || maxLen == 0) {
      return truncationSuffix == null ? "" : truncationSuffix;
    }

    final StringBuilder result = new StringBuilder();
    final char[] buffer = new char[Math.min(maxLen, chunkLen)];
    try (BufferedReader reader =
        new BufferedReader(new InputStreamReader(source, StandardCharsets.UTF_8))) {
      for (int totalLen = 0; totalLen <= maxLen; ) {
        int actualReadLen = reader.read(buffer, 0, buffer.length);
        if (actualReadLen == -1) {
          break;
        }
        if (actualReadLen > maxLen - totalLen) {
          result.append(buffer, 0, maxLen - totalLen);
          if (truncationSuffix != null) {
            result.append(truncationSuffix);
          }
          break;
        }
        result.append(buffer, 0, actualReadLen);
        totalLen += actualReadLen;
      }
    }
    return result.toString();
  }
}
