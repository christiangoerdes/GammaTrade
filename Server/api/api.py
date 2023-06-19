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

# initialize marketplace
b = GammaTrade(100)

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


# Accout section

# sign up endpoint 
@api.post("/sign-up")
async def signUp(name: str, password: str):
    return {

    }


# login endpoint 
@api.get("/login")
async def login(name: str, password: str):
    return {
        
    }


# deposit endpoint 
@api.put("/deposit")
async def deposit(name: str, password: str, amount: float):
    return {
        
    }


# withdraw endpoint 
@api.put("/withdraw")
async def withdraw(name: str, password: str, amount: float):
    return {
        
    }


# endpoint to add an item 
@api.post("/add-item")
async def additem(name: str, password: str, itemName: str, itemPrice : float):
    return {
        
    }


# Market section

# endpoint to get all items up for sale
@api.get("/market")
async def market():
    return {
        
    }


# endpoint to sell an item 
@api.put("/sell")
async def sell(name: str, password: str, itemName: str):
    return {
        
    }


# endpoint to buy an item 
@api.put("/buy")
async def buy(name: str, password: str, itemName: str):
    return {
        
    }