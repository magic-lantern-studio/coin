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
  \class SoX3DBackgroundNode SoX3DBackgroundNode.h Inventor/X3Dnodes/SoX3DBackgroundNode.h
  \brief The SoX3DBackgroundNode is an abstract base type for all background nodes in the X3D specification.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  X3DBackgroundNode : X3DBindableNode { 
    SFBool   [in]     set_bind
    MFFloat  [in,out] groundAngle []      [0,π/2]
    MFColor  [in,out] groundColor []      [0,1]
    SFNode   [in,out] metadata    NULL    [X3DMetadataObject]
    MFFloat  [in,out] skyAngle    []      [0,π]
    MFColor  [in,out] skyColor    0 0 0   [0,1]
    SFTime   [out]    bindTime
    SFBool   [out]    isBound
  }
  \endverbatim

  X3DBackgroundNode is the abstract type from which all backgrounds inherit. X3DBackgroundNode is a bindable node that when bound to defines the panoramic background for the scene. For complete information on backgrounds, see "24.2 Concepts" (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/enveffects.html#Concepts).

*/

/*!
  SoMFFloat SoX3DBackgroundNode::groundAngle
  An exposed field specifying the angles from the nadir that the concentric circles of colour appear.
*/

/*!
  SoMFColor SoX3DBackgroundNode::groundColor
  An exposed field specifying the colour of the ground at the various angles on the ground partial sphere. 
*/

/*!
  SoMFFloat SoX3DBackgroundNode::skyAngle
  An exposed field specifying the angles from the zenith in which concentric circles of colour appear.
*/

/*!
  SoMFColor SoX3DBackgroundNode::skyColor
  An exposed field specifying the colour of the sky at various angles on the sky sphere.  
*/


#include <Inventor/X3Dnodes/SoX3DBackgroundNode.h>
#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "nodes/SoSubNodeP.h"

// *************************************************************************

class SoX3DBackgroundNodeP {
};

// *************************************************************************

SO_NODE_SOURCE(SoX3DBackgroundNode);

// *************************************************************************

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DBackgroundNode::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DBackgroundNode, SO_X3D_NODE_TYPE);
}

#define PRIVATE(thisp) ((thisp)->pimpl)

SoX3DBackgroundNode::SoX3DBackgroundNode(void)
  : SoX3DBindableNode()
{
  PRIVATE(this) = new SoX3DBackgroundNodeP;

  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DBackgroundNode);

  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(groundAngle);
  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(groundColor);
  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(skyAngle);
  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(skyColor);
}

SoX3DBackgroundNode::~SoX3DBackgroundNode()
{
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
