import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

public class ReceiveThread extends Thread {

    private Socket socket;

    ReceiveThread(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
            InputStream is = socket.getInputStream();
            byte[] buf = new byte[512];

            while (true) {
                int len = is.read(buf);
                if(len == -1){
                    break;
                }
                System.out.println(new String(buf, 0, len));

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

