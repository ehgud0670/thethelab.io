public class SumThread extends Thread {
	private static int sum;
	@Override
		public void run() {
			sum();
		}

	private static void sum() {

		int local = 0;
		for (int i = 0; i < 2100000000 / Project.getThread_count(); i++) {
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
