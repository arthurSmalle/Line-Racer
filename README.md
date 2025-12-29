# Line racer project
De code is modulair opgebouwd.
De verschillende componenten zijn te vinden in de "src" map.
Hieronder worden de verschillende componenten besproken.

## angle controller
In deze map zitten alle stukken code die de robot de mogelijkheid geven om de sensoren te gebruiken en interpreteren.
Deze sensoren worden specifiek gebruikt om de hoek te bepalen tussen de robot en de lijn.

## motor control
In deze map zitten alle stukken code die gebruikt worden om de wielen aan een bepaalde snelheid te laten draaien.

## music player
Deze map omvat de code waarmee de robot de speaker aanstuurt.

## PID
Dit is een implementatie van een PID controller die in de andere modules gebruikt word.

## Robot states
Dit zijn de implementaties boven op de abstracte interface voor de state machine.

## state machine
Dit is een abstracte implementatie van een state machine.
Behalve deze abstracte implementatie is er ook een deel dat meer specifiek van toepassing is voor deze robot.
Dit deel bevat enkel statische velden die dan kunnen aangeroepen worden door alle "Robot states" die hier van erven.
