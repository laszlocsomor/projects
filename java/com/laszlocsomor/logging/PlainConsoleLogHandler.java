package com.laszlocsomor.logging;

import java.util.logging.ConsoleHandler;
import java.util.logging.Handler;
import java.util.logging.LogRecord;
import java.util.logging.Logger;

public final class PlainConsoleLogHandler extends ConsoleHandler {
  private static final Logger logger = Logger.getLogger(PlainConsoleLogHandler.class.getName());

  public static void setAsDefault() {
    for (Handler h : logger.getParent().getHandlers()) {
      if (h instanceof ConsoleHandler && !(h instanceof PlainConsoleLogHandler)) {
        logger.getParent().removeHandler(h);
        logger.getParent().addHandler(new PlainConsoleLogHandler());
        return;
      }
    }
  }

  @Override
  public void publish(LogRecord record) {
    System.out.printf(
        "%s %s [%s %s.%s] %s%n",
        record.getLevel().getName().charAt(0),
        record.getInstant(),
        Thread.currentThread().getName(),
        record.getSourceClassName(),
        record.getSourceMethodName(),
        record.getMessage());
  }
}
