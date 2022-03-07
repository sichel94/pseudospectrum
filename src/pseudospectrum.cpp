/******************************************************************************
https://github.com/sichel94/pseudospectrum_plot

Distributed as-is; no warranty is given.
******************************************************************************/
#include "pseudospectrum.h"
#include <Arduino.h>
#include <U8g2lib.h>

void pseudospectrum::addSpectrum(spectrum& s)
{
	if(noSpectra < MAX_SPECTRA)
	spectra[noSpectra++] = &s;
}

sval_t pseudospectrum::getValue(unsigned int nm)
{
	sval_t retval = 0;
	for (int i = 0; i < noSpectra; i++)
	{
		spectrum* s = spectra[i];
		retval += s->getValue(nm);
	}
	return retval;
}

spectrum::spectrum(int start, int stop, sval_t* data, unsigned int points)
{
	start_nm = start;
	stop_nm = stop;
	s_data = data;
	s_points = points;
}

sval_t spectrum::getValue(unsigned int nm)
{
	if (nm < start_nm)
		return s_data[0];
	if (nm > stop_nm)
		return s_data[s_points];
	float idx = (nm - start_nm)*s_points/stop_nm;

	unsigned int idx_l, idx_h;
	idx_l = (unsigned int)idx;
	idx_h = idx_l+1;

	sval_t val_l = s_data[idx_l];
	sval_t val_h = s_data[idx_h];

	return amount * (val_l + (idx-idx_l)*(val_h - val_l));
}

void spectrum::setAmount(sval_t a)
{
	amount = a;
}