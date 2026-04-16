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
  \class SoX3DVertexLine SoX3DVertexLine.h Inventor/X3Dnodes/SoX3DVertexLine.h
  \brief The SoX3DVertexLine class is a superclass for line based X3D geometry.
*/

/*!
  \var SoSFNode SoX3DVertexLine::coord
  Should contain an SoX3DCoordinate node.
*/

/*!
  \var SoSFNode SoX3DVertexLine::color
  Can contain an SoX3DColor node if multiple colors are wanted.
*/

/*!
  \var SoSFBool SoX3DVertexLine::colorPerVertex

  When TRUE, colors will be bound per vertex, otherwise per
  line. Default value is TRUE.
  
*/

#include <Inventor/X3Dnodes/SoX3DVertexLine.h>

#include <cstddef>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/actions/SoX3DGLRenderAction.h>

#include "nodes/SoSubNodeP.h"

SO_NODE_ABSTRACT_SOURCE(SoX3DVertexLine);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DVertexLine::initClass(void)
{
  SO_NODE_INTERNAL_INIT_ABSTRACT_CLASS(SoX3DVertexLine, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DVertexLine::SoX3DVertexLine(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DVertexLine);

  SO_X3DNODE_ADD_EXPOSED_FIELD(coord, (NULL));
  SO_X3DNODE_ADD_EXPOSED_FIELD(color, (NULL));
  SO_X3DNODE_ADD_FIELD(colorPerVertex, (TRUE));
}

/*!
  Destructor.
*/
SoX3DVertexLine::~SoX3DVertexLine()
{
}

// doc in parent
void
SoX3DVertexLine::doAction(SoAction * action)
{
  SoNode * node;

  node = this->coord.getValue();
  if (node) node->doAction(action);

  node = this->color.getValue();
  if (node) node->doAction(action);
}

// doc in parent
void
SoX3DVertexLine::GLRender(SoX3DGLRenderAction * action)
{
  SoNode * node;
  
  node = this->coord.getValue();
  if (node) node->GLRender(action);
  
  node = this->color.getValue();
  if (node) node->GLRender(action);
}

// doc in parent
void
SoX3DVertexLine::getBoundingBox(SoGetBoundingBoxAction * action)
{
  inherited::getBoundingBox(action);
}

// doc in parent
void
SoX3DVertexLine::callback(SoCallbackAction * action)
{
  inherited::callback(action);
}

// doc in parent
void
SoX3DVertexLine::pick(SoPickAction * action)
{
  inherited::pick(action);
}

// doc in parent
void
SoX3DVertexLine::notify(SoNotList * list)
{
  inherited::notify(list);
}

// doc in parent
SbBool
SoX3DVertexLine::shouldGLRender(SoX3DGLRenderAction * action)
{
  if (this->coord.getValue() == NULL) return FALSE;
  return inherited::shouldGLRender(action);
}

#endif // HAVE_X3D
