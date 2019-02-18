/* -*- c++ -*- */
/* 
 * Copyright 2019 gr-ook_remote author.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
//#include <gnuradio/blocks/pdu.h>

#include "decode_fm_impl.h"

namespace gr {
  namespace ook_remote {

    decode_fm::sptr
    decode_fm::make()
    {
      return gnuradio::get_initial_sptr
        (new decode_fm_impl());
    }

    /*
     * The private constructor
     */
    decode_fm_impl::decode_fm_impl()
      : gr::block("decode_fm",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(0, 0, 0))
    {
      d_port = pmt::mp("out");
      message_port_register_out(d_port);

      decode_state = WAITING_FOR_FIRST;
      on_time = 0;
      off_time = 0;
      period = 0;
    }

    /*
     * Our virtual destructor.
     */
    decode_fm_impl::~decode_fm_impl()
    {
    }

    void
    decode_fm_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
      ninput_items_required[0] = noutput_items;
    }

    int
    decode_fm_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

/*      for(int i = 0; i < noutput_items; i++) {
        out[i] = in[i] * in[i];
      }
*/
      for(int i = 0; i < ninput_items[0]; i++) {
        uint64_t now_sample = block::nitems_read(0) + i;
        switch(decode_state) {
          case WAITING_FOR_FIRST:
            if(in[i] > 0.9f) {
            on_time = now_sample;
            decode_state = ON_STATE;
            }
            break;
          case ON_STATE:
            if(in[i] < 0.1f) {
            off_time = now_sample;
            decode_state = OFF_STATE;
            }
            break;
          case OFF_STATE:
            if(in[i] > 0.9f) {
              period = now_sample - on_time;
              float duty = 0.0f;
              if(period != 0)
                duty = (off_time - on_time)/(float)period;
              if(duty > 0.2f && duty < 0.4) {
                sequence.push_back(0.0f);
              } else if(duty > 0.6f && duty < 0.8) {
                sequence.push_back(1.0f);
              }

              on_time = now_sample;
              decode_state = ON_STATE;
            }
            if(period != 0) {
              if(off_time + period * 3 < now_sample) {
                decode_state = WAITING_FOR_FIRST;
                //pmt::pmt_t msg = blocks::pdu::make_pdu_vector(blocks::pdu::float_t, (uint8_t *)sequence.data(), sequence.size());
                pmt::pmt_t msg = pmt::init_f32vector(sequence.size(), sequence.data());
                message_port_pub(d_port, msg);
                sequence.clear();
              }
            }
          break;
        }
      }
      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return 0;
    }

  } /* namespace ook_remote */
} /* namespace gr */

