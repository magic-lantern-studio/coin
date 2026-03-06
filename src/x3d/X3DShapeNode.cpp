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
  \class SoX3DShapeNode SoX3DShapeNode.h Inventor/X3Dnodes/SoX3DShapeNode.h
  \brief The SoX3DShapeNode is an abstract node type for all shapes in the X3D specification.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  X3DShapeNode : X3DChildNode, X3DBoundedObject {
    SFNode  [in,out] appearance NULL     [X3DAppearanceNode]
    SFNode  [in,out] geometry   NULL     [X3DGeometryNode]
    SFNode  [in,out] metadata   NULL     [X3DMetadataObject]
    SFVec3f []       bboxCenter 0 0 0    (-∞,∞)
    SFVec3f []       bboxSize   -1 -1 -1 [0,∞) or −1 −1 −1
  }
  \endverbatim

  This is the base node type for all Shape nodes.

*/

/*!
  SoSFNode SoX3DShapeNode::appearance
  An X3DAppearanceNode.
*/

/*!
  SoSFNode SoX3DShapeNode::geometry
  An X3DGeometryNode.
*/

#include <Inventor/X3Dnodes/SoX3DShapeNode.h>
#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "nodes/SoSubNodeP.h"

// *************************************************************************

class SoX3DShapeNodeP {
};

// *************************************************************************

SO_NODE_SOURCE(SoX3DShapeNode);

// *************************************************************************

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DShapeNode::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DShapeNode, SO_X3D_NODE_TYPE);
}

#define PRIVATE(thisp) ((thisp)->pimpl)

/*!
  Constructor.
*/
SoX3DShapeNode::SoX3DShapeNode(void)
  : SoX3DChildNode()
{
  PRIVATE(this) = new SoX3DShapeNodeP;

  SO_X3DNODE_ADD_EXPOSED_FIELD(appearance, (NULL));
  SO_X3DNODE_ADD_EXPOSED_FIELD(geometry, (NULL));

  SO_X3DNODE_ADD_FIELD(bboxCenter, (0, 0, 0));
  SO_X3DNODE_ADD_FIELD(bboxCenter, (-1, -1, -1));
  // FIXME: bboxCenter and bboxSize should be implemented in the
  // SoX3DBoundedObject. Unfortuantely, Coin does not handle multiple
  // inhertance very well due to the mechanism/macros used to determine
  // node type and field management (ambiguous method errors). For now, 
  // place these fields here.
  // 2026-03-11 msm (WizzerWorks)
}

/*!
  Destructor.
*/
SoX3DShapeNode::~SoX3DShapeNode()
{
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
