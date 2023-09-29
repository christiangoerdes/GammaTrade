# GammaTrade 

## General Information 
This project is a collaborative effort developed as part of the Object-Oriented Software Development module. It comprises a client implemented in React and a server implemented using Python, C++, and Pybind. The communication between the client and server operates using the REST architecture. The project was completed within a tight timeframe of just 3 days.

Due to some issues such as an unsatisfactory API and the absence of a database, the project was later reimplemented using Spring Boot to address these shortcomings and improve overall functionality.
For the updated and improved version of this project, please refer to the [ElectroTrade](https://github.com/christiangoerdes/ElectroTradeBackend) repository. 

## Server
### Starting the Server with Docker
To start the server using Docker, you need to have Docker configured on your device. Afterward, execute the following commands in the `/Server` directory:

Build the container:
```
sudo docker build -t gammatrade .
```
Start the container:
```
sudo docker run --network host gammatrade
```

### Starting the Server without Docker
#### Creating a Build:
To create a build, enter the following command in the `/Server` directory of the project:
    
    cmake -S . -B build && cmake --build build && cmake --install build

#### Starting the API:
To start the API, execute one of the following commands in the `/Server/api` directory:
```
    uvicorn api:api --port 8000 --reload
```
```
    python3 -m uvicorn api:api --port 8000  --reload
```
---
## Client

To use the client, you first need to install Node.js.

Next, in the axiosConfig file located in the `/Client` directory, set the baseURL to the server host you want to use.

To install dependencies, run the following command in the `/Client` directory:
```
npm install
```
To start the client, run the following command in the `/Client` directory:
```
npm start
```

## Projektdetails
[Implementation Details](https://github.com/christiangoerdes/GammaTrade/blob/a6674459dc4a86af7a074fc54c104191ab5bb373/docs/Implementation%20Details/implementation_details.drawio.png)
[Gantt Chart](https://github.com/christiangoerdes/GammaTrade/blob/7bb6c9f15e340af347f4c7cbfe48cff70999b4ab/docs/Gantt%20Chart/Gantt%20Chart.png)
