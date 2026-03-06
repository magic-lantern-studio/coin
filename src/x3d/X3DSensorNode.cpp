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
  \class SoX3DSensorNode SoX3DSensorNode.h Inventor/X3Dnodes/SoX3DSensorNode.h
  \brief The SoX3DSensorNode is an abstract node type for all sensors in the X3D specification.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  X3DSensorNode : X3DChildNode {
    SFBool [in,out] enabled  TRUE
    SFNode [in,out] metadata NULL [X3DMetadataObject]
    SFBool [out]    isActive
  }
  \endverbatim

  This abstract node type is the base type for all sensors.
*/

/*!
  SoSFBool SoX3DSensorNode::enabled
  Enable or disable the sensor.
*/

/*!
  SoSFBool SoX3DSensorNode:isActive
  An eventOut that is sent when the sensor is active.
*/

#include <Inventor/X3Dnodes/SoX3DSensorNode.h>
#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "nodes/SoSubNodeP.h"

// *************************************************************************

class SoX3DSensorNodeP {
};

// *************************************************************************

SO_NODE_SOURCE(SoX3DSensorNode);

// *************************************************************************

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DSensorNode::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DSensorNode, SO_X3D_NODE_TYPE);
}

#define PRIVATE(thisp) ((thisp)->pimpl)

SoX3DSensorNode::SoX3DSensorNode(void)
  : SoX3DChildNode()
{
  PRIVATE(this) = new SoX3DSensorNodeP;

  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DSensorNode);

  SO_X3DNODE_ADD_EXPOSED_FIELD(enabled, (TRUE));
  SO_X3DNODE_ADD_EVENT_OUT(isActive);
}

SoX3DSensorNode::~SoX3DSensorNode()
{
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
