public class Project {
	private static int thread_count = 1;

	public static void main(String[] args) {
		if (args.length == 1) {
			thread_count = Integer.parseInt(args[0]);
		}
		Thread[] threads = new SumThread[thread_count];

  	long start = System.currentTimeMillis();
		//멀티 스레드 동작
		for (int i = 0; i < thread_count; i++) {
			threads[i] = new SumThread();
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

		System.out.println("sum: " + SumThread.getSum());
		long end = System.currentTimeMillis();
		System.out.println("time: " + (end - start)/1000.0);
	}

	static int getThread_count() {
		return thread_count;
	}
}
