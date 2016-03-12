# HeatBed_Temp_Controler
RepRap MK2 heatbed temperature controler for 24V external power supply

Used a 100K Thermistor with 10K serial resistor.
All values are calculate from a Python script using the typical Steinhart equation.

The script is also in this repo.

A relay control was added to the original script in a dirty code, it's just an example as it shuts off at 21°C. Either ajust this value in the code, either ajust the code to make it variable ;)

![Arduino_Controler](hbcontroler.jpg)

