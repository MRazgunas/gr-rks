/* -*- c++ -*- */

#define OOK_REMOTE_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ook_remote_swig_doc.i"

%{
#include "ook_remote/decode_fm.h"
%}


%include "ook_remote/decode_fm.h"
GR_SWIG_BLOCK_MAGIC2(ook_remote, decode_fm);
