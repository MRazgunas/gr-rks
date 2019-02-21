/* -*- c++ -*- */

#define RKS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "rks_swig_doc.i"

%{
#include "rks/binary_decoder_pulse_lenght.h"
%}


%include "rks/binary_decoder_pulse_lenght.h"
GR_SWIG_BLOCK_MAGIC2(rks, binary_decoder_pulse_lenght);
