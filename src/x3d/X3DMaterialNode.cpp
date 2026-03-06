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
  \class SoX3DMaterialNode SoX3DMaterialNode.h Inventor/X3Dnodes/SoX3DMaterialNode.h
  \brief The SoX3DMaterialNode is a base node type for the child nodes of X3DMaterialNode type.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  X3DMaterialNode : X3DAppearanceChildNode {
    SFNode [in,out] metadata NULL [X3DMetadataObject]
  }
  \endverbatim

  This is the base node type for the child nodes of the X3DMaterialNode type.

*/

#include <Inventor/X3Dnodes/SoX3DMaterialNode.h>
#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "nodes/SoSubNodeP.h"

// *************************************************************************

class SoX3DMaterialNodeP {
};

// *************************************************************************

SO_NODE_SOURCE(SoX3DMaterialNode);

// *************************************************************************

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DMaterialNode::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DMaterialNode, SO_X3D_NODE_TYPE);
}

#define PRIVATE(thisp) ((thisp)->pimpl)

SoX3DMaterialNode::SoX3DMaterialNode(void)
  : SoX3DAppearanceChildNode()
{
  PRIVATE(this) = new SoX3DMaterialNodeP;

  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DMaterialNode);
}

SoX3DMaterialNode::~SoX3DMaterialNode()
{
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
