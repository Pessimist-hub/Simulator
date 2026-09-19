# Simulator
Island Cleaner Simulator
## Ideea jocului
Playerul se trezeste singur, fără să știe cum a ajuns acolo. Insula cindva era nu poluata, dar acum e plină de gunoaie și murdărie peste tot. I se spune (printr-un mesaj sau un semn găsit pe plajă) că nu poate pleca de pe insulă până nu o curăță complet.
Scopul jocului: strângi tot gunoiul de pe insulă ca să poți scăpa de acolo.
Cum se joacă
Te miști pe insulă cu W A S D
Când te apropii de un gunoi, îl iei automat (sau apeși E)
Pentru fiecare gunoi luat primești câteva puncte/coinuri
Cu coinurile astea poți cumpăra upgrade-uri, ca să te ajute să cureți mai repede (de exemplu iei gunoiul de la o distanță mai mare, sau te miști mai repede)
Când ai luat tot gunoiul de pe insulă, apare o barcă (sau un portal) prin care poți pleca asta e finalul jocului
De ce coinuri și upgrade-uri
Ca să nu fie plictisitor doar să aduni gunoi fără sens, o sa fie un sistem de recompensă. Cu cât cureți mai mult, cu atât progresezi mai repede.
Idei de upgrade:
Playerul o sa poata  sa ia gunoiul la distanta
Viteză de mișcare mai mare
Un fel de magnet care atrage gunoiul din jur
Upgrade la cos de gunoi
Player care se mișcă pe hartă
Gunoaie puse prin diferite locuri de pe insulă când player-ul dă de ele, dispar și adaugă puncte
Un contor care ține minte câte gunoaie au mai rămas
Un contor pentru coinuri
Când gunoiul a ajuns la 0, apare barca/portalul și jocul se termină


# Point
x, y, z
DistanceTo
# Item
name
position
value
# Player
position
coins
movementSpeed
pickupRange
Move, BuySpeed, BuyRange
# Map
width, depth
trash (vector<Item>)
Init, TrashLeft, Collect
# AudioController
PlayPickup
# GameEngine
Init
Run
# EventListener
GetEvent
# Renderer
Clear
PutText
DrawMap
