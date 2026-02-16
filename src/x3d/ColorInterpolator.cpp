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
  \class SoX3DColorInterpolator SoX3DColorInterpolator.h Inventor/X3Dnodes/SoX3DColorInterpolator.h
  \brief The SoX3DColorInterpolator class is used to interpolate color values.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT

  \verbatim
  ColorInterpolator {
    eventIn      SFFloat set_fraction        # (-inf, inf)
    exposedField MFFloat key           []    # (-inf, inf)
    exposedField MFColor keyValue      []    # [0,1]
    eventOut     SFColor value_changed
  }
  \endverbatim

  This node interpolates among a list of MFColor key values to produce
  an SFColor (RGB) value_changed event. The number of colours in the
  keyValue field shall be equal to the number of keyframes in the key
  field. The keyValue field and value_changed events are defined in
  RGB colour space. A linear interpolation using the value of
  set_fraction as input is performed in HSV space (see 
  http://www.web3d.org/x3d/specifications/vrml/ISO-IEC-14772-X3D/part1/bibliography.html#[FOLE]
  for description of RGB and HSV colour spaces). The results are undefined
  when interpolating between two consecutive keys with complementary
  hues.  

  4.6.8, Interpolator nodes
  (<http://www.web3d.org/x3d/specifications/vrml/ISO-IEC-14772-X3D/part1/concepts.html#4.6.8>), 
  contains a detailed discussion of interpolators.

*/


/*!
  \var SoMFColor SoX3DColorInterpolator::keyValue
  The color values.
*/

/*!
  \var SoEngineOutput SoX3DColorInterpolator::value_changed
  The eventOut color.
*/

#include <Inventor/X3Dnodes/SoX3DColorInterpolator.h>

#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "engines/SoSubNodeEngineP.h"

SO_NODEENGINE_SOURCE(SoX3DColorInterpolator);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DColorInterpolator::initClass(void) // static
{
  SO_NODEENGINE_INTERNAL_INIT_CLASS(SoX3DColorInterpolator);
}

/*!
  Constructor.
*/
SoX3DColorInterpolator::SoX3DColorInterpolator(void)
{
  SO_NODEENGINE_INTERNAL_CONSTRUCTOR(SoX3DColorInterpolator);

  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(keyValue);
  SO_NODEENGINE_ADD_OUTPUT(value_changed, SoSFColor);
}

/*!
  Destructor.
*/
SoX3DColorInterpolator::~SoX3DColorInterpolator() // virtual, protected
{
}

// doc in parent
void
SoX3DColorInterpolator::evaluate(void)
{
  float interp;
  int idx = this->getKeyValueIndex(interp, this->keyValue.getNum());
  if (idx < 0) return;

  const SbColor * v = this->keyValue.getValues(0);

  SbColor v0 = v[idx];
  if (interp > 0.0f) {
    SbColor v1 = v[idx+1];
    v0 = v0 + (v1-v0)*interp;
  }
  SO_ENGINE_OUTPUT(value_changed, SoSFColor, setValue(v0));
}

#endif // HAVE_X3D
