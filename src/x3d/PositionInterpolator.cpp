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
  \class SoX3DPositionInterpolator SoX3DPositionInterpolator.h Inventor/X3Dnodes/SoX3DPositionInterpolator.h
  \brief The SoX3DPositionInterpolator class is used to interpolate 3D points.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT

  \verbatim
  PositionInterpolator {
    eventIn      SFFloat set_fraction        # (-,)
    exposedField MFFloat key           []    # (-,)
    exposedField MFVec3f keyValue      []    # (-,)
    eventOut     SFVec3f value_changed
  }
  \endverbatim
  
  The PositionInterpolator node linearly interpolates among a list of
  3D vectors. The keyValue field shall contain exactly as many values
  as in the key field.  4.6.8, Interpolator nodes
  (<http://www.web3d.org/x3d/specifications/vrml/ISO-IEC-14772-X3D/part1/concepts.html#4.6.8>),
  contains a more detailed discussion of interpolators.

*/

/*!
  \var SoMFVec3f SoX3DPositionInterpolator::keyValue
  The keyValue vector.
*/

/*!
  \var SoEngineOutput SoX3DPositionInterpolator::value_changed
  The eventOut which is sent every time the interpolator has calculated a new value.
*/

#include <Inventor/X3Dnodes/SoX3DPositionInterpolator.h>

#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "engines/SoSubNodeEngineP.h"

SO_NODEENGINE_SOURCE(SoX3DPositionInterpolator);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DPositionInterpolator::initClass(void) // static
{
  SO_NODEENGINE_INTERNAL_INIT_CLASS(SoX3DPositionInterpolator);
}

/*!
  Constructor.
*/
SoX3DPositionInterpolator::SoX3DPositionInterpolator(void)
{
  SO_NODEENGINE_INTERNAL_CONSTRUCTOR(SoX3DPositionInterpolator);

  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(keyValue);
  SO_NODEENGINE_ADD_OUTPUT(value_changed, SoSFVec3f);
}

/*!
  Destructor.
*/
SoX3DPositionInterpolator::~SoX3DPositionInterpolator()
{
}

// Doc in parent
void
SoX3DPositionInterpolator::evaluate(void)
{
  float interp;
  int idx = this->getKeyValueIndex(interp, this->keyValue.getNum());
  if (idx < 0) return;
  
  const SbVec3f * v = this->keyValue.getValues(0);

  SbVec3f v0 = v[idx];
  if (interp > 0.0f) {
    SbVec3f v1 = v[idx+1];
    v0 = v0 + (v1-v0)*interp;
  }
  SO_ENGINE_OUTPUT(value_changed, SoSFVec3f, setValue(v0));
}

#endif // HAVE_X3D
