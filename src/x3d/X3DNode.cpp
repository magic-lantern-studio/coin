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
  \class SoX3DNode SoX3DNode.h Inventor/X3Dnodes/SoX3DNode.h
  \brief The SoX3DNode is an abstract node type and is the base type for all nodes in the X3D specification.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  X3DNode {
    SFNode [in,out] metadata NULL [X3DMetadataObject]
  }
  \endverbatim

  This abstract node type is the base type for all nodes in the X3D system.

*/

#include <Inventor/X3Dnodes/SoX3DNode.h>
#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "nodes/SoSubNodeP.h"

// *************************************************************************

class SoX3DNodeP {
};

// *************************************************************************

SO_NODE_SOURCE(SoX3DNode);

// *************************************************************************

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DNode::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DNode, SO_X3D_NODE_TYPE);
}

#define PRIVATE(thisp) ((thisp)->pimpl)

SoX3DNode::SoX3DNode(void)
  : SoNode()
{
  PRIVATE(this) = new SoX3DNodeP;

  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DNode);

  SO_X3DNODE_ADD_EXPOSED_FIELD(metadata, (NULL));
}

SoX3DNode::~SoX3DNode()
{
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
