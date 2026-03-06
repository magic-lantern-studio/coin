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
  \class SoX3DBindableNode SoX3DBindableNode.h Inventor/X3Dnodes/SoX3DBindableNode.h
  \brief The SoX3DBindableNode is an abstract base type for all bindable nodes in the X3D specification.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  X3DBindableNode : X3DChildNode {
    SFBool [in]     set_bind
    SFNode [in,out] metadata NULL [X3DMetadataObject]
    SFTime [out]    bindTime
    SFBool [out]    isBound
  }
  \endverbatim

  X3DBindableNode is the abstract base type for all bindable children nodes, including Background, TextureBackground, Fog, NavigationInfo and Viewpoint. For complete discussion of bindable behaviors, see "7.2.2 Bindable children nodes" (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/core.html#BindableChildrenNodes).
*/

/*!
  SoSFBool SoX3DBindableNode::set_bind
  An eventIn which is triggered when a node should be bound.
*/

/*!
  SoSFTime SoX3DBindableNode::bindTime
  An eventOut that is sent when the node has been bound.
*/

/*!
  SoSFBool SoX3DBindable::isBound
  An eventOut that is sent after the node has been bound/unbound.
*/

#include <Inventor/X3Dnodes/SoX3DBindableNode.h>
#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "nodes/SoSubNodeP.h"

// *************************************************************************

class SoX3DBindableNodeP {
};

// *************************************************************************

SO_NODE_SOURCE(SoX3DBindableNode);

// *************************************************************************

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DBindableNode::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DBindableNode, SO_X3D_NODE_TYPE);
}

#define PRIVATE(thisp) ((thisp)->pimpl)

SoX3DBindableNode::SoX3DBindableNode(void)
  : SoX3DChildNode()
{
  PRIVATE(this) = new SoX3DBindableNodeP;

  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DBindableNode);

  SO_X3DNODE_ADD_EVENT_IN(set_bind);
  SO_X3DNODE_ADD_EVENT_OUT(bindTime);
  SO_X3DNODE_ADD_EVENT_OUT(isBound);
}

SoX3DBindableNode::~SoX3DBindableNode()
{
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
