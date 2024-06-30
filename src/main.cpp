#include "OrderBook.h"

int main() {
	OrderBook orderBook;

	while (true) {
		Order order = createOrder();
		orderBook.addOrder(order);

		char cont;
		std::cout << "Do you want to add another order? (y/n): ";
		std::cin >> cont;
		if (cont == 'n') break;
	}
	return 0;
}