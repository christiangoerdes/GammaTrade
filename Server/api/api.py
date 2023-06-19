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

@api.get("/login")

@api.put("/deposit")

@api.put("/withdraw")

@api.post("/add-item")


# Market section

@api.get("/market")

@api.put("/sell")

@api.put("/buy")
