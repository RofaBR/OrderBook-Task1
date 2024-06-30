#include "OrderBook.h"

bool OrderBook::compareSellOrders(const Order& a, const Order& b) { return a.price < b.price; }
bool OrderBook::compareBuyOrders(const Order& a, const Order& b) { return a.price > b.price; }

std::ostream& operator<<(std::ostream& os, const BalanceChange& bc) {
	os << "User ID: " << bc.user_id << ", Change: " << bc.change_type << bc.value << " " << bc.currency;
	return os;
}

void OrderBook::matchOrders() {
	while (!sell_orders.empty() && !buy_orders.empty() &&
		sell_orders.front().price <= buy_orders.front().price) {
		Order sell = sell_orders.front();
		Order buy = buy_orders.front();

		int64_t transaction_amount = std::min(sell.amount, buy.amount);
		double transaction_price = sell.price;

		std::cout << "User: " << sell.user_id << " sells " << transaction_amount
			<< " UAH at " << transaction_price << " USD/UAH to User "
			<< buy.user_id << std::endl;
		
		sell.amount -= transaction_amount;
		buy.amount -= transaction_amount;

		std::cout << BalanceChange(sell.user_id, '+',transaction_amount * transaction_price, "USD") << std::endl;
		std::cout << BalanceChange(sell.user_id, '-',transaction_amount, "UAH") << std::endl;
		std::cout << BalanceChange(buy.user_id, '-', transaction_amount * transaction_price, "USD") << std::endl;
		std::cout << BalanceChange(buy.user_id, '+',transaction_amount, "UAH") << std::endl;

		if (sell.amount == 0) {
			sell_orders.erase(sell_orders.begin());
		}
		else {
			sell_orders.front().amount = sell.amount;
		}

		if (buy.amount == 0) {
			buy_orders.erase(buy_orders.begin());
		}
		else {
			buy_orders.front().amount = buy.amount;
		}
	}
}

void OrderBook::addOrder(const Order& order) {
	if (order.side) { // buy order
		buy_orders.push_back(order);
		buy_orders.sort(compareBuyOrders);
	}
	else {	// sell order
		sell_orders.push_back(order);
		sell_orders.sort(compareSellOrders);
	}
	matchOrders();
}

Order createOrder() {
	int64_t user_id, amount;
	double price;
	std::string side_str;
	bool side;

	while (true) {
		try {
			std::cout << "Enter user ID: ";
			if (!(std::cin >> user_id)) throw std::invalid_argument("Invalid input. Please enter a valid integer for user ID.");

			std::cout << "Enter amount (UAH): ";
			if (!(std::cin >> amount)) throw std::invalid_argument("Invalid input. Please enter a valid integer for amount.");

			std::cout << "Enter price (USD per UAH): ";
			if (!(std::cin >> price)) throw std::invalid_argument("Invalid input. Please enter a valid number for price.");

			std::cout << "Enter side (buy/sell): ";
			std::cin >> side_str;
			if (side_str != "buy" && side_str != "sell") throw std::invalid_argument("Invalid input. Please enter 'buy' or 'sell'.");
			side = (side_str == "buy");

			break;
		}
		catch (const std::invalid_argument& e) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << e.what() << std::endl;
		}
	}

	return Order(user_id, amount, price, side);
}