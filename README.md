# Gamma Trade

## Server starten
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

Zum Installieren der Abhängikeiten muss folgender Befehl im `/Client` Verzeichnis ausgeführt werden:

    npm install

Zum Starten des Clients muss folgender Befehl im `/Client` Verzeichnis ausgeführt werden:

    npm start

## Mitglieder
- Ibrahim Fakhir
- Christian Goerdes
- Sergej Zuev
