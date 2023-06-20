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
        return {"status": True}
    elif(stat == 1): 
        return {"status": "wrong password"}
    else:
        return {"status": "user not found"}


# Deposit endpoint 
@api.get("/deposit")
async def deposit(name: str, password: str, amount: float):
    return {"success": g.deposit(name, password, amount)}


# Withdraw endpoint 
@api.get("/withdraw")
async def withdraw(name: str, password: str, amount: float):
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
async def getStocks():
    return {"stocks": get_stocks()}

# Endpoint to get stocks for user
@api.get("/get-my-stocks")
async def getMyStocks(name: str, password: str):
    return {"stocks": get_my_stocks(name, password)}


# Get all stocks
def get_stocks():
    s = g.get_stocks()
    stocks = []
    for stock in s:
        stock_obj = {
            "name": stock.getName(),
            "price": stock.getPrice(),
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
            "plot": base64.b64encode(generate_plot(stock.getPriceHistory())).decode('utf-8')
        }
        stocks.append(stock_obj)
    return stocks


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