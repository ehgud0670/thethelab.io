public class SumThread extends Thread {
	private static int sum;
	@Override
		public void run() {
			sum();
		}

	private static void sum() {

		int local = 0;
		for (int i = 0; i < 1000000000 / Project.getThreadCount(); i++) {
			++local;
		}
		synchronized (SumThread.class) {
			sum += local;
		}

	}

	static int getSum() {
		return sum;
	}
}
