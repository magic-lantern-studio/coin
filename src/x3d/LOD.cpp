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
  \class SoX3DLOD SoX3DLOD.h Inventor/X3Dnodes/SoX3DLOD.h
  \brief The SoX3DLOD class is used to represent various levels of detail based on distance.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  LOD : X3DGroupingNode {
    MFNode  [in]     addChildren             [X3DChildNode]
    MFNode  [in]     removeChildren          [X3DChildNode]
    MFNode  [in,out] children       []       [X3DChildNode]
    SFNode  [in,out] metadata       NULL     [X3DMetadataObject]
    SFVec3f []       bboxCenter     0 0 0    (-∞,∞)
    SFVec3f []       bboxSize       -1 -1 -1 [0,∞) or −1 −1 −1
    SFVec3f []       center         0 0 0    (-∞,∞)
    MFFloat []       range          []       [0,∞) or -1 
  }
  \endverbatim

The LOD node specifies various levels of detail or complexity for a given object, and provides hints allowing browsers to automatically choose the appropriate version of the object based on the distance from the user. The children field contains a list of nodes that represent the same object or objects at varying levels of detail, ordered from highest level of detail to the lowest level of detail. The range field specifies the ideal distances at which to switch between the levels. However, browsers are allowed to disregard level distances in order to provide better performance. "10.2.1 Grouping and children node types" (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Groupingandchildrennodes) contains details on the types of nodes that are legal values for children.

  The center field is a translation offset in the local coordinate
  system that specifies the centre of the LOD node for distance
  calculations.

  The number of nodes in the level field shall exceed the number of
  values in the range field by one (i.e., N+1 level values for N range
  values). The range field contains monotonic increasing values that
  shall be greater than zero. In order to calculate which level to
  display, first the distance is calculated from the viewer's
  location, transformed into the local coordinate system of the LOD
  node (including any scaling transformations), to the center point of
  the LOD node.  Then, the LOD node evaluates the step function L(d)
  to choose a level for a given value of d (where d is the distance
  from the viewer position to the centre of the LOD node).

  Let n ranges, R0, R1, R2, ..., Rn-1, partition the domain (0, +infinity)
  into n+1 subintervals given by (0, R0), [R0, R1)...  , [Rn-1,
  +infinity). Also, let n levels L0, L1, L2, ..., Ln-1 be the values
  of the step function function L(d). The level node, L(d), for a
  given distance d is defined as follows:

  \verbatim
    L(d) = L0,   if d < R0,
         = Li+1, if Ri <= d < Ri+1, for -1 < i < n-1,
         = Ln-1, if d >= Rn-1.
  \endverbatim

  The L(d)th node of the children field is that which is displayed

  Specifying too few levels will result in the last level being used
  repeatedly for the lowest levels of detail. If more levels than
  ranges are specified, the extra levels are ignored. An empty range
  field is an exception to this rule. This case is a hint to the
  browser that it may choose a level automatically to maintain a
  constant display rate. Each value in the range field shall be
  greater than the previous value.

  LOD nodes are evaluated top-down in the scene graph. Only the
  descendants of the currently selected level are rendered. All nodes
  under an LOD node continue to receive and send events regardless of
  which LOD node's level is active. For example, if an active
  TimeSensor node is contained within an inactive level of an LOD
  node, the TimeSensor node sends events regardless of the LOD node's
  state.

  The bboxCenter and bboxSize fields specify a bounding box that encloses the LOD node's children. This is a hint that may be used for optimization purposes. The results are undefined if the specified bounding box is smaller than the actual bounding box of the child with the largest bounding box at any time. A default bboxSize value, (−1, −1, −1), implies that the bounding box is not specified and, if needed, is calculated by the browser. A description of the bboxCenter and bboxSize fields is contained in "10.2.2 Bounding boxes" (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Boundingboxes).
*/

/*!
  \var SoMFFloat SoX3DLOD::range
  The range for each level.
*/

/*!
  \var SoSFVec3f SoX3DLOD::center
  The center used when calculating distance.
*/

/*!
  \var SoMFNode SoX3DLOD::level
  The different levels.
*/

#include <Inventor/X3Dnodes/SoX3DLOD.h>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/X3Dnodes/SoX3DParent.h>
#include <Inventor/actions/SoX3DGLRenderAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/misc/SoChildList.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/SbMatrix.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/system/gl.h>

#include "glue/glp.h"
#include "rendering/SoGL.h"
#include "nodes/SoSubNodeP.h"
#include "nodes/SoSoundElementHelper.h"
#include "profiler/SoNodeProfiling.h"

// *************************************************************************

class SoX3DLODP  : public SoSoundElementHelper
{
public:
  SbBool childlistvalid;
};

#define PRIVATE(obj) ((obj)->pimpl)

// *************************************************************************

SO_NODE_SOURCE(SoX3DLOD);

// *************************************************************************

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DLOD::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DLOD, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DLOD::SoX3DLOD(void)
{
  this->commonConstructor();
}

/*!
  Destructor.
*/
SoX3DLOD::~SoX3DLOD() // virtual, protected
{
  delete PRIVATE(this);
}

/*!
  Constructor. \a levels is the expected number of levels.
*/
SoX3DLOD::SoX3DLOD(int levels)
  : SoGroup(levels)
{
  this->commonConstructor();
}

void
SoX3DLOD::commonConstructor(void)
{
  PRIVATE(this) = new SoX3DLODP;
  PRIVATE(this)->childlistvalid = FALSE;
  
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DLOD);

  SO_X3DNODE_ADD_FIELD(center, (0.0f, 0.0f, 0.0f));
  SO_X3DNODE_ADD_EMPTY_MFIELD(range);
  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(level);

  // HACK WARNING: All children of this node are stored in the level
  // field. Avoid double notifications (because of notification
  // through SoChildList) be reallocating the SoChildList with a
  // NULL-parent here. SoGroup will have allocated an SoChildList in
  // its constructor when we get here.
  delete this->SoGroup::children;
  this->SoGroup::children = new SoChildList(NULL);
}

// *************************************************************************

// Doc in parent
SbBool
SoX3DLOD::affectsState(void) const // virtual
{
  return FALSE;
}

/*!
  Adds a new level.
*/
void
SoX3DLOD::addLevel(SoNode * levelptr)
{
  this->addChild(levelptr);
}

/*!
  Inserts a new level.
*/
void
SoX3DLOD::insertLevel(SoNode * levelptr,
                       int idx)
{
  this->insertChild(levelptr, idx);
}

/*!
  Returns a level.
*/
SoNode *
SoX3DLOD::getLevel(int idx) const
{
  return this->getChild(idx);
}

/*!
  Find \a node, and return the level index or -1 if not found.
*/
int
SoX3DLOD::findLevel(const SoNode * node) const
{
  return this->findChild(node);
}

/*!
  Return the number of levels.
*/
int
SoX3DLOD::getNumLevels(void) const
{
  return this->level.getNum();
}

/*!
  Removes the level at index \a idx.
*/
void
SoX3DLOD::removeLevel(int idx)
{
  this->removeChild(idx);
}

/*!
  Find \a level, and remove it if found.
*/
void
SoX3DLOD::removeLevel(SoNode * levelptr)
{
  this->removeChild(levelptr);
}

/*!
  Remove all levels.
*/
void
SoX3DLOD::removeAllLevels(void)
{
  this->removeAllChildren();
}

/*!
  Replace the level at \a idx with \a node.
*/
void
SoX3DLOD::replaceLevel(int idx,
                        SoNode * node)
{
  this->replaceChild(idx, node);
}

/*!
  Find \a oldnode, and replace it with \a newnode.
*/
void
SoX3DLOD::replaceLevel(SoNode * oldnode,
                        SoNode * newnode)
{
  this->replaceChild(oldnode, newnode);
}

// Doc in parent
void
SoX3DLOD::doAction(SoAction * action)
{
  int numindices;
  const int * indices;
  SoAction::PathCode pathcode = action->getPathCode(numindices, indices);
  if (pathcode == SoAction::IN_PATH) {
    this->getChildren()->traverseInPath(action, numindices, indices);
  }
  else {
    int idx = this->whichToTraverse(action);;
    if (idx >= 0) {
      this->getChildren()->traverse(action, idx);
      PRIVATE(this)->enableTraversingOfInactiveChildren();
      PRIVATE(this)->traverseInactiveChildren(this, action, idx, pathcode,
                                              this->getNumChildren(), 
                                              this->getChildren());
    }
  }
}

// doc in parent
void
SoX3DLOD::callback(SoCallbackAction * action)
{
  SoX3DLOD::doAction((SoAction*)action);
}

// doc in parent
void
SoX3DLOD::GLRender(SoX3DGLRenderAction * action)
{
  switch (action->getCurPathCode()) {
  case SoAction::NO_PATH:
  case SoAction::BELOW_PATH:
    SoX3DLOD::GLRenderBelowPath(action);
    break;
  case SoAction::IN_PATH:
    SoX3DLOD::GLRenderInPath(action);
    break;
  case SoAction::OFF_PATH:
    SoX3DLOD::GLRenderOffPath(action);
    break;
  default:
    assert(0 && "unknown path code.");
    break;
  }
}

// doc in parent
void
SoX3DLOD::rayPick(SoRayPickAction * action)
{
  SoX3DLOD::doAction((SoAction*) action);
}

// doc in parent
void
SoX3DLOD::getBoundingBox(SoGetBoundingBoxAction * action)
{
  // FIXME: SGI OIV seems to do some extra work here, but the manual
  // pages states that it should do a normal SoGroup traversal.
  // we should _not_ use whichToTraverse() to calculate bbox as
  // this would cause cache dependencies on the camera and
  // the model matrix.                       pederb, 2001-02-21
  inherited::getBoundingBox(action);
}

// doc in parent
void
SoX3DLOD::search(SoSearchAction * action)
{
  inherited::search(action);
}

// doc in parent
void
SoX3DLOD::write(SoWriteAction * action)
{
  SoNode::write(action);
}

// doc in parent
void
SoX3DLOD::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  SoX3DLOD::doAction((SoAction*) action);
}

// doc in parent
void
SoX3DLOD::audioRender(SoAudioRenderAction * action)
{
  PRIVATE(this)->preAudioRender(this, action);
  SoX3DLOD::doAction((SoAction*) action);
  PRIVATE(this)->postAudioRender(this, action);
}

// doc in parent
void
SoX3DLOD::GLRenderBelowPath(SoX3DGLRenderAction * action)
{
  int idx = this->whichToTraverse(action);
  if (idx >= 0) {
    SoNode * child = (SoNode*) this->getChildren()->get(idx);
    action->pushCurPath(idx, child);
    if (!action->abortNow()) {
      SoNodeProfiling profiling;
      profiling.preTraversal(action);
      child->GLRenderBelowPath(action);
      profiling.postTraversal(action);
#if COIN_DEBUG
      // The GL error test is default disabled for this optimized
      // path.  If you get a GL error reporting an error in the
      // Separator node, enable this code by setting the environment
      // variable COIN_GLERROR_DEBUGGING to "1" to see exactly which
      // node caused the error.
      static SbBool chkglerr = sogl_glerror_debugging();
      if (chkglerr) {
        cc_string str;
        cc_string_construct(&str);
        const unsigned int errs = coin_catch_gl_errors(&str);
        if (errs > 0) {
          SoDebugError::post("SoX3DLOD::GLRenderBelowPath",
                             "glGetError()s => '%s', nodetype: '%s'",
                             cc_string_get_text(&str),
                             (*this->getChildren())[idx]->getTypeId().getName().getString());
        }
        cc_string_clean(&str);
      }
#endif // COIN_DEBUG
    }
    action->popCurPath();
  }
  // don't auto cache LOD nodes.
  SoGLCacheContextElement::shouldAutoCache(action->getState(),
                                           SoGLCacheContextElement::DONT_AUTO_CACHE);
}

// doc in parent
void
SoX3DLOD::GLRenderInPath(SoX3DGLRenderAction * action)
{
  int numindices;
  const int * indices;
  SoAction::PathCode pathcode = action->getPathCode(numindices, indices);

  if (pathcode == SoAction::IN_PATH) {
    for (int i = 0; (i < numindices) && !action->hasTerminated(); i++) {
      int idx = indices[i];
      SoNode * child = this->getChild(idx);
      action->pushCurPath(idx, child);
      if (!action->abortNow()) {
        SoNodeProfiling profiling;
        profiling.preTraversal(action);
        child->GLRenderInPath(action);
        profiling.postTraversal(action);
      }
      action->popCurPath(pathcode);
    }
  }
  else {
    assert(pathcode == SoAction::BELOW_PATH);
    SoX3DLOD::GLRenderBelowPath(action);
  }
}

// doc in parent
void
SoX3DLOD::GLRenderOffPath(SoX3DGLRenderAction * action)
{
  int idx = this->whichToTraverse(action);;
  if (idx >= 0) {
    SoNode * child = this->getChild(idx);
    if (child->affectsState()) {
      action->pushCurPath(idx, child);
      if (!action->abortNow()) {
        SoNodeProfiling profiling;
        profiling.preTraversal(action);
        child->GLRenderOffPath(action);
        profiling.postTraversal(action);
      }
      action->popCurPath();
    }
  }
}

// doc in parent
void
SoX3DLOD::addChild(SoNode * child)
{
  this->level.addNode(child);
  PRIVATE(this)->childlistvalid = FALSE;
}

// doc in parent
void
SoX3DLOD::insertChild(SoNode * child, int idx)
{
  this->level.insertNode(child, idx);
  PRIVATE(this)->childlistvalid = FALSE;
}

// doc in parent
SoNode *
SoX3DLOD::getChild(int idx) const
{
  return this->level.getNode(idx);
}

// doc in parent
int
SoX3DLOD::findChild(const SoNode * child) const
{
  return this->level.findNode(child);
}

// doc in parent
int
SoX3DLOD::getNumChildren(void) const // virtual
{
  return this->level.getNumNodes();
}

// doc in parent
void
SoX3DLOD::removeChild(int idx)
{
  this->level.removeNode(idx);
  PRIVATE(this)->childlistvalid = FALSE;
}

// doc in parent
void
SoX3DLOD::removeChild(SoNode * child)
{
  this->level.removeNode(child);
  PRIVATE(this)->childlistvalid = FALSE;
}

// doc in parent
void
SoX3DLOD::removeAllChildren(void)
{
  this->level.removeAllNodes();
  SoGroup::children->truncate(0);
  PRIVATE(this)->childlistvalid = TRUE;
}

// doc in parent
void
SoX3DLOD::replaceChild(int idx, SoNode * child)
{
  this->level.replaceNode(idx, child);
  PRIVATE(this)->childlistvalid = FALSE;
}

// doc in parent
void
SoX3DLOD::replaceChild(SoNode * old,
                           SoNode * child)
{
  this->level.replaceNode(old, child);
  PRIVATE(this)->childlistvalid = FALSE;
}

// doc in parent
void
SoX3DLOD::notify(SoNotList * list)
{
  SoField * f = list->getLastField();
  if (f == &this->level) {
    PRIVATE(this)->childlistvalid = FALSE;
  }
  inherited::notify(list);
  PRIVATE(this)->notifyCalled();
}

// doc in parent
SbBool
SoX3DLOD::readInstance(SoInput * in,
                        unsigned short flags)
{
  SoGroup::children->truncate(0);
  SbBool oldnot = this->level.enableNotify(FALSE);
  SbBool ret = inherited::readInstance(in, flags);
  if (oldnot) this->level.enableNotify(TRUE);
  PRIVATE(this)->childlistvalid = FALSE;
  return ret;
}

// doc in parent
void
SoX3DLOD::copyContents(const SoFieldContainer * from,
                       SbBool copyConn)
{
  SoGroup::children->truncate(0);
  SoNode::copyContents(from, copyConn);
  PRIVATE(this)->childlistvalid = FALSE;
}

/*!
  Returns the child to traverse based on distance to current viewpoint.
*/
int
SoX3DLOD::whichToTraverse(SoAction * action)
{
  // FIXME: according to the spec, if range is empty, we should decide
  // a level to try to maintain a constant/high frame rate...
  // pederb, 2002-06-10
  SoState * state = action->getState();
  const SbMatrix & mat = SoModelMatrixElement::get(state);
  const SbViewVolume & vv = SoViewVolumeElement::get(state);

  SbVec3f worldcenter;
  mat.multVecMatrix(this->center.getValue(), worldcenter);

  float dist = (vv.getProjectionPoint() - worldcenter).length();

  int i;
  int n = this->range.getNum();

  for (i = 0; i < n; i++) {
    if (dist < this->range[i]) break;
  }
  if (i >= this->getNumChildren()) i = this->getNumChildren() - 1;
  return i;
}

// doc in parent
SoChildList *
SoX3DLOD::getChildren(void) const
{
  if (!PRIVATE(this)->childlistvalid) {
    SoX3DParent::updateChildList(this->level.getValues(0),
                                  this->level.getNum(),
                                  *SoGroup::children);
    ((SoX3DLOD*)this)->pimpl->childlistvalid = TRUE;
  }
  return SoGroup::children;
}

#undef PRIVATE

#endif // HAVE_X3D
