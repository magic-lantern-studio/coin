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
  \class SoX3DCollision SoX3DCollision.h Inventor/X3Dnodes/SoX3DCollision.h
  \brief The SoX3DCollision class is used for collision detection with the avatar.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT

  \verbatim
  Collision {
    eventIn      MFNode   addChildren
    eventIn      MFNode   removeChildren
    exposedField SFBool   enabled
    exposedField MFNode   children        []
    exposedField SFNode   metadata        NULL
    field        SFVec3f  bboxCenter      0 0 0      # (-inf,inf)
    field        SFVec3f  bboxSize        -1 -1 -1   # (0,inf) or -1,-1,-1
    field        SFNode   proxy           NULL
    eventOut     SFTime   collideTime
    eventOut     SFBool   isActive
  }
  \endverbatim

  The Collision node is a grouping node that specifies the collision
  detection properties for its children (and their descendants),
  specifies surrogate objects that replace its children during
  collision detection, and sends events signalling that a collision
  has occurred between the avatar and the Collision node's geometry or
  surrogate. By default, all geometric nodes in the scene are
  collidable with the viewer except IndexedLineSet, PointSet, and
  Text. Browsers shall detect geometric collisions between the avatar
  (see SoX3DNavigationInfo) and the scene's geometry and prevent the
  avatar from 'entering' the geometry. See 23.2.4, Collision detection
  and terrain following
  (<https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/navigation.html#Collisiondetection>),
  for general information on collision detection.

  If there are no Collision nodes specified in a X3D file, browsers
  shall detect collisions between the avatar and all objects during
  navigation.

  Subclause 4.6.5, Grouping and children node typess
  (<https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Groupingandchildrennodes>),
  contains a description of the children, addChildren, and
  removeChildren fields and eventIns.

  The Collision node's collide field enables and disables collision
  detection. If collide is set to FALSE, the children and all
  descendants of the Collision node shall not be checked for
  collision, even though they are drawn. This includes any descendent
  Collision nodes that have collide set to TRUE (i.e., setting collide
  to FALSE turns collision off for every node below it).

  Collision nodes with the collide field set to TRUE detect the
  nearest collision with their descendent geometry (or proxies). When
  the nearest collision is detected, the collided Collision node sends
  the time of the collision through its collideTime eventOut. If a
  Collision node contains a child, descendant, or proxy (see below)
  that is a Collision node, and both Collision nodes detect that a
  collision has occurred, both send a collideTime event at the same
  time. A collideTime event shall be generated if the avatar is
  colliding with collidable geometry when the Collision node is read
  from a X3D file or inserted into the transformation hierarchy.

  The bboxCenter and bboxSize fields specify a bounding box that
  encloses the Collision node's children. This is a hint that may be
  used for optimization purposes. The results are undefined if the
  specified bounding box is smaller than the actual bounding box of
  the children at any time. A default bboxSize value, (-1, -1, -1),
  implies that the bounding box is not specified and if needed shall
  be calculated by the browser. More details on the bboxCenter and
  bboxSize fields can be found in 10.2.2, Bounding boxes.
  (<https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Boundingboxes>),

  The collision proxy, defined in the proxy field, is any legal
  children node as described in 10.2.1, Grouping and children node typess,
  (<https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Groupingandchildrennodes>),
  that is used as a substitute for the Collision node's children
  during collision detection. The proxy is used strictly for collision
  detection; it is not drawn.

  If the value of the collide field is
  TRUE and the proxy field is non-NULL, the proxy field defines the
  scene on which collision detection is performed. If the proxy value
  is NULL, collision detection is performed against the children of
  the Collision node.

  If proxy is specified, any descendent children
  of the Collision node are ignored during collision detection. If
  children is empty, collide is TRUE, and proxy is specified,
  collision detection is performed against the proxy but nothing is
  displayed. In this manner, invisible collision objects may be
  supported.

  The collideTime eventOut generates an event specifying the time when
  the avatar (see SoX3DNavigationInfo) makes contact with the
  collidable children or proxy of the Collision node.  An ideal
  implementation computes the exact time of collision. Implementations
  may approximate the ideal by sampling the positions of collidable
  objects and the user. The SoX3DNavigationInfo node contains additional
  information for parameters that control the avatar size.
*/

/*!
  \var SoSFBool SoX3DCollision::enabled
  Enable/disable collision.
*/

/*!
  \var SoSFNode SoX3DCollision::proxy
  Proxy node(s) used for collision testing.
*/

/*!
  \var SoSFTime SoX3DCollision::collideTime
  An eventOut sent for each collision that occurs.
*/

/*!
  \var SoSFBool SoX3DCollision::isActive
  An eventOut sent when the collision becomes active.
*/

/*!
  \var SoSFNode SoX3DCollision::metadata
  Can contain an SoX3DMetadataObject. Is NULL by default.
*/


#include <Inventor/X3Dnodes/SoX3DCollision.h>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/actions/SoX3DGLRenderAction.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/misc/SoChildList.h>
#include <Inventor/elements/SoCacheElement.h>

#include "nodes/SoSubNodeP.h"
#include "profiler/SoNodeProfiling.h"

SO_NODE_SOURCE(SoX3DCollision);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DCollision::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DCollision, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DCollision::SoX3DCollision(void)
{
  this->commonConstructor();
}

/*!
  Constructor. \a numchildren is the expected number of children.
*/
SoX3DCollision::SoX3DCollision(int numchildren)
  : inherited(numchildren)
{
  this->commonConstructor();
}

void
SoX3DCollision::commonConstructor(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DCollision);

  SO_X3DNODE_ADD_EXPOSED_FIELD(enabled, (TRUE));
  SO_X3DNODE_ADD_EXPOSED_FIELD(metadata, (NULL));
  SO_X3DNODE_ADD_FIELD(bboxCenter, (1.0f, 1.0f, 1.0f));
  SO_X3DNODE_ADD_FIELD(bboxSize, (0, 0, 0));
  SO_X3DNODE_ADD_FIELD(proxy, (NULL));

  SO_X3DNODE_ADD_EVENT_OUT(collideTime);
  SO_X3DNODE_ADD_EVENT_OUT(isActive);
}

/*!
  Destructor.
*/
SoX3DCollision::~SoX3DCollision() // virtual, protected
{
}

// doc in parent
void
SoX3DCollision::GLRender(SoX3DGLRenderAction * action)
{
  SoState * state = action->getState();
  state->push();

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

// doc in parent
void
SoX3DCollision::notify(SoNotList * list)
{
  inherited::notify(list);
}

#endif // HAVE_X3D
