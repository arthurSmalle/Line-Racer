# Closed loop motor control

Dit object zorgt er voor dat je de motor exact kan instellen

## Functies en uitleg:
### basis functies
#### Set point
Stel in hoeveel rpm de motor moet halen wanneer "update()" word aangeroepen.
```c++
void set_set_point(const float set_point);
```
#### update
Deze functie moet constant aangeroepen worden zodat de motor zijn rpm zou bijsturen.
```c++
void update();
```
### Extra functies voor meer controle en configuratie
#### draairichting aanpassen
Geef een boolean mee om de draairichting aan te passen
true = met de klok mee
false = tegen de klok
```c++
void set_clock_wise(bool clk);
```
#### update time aanpassen (van de controller)
Tijd in ms tussen wanneer de controler zijn berekeningen opnieuw maakt (standaard 50)
```c++
void set_update_time(const unsigned long update_time);
```
#### update time van tachometer aanpassen (berekent de rpm)
Niet aan te raden maar de update tijd van de tachometer kan aangepast worden, te kleine waarden geven een foute meting. Te grote waarden kunnen voor een traag systeem zorgen
```c++
void set_tachometer_interval_time(const unsigned long interval);
```
#### RPM meting opvragen
Met volgende functie kan je de rpm waarde die gemeten word door de tachometer opvragen (om andere berekeningen mee te doen)
```c++
float get_rpm();
```
# Angle predictor

Dit object voorspelt de hoek waaronder de robot staat ten opzichte van de lijn
## basis functies
### update de meting
Laat de sensoren een nieuwe meting doen
```c++
void update_ir_readings();
```
### Vraag een voorspelling van de hoek op
Met de volgende functie zal er een voorspelling gemaakt worden op basis van de metingen die moeten upgedate worden met *update_ir_readings()*
```c++
float predict_angle();
```
### Vraag de vorige voorspelling op
Vraag de voorspelling op zonder een nieuwe berekeningen te maken (*predict_angle* maakt WEL een nieuwe berekingen)
```c++
float get_last_perdiciont();
```
