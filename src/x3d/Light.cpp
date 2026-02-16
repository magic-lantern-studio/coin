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
  \class SoX3DLight SoX3DLight.h Inventor/X3Dnodes/SoX3DLight.h
  \brief The SoX3DLight class is a superclass for X3D light nodes.
*/

/*!
  \var SoSFBool SoX3DLight::on
  Enable/disable light. Default value is TRUE.
*/

/*!
  \var SoSFFloat SoX3DLight::intensity
  The light intensity. A value from 0 to 1. Default value is 1.
*/

/*!
  \var SoSFColor SoX3DLight::color
  The light color. Default value is (1, 1, 1).
*/

/*!
  \var SoSFFloat SoX3DLight::ambientIntensity
  The light ambient intensity. A value from 0 to 1. Default value is 0.
*/

#include <Inventor/X3Dnodes/SoX3DLight.h>
#include "coindefs.h"

#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "nodes/SoSubNodeP.h"

SO_NODE_ABSTRACT_SOURCE(SoX3DLight);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DLight::initClass(void)
{
  SO_NODE_INTERNAL_INIT_ABSTRACT_CLASS(SoX3DLight, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DLight::SoX3DLight(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DLight);

  SO_X3DNODE_ADD_FIELD(on, (TRUE));
  SO_X3DNODE_ADD_FIELD(intensity, (1.0f));
  SO_X3DNODE_ADD_FIELD(color, (1.0f, 1.0f, 1.0f));
  SO_X3DNODE_ADD_FIELD(ambientIntensity, (0.0f));
}

/*!
  Destructor.
*/
SoX3DLight::~SoX3DLight()
{
}

// Doc in parent
void
SoX3DLight::GLRender(SoGLRenderAction * COIN_UNUSED_ARG(action))
{
}

#endif // HAVE_X3D
