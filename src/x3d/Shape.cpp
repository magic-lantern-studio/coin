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
  \class SoX3DShape SoX3DShape.h Inventor/X3Dnodes/SoX3DShape.h
  \brief The SoX3DShape class holds geometry and geometry appearance nodes.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  Shape : X3DShapeNode {
    SFNode  [in,out] appearance NULL     [X3DAppearanceNode]
    SFNode  [in,out] geometry   NULL     [X3DGeometryNode]
    SFNode  [in,out] metadata   NULL     [X3DMetadataObject]
    SFVec3f []       bboxCenter 0 0 0    (-∞,∞)
    SFVec3f []       bboxSize   -1 -1 -1 [0,∞) or −1 −1 −1
  }
  \endverbatim

  The Shape node has two fields, \e appearance and \e geometry, which
  are used to create rendered objects in the world. The \e appearance
  field contains an SoX3DAppearance node that specifies the visual
  attributes (e.g., material and texture) to be applied to the
  geometry. The geometry field contains a geometry node. The specified
  geometry node is rendered with the specified appearance nodes
  applied. See "12.2 Concepts"
  (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/shape.html#Concepts),
  and SoX3DAppearance, for more information.

  "17 Lighting component"
  (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/lighting.html),
  contains details of the X3D lighting model and the interaction
  between Appearance nodes and geometry nodes.

  If the geometry field is NULL, the object is not drawn.

  The bboxCenter and bboxSize fields specify a bounding box that encloses the Shape node's geometry. This is a hint that may be used for optimization purposes. The results are undefined if the specified bounding box is smaller than the actual bounding box of the geometry at any time. A default bboxSize value, (-1, -1, -1), implies that the bounding box is not specified and, if needed, is calculated by the browser. A description of the bboxCenter and bboxSize fields is contained in "10.2.2 Bounding boxes" (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Boundingboxes).
*/

/*!
  \enum SoX3DShape::CacheEnabled
  Used to enumerate cache strategies.
*/

/*!
  \var SoX3DShape::CacheEnabled SoX3DShape::OFF
  Never cache
*/

/*!
  \var SoX3DShape::CacheEnabled SoX3DShape::ON
  Always cache
*/

/*!
  \var SoX3DShape::CacheEnabled SoX3DShape::AUTO
  Use heuristics to try to figure out the optimal caching policy.
*/

/*!
  \var SoSFNode SoX3DShape::appearance
  Can store an SoX3DAppearance node, or NULL.
*/

/*!
  \var SoSFNode SoX3DShape::geometry
  Can store any SoX3DGeometry subclass, or NULL.
*/

/*!
  \var SoSFEnum SoX3DShape::renderCaching
  Render caching strategy. Default value is AUTO.
*/

/*!
  \var SoSFEnum SoX3DShape::boundingBoxCaching
  Bounding box caching strategy. Default value is AUTO.
*/

#include <Inventor/X3Dnodes/SoX3DShape.h>

#include <cstddef>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/X3Dnodes/SoX3DAppearance.h>
#include <Inventor/X3Dnodes/SoX3DMaterial.h>
#include <Inventor/X3Dnodes/SoX3DParent.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/misc/SoChildList.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/elements/SoLocalBBoxMatrixElement.h>
#include <Inventor/elements/SoCullElement.h>
#include <Inventor/elements/SoComplexityTypeElement.h>
#include <Inventor/caches/SoBoundingBoxCache.h>
#include <Inventor/caches/SoGLCacheList.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/caches/SoGLCacheList.h>
#include <Inventor/elements/SoGLShapeHintsElement.h>
#include <Inventor/system/gl.h>
#ifdef HAVE_THREADS
#include <Inventor/threads/SbMutex.h>
#endif // HAVE_THREADS

#include "rendering/SoGL.h"
#include "nodes/SoSubNodeP.h"
#include "tidbitsp.h"
#include "profiler/SoNodeProfiling.h"

// *************************************************************************

class SoX3DShapeP {
public:
  SoGLCacheList * cachelist;
  SoChildList * childlist;
  SbBool childlistvalid;

#ifdef COIN_THREADSAFE
  SbMutex childlistmutex;
  void lockChildList(void) { this->childlistmutex.lock(); }
  void unlockChildList(void) { this->childlistmutex.unlock(); }
#else // !COIN_THREADSAFE
  void lockChildList(void) { }
  void unlockChildList(void) { }
#endif // !COIN_THREADSAFE
};

// *************************************************************************

SO_NODE_SOURCE(SoX3DShape);

// *************************************************************************

static int sovrmlshape_numrendercaches = 0;

static void sovrmlshape_cleanup(void) {                                           
  sovrmlshape_numrendercaches = 0;
}

// *************************************************************************

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DShape::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DShape, SO_X3D_NODE_TYPE);
  coin_atexit((coin_atexit_f*)sovrmlshape_cleanup, CC_ATEXIT_NORMAL); 

  SoType type = SoX3DShape::getClassTypeId();
  SoRayPickAction::addMethod(type, SoNode::rayPickS);
}

#define PRIVATE(thisp) ((thisp)->pimpl)

SoX3DShape::SoX3DShape(void)
  : SoX3DShapeNode()
{
  PRIVATE(this) = new SoX3DShapeP;

  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DShape);

  SO_NODE_ADD_FIELD(renderCaching, (AUTO));
  SO_NODE_ADD_FIELD(boundingBoxCaching, (AUTO));

  SO_NODE_DEFINE_ENUM_VALUE(CacheEnabled, ON);
  SO_NODE_DEFINE_ENUM_VALUE(CacheEnabled, OFF);
  SO_NODE_DEFINE_ENUM_VALUE(CacheEnabled, AUTO);

  SO_NODE_SET_SF_ENUM_TYPE(renderCaching, CacheEnabled);
  SO_NODE_SET_SF_ENUM_TYPE(boundingBoxCaching, CacheEnabled);

  // supply a NULL-pointer as parent, since notifications will be 
  // handled by the fields that actually contain the node(s)
  PRIVATE(this)->childlist = new SoChildList(NULL);
  PRIVATE(this)->childlistvalid = FALSE;
  PRIVATE(this)->cachelist = NULL;
}

SoX3DShape::~SoX3DShape()
{
  delete PRIVATE(this)->childlist;
  delete PRIVATE(this)->cachelist;
  delete PRIVATE(this);
}

void
SoX3DShape::setNumRenderCaches(int num)
{
  sovrmlshape_numrendercaches = num;
}

int
SoX3DShape::getNumRenderCaches(void)
{
  return sovrmlshape_numrendercaches;
}

SbBool
SoX3DShape::affectsState(void) const
{
  return FALSE;
}

void
SoX3DShape::doAction(SoAction * action)
{
  SoState * state = action->getState();

  if (state->isElementEnabled(SoLazyElement::getClassStackIndex())) {
    if ((this->appearance.getValue() == NULL) ||
        (((SoX3DAppearance*)this->appearance.getValue())->material.getValue() == NULL)) {
      SoLazyElement::setLightModel(state, SoLazyElement::BASE_COLOR);
    }
  }

  state->push();
  int numindices;
  const int * indices;
  if (action->getPathCode(numindices, indices) == SoAction::IN_PATH) {
    this->getChildren()->traverseInPath(action, numindices, indices);
  }
  else {
    this->getChildren()->traverse(action); // traverse all children
  }
  state->pop();
}

void
SoX3DShape::callback(SoCallbackAction * action)
{
  SoX3DShape::doAction((SoAction*) action);
}

void
SoX3DShape::GLRender(SoGLRenderAction * action)
{
  SoState * state = action->getState();
  state->push();

  if ((this->appearance.getValue() == NULL) ||
      (((SoX3DAppearance*)this->appearance.getValue())->material.getValue() == NULL)) {
    SoLazyElement::setLightModel(state, SoLazyElement::BASE_COLOR);
  }

  int numindices;
  const int * indices;
  SoAction::PathCode pathcode = action->getPathCode(numindices, indices);

  SoNode ** childarray = (SoNode**) this->getChildren()->getArrayPtr();

  if (pathcode == SoAction::IN_PATH) {
    int lastchild = indices[numindices - 1];
    for (int i = 0; i <= lastchild && !action->hasTerminated(); i++) {
      SoNode * child = childarray[i];
      action->pushCurPath(i, child);
      if (action->getCurPathCode() != SoAction::OFF_PATH ||
          child->affectsState()) {
        if (!action->abortNow()) {
          SoNodeProfiling profiling;
          profiling.preTraversal(action);
          child->GLRender(action);
          profiling.postTraversal(action);
        }
        else {
          SoCacheElement::invalidate(state);
        }
      }
      action->popCurPath(pathcode);
    }
  }
  else {
    action->pushCurPath();
    int n = this->getChildren()->getLength();
    for (int i = 0; i < n && !action->hasTerminated(); i++) {
      action->popPushCurPath(i, childarray[i]);
      if (action->abortNow()) {
        // only cache if we do a full traversal
        SoCacheElement::invalidate(state);
        break;
      }
      SoNodeProfiling profiling;
      profiling.preTraversal(action);
      childarray[i]->GLRender(action);
      profiling.postTraversal(action);
    }
    action->popCurPath();
  }
  state->pop();
}

void
SoX3DShape::getBoundingBox(SoGetBoundingBoxAction * action)
{
  SoState * state = action->getState();
  state->push();
  int numindices;
  const int * indices;
  if (action->getPathCode(numindices, indices) == SoAction::IN_PATH) {
    this->getChildren()->traverseInPath(action, numindices, indices);
  }
  else {
    this->getChildren()->traverse(action); // traverse all children
  }
  state->pop();
}

void
SoX3DShape::rayPick(SoRayPickAction * action)
{
  SoX3DShape::doAction(action);
}

// doc in parent
void
SoX3DShape::write(SoWriteAction * action)
{
  // do not call inherited::write() or SoGroup::write()
  this->boundingBoxCaching.setDefault(TRUE);
  this->renderCaching.setDefault(TRUE);
  inherited::write(action);
}

void
SoX3DShape::search(SoSearchAction * action)
{
  // Include this node in the search.
  SoNode::search(action);
  if (action->isFound()) return;

  SoX3DShape::doAction(action);
}

void
SoX3DShape::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  SoX3DShape::doAction((SoAction*) action);
}

SoChildList *
SoX3DShape::getChildren(void) const
{
  if (!PRIVATE(this)->childlistvalid) {
    // this is not 100% thread safe. The assumption is that no nodes
    // will be added or removed while a scene graph is being
    // traversed. For Coin, this is an ok assumption.
    PRIVATE(this)->lockChildList();
    // test again after we've locked
    if (!PRIVATE(this)->childlistvalid) {
      SoX3DShape * thisp = (SoX3DShape*) this;
      SoX3DParent::updateChildList(thisp, *(PRIVATE(thisp)->childlist));
      PRIVATE(thisp)->childlistvalid = TRUE;
    }
    PRIVATE(this)->unlockChildList();
  }
  return PRIVATE(this)->childlist;
}

void
SoX3DShape::notify(SoNotList * list)
{
  SoField * f = list->getLastField();
  if (f && f->getTypeId() == SoSFNode::getClassTypeId()) {
    PRIVATE(this)->childlistvalid = FALSE;
  }
  inherited::notify(list);
}

void
SoX3DShape::copyContents(const SoFieldContainer * from,
                          SbBool copyConn)
{
  inherited::copyContents(from, copyConn);
  PRIVATE(this)->childlistvalid = FALSE;
  PRIVATE(this)->childlist->truncate(0);
}

#undef PRIVATE

#endif // HAVE_X3D
