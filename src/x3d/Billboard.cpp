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
  \class SoX3DBillboard SoX3DBillboard.h Inventor/X3Dnodes/SoX3DBillboard.h
  \brief The SoX3DBillboard class is used for rotating geometry towards the viewpoint.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  Billboard : X3DGroupingNode {
    MFNode  [in]     addChildren             [X3DChildNode]
    MFNode  [in]     removeChildren          [X3DChildNode]
    SFVec3f [in,out] axisOfRotation 0 1 0    (-∞,∞)
    MFNode  [in,out] children       []       [X3DChildNode]
    SFNode  [in,out] metadata       NULL     [X3DMetadataObject]
    SFVec3f []       bboxCenter     0 0 0    (-∞,∞)
    SFVec3f []       bboxSize       -1 -1 -1 [0,∞) or −1 −1 −1
  }
  \endverbatim

  The Billboard node is a grouping node which modifies its coordinate
  system so that the Billboard node's local Z-axis turns to point at
  the viewer.  The Billboard node has children which may be other
  children nodes.

  The axisOfRotation field specifies which axis to
  use to perform the rotation. This axis is defined in the local
  coordinate system.

  When the axisOfRotation field is not (0, 0, 0),
  the following steps describe how to rotate the billboard to face the
  viewer:

  \li a. Compute the vector from the Billboard node's origin to the
  viewer's position. This vector is called the billboard-to-viewer
  vector.

  \li b. Compute the plane defined by the axisOfRotation and the
  billboard-to-viewer vector.

  \li c. Rotate the local Z-axis of the billboard into the plane from b., pivoting
  around the axisOfRotation.

  When the axisOfRotation field is set to (0, 0, 0), the special case
  of viewer-alignment is indicated. In this case, the object rotates
  to keep the billboard's local Y-axis parallel with the Y-axis of the
  viewer.  This special case is distinguished by setting the
  axisOfRotation to (0, 0, 0). The following steps describe how to
  align the billboard's Y-axis to the Y-axis of the viewer:

  \li d. Compute the billboard-to-viewer vector.

  \li e. Rotate the Z-axis of the billboard to be collinear with the
  billboard-to-viewer vector and pointing towards the viewer's
  position.

  \li f. Rotate the Y-axis of the billboard to be parallel and
  oriented in the same direction as the Y-axis of the viewer.

  If the axisOfRotation and the billboard-to-viewer line are
  coincident, the plane cannot be established and the resulting
  rotation of the billboard is undefined. For example, if the
  axisOfRotation is set to (0,1,0) (Y-axis) and the viewer flies over
  the billboard and peers directly down the Y-axis, the results are
  undefined.

  Multiple instances of Billboard nodes (DEF/USE) operate
  as expected: each instance rotates in its unique coordinate system
  to face the viewer.

  Subclause "10.2.1, Grouping and children node types"
  (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Groupingandchildrennodes),
  provides a description of the children, addChildren, and
  removeChildren fields and eventIns.

  The bboxCenter and bboxSize
  fields specify a bounding box that encloses the Billboard node's
  children. This is a hint that may be used for optimization
  purposes. The results are undefined if the specified bounding box is
  smaller than the actual bounding box of the children at any time. A
  default bboxSize value, (-1, -1, -1), implies that the bounding box
  is not specified and if needed shall be calculated by the browser. A
  description of the bboxCenter and bboxSize fields is contained in
  "10.2.2, Bounding boxes"
  (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Boundingboxes),

  \ENDWEB3D
*/

// *************************************************************************

/*!
  \var SoSFVec3f SoX3DBillboard::axisOfRotation

  The axis of rotation for the geometry.
*/

/*!
  \var SoSFVec3f SoX3DBillboard::bboxCenter
  The bounding box center hint. Default value is (0, 0, 0).
*/

/*!
  \var SoSFVec3f SoX3DBillboard::bboxSize
  The bounding box size hint. Default value is (-1, -1, -1).
*/


// *************************************************************************

#include <Inventor/X3Dnodes/SoX3DBillboard.h>

#include <cmath>
#include <cfloat>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/SbPlane.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/misc/SoChildList.h>
#include <Inventor/SbRotation.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/system/gl.h>

#include "nodes/SoSubNodeP.h"
#include "rendering/SoGL.h"
#include "glue/glp.h"
#include "profiler/SoNodeProfiling.h"

// *************************************************************************

SO_NODE_SOURCE(SoX3DBillboard);

// *************************************************************************

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DBillboard::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DBillboard, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DBillboard::SoX3DBillboard(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DBillboard);

  SO_X3DNODE_ADD_EXPOSED_FIELD(axisOfRotation, (0.0f, 0.0f, 0.0f));
  SO_X3DNODE_ADD_FIELD(bboxCenter, (0.0f, 0.0f, 0.0f));
  SO_X3DNODE_ADD_FIELD(bboxSize, (-1.0f, -1.0f, -1.0f));
}

/*!
  Constructor. \a numchildren is the expected number of children.
*/
SoX3DBillboard::SoX3DBillboard(int numchildren)
  : inherited(numchildren)
{
}

/*!
  Destructor.
*/
SoX3DBillboard::~SoX3DBillboard()
{
}

// *************************************************************************

// doc in parent
void
SoX3DBillboard::doAction(SoAction * action)
{
  SoState * state = action->getState();
  state->push();
  this->performRotation(state);
  SoX3DGroupingNode::doAction(action);
  state->pop();
}

// doc in parent
void
SoX3DBillboard::callback(SoCallbackAction * action)
{
  SoX3DBillboard::doAction((SoAction*) action);
}

// doc in parent
void
SoX3DBillboard::GLRender(SoGLRenderAction * action)
{
  switch (action->getCurPathCode()) {
  case SoAction::NO_PATH:
  case SoAction::BELOW_PATH:
    this->GLRenderBelowPath(action);
    break;
  case SoAction::OFF_PATH:
    // do nothing. Separator will reset state.
    break;
  case SoAction::IN_PATH:
    this->GLRenderInPath(action);
    break;
  }
}

// doc in parent
void
SoX3DBillboard::getBoundingBox(SoGetBoundingBoxAction * action)
{
  SoState * state = action->getState();
  state->push();
  this->performRotation(state);
  SoX3DGroupingNode::getBoundingBox(action);
  state->pop();
}

// Doc in parent
void
SoX3DBillboard::getMatrix(SoGetMatrixAction * action)
{
  SoState * state = action->getState();
  state->push();

  const SbViewVolume & vv = SoViewVolumeElement::get(state);
  SbRotation rot = this->computeRotation(action->getInverse(), vv);

  SbMatrix rotM;
  rotM.setRotate(rot);
  action->getMatrix().multLeft(rotM);
  SbMatrix invRotM;
  invRotM.setRotate(rot.inverse());
  action->getInverse().multRight(invRotM);

  SoX3DGroupingNode::getMatrix(action);
  state->pop();
}

// doc in parent
void
SoX3DBillboard::pick(SoPickAction * action)
{
  SoX3DBillboard::doAction((SoAction*) action);
}

// doc in parent
void
SoX3DBillboard::search(SoSearchAction * action)
{
  SoNode::search(action);
  if (action->isFound()) return;
  SoX3DGroupingNode::doAction(action);
}

// doc in parent
void
SoX3DBillboard::GLRenderBelowPath(SoGLRenderAction * action)
{
  SoState * state = action->getState();

  // never cache this node
  SoCacheElement::invalidate(state);

  state->push();
  this->performRotation(state);

  int n = this->getChildren()->getLength();
  SoNode ** childarray = (SoNode**) this->getChildren()->getArrayPtr();

  action->pushCurPath();
  for (int i = 0; i < n && !action->hasTerminated(); i++) {
    action->popPushCurPath(i, childarray[i]);
    if (action->abortNow()) {
      // only cache if we do a full traversal
      break;
    }
    SoNodeProfiling profiling;
    profiling.preTraversal(action);
    childarray[i]->GLRenderBelowPath(action);
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
        SoDebugError::post("SoX3DBillboard::GLRenderBelowPath",
                           "GL error: '%s', nodetype: %s",
                           cc_string_get_text(&str),
                           (*this->getChildren())[i]->getTypeId().getName().getString());
      }
      cc_string_clean(&str);
    }
#endif // COIN_DEBUG
  }
  action->popCurPath();
  state->pop();
}

// doc in parent
void
SoX3DBillboard::GLRenderInPath(SoGLRenderAction * action )
{
  int numindices;
  const int * indices;

  SoAction::PathCode pathcode = action->getPathCode(numindices, indices);

  if (pathcode == SoAction::IN_PATH) {
    SoState * state = action->getState();
    SoCacheElement::invalidate(state);
    SoNode ** childarray = (SoNode**) this->getChildren()->getArrayPtr();
    state->push();
    this->performRotation(state);

    int childidx = 0;
    for (int i = 0; i < numindices; i++) {
      for (; childidx < indices[i] && !action->hasTerminated(); childidx++) {
        SoNode * offpath = childarray[childidx];
        if (offpath->affectsState()) {
          action->pushCurPath(childidx, offpath);
          if (!action->abortNow()) {
            SoNodeProfiling profiling;
            profiling.preTraversal(action);
            offpath->GLRenderOffPath(action);
            profiling.postTraversal(action);
          }
          action->popCurPath(pathcode);
        }
      }
      SoNode * inpath = childarray[childidx];
      action->pushCurPath(childidx, inpath);
      if (!action->abortNow()) {
        SoNodeProfiling profiling;
        profiling.preTraversal(action);
        inpath->GLRenderInPath(action);
        profiling.postTraversal(action);
      }
      action->popCurPath(pathcode);
      childidx++;
    }
    state->pop();
  }
  else {
    // we got to the end of the path
    assert(action->getCurPathCode() == SoAction::BELOW_PATH);
    this->GLRenderBelowPath(action);
  }
}

// doc in parent
void
SoX3DBillboard::GLRenderOffPath(SoGLRenderAction * COIN_UNUSED_ARG(action))
{
  // do nothing
}

// doc in parent
void
SoX3DBillboard::notify(SoNotList * list)
{
  inherited::notify(list);
}

//
// private method that appends the needed rotation to the state
//
void
SoX3DBillboard::performRotation(SoState * state) const
{
  SbMatrix imm = SoModelMatrixElement::get(state).inverse();
  const SbViewVolume & vv = SoViewVolumeElement::get(state);

  SbRotation rot = computeRotation(imm, vv);

  // append the desired rotation to the state
  SoModelMatrixElement::rotateBy(state, (SoNode*) this, rot);
}

//
// private method that computes the needed rotation
//
SbRotation
SoX3DBillboard::computeRotation(SbMatrix const & invMM, SbViewVolume const & vv) const
{
  SbVec3f rotaxis = this->axisOfRotation.getValue();

  SbVec3f up, look, right;
  
  invMM.multDirMatrix(vv.getViewUp(), up);
  invMM.multDirMatrix(-vv.getProjectionDirection(), look);

  if (rotaxis == SbVec3f(0.0f, 0.0f, 0.0f)) {
    // always orient the billboard towards the viewer
    right = up.cross(look);
    up = look.cross(right);
  } else { 
    // The X3D spec calls for rotating the local Z-axis of the
    // billboard to face the viewer, pivoting around the axis of
    // rotation. If the axis of rotation is the Z-axis, this angle
    // will be zero, and no rotation can happen. We don't actually
    // bother to compute this angle at all, but set up = rotaxis and
    // use cross products from there to construct the rotation matrix.
    // This is more numerically stable, more general, and the code is
    // much nicer, but it also means that we must check specifically
    // for this case.
    if (rotaxis == SbVec3f(0.0f, 0.0f, 1.0f)) { return SbRotation::identity(); }
    
    up = rotaxis;
    right = up.cross(look);
    look = right.cross(up);
  }

  // construct the rotation matrix with the vectors defining the
  // desired orientation
  SbMatrix matrix = SbMatrix::identity();

  right.normalize();
  up.normalize();
  look.normalize();
  
  matrix[0][0] = right[0];
  matrix[0][1] = right[1];
  matrix[0][2] = right[2];
  
  matrix[1][0] = up[0];
  matrix[1][1] = up[1];
  matrix[1][2] = up[2];
  
  matrix[2][0] = look[0];
  matrix[2][1] = look[1];
  matrix[2][2] = look[2];

  return SbRotation(matrix);
}

#endif // HAVE_X3D
