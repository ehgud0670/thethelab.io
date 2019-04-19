public class Project {
	private static long sum = 0;
	private static int thread_count = 1;

	public static void main(String[] args) {
		if (args.length == 1) {
			thread_count = Integer.parseInt(args[0]);
		}
		Thread[] threads = new AddThread[thread_count];

		long start = System.currentTimeMillis();
		//멀티 스레드 동작
		for (int i = 0; i < thread_count; i++) {
			threads[i] = new AddThread();
			threads[i].start();
		}

		//메인에서 대기
		for (int i = 0; i < thread_count; i++) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		System.out.println("sum: " + sum);
		long end = System.currentTimeMillis();
		System.out.println("time: " + (end-start)/1000.0);
	}

	static class AddThread extends Thread {

		@Override
			public void run() {
				add();
			}

		static void add() {

			long local = 0;
			for (long i = 0; i < 2100000000 / thread_count; i++) {
				++local;
			}
			synchronized (AddThread.class) {
				sum += local;
			}

		}
	}
}
