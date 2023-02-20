import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class OrdersThread extends MyFileIO implements Runnable {
	private final BufferedReader ordersReader;
	private final BufferedWriter ordersWriter;
	private final BufferedWriter productsWriter;
	private final File productsFile;
	private final ExecutorService tpe;
	private final AtomicInteger inQueue;
	private final Order order;

	public OrdersThread(BufferedReader ordersReader, BufferedWriter ordersWriter, BufferedWriter productsWriter, File productsFile, ExecutorService tpe, AtomicInteger inQueue, Order order) {
		this.ordersReader = ordersReader;
		this.ordersWriter = ordersWriter;
		this.productsWriter = productsWriter;
		this.productsFile = productsFile;
		this.tpe = tpe;
		this.inQueue = inQueue;
		this.order = order;
	}

	@Override
	public void run() {
		String st = getFileLine(ordersReader);
		// Read file line by line and call product threads for each
		while (st != null) {

			String[] order = st.split(",");
			String orderId = order[0];
			int productNumbers = Integer.parseInt(order[1]);

			// Insert a new task into the pool, for each new order
			inQueue.incrementAndGet();
			tpe.submit(new ProductThread(ordersReader, ordersWriter, productsWriter, productsFile, orderId, productNumbers, tpe, inQueue));

			// Get another order
			st = getFileLine(ordersReader);
		}

		int left = inQueue.decrementAndGet();
		if (left == 0) {
			tpe.shutdown();
		}

		// Order finished, write in orders_out
		if (order != null) {
			if (order.productNumbers != 0) {
				String orderOut = order.orderId + "," + order.productNumbers;
				if (order.productsLeft == 0)
					orderOut += ",shipped";
				writeFileLine(ordersWriter, orderOut);
			}
		}
	}
}
