try: 
    import GammaTrade
except ImportError as e:
    print(f"The import caused the following exception: {e}")
    exit(1)

import os
from fastapi import FastAPI
import uvicorn
from fastapi.middleware.cors import CORSMiddleware

# initialize marketplace
b = GammaTrade()

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

@api.post("/sign-up")
async def signUp(name: str, password: str):

@api.get("/login")
async def login(name: str, password: str):

@api.put("/deposit")
async def deposit(name: str, password: str):

@api.put("/withdraw")
async def withdraw(name: str, password: str):

@api.post("/add-item")
async def additem(name: str, password: str):


# Market section

@api.get("/market")
async def market():

@api.put("/sell")
async def sell(name: str, password: str):

@api.put("/buy")
async def buy(name: str, password: str):
