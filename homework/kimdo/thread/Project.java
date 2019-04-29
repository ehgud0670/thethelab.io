public class Project {
	private static int threadCount = 1;

	public static void main(String[] args) {
		if (args.length == 1) {
			threadCount = Integer.parseInt(args[0]);
		}
		Thread[] threads = new SumThread[threadCount];

  	long start = System.currentTimeMillis();
		//멀티 스레드 동작
		for (int i = 0; i < threadCount; i++) {
			threads[i] = new SumThread();
			threads[i].start();
		}

		//메인에서 대기
		for (int i = 0; i < threadCount; i++) {
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

	static int getThreadCount() {
		return threadCount;
	}
}
