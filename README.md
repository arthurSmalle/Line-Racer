# Line racer project
De code is modulair opgebouwd.
De verschillende componenten zijn te vinden in de "src" map.
Hieronder worden de verschillende componenten besproken.

## Alle source code van de robot

### angle controller
In deze map zitten alle stukken code die de robot de mogelijkheid geven om de sensoren te gebruiken en interpreteren.
Deze sensoren worden specifiek gebruikt om de hoek te bepalen tussen de robot en de lijn.

### motor control
In deze map zitten alle stukken code die gebruikt worden om de wielen aan een bepaalde snelheid te laten draaien.

### music player
Deze map omvat de code waarmee de robot de speaker aanstuurt.

### PID
Dit is een implementatie van een PID controller die in de andere modules gebruikt word.

### Robot states
Dit zijn de implementaties boven op de abstracte interface voor de state machine.

### state machine
Dit is een abstracte implementatie van een state machine.
Behalve deze abstracte implementatie is er ook een deel dat meer specifiek van toepassing is voor deze robot.
Dit deel bevat enkel statische velden die dan kunnen aangeroepen worden door alle "Robot states" die hier van erven.

## Extra
onder de folder "misc" staan enkele extra's die tijdens dit project gebruikt zijn.

### 3D files
Dit zijn de 3D stl bestanden van de robot

### ble app
De python "app" gebruikt om de robot aan te sturen over bluetooth

### python script
een python script die in het begin gebruikt werd om de waarden van de robot te interpreteren en plotten
