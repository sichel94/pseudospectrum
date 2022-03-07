/******************************************************************************
https://github.com/sichel94/pseudospectrum 

Distributed as-is; no warranty is given.
******************************************************************************/
#ifndef __PSEUDOSPECTRUM__
#define __PSEUDOSPECTRUM__

#include <Arduino.h>

// sval_t is the type of the spectrum values. define approprately to your spectrum data
// It will however significantly increase speed to use fixed point numbers on non FPU-archs 
//#define sval_t int
//#define sval_t long int
#define sval_t float
//#define sval_t double

#define MAX_SPECTRA 8

class spectrum
{
	public:
		spectrum(int, int, sval_t*, unsigned int);
		sval_t getValue(unsigned int);
		void setAmount(sval_t);

	private:
		int start_nm;
		int stop_nm;
		unsigned int s_points;
		sval_t* s_data;
		sval_t amount = 0;
};


class pseudospectrum
{
	public:
		void addSpectrum(spectrum&);
		sval_t getValue(unsigned int nm);

	private:
		unsigned int noSpectra = 0;
		spectrum* spectra[MAX_SPECTRA];
};

extern spectrum spectrum_VEML6075_UVA;
extern spectrum spectrum_VEML6075_UVB;
extern spectrum spectrum_GUVB_C31SM;

#endif