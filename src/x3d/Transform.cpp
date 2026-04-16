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
  \class SoX3DTransform SoX3DTransform.h Inventor/X3Dnodes/SoX3DTransform.h
  \brief The SoX3DTransform class is a grouping node that defines a transformation for its children.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  Transform : X3DGroupingNode {
    MFNode     [in]     addChildren               [X3DChildNode]
    MFNode     [in]     removeChildren            [X3DChildNode]
    SFVec3f    [in,out] center           0 0 0    (-∞,∞)
    MFNode     [in,out] children         []       [X3DChildNode]
    SFNode     [in,out] metadata         NULL     [X3DMetadataObject]
    SFRotation [in,out] rotation         0 0 1 0  [-1,1] or (-∞,∞)
    SFVec3f    [in,out] scale            1 1 1    (0,∞)
    SFRotation [in,out] scaleOrientation 0 0 1 0  [-1,1] or (-∞,∞)
    SFVec3f    [in,out] translation      0 0 0    (-∞,∞)
    SFVec3f    []       bboxCenter       0 0 0    (-∞,∞)
    SFVec3f    []       bboxSize         -1 -1 -1 [0,∞) or −1 −1 −1
  }
  \endverbatim

  The Transform node is a grouping node that defines a coordinate
  system for its children that is relative to the coordinate systems
  of its ancestors.  See "4.3.5, Transformation hierarchy"
  (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/concepts.html#Transformationhierarchy),
  and "4.3.6, Standard units and coordinate system"
  (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/concepts.html#Standardunitscoordinates),
  for a description of coordinate systems and transformations.

  "10.2.1, Grouping and children node types"
  (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#GroupingAndChildrenNodes),
  provides a description of the children, addChildren, and removeChildren
  fields.

  The bboxCenter and bboxSize fields specify a bounding box that
  encloses the children of the Transform node. This is a hint that may
  be used for optimization purposes. The results are undefined if the
  specified bounding box is smaller than the actual bounding box of
  the children at any time. A default bboxSize value, (-1, -1, -1),
  implies that the bounding box is not specified and, if needed, shall
  be calculated by the browser. The bounding box shall be large enough
  at all times to enclose the union of the group's children's bounding
  boxes; it shall not include any transformations performed by the
  group itself (i.e., the bounding box is defined in the local
  coordinate system of the children). The results are undefined if the
  specified bounding box is smaller than the true bounding box of the
  group. A description of the bboxCenter and bboxSize fields is
  provided in "10.2.2, Bounding boxes"
  (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#BoundingBoxes).

  The translation, rotation, scale, scaleOrientation and center fields
  define a geometric 3D transformation consisting of (in order):

  - a (possibly) non-uniform scale about an arbitrary point;
  - a rotation about an arbitrary point and axis;
  - a translation.

  The \e center field specifies a translation offset from the origin
  of the local coordinate system (0,0,0). The \e rotation field
  specifies a rotation of the coordinate system. The \e scale field
  specifies a non-uniform scale of the coordinate system. scale values
  shall be greater than zero. The \e scaleOrientation specifies a
  rotation of the coordinate system before the scale (to specify
  scales in arbitrary orientations). The scaleOrientation applies only
  to the scale operation.  The \e translation field specifies a
  translation to the coordinate system.

  Given a 3-dimensional point
  P and Transform node, P is transformed into point P' in its
  parent's coordinate system by a series of intermediate
  transformations. In matrix transformation notation, where C
  (center), SR (scaleOrientation), T (translation), R (rotation), and
  S (scale) are the equivalent transformation matrices,

  \verbatim
  P' = T × C × R × SR × S × -SR × -C × P
  \endverbatim

  The following Transform node:

  \verbatim
  Transform {
    center           C
    rotation         R
    scale            S
    scaleOrientation SR
    translation      T
    children         [...]
  }
  \endverbatim

  is equivalent to the nested sequence of:

  \verbatim
  Transform {
    translation T
    children Transform {
      translation C
      children Transform {
        rotation R
        children Transform {
          rotation SR
          children Transform {
            scale S
            children Transform {
              rotation -SR
              children Transform {
                translation -C
                children [...]
              }
            }
          }
        }
      }
    }
  }
  \endverbatim

*/

/*!
  \var SoSFVec3f SoX3DTransform::translation
  The translation vector. Default value is (0, 0, 0).
*/

/*!
  \var SoSFRotation SoX3DTransform::rotation
  The rotation around the center point. Default value is null-rotation.
*/

/*!
  \var SoSFVec3f SoX3DTransform::scale
  The scale vector about the center point. Default value is (1, 1, 1).
*/

/*!
  \var SoSFRotation SoX3DTransform::scaleOrientation
  The scale orientation. Default value is a null-rotation.
*/

/*!
  \var SoSFVec3f SoX3DTransform::center
  The center point. Default value is (0, 0, 0).
*/


#include <Inventor/X3Dnodes/SoX3DTransform.h>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/misc/SoChildList.h>

#include "nodes/SoSubNodeP.h"

SO_NODE_SOURCE(SoX3DTransform);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DTransform::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DTransform, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DTransform::SoX3DTransform(void)
{
  this->commonConstructor();
}

/*!
  Constructor. \a numchildren is the expected number of children.
*/
SoX3DTransform::SoX3DTransform(int numchildren)
  : inherited(numchildren)

{
  this->commonConstructor();
}

void
SoX3DTransform::commonConstructor(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DTransform);

  SO_X3DNODE_ADD_EXPOSED_FIELD(translation, (0.0f, 0.0f, 0.0f));
  SO_X3DNODE_ADD_EXPOSED_FIELD(rotation, (SbRotation::identity()));
  SO_X3DNODE_ADD_EXPOSED_FIELD(scale, (1.0f, 1.0f, 1.0f));
  SO_X3DNODE_ADD_EXPOSED_FIELD(scaleOrientation, (SbRotation::identity()));
  SO_X3DNODE_ADD_EXPOSED_FIELD(center, (0.0f, 0.0f, 0.0f));
}

/*!
  Destructor
*/
SoX3DTransform::~SoX3DTransform()
{
}

/*!
  Sets the transformation to translate to \a frompoint, with a rotation
  so that the (0,0,-1) vector is rotated into the vector from \a frompoint
  to \a topoint.
*/
void
SoX3DTransform::pointAt(const SbVec3f & from,
                         const SbVec3f & to)
{
  this->scale = SbVec3f(1.0f, 1.0f, 1.0f);
  this->center = SbVec3f(0.0f, 0.0f, 0.0f);
  this->scaleOrientation = SbRotation::identity();

  this->translation = from;
  SbVec3f dir = to - from;
  dir.normalize();

  SbRotation rot(SbVec3f(0.0f, 0.0f, -1.0f), dir);
  this->rotation = rot;
}

/*!
  Calculates the matrices to/from scale space.
*/
void
SoX3DTransform::getScaleSpaceMatrix(SbMatrix & matrix,
                                     SbMatrix & inverse) const
{
  SbMatrix tmp;
  matrix.setTranslate(-center.getValue());
  tmp.setRotate(scaleOrientation.getValue().inverse());
  matrix.multRight(tmp);
  tmp.setScale(scale.getValue());
  matrix.multRight(tmp);
  inverse = matrix.inverse();
}

/*!
  Calculates the matrices to/from rotation space.
*/
void
SoX3DTransform::getRotationSpaceMatrix(SbMatrix & matrix,
                                        SbMatrix & inverse) const
{
  SbMatrix tmp;
  matrix.setTranslate(-this->center.getValue());
  tmp.setRotate(this->scaleOrientation.getValue().inverse());
  matrix.multRight(tmp);
  tmp.setScale(this->scale.getValue());
  matrix.multRight(tmp);
  tmp.setRotate(this->scaleOrientation.getValue());
  matrix.multRight(tmp);
  tmp.setRotate(this->rotation.getValue());
  matrix.multRight(tmp);
  inverse = matrix.inverse();
}

/*!
  Calculates the matrices to/from translation space.
*/
void
SoX3DTransform::getTranslationSpaceMatrix(SbMatrix & matrix,
                                           SbMatrix & inverse) const
{
  SbMatrix tmp;
  matrix.setTranslate(-this->center.getValue());
  tmp.setRotate(this->scaleOrientation.getValue().inverse());
  matrix.multRight(tmp);
  tmp.setScale(this->scale.getValue());
  matrix.multRight(tmp);
  tmp.setRotate(this->scaleOrientation.getValue());
  matrix.multRight(tmp);
  tmp.setRotate(this->rotation.getValue());
  matrix.multRight(tmp);
  tmp.setTranslate(this->center.getValue());
  matrix.multRight(tmp);
  tmp.setTranslate(this->translation.getValue());
  matrix.multRight(tmp);
  inverse = matrix.inverse();
}

/*!
  Premultiplies this transformation by \a mat.
*/
void
SoX3DTransform::multLeft(const SbMatrix & matrix)
{
  SbMatrix tmp;
  tmp.setTransform(this->translation.getValue(),
                   this->rotation.getValue(),
                   this->scale.getValue(),
                   this->scaleOrientation.getValue(),
                   this->center.getValue());

  tmp.multLeft(matrix);
  this->setMatrix(tmp);
}

/*!
  Postmultiplies this transformation by \a mat.
*/
void
SoX3DTransform::multRight(const SbMatrix & matrix)
{
  SbMatrix tmp;
  tmp.setTransform(this->translation.getValue(),
                   this->rotation.getValue(),
                   this->scale.getValue(),
                   this->scaleOrientation.getValue(),
                   this->center.getValue());
  tmp.multRight(matrix);
  this->setMatrix(tmp);
}

void
/*!
  Premultiplies this transformation by the transformation in \a leftnode.
*/
SoX3DTransform::combineLeft(SoX3DTransform * leftnode)
{
  SoGetMatrixAction ma(SbViewportRegion(100,100));
  ma.apply(leftnode);
  this->multLeft(ma.getMatrix());
}

/*!
  Postmultiplies this transformation by the transformation in \a rightnode.
*/
void
SoX3DTransform::combineRight(SoX3DTransform * rightnode)
{
  SoGetMatrixAction ma(SbViewportRegion(100,100));
  ma.apply(rightnode);
  this->multRight(ma.getMatrix());
}

/*!
  Sets the fields to create a transformation equal to \a mat.
*/
void
SoX3DTransform::setMatrix(const SbMatrix & matrix)
{
  SbVec3f t, s, c = this->center.getValue();
  SbRotation r, so;
  matrix.getTransform(t,r,s,so,c);

  this->translation = t;
  this->rotation = r;
  this->scale = s;
  this->scaleOrientation = so;
}

/*!
  Sets the \e center field to \a newcenter. This might affect one
  or more of the other fields.
*/
void
SoX3DTransform::recenter(const SbVec3f & newcenter)
{
  SbMatrix matrix;
  matrix.setTransform(this->translation.getValue(),
                      this->rotation.getValue(),
                      this->scale.getValue(),
                      this->scaleOrientation.getValue(),
                      this->center.getValue());
  SbVec3f t, s;
  SbRotation r, so;
  matrix.getTransform(t, r, s, so, newcenter);
  this->translation = t;
  this->rotation = r;
  this->scale = s;
  this->scaleOrientation = so;
  this->center = newcenter;
}

// doc in parent
void
SoX3DTransform::doAction(SoAction * action)
{
  SoState * state = action->getState();
  state->push();
  this->applyMatrix(state);
  SoGroup::doAction(action);
  state->pop();
}

// doc in parent
void
SoX3DTransform::callback(SoCallbackAction * action)
{
  SoState * state = action->getState();
  state->push();
  this->applyMatrix(state);
  inherited::callback(action);
  state->pop();
}

// doc in parent
void
SoX3DTransform::getBoundingBox(SoGetBoundingBoxAction * action)
{
  SoState * state = action->getState();
  state->push();
  this->applyMatrix(state);
  inherited::getBoundingBox(action);
  state->pop();
}

// doc in parent
void
SoX3DTransform::getMatrix(SoGetMatrixAction * action)
{
  // need to push/pop to handle SoUnitsElement correctly
  action->getState()->push();

  SbMatrix m;
  m.setTransform(this->translation.getValue(),
                 this->rotation.getValue(),
                 this->scale.getValue(),
                 this->scaleOrientation.getValue(),
                 this->center.getValue());
  action->getMatrix().multLeft(m);
  SbMatrix mi = m.inverse();
  action->getInverse().multRight(mi);

  SoGroup::getMatrix(action);
  action->getState()->pop();
}

// doc in parent
void
SoX3DTransform::rayPick(SoRayPickAction * action)
{
  SoState * state = action->getState();
  state->push();
  this->applyMatrix(state);
  inherited::rayPick(action);
  state->pop();
}

// doc in parent
void
SoX3DTransform::audioRender(SoAudioRenderAction * action)
{
  SoX3DTransform::doAction((SoAction*)action);
}

// doc in parent
void
SoX3DTransform::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  SoState * state = action->getState();
  state->push();
  this->applyMatrix(state);
  SoGroup::getPrimitiveCount(action);
  state->pop();
}

// doc in parent
void
SoX3DTransform::GLRenderBelowPath(SoX3DGLRenderAction * action)
{
  SoState * state = action->getState();
  state->push();
  this->applyMatrix(state);
  inherited::GLRenderBelowPath(action);
  state->pop();
}

// doc in parent
void
SoX3DTransform::GLRenderInPath(SoX3DGLRenderAction * action)
{
  if (action->getCurPathCode() == SoAction::IN_PATH) {
    SoState * state = action->getState();
    state->push();
    this->applyMatrix(state);
    inherited::GLRenderInPath(action);
    state->pop();
  }
  else {
    // we got to the end of the path
    this->GLRenderBelowPath(action);
  }
}

// doc in parent
void
SoX3DTransform::notify(SoNotList * list)
{
  inherited::notify(list);
}

//
// applies transformation to state.
//
void
SoX3DTransform::applyMatrix(SoState * state)
{
  SbMatrix matrix;
  matrix.setTransform(this->translation.getValue(),
                      this->rotation.getValue(),
                      this->scale.getValue(),
                      this->scaleOrientation.getValue(),
                      this->center.getValue());
  if (matrix != SbMatrix::identity()) {
    SoModelMatrixElement::mult(state, this, matrix);
  }
}

#endif // HAVE_X3D
