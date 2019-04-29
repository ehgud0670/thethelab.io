
import static java.lang.Thread.sleep;

public class ThreadLocalExample {

	public static void main(String[] args) {

		Thread[] thread = new RandomThread[3];
		for (int i = 0; i < 3; i++) {
			thread[i] = new RandomThread();
			thread[i].start();
		}
		for (int i = 0; i < 3; i++) {
			try {
				thread[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}


	}

}
