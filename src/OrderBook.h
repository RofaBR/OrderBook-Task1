#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdint>
#include <list>
#include <string>
#include <limits>

class Order {
public:
	int64_t user_id;
	int64_t amount;
	double price;
	bool side; //true for buy, false for sell

	Order(int64_t u_id, int64_t amt, double prc, bool sd)
		: user_id(u_id), amount(amt), price(prc), side(sd) {}
};

class BalanceChange {
private:
    int64_t user_id;
    int64_t value;
    std::string currency;
    char change_type;

public:
    BalanceChange(int64_t uid, const char& type, int64_t val, const std::string& cur)
        : user_id(uid), value(val), currency(cur), change_type(type) {}

    friend std::ostream& operator<<(std::ostream& os, const BalanceChange& bc);
};

class OrderBook {
private:
	std::list<Order> sell_orders;
	std::list<Order> buy_orders;

	static bool compareSellOrders(const Order& a, const Order& b);
	static bool compareBuyOrders(const Order& a, const Order& b);


	void matchOrders();

public:
	void addOrder(const Order& order);
};

Order createOrder();

#endif // ORDERBOOK_H