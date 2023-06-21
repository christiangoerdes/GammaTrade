try: 
    import gammaTrade
except ImportError as e:
    print(f"The import caused the following exception: {e}")
    exit(1)

import os
import io
from gammaTrade import GammaTrade
from fastapi import FastAPI
import uvicorn
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse
import numpy as np
import matplotlib.pyplot as plt
from io import BytesIO
import tempfile
import base64

# Initialize marketplace
g = GammaTrade(100)

# Initialize API
api = FastAPI()

# Enable access from other devices
api.add_middleware(
    CORSMiddleware,
    allow_origins="*",
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


# Sign up endpoint 
@api.get("/sign-up")
async def signUp(name: str, password: str):
    return {"success": g.sign_up(name, password)}


# Login endpoint 
@api.get("/login")
async def login(name: str, password: str):
    stat = g.login(name, password)
    if(stat == 0):
        return {"status": "login successful"}
    elif(stat == 1): 
        return {"status": "wrong password"}
    else:
        return {"status": "user not found"}


# Deposit endpoint 
@api.get("/deposit")
async def deposit(name: str, password: str, amount: int):
    return {"success": g.deposit(name, password, amount)}


# Withdraw endpoint 
@api.get("/withdraw")
async def withdraw(name: str, password: str, amount: int):
    return {"success": g.withdraw(name, password, amount)}


# Endpoint to buy stocks
@api.get("/buy-stocks")
async def buyStocks(name: str, password: str, stock: str, quantity : int):
    return {"success": g.buy_stocks(name, password, stock, quantity)}


# Endpoint to sell stocks
@api.get("/sell-stocks")
async def sellStocks(name: str, password: str, stock: str, quantity : int):
    return {"success": g.sell_stocks(name, password, stock, quantity)}


# Endpoint to sell stocks
@api.get("/get-stocks")
async def getStocks(name: str, password: str):
    return {"stocks": get_stocks(name, password)}

# Endpoint to get balance for user
@api.get("/get-my-balance")
async def getMyBalance(name: str, password: str):
    return {"balance": g.get_balance_for(name, password)}

# Endpoint to get the total value of the stocks an account owns
@api.get("/get-my-stock-value")
async def getMyStockValue(name: str, password: str):
    return {"value": g.get_stock_sum_for(name, password)}

# Get all stocks
def get_all_stocks():
    s = g.get_stocks()
    stocks = []
    for stock in s:
        stock_obj = {
            "name": stock.getName(),
            "price": stock.getPrice(),
            "amount": 0,
            "plot": base64.b64encode(generate_plot(stock.getPriceHistory())).decode('utf-8')
        }
        stocks.append(stock_obj)
    return stocks

# Get the stocks for an account 
def get_my_stocks(name, password):
    s = g.get_stocks_for(name, password)
    stocks = []
    for stock in s:
        stock_obj = {
            "name": stock.getName(),
            "price": stock.getPrice(),
            "amount": g.get_account(name, password).get_stocks()[stock.getName()],
            "plot": base64.b64encode(generate_plot(stock.getPriceHistory())).decode('utf-8')
        }
        stocks.append(stock_obj)
    return stocks

# Get all stocks merged with the stocks for an account 
def get_stocks(name, password):
    all_stocks = get_all_stocks()
    my_stocks = get_my_stocks(name, password)
    merged_stocks = []
    for stock in my_stocks:
        merged_stock = {
            "name": stock["name"],
            "price": stock["price"],
            "amount": stock["amount"],
            "plot": stock["plot"]
        }
        merged_stocks.append(merged_stock)

    # Add stocks from all_stocks that aren't in my_stocks
    for stock in all_stocks:
        stock_names = [s["name"] for s in my_stocks]
        if stock["name"] not in stock_names:
            merged_stock = {
                "name": stock["name"],
                "price": stock["price"],
                "amount": 0,
                "plot": stock["plot"]
            }
            merged_stocks.append(merged_stock)
    return merged_stocks


# Get the current price history of all stocks
def get_history():
    history = []
    stocks = g.get_stocks()
    for stock in stocks: 
        history.append(stock.getPriceHistory())
    return history

# Generate a plot of the price history for each stock

def generate_plot(price_history):
    time = np.arange(len(price_history))
    plt.plot(time, price_history)
    plt.title('Price History')
    plt.xlabel('Time')
    plt.ylabel('Price')
    plt.grid(True)
    # Save the plot image to a byte stream
    image_stream = io.BytesIO()
    plt.savefig(image_stream, format='png')
    image_stream.seek(0)  # Set the stream position to the beginning
    plt.clf()  # Clear the figure for the next plot
    return image_stream.read()