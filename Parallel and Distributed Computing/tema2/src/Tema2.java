import java.io.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

public class Tema2 {

	public static void main(String[] args) {
		// Get args
		String inputFolder = args[0];
		int P = Integer.parseInt(args[1]);

		// Get the readers and writers for the files
		File ordersFile = new File(inputFolder + "/orders.txt");
		File productsFile = new File(inputFolder + "/order_products.txt");
		BufferedReader ordersReader = null;
		BufferedWriter ordersWriter = null;
		BufferedWriter productsWriter = null;

		try {
			ordersReader = new BufferedReader(new FileReader(ordersFile));
			ordersWriter = new BufferedWriter(new FileWriter("orders_out.txt"));
			productsWriter = new BufferedWriter(new FileWriter("order_products_out.txt"));
		} catch (IOException e) {
			e.printStackTrace();
		}

		// Start executor service
		AtomicInteger inQueue = new AtomicInteger(0);
		ExecutorService tpe = Executors.newFixedThreadPool(P);
		for (int i = 0; i < P; i ++) {
			inQueue.incrementAndGet();
			tpe.submit(new OrdersThread(ordersReader, ordersWriter, productsWriter, productsFile, tpe, inQueue, null));
		}

		// Close readers and writers when all threads finish
		boolean finished = false;
		try {
			finished = tpe.awaitTermination(1, TimeUnit.MINUTES);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		if (finished) {

			try {
				if (ordersReader != null) {
					ordersReader.close();
				}
				if (ordersWriter != null) {
					ordersWriter.close();
				}
				if (productsWriter != null) {
					productsWriter.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}
}