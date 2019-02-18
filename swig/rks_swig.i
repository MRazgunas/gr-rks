/* -*- c++ -*- */

#define RKS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "rks_swig_doc.i"

%{
#include "rks/came_fixed_code_decoder.h"
%}


%include "rks/came_fixed_code_decoder.h"
GR_SWIG_BLOCK_MAGIC2(rks, came_fixed_code_decoder);
