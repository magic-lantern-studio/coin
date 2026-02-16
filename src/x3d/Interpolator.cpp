/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#ifdef HAVE_X3D

/*!
  \class SoX3DInterpolator SoX3DInterpolator.h Inventor/X3Dnodes/SoX3DInterpolator.h
  \brief The SoX3DInterpolator class is an internal abstract class.

  This class collects the two fields that are common for all
  interpolator nodes, plus common code that operates on these
  fields. Since this is an abstract "helper" class, it does not
  represent an actual node from the X3D specification, so don't use
  it as such.

  For more information, a detailed discussion of interpolators is
  available in section 4.6.8 of the X3D specification:

  <http://www.web3d.org/x3d/specifications/vrml/ISO-IEC-14772-X3D/part1/concepts.html#4.6.8>
*/

/*!
  \var SoMFFloat SoX3DInterpolator::key

  This field contains a set of floating point values which the
  interpolation will run over. The key values should be monotonically
  non-decreasing.

  The field is inherited from its declaration in the abstract
  SoX3DInterpolator class into a range of different X3D interpolator
  nodes.

  See the class documentation of the \e non-abstract X3D interpolator
  node you want to use for information on what the key values
  represent in that specific context.
*/
/*!
  \var SoSFFloat SoX3DInterpolator::set_fraction

  The set_fraction field gets an input signal that triggers a
  calculation of the next value_changed eventOut value.

  The field is inherited from its declaration in the abstract
  SoX3DInterpolator class into a range of different X3D interpolator
  nodes.
*/

#include <Inventor/X3Dnodes/SoX3DInterpolator.h>

#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "engines/SoSubNodeEngineP.h"

SO_NODEENGINE_ABSTRACT_SOURCE(SoX3DInterpolator);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DInterpolator::initClass(void) // static
{
  SO_NODEENGINE_INTERNAL_INIT_ABSTRACT_CLASS(SoX3DInterpolator);
}

SoX3DInterpolator::SoX3DInterpolator(void) // protected
{
  SO_NODEENGINE_CONSTRUCTOR(SoX3DInterpolator);

  SO_X3DNODE_ADD_EVENT_IN(set_fraction);

  // initialize set_fraction to some value, since if set_fraction is
  // never set, we'll attempt to read an uninitialized value when the
  // interpolator is destructed (all engines evaluates when
  // destructed)
  this->set_fraction.enableNotify(FALSE);
  this->set_fraction = 0.0f;
  this->set_fraction.enableNotify(TRUE);
  
  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(key);
}

SoX3DInterpolator::~SoX3DInterpolator() // virtual, protected
{
}

/*!
  \COININTERNAL
*/
int 
SoX3DInterpolator::getKeyValueIndex(float & interp, int numvalues)
{
  float fraction = this->set_fraction.getValue();
  const int n = this->key.getNum();
  if (n == 0 || numvalues == 0) return -1;

  const float * t = this->key.getValues(0); 
  for (int i = 0; i < SbMin(n, numvalues); i++) {
    if (fraction < t[i]) {
      if (i == 0) {
        interp = 0.0f;
        return 0;
      }
      else {
        float delta = t[i] - t[i-1];
        if (delta > 0.0f) {
          interp = (fraction - t[i-1]) / delta;
        }
        else interp = 0.0f;
      }
      return i-1;
    }
  }
  interp = 0.0f;
  return SbMin(numvalues,n)-1;
}

#endif // HAVE_X3D
