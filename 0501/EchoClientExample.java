import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.Scanner;

public class EchoClientExample {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket();
            socket.connect(new InetSocketAddress("localhost", 5001));

            InputStream is = socket.getInputStream();
            OutputStream os = socket.getOutputStream();

            Scanner sc = new Scanner(System.in);

            while (true) {
                String str = sc.nextLine();
                os.write(str.getBytes());

                byte[] buf = new byte[512];
                int len = is.read(buf);
                if (len == -1) {
                    break;
                }

                System.out.println(new String(buf, 0, len));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
