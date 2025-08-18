/*
 *  This code is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This code is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/* Copyright (C) 2022-2023 Max-Planck-Society, Philipp Arras
   Authors: Philipp Arras */

#include <complex>
#include <cstdint>
#include <vector>
using namespace std;
using shape_t = vector<size_t>;

#include "ducc0/bindings/array_descriptor.h"
#include "ducc0/bindings/typecode.h"
#include "ducc0/fft/fft.h"
#include "ducc0/fft/fft1d_impl.h"
#include "ducc0/fft/fftnd_impl.h"
#include "ducc0/infra/mav.cc"
#include "ducc0/infra/threading.cc"

static constexpr size_t F32 = ducc0::Typecode<float>::value;
static constexpr size_t F64 = ducc0::Typecode<double>::value;
static constexpr size_t C64 = ducc0::Typecode<complex<float>>::value;
static constexpr size_t C128 = ducc0::Typecode<complex<double>>::value;

shape_t arraydesc2vec(const ducc0::ArrayDescriptor &arrdesc) {
  auto mav = ducc0::to_cmav<false, size_t, 1>(arrdesc);
  shape_t res;
  for (size_t i = 0; i < mav.shape(0); i++)
    res.push_back(mav(i));
  return res;
}

template <typename T>
void fft_c2c(const ducc0::ArrayDescriptor &in, ducc0::ArrayDescriptor &out,
             const ducc0::ArrayDescriptor &axes, const bool forward,
             const double fct, const size_t nthreads) {
  auto in_mav = ducc0::to_cfmav<false, complex<T>>(in);
  auto out_mav = ducc0::to_vfmav<false, complex<T>>(out);
  auto axes1 = arraydesc2vec(axes);
  ducc0::c2c(in_mav, out_mav, axes1, forward, T(fct), nthreads);
}

extern "C" {

void fft_c2c_(const ducc0::ArrayDescriptor &in, ducc0::ArrayDescriptor &out,
              const ducc0::ArrayDescriptor &axes, const bool forward,
              const double fct, const size_t nthreads) {
  if (in.dtype == C128)
    fft_c2c<double>(in, out, axes, forward, fct, nthreads);
  else if (in.dtype == C64)
    fft_c2c<float>(in, out, axes, forward, fct, nthreads);
  else
    MR_fail("Type not supported");
}
}
