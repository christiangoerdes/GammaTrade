# Gamma Trade - Uni Projekt 3
Eine Stock-Trading Plattform 
## Projektdetails
[Implementation Details](https://github.com/christiangoerdes/GammaTrade/blob/a6674459dc4a86af7a074fc54c104191ab5bb373/docs/Implementation%20Details/implementation_details.drawio.png)

## Server mit Docker starten
Um den Server mit Docker zu starten, muss man Docker auf seinem Gerät konfiguriert haben. Anschließend  müssen die folgenden Commands im `/Server` Verzeichnis ausgeführt werden:


Container bauen:

    sudo docker build -t gammatrade .

Container starten:

    sudo docker run --network host gammatrade


## Server ohne Docker starten
### Build erstellen:
Um einen Build zu erstellen, muss der folgende Command im `/Server` Verzeichnis des Projekts eingegeben werden:
    
    cmake -S . -B build && cmake --build build && cmake --install build

### API starten:
Um die API zu starten, muss einer der beiden folgenden Commands im `/Server/api` Verzeichnis ausgeführt werden:

    uvicorn api:api --port 8000 --reload
 ###

    python3 -m uvicorn api:api --port 8000  --reload

---
## Client starten

Um den Client zu nutzen, muss zuerst Node installiert werden.

Anschließend muss im `/Client` Verzeichnis in der axiosConfig die baseURL auf den Server-host gestellt werden, den man nutzen möchte.

Zum Installieren der Abhängigkeiten muss folgender Befehl im `/Client` Verzeichnis ausgeführt werden:

    npm install

Zum Starten des Clients muss folgender Befehl im `/Client` Verzeichnis ausgeführt werden:

    npm start

## Mitglieder
- Ibrahim Fakhir
- Christian Goerdes
- Sergej Zuev

## Aufteilung und Umsetzung
Das Projekt wurde so realisiert, dass Client und Server unabhängig von einander sind. Zum Entwickeln wurde dabei der Server in die Spiellogik und API aufgeteilt. Die drei Bestandteile wurden im wesentlichen wie folgt aufgeteilt:
- Client - Ibo
- API - Chrisi     
- Spiellogik - Sergej

[Gantt Chart](https://github.com/christiangoerdes/GammaTrade/blob/7bb6c9f15e340af347f4c7cbfe48cff70999b4ab/docs/Gantt%20Chart/Gantt%20Chart.png)
