import java.io.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class ProductThread extends MyFileIO implements Runnable {//Callable<Integer> {
	private final BufferedReader ordersReader;
	private final BufferedWriter ordersWriter;
	private final BufferedWriter productsWriter;
	private final File productsFile;
	private final String orderId;
	private final int productNumbers;
	private final ExecutorService tpe;
	private final AtomicInteger inQueue;

	public ProductThread(BufferedReader ordersReader, BufferedWriter ordersWriter, BufferedWriter productsWriter, File productsFile, String orderId, int productNumbers, ExecutorService tpe, AtomicInteger inQueue) {
		this.ordersReader = ordersReader;
		this.ordersWriter = ordersWriter;
		this.productsWriter = productsWriter;
		this.productsFile = productsFile;
		this.orderId = orderId;
		this.productNumbers = productNumbers;
		this.tpe = tpe;
		this.inQueue = inQueue;
	}


	@Override
	public void run() {
		int productsLeft = productNumbers;
		// Search for the products of the current order
		BufferedReader productsReader = null;
		try {
			productsReader = new BufferedReader(new FileReader(productsFile));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		String orderProduct = null;
		if (productsReader != null) {
			orderProduct = getFileLine(productsReader);
		}

		while (orderProduct != null && productsLeft > 0) {
			String[] product = orderProduct.split(",");
			String oId = product[0];
			String productId = product[1];
			if (oId.equals(orderId)) {
				// Found a product for the current order
				productsLeft--;
				// Write to orders_products_out
				String productOut = oId + "," + productId + ",shipped";
				writeFileLine(productsWriter, productOut);
			}
			orderProduct = getFileLine(productsReader);
		}

		try {
			if (productsReader != null) {
				productsReader.close();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

		// Call the order threads, who should write in orders_out.txt that this order has been shipped or not
		Order order = new Order(orderId, productNumbers, productsLeft);
		tpe.submit(new OrdersThread(ordersReader, ordersWriter, productsWriter, productsFile, tpe, inQueue, order));
	}
}
