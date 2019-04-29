
public class RandomThread extends Thread {
	private static ThreadLocal<Integer> integerThreadLocal =
		new ThreadLocal<>();

	@Override
		public void run() {
			int local = (int) (Math.random() * 1000);
			integerThreadLocal.set(local);
			try {
				sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			System.out.println("Thread local: " + integerThreadLocal.get());

		}

}
