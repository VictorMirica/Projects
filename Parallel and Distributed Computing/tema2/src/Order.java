// Class representing an Order
public class Order {
	public String orderId;
	public int productNumbers;
	public int productsLeft;

	public Order(String orderId, int productNumbers, int productsLeft) {
		this.orderId = orderId;
		this.productNumbers = productNumbers;
		this.productsLeft = productsLeft;
	}
}
