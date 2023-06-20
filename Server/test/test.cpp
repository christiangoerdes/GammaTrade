#include <gtest/gtest.h>
#include "../include/gammaTrade.hpp"
#include "../include/stock.hpp"
#include "../include/account.hpp"

TEST(GammaTradeTest, SignUp) {

    GammaTrade gamma(100); // initialize trading platform with timespan 100
    ASSERT_TRUE(gamma.sign_up("Trader1", "password1")); // create an account
    ASSERT_EQ(gamma.login("Trader1", "password2"), 1); // invalid credentials
    ASSERT_EQ(gamma.login("Trader1", "password1"), 0); // valid credentials
    ASSERT_TRUE(gamma.sign_up("Trader2", "password2")); // create second account+

}

TEST(GammaTradeTest, Trade) {

    GammaTrade gamma(100); // initialize trading platform with timespan 100
    
    gamma.sign_up("Trader1", "password1"); // create an account
    ASSERT_FALSE(gamma.buy_stocks("Trader1", "password1", "DogeCoin", 10)); // cannot buy stocks with no money deposited
    ASSERT_TRUE(gamma.deposit("Trader1", "password1", 10000));
    ASSERT_TRUE(gamma.buy_stocks("Trader1", "password1", "DogeCoin", 5)); // buy 5 DogeCoins (initially worth $1000)
    ASSERT_FALSE(gamma.sell_stocks("Trader1", "password1", "CrystalWater", 5)); // cannot sell stocks not in portfolio
    ASSERT_FALSE(gamma.sell_stocks("Trader1", "password1", "DogeCoin", 10)); // cannot sell more stocks than in portfolio
    ASSERT_TRUE(gamma.sell_stocks("Trader1", "password1", "DogeCoin", 5)); // can sell owned stocks
    ASSERT_FALSE(gamma.withdraw("Trader1", "password1", 100000)); // cannot withdraw more than is deposited
    ASSERT_TRUE(gamma.withdraw("Trader1", "password1", 5000)); // can withdraw some deposited money
    
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
