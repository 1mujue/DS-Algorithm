#include <limits.h>
// Problem: given an int array prices, prices[i] represents
// the price of stock at i day. You can buy or sell the stock
// for price[i] at i day. You can do sell and buy in ONE day, as
// long as you make sure there is NO MORE THAN one stock in your hand.

// This is very "Greedy". If we buy stock at (i - 1) day
// and prices[i] > prices[i - 1], then of course we can sell at i day.
// Why? If prices[i + 1] > prices[i], then we can BUY STOCK AGAIN at 
// i day, and then sell it on (i + 1) day. It is same as we buy the stock
// at (i - 1) day and then sell it at (i + 1) day.

// Then what if prices[i] < prices[i - 1]? In this case, for any k > i, if 
// prices[k] - prices[i] is ALWAYS larger than prices[k] - prices[i - 1], 
// so we can SELL the stock at (i - 1) day(buy it and sell it at the same day)
// and buy stock at i day. Then when we want to sell it, we will get more 
// profit.
int maxProfit(int* prices, int pricesSize) {
    int ans = 0;
    int prev = INT_MAX;
    for(int i = 0; i < pricesSize; i++){
        int p = prices[i];
        if(p > prev){
            ans += p - prev;
        }
        prev = p;
    }
    return ans;
}