#define THERMISTOR_PIN 0

// Thermistor lookup table for RepRap Temperature Sensor Boards (http://make.rrrf.org/ts)
// Made with createTemperatureLookup.py (http://svn.reprap.org/trunk/reprap/firmware/Arduino/utilities/createTemperatureLookup.py)
// ./createTemperatureLookup.py --r0=100000 --t0=25 --r1=0 --r2=4700 --beta=4066 --max-adc=1023
// r0: 100000
// t0: 25
// r1: 0
// r2: 4700
// beta: 4066
// max adc: 1023
#define NUMTEMPS 20
short temptable[NUMTEMPS][2] = {
   {1, 650},
   {54, 208},
   {107, 169},
   {160, 148},
   {213, 133},
   {266, 122},
   {319, 112},
   {372, 104},
   {425, 96},
   {478, 89},
   {531, 83},
   {584, 76},
   {637, 70},
   {690, 63},
   {743, 57},
   {796, 49},
   {849, 41},
   {902, 31},
   {955, 18},
   {1008, -10}
};

void setup()
{
   Serial.begin(9600);
   Serial.println("Starting temperature exerciser.");
}

void loop()
{
   int rawvalue = analogRead(THERMISTOR_PIN);
   int celsius = read_temp();
   int fahrenheit = (((celsius * 9) / 5) + 32);

   Serial.print("Current temp: ");
   Serial.print(celsius);
   Serial.print("C / ");
   Serial.print(fahrenheit);
   Serial.println("F");
   
   Serial.print("Raw value: ");
   Serial.println(rawvalue);
   Serial.println(" ");

if (celsius < 21)
{
  digitalWrite(8, HIGH);
}
else
{
  digitalWrite(8,LOW);
}
   delay(1000);
}

int read_temp()
{
   int rawtemp = analogRead(THERMISTOR_PIN);
   int current_celsius = 0;

   byte i;
   for (i=1; i<NUMTEMPS; i++)
   {
      if (temptable[i][0] > rawtemp)
      {
         int realtemp  = temptable[i-1][1] + (rawtemp - temptable[i-1][0]) * (temptable[i][1] - temptable[i-1][1]) / (temptable[i][0] - temptable[i-1][0]);

         if (realtemp > 255)
            realtemp = 255;

         current_celsius = realtemp;

         break;
      }
   }

   // Overflow: We just clamp to 0 degrees celsius
   if (i == NUMTEMPS)
   current_celsius = 0;

   return current_celsius;
}
