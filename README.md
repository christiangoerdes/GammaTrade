# Gamma Trade

## Projektdetails
[Implementation Details](https://gitlab.informatik.uni-bonn.de/xx_best_oose_group_xx/projektgamma/-/blob/0cdbedb0b7108f8d738c584a4b776d6a5f09b266/docs/Implementation%20Details/implementation_details.drawio.png)

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

## Aufteilung und Umsetzung
Das Projekt wurde so realisiert, dass Client und Server unabhängig von einander sind. Zum Entwickeln wurde dabei der Server in die Spiellogik und API aufgeteilt. Die drei Bestandteile wurden im wesentlichen wie folgt aufgeteilt:
- Client - Ibo
- API - Chrisi     
- Spiellogik - Sergej

[Gantt Chart](https://gitlab.informatik.uni-bonn.de/xx_best_oose_group_xx/projektgamma/-/blob/2ffa367af6ab2fdee50094991a03205352c6efcb/docs/Gantt%20Chart/Gantt%20Chart.png)