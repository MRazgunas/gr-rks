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

#ifndef INCLUDED_RKS_CAME_FIXED_CODE_DECODER_IMPL_H
#define INCLUDED_RKS_CAME_FIXED_CODE_DECODER_IMPL_H

#include <rks/came_fixed_code_decoder.h>

namespace gr {
  namespace rks {

    class came_fixed_code_decoder_impl : public came_fixed_code_decoder
    {
     private:
      // Nothing to declare in this block.
      enum {
        WAITING_FOR_SYNC_PULSE,
        WAITING_FOR_SYNC_ENDING,
        WAITING_FOR_BIT_START,
        WAITING_FOR_BIT_END
      } detector_state;
      uint64_t last_on;
      uint64_t last_off;
      uint64_t sync_lenght;
      pmt::pmt_t out_port;
      std::vector<float> remote_code;

      bool p_enable_sync; 
      int p_high_min_lenght, p_high_max_lenght;
      int p_low_min_lenght, p_low_max_lenght;

     public:
      came_fixed_code_decoder_impl(bool enable_sync, 
        int high_min_lenght, int high_max_lenght,
        int low_min_lenght, int low_max_lenght);
      ~came_fixed_code_decoder_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace rks
} // namespace gr

#endif /* INCLUDED_RKS_CAME_FIXED_CODE_DECODER_IMPL_H */

