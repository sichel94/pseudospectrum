/******************************************************************************
https://github.com/sichel94/pseudospectrum 

Distributed as-is; no warranty is given.
******************************************************************************/
#include "pseudospectrum.h"
#include "guvbc31sm.h"
#include <SparkFun_VEML6075_Arduino_Library.h>

// Define spectra
float spectrum_VEML6075_UVA_data[] = {0.00355240000000000 , 0.0152358509659469 , 0.0269193019318937 , 0.0489804808641308 , 0.0789484862205472 , 0.108243634020053, 0.136077724329626, 0.185727729278396, 0.261172320000000, 0.405010848053878, 0.612134359238937, 0.835217157310655, 0.993037296000000, 0.938587709755225, 0.685168770402971, 0.377109341026001, 0.162344535000001, 0.0559058934823692 , 0.0289520600000000 , 0.0159549061661950 , 0.0108116485959947};
float spectrum_VEML6075_UVB_data[] = {0.0266430000000000 , 0.104191780776585, 0.218401380000000, 0.440675104808499, 0.708703416000001, 0.933392550000000, 0.997779750000000, 0.869348045353232, 0.494595274285713, 0.179396159147300, 0.0670111272727272 , 0.0290763945126106 , 0.0142843914317361 , 0.00805834405928097, 0.00501776644788097, 0.00255328819313451 ,8.88099383880472e-05 , 0, 0, 0, 0};
float spectrum_GUVB_C31SM_data[] = {0,1};
spectrum spectrum_VEML6075_UVA(300,400,spectrum_VEML6075_UVA_data,21);
spectrum spectrum_VEML6075_UVB(300,400,spectrum_VEML6075_UVB_data,21);
spectrum spectrum_GUVB_C31SM(300,400,spectrum_GUVB_C31SM_data,2);

// Sensor Objects
GUVB guvb;
VEML6075 veml;

// Pseudospectrum object
pseudospectrum ps;

void setup()
{
  Wire.begin();
  if (guvb.begin() == false)
    Serial.println("Cant verify guvb ID, check connection?");
  if (veml.begin() == false)
    Serial.println("Cant verify veml, check connection?");

  ps.addSpectrum(spectrum_VEML6075_UVA);
  ps.addSpectrum(spectrum_VEML6075_UVB);
  ps.addSpectrum(spectrum_GUVB_C31SM);
}

void loop()
{
  // Get UV Values
  float g = guvb.getUV();
  float va = veml.uva();
  float vb = veml.uvb();

  // Update amounts in spectra
  spectrum_VEML6075_UVA.setAmount(va);
  spectrum_VEML6075_UVB.setAmount(vb);
  spectrum_GUVB_C31SM.setAmount(g);

  // print pseudospectrum
  for (int i = 250; i < 400; i++)
  {
   Serial.print(i);
   Serial.print(" nm; ");
   Serial.print(ps.getValue(i));
   Serial.println(" AU"); 
  }
  delay(10000);
}

