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
  \class SoX3DPointSet SoX3DPointSet.h Inventor/X3Dnodes/SoX3DPointSet.h
  \brief The SoX3DPointSet class is used to represent a set of 3D points.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  PointSet : X3DGeometryNode { 
    SFNode [in,out] color    NULL [X3DColorNode]
    SFNode [in,out] coord    NULL [X3DCoordinateNode]
    SFNode [in,out] metadata NULL [X3DMetadataObject]
  }
  \endverbatim
  
  The PointSet node specifies a set of 3D points, in the local
  coordinate system, with associated colours at each point. The \e coord
  field specifies a SoX3DCoordinate node (or instance of a Coordinate
  node). The results are undefined if the \e coord field specifies any
  other type of node. PointSet uses the coordinates in order. If the
  \e coord field is NULL, the point set is considered empty.

  PointSet nodes are not lit, not texture-mapped, nor do they participate in
  collision detection. The size of each point is implementation-
  dependent.

  If the \e color field is not NULL, it shall specify a
  SoX3DColor node that contains at least the number of points
  contained in the \e coord node. The results are undefined if the \e color
  field specifies any other type of node. Colours shall be applied to
  each point in order. The results are undefined if the number of
  values in the Color node is less than the number of values specified
  in the Coordinate node.

  If the \e color field is NULL and there is a
  SoX3DMaterial node defined for the SoX3DAppearance node affecting
  this PointSet node, the \e emissiveColor of the Material node shall be
  used to draw the points. More details on lighting equations can be
  found in [17 Lighting component](https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/lighting.html).
*/

/*!
  \var SoSFNode SoX3DPointSet::coord
  Should contain an SoX3DCoordinate node.
*/

/*!
  \var SoSFNode SoX3DPointSet::color
  Can contain an SoX3DColor node when color per point is needed.
*/

#include <Inventor/X3Dnodes/SoX3DPointSet.h>
#include "coindefs.h"

#include <cstddef>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/X3Dnodes/SoX3DCoordinate.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>

#include "nodes/SoSubNodeP.h"

SO_NODE_ABSTRACT_SOURCE(SoX3DPointSet);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DPointSet::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DPointSet, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DPointSet::SoX3DPointSet(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DPointSet);

  SO_X3DNODE_ADD_EXPOSED_FIELD(coord, (NULL));
  SO_X3DNODE_ADD_EXPOSED_FIELD(color, (NULL));
}

/*!
  Destructor.
*/
SoX3DPointSet::~SoX3DPointSet()
{
}

// doc in parent
void
SoX3DPointSet::doAction(SoAction * action)
{
  SoNode * node;

  node = this->coord.getValue();
  if (node) node->doAction(action);

  node = this->color.getValue();
  if (node) node->doAction(action);
}

// doc in parent
void
SoX3DPointSet::GLRender(SoX3DGLRenderAction * action)
{
  SoNode * node;

  node = this->coord.getValue();
  if (node) node->GLRender(action);

  node = this->color.getValue();
  if (node) node->GLRender(action);
}

// doc in parent
void
SoX3DPointSet::getBoundingBox(SoGetBoundingBoxAction * action)
{
  inherited::getBoundingBox(action);
}

// doc in parent
void
SoX3DPointSet::callback(SoX3DCallbackAction * action)
{
  inherited::callback(action);
}

// doc in parent
void
SoX3DPointSet::pick(SoPickAction * action)
{
  inherited::pick(action);
}

// doc in parent
void
SoX3DPointSet::notify(SoNotList * list)
{
  inherited::notify(list);
}

// doc in parent
void
SoX3DPointSet::computeBBox(SoAction * COIN_UNUSED_ARG(action), SbBox3f & box,
                           SbVec3f & center)
{
  SoX3DCoordinate * node = (SoX3DCoordinate*) this->coord.getValue();
  if (node == NULL) return;

  int num = node->point.getNum();
  const SbVec3f * coords = node->point.getValues(0);

  box.makeEmpty();
  while (num--) {
    box.extendBy(*coords++);
  }
  if (!box.isEmpty()) center = box.getCenter();
}

// doc in parent
void
SoX3DPointSet::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  if (!this->shouldPrimitiveCount(action)) return;

  SoX3DCoordinate * c = (SoX3DCoordinate*) this->coord.getValue();
  if (c) {
    action->addNumPoints(c->point.getNum());
  }
}

// doc in parent
SbBool
SoX3DPointSet::shouldGLRender(SoX3DGLRenderAction * action)
{
  if (this->coord.getValue() == NULL) return FALSE;
  return inherited::shouldGLRender(action);
}

#endif // HAVE_X3D
