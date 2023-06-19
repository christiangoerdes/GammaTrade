try: 
    import gammaTrade
except ImportError as e:
    print(f"The import caused the following exception: {e}")
    exit(1)

import os
from gammaTrade import GammaTrade
from fastapi import FastAPI
import uvicorn
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse

# initialize marketplace
g = GammaTrade(100)

# initialize API
api = FastAPI()

# Enable access from other devices
api.add_middleware(
    CORSMiddleware,
    allow_origins="*",
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)



# sign up endpoint 
@api.get("/sign-up")
async def signUp(name: str, password: str):
    return {"success": g.sign_up(name, password)}


# login endpoint 
@api.get("/login")
async def login(name: str, password: str):
    stat = g.login(name, password)
    if(stat == 0):
        return {"status": True}
    elif(stat == 1): 
        return {"status": "wrong password"}
    else:
        return {"status": "User not found"}


# deposit endpoint 
@api.get("/deposit")
async def deposit(name: str, password: str, amount: float):
    return {"success": g.deposit(name, password, amount)}


# withdraw endpoint 
@api.get("/withdraw")
async def withdraw(name: str, password: str, amount: float):
    return {"success": g.withdraw(name, password, amount)}


# endpoint to buy stocks
@api.get("/buy-stocks")
async def buyStocks(name: str, password: str, stock: str, quantity : int):
    return {"success": g.buy_stocks(name, password, stock, quantity)}


# endpoint to sell stocks
@api.get("/sell-stocks")
async def sellStocks(name: str, password: str, stock: str, quantity : int):
    return {"success": g.sell_stocks(name, password, stock, quantity)}


# endpoint to sell stocks
@api.get("/get-stocks")
async def getStocks():
    return {"stocks": get_stocks()}

@api.get("/get-my-stocks")
async def getMyStocks(name: str, password: str):
    return {"stocks": get_my_stocks(name, password)}


def get_stocks():
    s = g.get_stocks()
    stocks = []
    for stock in s:
        stock_obj = {
            "name": stock.getName(),
            "price": stock.getPrice()
        }
        stocks.append(stock_obj)
    return stocks

def get_my_stocks(name, password):
    s = g.get_stocks_for(name, password)
    stocks = []
    for stock in s:
        stock_obj = {
            "name": stock.getName(),
            "price": stock.getPrice()
        }
        stocks.append(stock_obj)
    return stocks




import numpy as np
import matplotlib.pyplot as plt
from io import BytesIO
import tempfile


def get_history():
    history = []
    stocks = g.get_stocks()
    for stock in stocks: 
        history.append(stock.getPriceHistory())
    return history

def generate_plot(price_history):
    time = np.arange(len(price_history))
    plt.plot(time, price_history)
    plt.title('Price History')
    plt.xlabel('Time')
    plt.ylabel('Value')
    plt.grid(True)

    print(time)
    # Save the plot image to a temporary file
    with tempfile.NamedTemporaryFile(suffix='.png', delete=False) as temp_file:
        plt.savefig(temp_file, format='png')
        temp_file_path = temp_file.name

    plt.clf()  # Clear the figure for the next plot
    return temp_file_path

@api.get("/foo")
async def foo():
    history = get_history()
    plots = []
    for price_history in history:
        plot_image = generate_plot(price_history)
        plots.append(plot_image)

    return [FileResponse(plot, media_type='image/png') for plot in plots][1]