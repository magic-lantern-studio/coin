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
  \class SoX3DVertexPoint SoX3DVertexPoint.h Inventor/X3Dnodes/SoX3DVertexPoint.h
  \brief The SoX3DVertexPoint class is a superclass for point based X3D shapes.
*/

/*!
  \var SoSFNode SoX3DVertexPoint::coord
  Should contain an SoX3DCoordinate node.
*/

/*!
  \var SoSFNode SoX3DVertexPoint::color
  Can contain an SoX3DColor node when color per point is needed.
*/

#include <Inventor/X3Dnodes/SoX3DVertexPoint.h>
#include "coindefs.h"

#include <cstddef>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/X3Dnodes/SoX3DCoordinate.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>

#include "nodes/SoSubNodeP.h"

SO_NODE_ABSTRACT_SOURCE(SoX3DVertexPoint);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DVertexPoint::initClass(void)
{
  SO_NODE_INTERNAL_INIT_ABSTRACT_CLASS(SoX3DVertexPoint, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DVertexPoint::SoX3DVertexPoint(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DVertexPoint);

  SO_X3DNODE_ADD_EXPOSED_FIELD(coord, (NULL));
  SO_X3DNODE_ADD_EXPOSED_FIELD(color, (NULL));
}

/*!
  Destructor.
*/
SoX3DVertexPoint::~SoX3DVertexPoint()
{
}

// Doc in parent
void
SoX3DVertexPoint::doAction(SoAction * action)
{
  SoNode * node;

  node = this->coord.getValue();
  if (node) node->doAction(action);

  node = this->color.getValue();
  if (node) node->doAction(action);
}

// Doc in parent
void
SoX3DVertexPoint::GLRender(SoGLRenderAction * action)
{
  SoNode * node;

  node = this->coord.getValue();
  if (node) node->GLRender(action);

  node = this->color.getValue();
  if (node) node->GLRender(action);
}

// Doc in parent
void
SoX3DVertexPoint::getBoundingBox(SoGetBoundingBoxAction * action)
{
  inherited::getBoundingBox(action);
}

// Doc in parent
void
SoX3DVertexPoint::callback(SoCallbackAction * action)
{
  inherited::callback(action);
}

// Doc in parent
void
SoX3DVertexPoint::pick(SoPickAction * action)
{
  inherited::pick(action);
}

// Doc in parent
void
SoX3DVertexPoint::notify(SoNotList * list)
{
  inherited::notify(list);
}

// Doc in parent
void
SoX3DVertexPoint::computeBBox(SoAction * COIN_UNUSED_ARG(action), SbBox3f & box,
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

// Doc in parent
void
SoX3DVertexPoint::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  if (!this->shouldPrimitiveCount(action)) return;

  SoX3DCoordinate * c = (SoX3DCoordinate*) this->coord.getValue();
  if (c) {
    action->addNumPoints(c->point.getNum());
  }
}

// Doc in parent
SbBool
SoX3DVertexPoint::shouldGLRender(SoGLRenderAction * action)
{
  if (this->coord.getValue() == NULL) return FALSE;
  return inherited::shouldGLRender(action);
}

#endif // HAVE_X3D
