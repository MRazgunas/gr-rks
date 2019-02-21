/* -*- c++ -*- */
/* 
 * Copyright 2019 Matas Razgunas.
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
#include "came_fixed_code_decoder_impl.h"

namespace gr {
  namespace rks {

    came_fixed_code_decoder::sptr
    came_fixed_code_decoder::make(bool enable_sync, 
        int high_min_lenght, int high_max_lenght,
        int low_min_lenght, int low_max_lenght)
    {
      return gnuradio::get_initial_sptr
        (new came_fixed_code_decoder_impl(enable_sync, 
        high_min_lenght, high_max_lenght,
        low_min_lenght, low_max_lenght));
    }

    /*
     * The private constructor
     */
    came_fixed_code_decoder_impl::came_fixed_code_decoder_impl(bool enable_sync, 
        int high_min_lenght, int high_max_lenght,
        int low_min_lenght, int low_max_lenght)
      : gr::block("came_fixed_code_decoder",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(0, 0, 0)),
        last_on(0),
        last_off(0),
        sync_lenght(0),
        detector_state(WAITING_FOR_SYNC_PULSE),
        out_port(pmt::mp("out")),
        p_enable_sync(enable_sync), 
        p_high_min_lenght(high_min_lenght), p_high_max_lenght(high_max_lenght),
        p_low_min_lenght(low_min_lenght), p_low_max_lenght(low_max_lenght)

    {
      message_port_register_out(out_port);
    }

    /*
     * Our virtual destructor.
     */
    came_fixed_code_decoder_impl::~came_fixed_code_decoder_impl()
    {
    }

    void
    came_fixed_code_decoder_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    came_fixed_code_decoder_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];

      for(int i = 0; i < ninput_items[0]; i++) {
        uint64_t now = block::nitems_read(0) + i;
        switch(detector_state) {
          case WAITING_FOR_SYNC_PULSE: //Nasty structure? TODO: clean up
            if(p_enable_sync && in[i] > 0.9f) {
              last_on = now;
              detector_state = WAITING_FOR_SYNC_ENDING;
              break;
            } else if (!p_enable_sync) {
              detector_state = WAITING_FOR_BIT_START;
            } else break;
          case WAITING_FOR_SYNC_ENDING:
            if(in[i] < 0.1f) {
              last_off = now;
              sync_lenght = last_off - last_on;
              detector_state = WAITING_FOR_BIT_START; 
            }
          break;
          case WAITING_FOR_BIT_START:
            if(in[i] > 0.9f) {
              last_on = now;
              detector_state = WAITING_FOR_BIT_END;              
            }
            if(last_off + sync_lenght * 6 < now) { //TODO: add parameter for timeout
              detector_state = WAITING_FOR_SYNC_PULSE;
              pmt::pmt_t msg = pmt::init_f32vector(remote_code.size(), remote_code.data());
              message_port_pub(out_port, msg);
              remote_code.clear();
            }
          break;
          case WAITING_FOR_BIT_END:
            if(in[i] < 0.1f) {
              last_off = now;
              detector_state = WAITING_FOR_BIT_START;

              /*float pulse_lenght_factor = (last_off - last_on)/(float) sync_lenght;    
              if(pulse_lenght_factor > 1.6f && pulse_lenght_factor < 2.5f) {
                remote_code.push_back(0);
              } else if(pulse_lenght_factor > 0.3f && pulse_lenght_factor < 1.4f) {
                remote_code.push_back(1);
              }*/
              uint64_t pulse_lenght = last_off - last_on;
              if(pulse_lenght > p_high_min_lenght && pulse_lenght < p_high_max_lenght)
                remote_code.push_back(1);
              if(pulse_lenght > p_low_min_lenght && pulse_lenght < p_low_max_lenght)
                remote_code.push_back(0);
            }
          break;
        }
      }

      consume_each (ninput_items[0]);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace rks */
} /* namespace gr */

