# OrderBook Application

## Overview

This application simulates an order book for buying and selling UAH (Ukrainian Hryvnia) using USD (US Dollar). Users can place buy or sell orders, and the system matches orders based on price and amount.

## Project Structure

- `OrderBook.h` - Header file containing the declarations of the `Order`, `BalanceChange`, and `OrderBook` classes.
- `OrderBook.cpp` - File with the implementation of the `OrderBook` class methods.
- `main.cpp` - Main program file containing the `main` function.

## Efficiency

### Time Complexity

- **Adding an Order**: O(n), where n is the number of orders in the list. This is because each new order must be inserted into a sorted list.
- **Matching Orders**: O(n * m) in the worst case, where n is the number of buy orders and m is the number of sell orders. In practice, matching is usually more efficient as it primarily involves the top of each list.

### Why This Solution is Efficient

- Maintaining sorted lists for buy and sell orders allows for efficient matching.
- The sorted order ensures that the best prices are always at the front of the list, minimizing the number of comparisons needed during matching.

## How to Compile
1. Ensure you have `g++` compiler and `make` utility installed on your system.

2. Open your terminal or command prompt.

3. Navigate to the directory where your project files (`OrderBook.h`, `OrderBook.cpp`, `main.cpp`, and `Makefile`) are located.

4. Compile the project by running the following command:
   ```sh
   make

5. Once compilation is successful, run the executable by executing:
    ```sh
    cd build/
    ./orderbook.exe

Follow the prompts to input user IDs, amounts in UAH, prices in USD per UAH, and specify whether it's a buy or sell order.
The application will match buy and sell orders based on price and amount, displaying transaction details and balance changes.