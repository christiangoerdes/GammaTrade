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
g = GammaTrade(1)

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

def kursverlauf(tendenz, streuung, dt, start, anzahl):
    sqdt = np.sqrt(dt)
    kurs = np.zeros(anzahl)
    kurs[0] = start
    for i in range(anzahl - 1):
        Y = 2 * np.random.rand() - 1.0
        kurs[i + 1] = kurs[i] * (1 + tendenz * dt + streuung * sqdt * Y)
    return kurs

np.random.seed()

def generate_plots(objects):
    plots = []
    for i, obj in enumerate(objects):
        start = obj.get('start', 5.0 * (2 * np.random.rand() - 1.0))
        drift = obj.get('drift', 0.3 * (2 * np.random.rand() - 1.0))
        tendenz = obj.get('tendenz', drift)
        streuung = obj.get('sd', 0.8)
        dt = obj.get('dt', 0.001)
        anzahl = obj.get('anzahl', 1000)

        kurs = kursverlauf(tendenz=tendenz, streuung=streuung, dt=dt, start=start, anzahl=anzahl)
        plt.plot(kurs)
        plt.title(f'Object {i+1}')
        plt.xlabel('Time')
        plt.ylabel('Value')
        plt.grid(True)
        plot_path = f'object_{i+1}.png'
        plt.savefig(plot_path)
        plots.append(plot_path)
        plt.clf()  # Clear the figure for the next plot
    return plots

objects = [
    {'start': 2.0, 'drift': 0.5, 'tendenz': 0.5, 'sd': 0.6, 'dt': 0.001, 'anzahl': 1000},
    {'start': -1.0, 'drift': -0.3, 'tendenz': -0.2, 'sd': 0.7, 'dt': 0.001, 'anzahl': 1000},
    # Add more custom objects as needed
]

get_stock_details():
    

image_paths = generate_plots(objects)
print(image_paths)

@api.get("/foo")
async def foo():
    return [FileResponse(path) for path in image_paths][1]