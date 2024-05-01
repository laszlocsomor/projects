import com.laszlocsomor.logging.PlainConsoleLogHandler;
import io.grpc.ManagedChannel;
import io.grpc.netty.NettyChannelBuilder;
import io.grpc.stub.StreamObserver;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.logging.Logger;

public final class ClientMain {
  private static final Logger logger = Logger.getLogger(ClientMain.class.getName());

  static {
    PlainConsoleLogHandler.setAsDefault();
  }

  public static void main(String[] args) throws Exception {
    logger.info("start");

    ManagedChannel ch = NettyChannelBuilder.forAddress("127.0.0.1", 12345).usePlaintext().build();

    HelloRespObs observer = new HelloRespObs();
    HelloGrpc.newStub(ch)
        .sayHello(HelloProto.HelloRequest.newBuilder().setName("laszlo").build(), observer);
    observer.isDone.await();

    ch.shutdown();
    ch.awaitTermination(5, TimeUnit.SECONDS);
  }

  private static final class HelloRespObs implements StreamObserver<HelloProto.HelloResponse> {
    public final CountDownLatch isDone = new CountDownLatch(1);

    @Override
    public void onNext(HelloProto.HelloResponse value) {
      logger.info("onNext: " + value);
    }

    @Override
    public void onError(Throwable t) {
      logger.info("onError: " + t);
      isDone.countDown();
    }

    @Override
    public void onCompleted() {
      logger.info("onCompleted");
      isDone.countDown();
    }
  }
}
