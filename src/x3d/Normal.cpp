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
  \class SoX3DNormal SoX3DNormal.h Inventor/X3Dnodes/SoX3DNormal.h
  \brief The SoX3DNormal class is used to bind normals to geometry.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT

  \verbatim
  Normal {
    exposedField MFVec3f vector  []   # (-,)
  }
  \endverbatim

  This node defines a set of 3D surface normal vectors to be used in
  the vector field of some geometry nodes (e.g., SoX3DIndexedFaceSet
  and SoX3DElevationGrid). This node contains one multiple-valued
  field that contains the normal vectors. Normals shall be of unit
  length.
*/

/*!
  \var SoMFVec3f SoX3DNormal::vector
  The normal vectors. Empty by default.
*/

#include <Inventor/X3Dnodes/SoX3DNormal.h>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoNormalElement.h>
#include <Inventor/elements/SoGLVBOElement.h>

#include "nodes/SoSubNodeP.h"
#include "rendering/SoVBO.h"

SO_NODE_SOURCE(SoX3DNormal);

class SoX3DNormalP {
 public:
  SoX3DNormalP() : vbo(NULL) { }
  ~SoX3DNormalP() { delete this->vbo; }
  
  SoVBO * vbo;
};

#define PRIVATE(obj) obj->pimpl

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DNormal::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DNormal, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DNormal::SoX3DNormal(void)
{
  PRIVATE(this) = new SoX3DNormalP;
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DNormal);

  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(vector);
}

/*!
  Destructor.
*/
SoX3DNormal::~SoX3DNormal()
{
  delete PRIVATE(this);
}

// Doc in parent
void
SoX3DNormal::doAction(SoAction * action)
{
  SoNormalElement::set(action->getState(), this,
                       this->vector.getNum(), this->vector.getValues(0));
}

// Doc in parent
void
SoX3DNormal::GLRender(SoGLRenderAction * action)
{
  //
  // FIXME: code to test if all normals are unit length, and store
  // this in some cached variable.  should be passed on to
  // SoGLNormalizeElement to optimize rendering (pederb)
  //
  SoX3DNormal::doAction((SoAction*) action);
  SoState * state = action->getState();
  
  SoBase::staticDataLock();
  SbBool setvbo = FALSE;
  const int num = this->vector.getNum();
  if (SoGLVBOElement::shouldCreateVBO(state, num)) {
    setvbo = TRUE;
    SbBool dirty = FALSE;
    if (PRIVATE(this)->vbo == NULL) {
      PRIVATE(this)->vbo = new SoVBO(GL_ARRAY_BUFFER, GL_STATIC_DRAW); 
      dirty =  TRUE;
    }
    else if (PRIVATE(this)->vbo->getBufferDataId() != this->getNodeId()) {
      dirty = TRUE;
    }
    if (dirty) {
      PRIVATE(this)->vbo->setBufferData(this->vector.getValues(0),
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
    SoGLVBOElement::setNormalVBO(state, PRIVATE(this)->vbo);
  }

}

// Doc in parent
void
SoX3DNormal::callback(SoCallbackAction * action)
{
  SoX3DNormal::doAction((SoAction*) action);
}

// Doc in parent
void
SoX3DNormal::pick(SoPickAction * action)
{
  SoX3DNormal::doAction((SoAction*) action);
}

// Doc in parent
void
SoX3DNormal::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  SoX3DNormal::doAction((SoAction*) action);
}

#undef PRIVATE
#endif // HAVE_X3D
