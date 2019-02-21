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


#ifndef INCLUDED_RKS_BINARY_DECODER_PULSE_LENGHT_H
#define INCLUDED_RKS_BINARY_DECODER_PULSE_LENGHT_H

#include <rks/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace rks {

    /*!
     * \brief <+description of block+>
     * \ingroup rks
     *
     */
    class RKS_API binary_decoder_pulse_lenght : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<binary_decoder_pulse_lenght> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of rks::binary_decoder_pulse_lenght.
       *
       * To avoid accidental use of raw pointers, rks::binary_decoder_pulse_lenght's
       * constructor is in a private implementation
       * class. rks::binary_decoder_pulse_lenght::make is the public interface for
       * creating new instances.
       */
      static sptr make(bool enable_sync, 
        int high_min_lenght, int high_max_lenght,
        int low_min_lenght, int low_max_lenght);
    };

  } // namespace rks
} // namespace gr

#endif /* INCLUDED_RKS_BINARY_DECODER_PULSE_LENGHT_H */

