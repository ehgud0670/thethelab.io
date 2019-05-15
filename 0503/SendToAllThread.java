import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.ArrayList;


public class SendToAllThread extends Thread {

    private Socket socket;
    private ArrayList<SendToAllThread> sendToAllThreadArrayList;

    SendToAllThread(Socket socket, ArrayList<SendToAllThread> sendToAllThreadArrayList){
        this.socket = socket;
        this.sendToAllThreadArrayList = sendToAllThreadArrayList;
        this.sendToAllThreadArrayList.add(this);
    }

    private void sendAllClients(byte[] buf, int len){
        for(SendToAllThread sendToAllThread: sendToAllThreadArrayList){
            OutputStream os;
            try {
                os = sendToAllThread.socket.getOutputStream();
                os.write(buf,0,len);
            } catch (IOException e) {
                e.printStackTrace();
            }

        }
    }

    @Override
    public void run() {
        try {

            while (true) {
                byte[] buf = new byte[512];
                InputStream is = socket.getInputStream();

                int len = is.read(buf);

                if(len == -1 ){
                    break;
                }
                sendAllClients(buf, len);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

