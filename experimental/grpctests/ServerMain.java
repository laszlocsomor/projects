import com.laszlocsomor.logging.PlainConsoleLogHandler;
import io.grpc.Server;
import io.grpc.netty.InternalProtocolNegotiators;
import io.grpc.netty.NettyServerBuilder;
import io.grpc.stub.StreamObserver;
import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.util.concurrent.TimeUnit;
import java.util.logging.Logger;

public final class ServerMain {
  private static final Logger logger = Logger.getLogger(ServerMain.class.getName());

  static {
    PlainConsoleLogHandler.setAsDefault();
  }

  public static void main(String[] args) throws InterruptedException, IOException {
    logger.info("start");

    Server server =
        NettyServerBuilder.forAddress(
                new InetSocketAddress(InetAddress.getByName("0.0.0.0"), 12345))
            .protocolNegotiator(InternalProtocolNegotiators.plaintext())
            .maxConcurrentCallsPerConnection(5)
            .maxInboundMessageSize(10_000)
            .maxInboundMetadataSize(10_000)
            .keepAliveTime(30, TimeUnit.SECONDS)
            .keepAliveTimeout(5, TimeUnit.SECONDS)
            .maxConnectionIdle(1, TimeUnit.MINUTES)
            .addService(new HelloImpl())
            .build();
    server.start();
    logger.info("listen on " + server.getPort());
    server.awaitTermination();
  }

  private static final class HelloImpl extends HelloGrpc.HelloImplBase {
    @Override
    public void sayHello(
        HelloProto.HelloRequest request,
        StreamObserver<HelloProto.HelloResponse> responseObserver) {
      logger.info("sayHello(" + request.getName() + ")");
      responseObserver.onNext(
          HelloProto.HelloResponse.newBuilder()
              .setMsg("Well hello " + request.getName() + " then! <3")
              .build());
      responseObserver.onCompleted();
    }
  }
}
