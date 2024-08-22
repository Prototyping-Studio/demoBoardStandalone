#include <Wire.h>
#include "Adafruit_SGP30.h"
#include "busyboard.h"

publishedVar<int> TVOC(0,"tvoc");
publishedVar<int> eCO2(0,"eco2");
publishedVar<int> rawH2(0,"raw_h2");
publishedVar<int> rawEthanol(0,"raw_ethanol");
publishedVar<int> TVOC_base(0,"tvoc_base");
publishedVar<int> eCO2_base(0,"eco2_base");

Adafruit_SGP30 sgp;

/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

void commSetup()
{
  Serial.print("${SERIAL");
  Serial.print(TVOC.getIdString());
  Serial.print(eCO2.getIdString());
  Serial.print(rawH2.getIdString());
  Serial.print(rawEthanol.getIdString());
  Serial.print(TVOC_base.getIdString());
  Serial.print(eCO2_base.getIdString());
  
  Serial.println("}");  
}

void setup() {
  
  Serial.begin(57600);
  while (!Serial) { delay(10); } // Wait for serial console to open!
  commSetup();

  if (!sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }

  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
  
  // If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'
  //sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
}

int counter = 0;
void loop() {
  // If you have a temperature / humidity sensor, you can set the absolute humidity to enable the humditiy compensation for the air quality signals
  //float temperature = 22.1; // [°C]
  //float humidity = 45.2; // [%RH]
  //sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));

  if (sgp.IAQmeasure())
  {
    TVOC = sgp.TVOC;
    eCO2 = sgp.eCO2;
  }
  if (sgp.IAQmeasureRaw())
  {
    rawH2 = sgp.rawH2;
    rawEthanol = sgp.rawEthanol;
  }

  delay(1000);

  counter++;
  if (counter == 30) {
    Serial.println("Getting baseline values...");
    counter = 0;
    uint16_t eCO2_base_tmp, TVOC_base_tmp;
    if (sgp.getIAQBaseline(&eCO2_base_tmp, &TVOC_base_tmp)) {
      eCO2_base = eCO2_base_tmp;
      TVOC_base = TVOC_base_tmp;
    }
  }
}

