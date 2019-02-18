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

#ifndef INCLUDED_OOK_REMOTE_DECODE_FM_IMPL_H
#define INCLUDED_OOK_REMOTE_DECODE_FM_IMPL_H

#include <ook_remote/decode_fm.h>
namespace gr {
  namespace ook_remote {

    class decode_fm_impl : public decode_fm
    {
     private:
      // Nothing to declare in this block.
      pmt::pmt_t d_port;

      enum {
        WAITING_FOR_FIRST,
        ON_STATE,
        OFF_STATE
      };
      uint8_t decode_state;
      uint64_t on_time;
      uint64_t off_time;
      uint32_t period;
      std::vector<float> sequence;

     public:
      decode_fm_impl();
      ~decode_fm_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace ook_remote
} // namespace gr

#endif /* INCLUDED_OOK_REMOTE_DECODE_FM_IMPL_H */

