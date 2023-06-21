try: 
    from gammaTrade import GammaTrade
except ImportError as e:
    print(f"The import caused the following exception: {e}")
    exit(1)

import os
import io
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


# Endpoint to get stocks
@api.get("/get-stocks")
async def getStocks(name: str, password: str):
    return {"stocks": get_stocks(name, password)}


# Endpoint to get stocks without login
@api.get("/get-stocks-logged-out")
async def getStocksLoggedOut():
    return {"stocks": get_all_stocks()}


# Endpoint to get one stock 
@api.get("/get-stock")
async def getStock(name: str, password: str, stock: str):
    return {"stock": get_stock(name, password, stock)}


# Endpoint to get one stock without login
@api.get("/get-stock-logged-out")
async def getStockLoggedOut(stock: str):
    return {"stock": get_stock_lo(stock)}


# Endpoint to get balance for user
@api.get("/get-my-balance")
async def getMyBalance(name: str, password: str):
    return {"balance": g.get_balance_for(name, password)}


# Endpoint to get the total value of the stocks an account owns
@api.get("/get-my-stock-value")
async def getMyStockValue(name: str, password: str):
    return {"value": g.get_stock_sum_for(name, password)}


# Get one stock 
def get_stock_lo(stock):
    s = g.get_stocks()
    for st in s:
        if st.getName() == stock:
            stock_obj = {
                "name": st.getName(),
                "price": st.getPrice(),
                "amount": 0,
                "plot": base64.b64encode(generate_plot(st.getPriceHistory())).decode('utf-8')
            }
            return stock_obj
    return None


# Get one stock 
def get_stock(name, password, stock):
    s = get_stocks(name, password)
    for st in s:
        if st["name"] == stock:
            return st
    return None

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


# Generate a plot of the price history for each stock
def generate_plot(price_history):
    
    y_min = np.min(price_history)
    y_max = np.max(price_history)

    # Step 2: Compute the range of the y-axis.
    y_range = 2 * (y_max - y_min)

    # Step 3: Set the limits of the y-axis.
    y_lower = y_min - y_range / 2
    y_upper = y_max + y_range / 2

    time = np.arange(-len(price_history)+1,1)
    # time = np.arange(len(price_history))
    plt.figure(facecolor= '#F5F5F5')
    plt.plot(time, price_history,  color='#062C30')
    plt.title('Price History')
    plt.xlabel('Time (in seconds)')
    plt.ylabel('Price in $')
    plt.ylim(y_lower, y_upper)  # Set the limits here
    plt.xlim(-len(time),5)
    plt.grid(True)
    # Save the plot image to a byte stream
    image_stream = io.BytesIO()
    plt.savefig(image_stream, format='png')
    image_stream.seek(0)  # Set the stream position to the beginning
    plt.clf()  # Clear the figure for the next plot
    return image_stream.read()