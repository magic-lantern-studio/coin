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
  \class SoX3DCoordinate SoX3DCoordinate.h Inventor/X3Dnodes/SoX3DCoordinate.h
  \brief The SoX3DCoordinate class is used to define 3D coordinates for shapes.

  \ingroup coin_X3Dnodes
  
  \WEB3DCOPYRIGHT

  \verbatim
  Coordinate { 
    exposedField MFVec3f point  []      # (-inf, inf) 
  }
  \endverbatim
 
  This node defines a set of 3D coordinates to be used in the coord
  field of vertex-based geometry nodes including SoX3DIndexedFaceSet,
  SoX3DIndexedLineSet, and SoX3DPointSet.

*/

/*!
  \var SoMFVec3f SoX3DCoordinate::point
  The coordinates. Empty by default.
*/

#include <Inventor/X3Dnodes/SoX3DCoordinate.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/elements/SoGLVBOElement.h>
#include <Inventor/actions/SoAction.h>

#include "nodes/SoSubNodeP.h"
#include "rendering/SoVBO.h"

SO_NODE_SOURCE(SoX3DCoordinate);

#define PRIVATE(obj) obj->pimpl

class SoX3DCoordinateP {
 public:
  SoX3DCoordinateP() : vbo(NULL) { }
  ~SoX3DCoordinateP() { delete this->vbo; }
  SoVBO * vbo;
};

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DCoordinate::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DCoordinate, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DCoordinate::SoX3DCoordinate(void)
{
  PRIVATE(this) = new SoX3DCoordinateP;
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DCoordinate);

  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(point);
}

/*!
  Destructor.
*/
SoX3DCoordinate::~SoX3DCoordinate()
{
  delete PRIVATE(this);
}

// Doc in parent
void
SoX3DCoordinate::doAction(SoAction * action)
{
  SoCoordinateElement::set3(action->getState(), this,
                            point.getNum(), point.getValues(0));
}

// Doc in parent
void
SoX3DCoordinate::GLRender(SoGLRenderAction * action)
{
  SoX3DCoordinate::doAction((SoAction*) action);
  
  SoState * state = action->getState();
  const int num = this->point.getNum();
  SbBool setvbo = FALSE;
  SoBase::staticDataLock();
  if (SoGLVBOElement::shouldCreateVBO(state, num)) {
    SbBool dirty = FALSE;
    setvbo = TRUE;
    if (PRIVATE(this)->vbo == NULL) {
      PRIVATE(this)->vbo = new SoVBO(GL_ARRAY_BUFFER, GL_STATIC_DRAW); 
      dirty =  TRUE;
    }
    else if (PRIVATE(this)->vbo->getBufferDataId() != this->getNodeId()) {
      dirty = TRUE;
    }
    if (dirty) {
      PRIVATE(this)->vbo->setBufferData(this->point.getValues(0),
                                        num*sizeof(SbVec3f),
                                        this->getNodeId());
    }
  }
  else if (PRIVATE(this)->vbo && PRIVATE(this)->vbo->getBufferDataId()) {
    // clear buffers to deallocate VBO memory
    PRIVATE(this)->vbo->setBufferData(NULL, 0, 0);
  }
  SoBase::staticDataUnlock();
  if (setvbo) {
    SoGLVBOElement::setVertexVBO(state, PRIVATE(this)->vbo);
  }

}

// Doc in parent
void
SoX3DCoordinate::getBoundingBox(SoGetBoundingBoxAction * action)
{
  SoX3DCoordinate::doAction((SoAction*) action);
}

// Doc in parent
void
SoX3DCoordinate::callback(SoCallbackAction * action)
{
  SoX3DCoordinate::doAction((SoAction*) action);
}

// Doc in parent
void
SoX3DCoordinate::pick(SoPickAction * action)
{
  SoX3DCoordinate::doAction((SoAction*) action);
}

#undef PRIVATE
#endif // HAVE_X3D
