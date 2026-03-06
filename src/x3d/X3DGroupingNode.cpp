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
  \class SoX3DGroupingNode SoX3DGroupingNode.h Inventor/X3Dnodes/SoX3DGroupingNode.h
  \brief The SoX3DGroupingNode is an abstract node type for all groups in the X3D specification.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  X3DGroupingNode : X3DChildNode, X3DBoundedObject { 
    MFNode  [in]     addChildren
    MFNode  [in]     removeChildren
    MFNode  [in,out] children       []       [X3DChildNode]
    SFNode  [in,out] metadata       NULL     [X3DMetadataObject]
    SFVec3f []       bboxCenter     0 0 0    (-∞,∞)
    SFVec3f []       bboxSize       -1 -1 -1 [0,∞) or −1 −1 −1
  }
  \endverbatim

  This abstract node type indicates that concrete node types derived from it contain children nodes and is the basis for all aggregation.

  More details on the children, addChildren, and removeChildren fields can be found in "10.2.1 Grouping and children node types" (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#GroupingAndChildrenNodes).

*/

/*!
  SoMFNode SoX3DGroupingNode::addChildren
  An eventIn that is used to add children to this node.
*/

/*!
  SoMFNode SoX3DGroupingNode:removeChildren
  An eventIn that is used to remove children from this node.
*/

/*!
  SoMFNode SoX3DGroupingNode::children
  An exposed field containing child nodes of this group.
*/

#include <Inventor/X3Dnodes/SoX3DGroupingNode.h>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/misc/SoChildList.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/SoOutput.h>
#include <Inventor/nodes/SoInfo.h>
#ifdef HAVE_THREADS
#include <Inventor/threads/SbMutex.h>
#endif // HAVE_THREADS

#include "nodes/SoSubNodeP.h"
#include "tidbitsp.h"

// *************************************************************************

class SoX3DGroupingNodeP {
public:
  SbBool childlistvalid;
  SoFieldSensor * addsensor;
  SoFieldSensor * removesensor;

#ifdef COIN_THREADSAFE
  SbMutex childlistmutex;
  void lockChildList(void) { this->childlistmutex.lock(); }
  void unlockChildList(void) { this->childlistmutex.unlock(); }
#else // !COIN_THREADSAFE
  void lockChildList(void) { }
  void unlockChildList(void) { }
#endif // !COIN_THREADSAFE

  static SoInfo * getNullNode(void) {
    if (SoX3DGroupingNodeP::nullnode == NULL) {
      SoX3DGroupingNodeP::nullnode = new SoInfo;
      SoX3DGroupingNodeP::nullnode->ref();
      SoX3DGroupingNodeP::nullnode->setName("SoX3DGroupingNode::nullnode");
    }
    return SoX3DGroupingNodeP::nullnode;
  }
  static void freeNullNode(void) {
    if (SoX3DGroupingNodeP::nullnode != NULL) {
      SoX3DGroupingNodeP::nullnode->unref();
      SoX3DGroupingNodeP::nullnode = NULL;
    }
  }

private:
  static SoInfo * nullnode;
};

SoInfo * SoX3DGroupingNodeP::nullnode = NULL;

static void
x3dparent_cleanup(void)
{
  SoX3DGroupingNodeP::freeNullNode();
}

// *************************************************************************

SO_NODE_SOURCE(SoX3DGroupingNode);

// *************************************************************************

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DGroupingNode::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DGroupingNode, SO_X3D_NODE_TYPE);
  // used when the 'children' field contains NULL-nodes
  coin_atexit((coin_atexit_f*) x3dparent_cleanup, CC_ATEXIT_NORMAL);
}

#define PRIVATE(thisp) ((thisp)->pimpl)

/*!
  Constructor.
*/
SoX3DGroupingNode::SoX3DGroupingNode(void)
  : SoX3DChildNode()
{
  this->commonConstructor();
}

/*!
  Constructor. \a numchildren is the expected number of children.
*/
SoX3DGroupingNode::SoX3DGroupingNode(int numchildren)
  : SoX3DChildNode(numchildren)
{
  this->commonConstructor();
}

void
SoX3DGroupingNode::commonConstructor(void)
{
  PRIVATE(this) = new SoX3DGroupingNodeP;
  PRIVATE(this)->childlistvalid = FALSE;

  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DGroupingNode);

  SO_X3DNODE_ADD_EVENT_IN(addChildren);
  SO_X3DNODE_ADD_EVENT_IN(removeChildren);
  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(children);

  SO_X3DNODE_ADD_FIELD(bboxCenter, (0, 0, 0));
  SO_X3DNODE_ADD_FIELD(bboxCenter, (-1, -1, -1));
  // FIXME: bboxCenter and bboxSize should be implemented in the
  // SoX3DBoundedObject. Unfortuantely, Coin does not handle multiple
  // inhertance very well due to the mechanism/macros used to determine
  // node type and field management (ambiguous method errors). For now, 
  // place these fields here.
  // 2026-03-11 msm (WizzerWorks)

  PRIVATE(this)->addsensor = new SoFieldSensor(field_sensor_cb, this);
  PRIVATE(this)->removesensor = new SoFieldSensor(field_sensor_cb, this);
  PRIVATE(this)->addsensor->attach(&this->addChildren);
  PRIVATE(this)->removesensor->attach(&this->removeChildren);

  // HACK WARNING: All children of this node are stored in the
  // children field. Avoid double notifications (because of
  // notification through SoChildList) be reallocating the SoChildList
  // with a NULL-parent here. SoGroup will have allocated an
  // SoChildList in its constructor when we get here.
  delete this->SoX3DChildNode::children;
  this->SoX3DChildNode::children = new SoChildList(NULL);
  // FIXME: this code was copied from SoX3DParent (no longer used).
  // Should SoX3DChildNode contain a list of children still?
  // 2026-03-12 msm (WizzerWorks)
}

/*!
  Destructor.
*/
SoX3DGroupingNode::~SoX3DGroupingNode()
{
  PRIVATE(this)->addsensor->detach();
  PRIVATE(this)->removesensor->detach();
  delete PRIVATE(this)->addsensor;
  delete PRIVATE(this)->removesensor;
  delete PRIVATE(this);
}

// doc in parent
SbBool
SoX3DGroupingNode::affectsState(void) const
{
  return FALSE;
}

// doc in parent
void
SoX3DGroupingNode::addChild(SoNode * child)
{
  this->children.addNode(child);
  PRIVATE(this)->childlistvalid = FALSE;
}

// doc in parent
void
SoX3DGroupingNode::insertChild(SoNode * child, int idx)
{
  this->children.insertNode(child, idx);
  PRIVATE(this)->childlistvalid = FALSE;
}

// doc in parent
SoNode *
SoX3DGroupingNode::getChild(int idx) const
{
  return this->children.getNode(idx);
}

// doc in parent
int
SoX3DGroupingNode::findChild(const SoNode * child) const
{
  return this->children.findNode(child);
}

// doc in parent
int
SoX3DGroupingNode::getNumChildren(void) const
{
  return this->children.getNumNodes();
}

// doc in parent
void
SoX3DGroupingNode::removeChild(int idx)
{
  this->children.removeNode(idx);
  if (this->children.getNum() > 0) {
    PRIVATE(this)->childlistvalid = FALSE;
  }
  else {
    SoX3DChildNode::children->truncate(0);
    PRIVATE(this)->childlistvalid = TRUE;
  }
}

// doc in parent
void
SoX3DGroupingNode::removeChild(SoNode * child)
{
  this->children.removeNode(child);
  if (this->children.getNum() > 0) {
    PRIVATE(this)->childlistvalid = FALSE;
  }
  else {
    SoX3DChildNode::children->truncate(0);
    PRIVATE(this)->childlistvalid = TRUE;
  }
}

// doc in parent
void
SoX3DGroupingNode::removeAllChildren(void)
{
  this->children.removeAllNodes();
  SoX3DChildNode::children->truncate(0);
  PRIVATE(this)->childlistvalid = TRUE;
}

// doc in parent
void
SoX3DGroupingNode::replaceChild(int idx, SoNode * child)
{
  this->children.replaceNode(idx, child);
  PRIVATE(this)->childlistvalid = FALSE;
}

// doc in parent
void
SoX3DGroupingNode::replaceChild(SoNode * old, SoNode * child)
{
  this->children.replaceNode(old, child);
  PRIVATE(this)->childlistvalid = FALSE;
}

// doc in parent
SoChildList *
SoX3DGroupingNode::getChildren(void) const
{
  if (!PRIVATE(this)->childlistvalid) {
    // this is not 100% thread safe. The assumption is that no nodes
    // will be added or removed while a scene graph is being
    // traversed. For Coin, this is an ok assumption.
    PRIVATE(this)->lockChildList();

    // test again after we've locked
    if (!PRIVATE(this)->childlistvalid) {
      SoX3DGroupingNode::updateChildList(this->children.getValues(0),
                                         this->children.getNum(),
                                         *SoX3DChildNode::children);
      PRIVATE((SoX3DGroupingNode*)this)->childlistvalid = TRUE;
    }
    PRIVATE(this)->unlockChildList();
  }
  return SoX3DChildNode::children;
}

// doc in parent
void
SoX3DGroupingNode::doAction(SoAction * action)
{
  inherited::doAction(action);
}

// doc in parent
void
SoX3DGroupingNode::search(SoSearchAction * action)
{
  inherited::search(action);
}

void
SoX3DGroupingNode::write(SoWriteAction * action)
{
  SoOutput * out = action->getOutput();

  if (out->getStage() == SoOutput::COUNT_REFS) {
    this->addWriteReference(out, FALSE);
  }
  else if (out->getStage() == SoOutput::WRITE) {
    if (this->writeHeader(out, FALSE, FALSE)) return;
    // don't use the standard SoFieldData, since we want the children
    // field to be written last.
    SoFieldData * fd = this->makeWriteData();
    fd->write(out, this);
    delete fd;
    this->writeFooter(out);
  }
  else assert(0 && "unknown stage");
}

// doc in parent
void
SoX3DGroupingNode::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  inherited::getPrimitiveCount(action);
}

// doc in parent
void
SoX3DGroupingNode::notify(SoNotList * list)
{
  SoField * f = list->getLastField();
  if (f == &this->children) {
    PRIVATE(this)->childlistvalid = FALSE;
  }
  inherited::notify(list);
}

// doc in parent
SbBool
SoX3DGroupingNode::readInstance(SoInput * in,
                                unsigned short flags)
{
  SbBool oldnot = this->children.enableNotify(FALSE);
  // call SoNode::readInstance(), not SoX3DChildNode::readInstance() since
  // this node stores all children in the children field.
  SbBool ret = SoNode::readInstance(in, flags);
  if (oldnot) this->children.enableNotify(TRUE);
  PRIVATE(this)->childlistvalid = FALSE;
  return ret;
}

// doc in parent
void
SoX3DGroupingNode::copyContents(const SoFieldContainer * from,
                                SbBool copyConn)
{
  SoX3DChildNode::children->truncate(0);
  PRIVATE(this)->addsensor->detach();
  PRIVATE(this)->removesensor->detach();
  SoNode::copyContents(from, copyConn);
  PRIVATE(this)->addsensor->attach(&this->addChildren);
  PRIVATE(this)->removesensor->attach(&this->removeChildren);
  PRIVATE(this)->childlistvalid = FALSE;
}

/*!
  A convenience method that can be used to update \a cl to match the
  list of nodes in \a nodes.
*/
void
SoX3DGroupingNode::updateChildList(const SoNode * const * nodes,
                                   const int numnodes,
                                   SoChildList & cl)
{
  int i;
  SbBool needcopy = TRUE;
  int numChildren = cl.getLength();
  if (numChildren && (numnodes == numChildren)) {
    const SoNode ** clarr = (const SoNode**) cl.getArrayPtr();
    for (i = 0; i < numnodes; i++) {
      // if the MFNode contains NULL values, we insert a dummy node
      // (of type SoInfo). This is to simplify the traversal code, and
      // to make it easier to check if the SoChildList is up-to-date
      if (clarr[i] == NULL) {
        if (nodes[i] != SoX3DGroupingNodeP::getNullNode()) break;
      }
      else {
        if (clarr[i] != nodes[i]) break;
      }
    }
    if (i == numnodes) needcopy = FALSE;
  }
  if (needcopy) {
    cl.truncate(0);
    for (i = 0; i < numnodes; i++) {
      if (nodes[i]) {
        cl.append((SoNode*) nodes[i]);
      }
      else {
        // insert a dummy SoInfo node
        cl.append(SoX3DGroupingNodeP::getNullNode());
      }
    }
  }
}

/*!
  A convenience method that is used to sync the nodes in \a cl with
  all nodes in SoSFNode fields in \a nodewithsfnode.
*/
void
SoX3DGroupingNode::updateChildList(SoNode * nodewithsfnode,
                                   SoChildList & cl)
{
  SbList <SoNode*> nodelist;

  const SoFieldData * fd = nodewithsfnode->getFieldData();
  const int n = fd->getNumFields();

  SoType sosftype = SoSFNode::getClassTypeId();
  for (int i = 0; i < n; i++) {
    SoField * f = fd->getField(nodewithsfnode, i);
    if (f->getTypeId() == sosftype) {
      SoNode * node = ((SoSFNode*) f)->getValue();
      if (node) nodelist.append(node);
    }
  }
  SoX3DGroupingNode::updateChildList(nodelist.getArrayPtr(),
                                     nodelist.getLength(),
                                     cl);
}

// Add children in addChildren field.
void
SoX3DGroupingNode::processAddChildren(void)
{
  const int n = this->addChildren.getNum();
  const SoNode ** nodes = this->addChildren.getValues(0);
  for (int i = 0; i < n; i++) {
    const SoNode * node = nodes[i];
    if (this->findChild(node) < 0) {
      this->addChild((SoNode*)node);
    }
  }
}

// Remove children in removeChildren field.
void
SoX3DGroupingNode::processRemoveChildren(void)
{
  const int n = this->removeChildren.getNum();
  const SoNode ** nodes = this->removeChildren.getValues(0);
  for (int i = 0; i < n; i++) {
    int idx = this->findChild(nodes[i]);
    if (idx >= 0) {
      this->removeChild(idx);
    }
  }
}

// Callback from the addChildren/removeChildren sensors.
void
SoX3DGroupingNode::field_sensor_cb(void * data, SoSensor * sensor)
{
  SoX3DGroupingNode * thisp = (SoX3DGroupingNode*) data;
  if (sensor == PRIVATE(thisp)->addsensor) {
    thisp->processAddChildren();
  }
  else {
    assert(sensor == PRIVATE(thisp)->removesensor);
    thisp->processRemoveChildren();
  }
}

// Reorganize field order so that the "children" field is written
// last.
SoFieldData *
SoX3DGroupingNode::makeWriteData(void)
{
  SoFieldData * newfd = new SoFieldData;
  const SoFieldData * fd = this->getFieldData();

  SoField * delay = &this->children;
  const int n = fd->getNumFields();

  for (int i = 0; i < n; i++) {
    SoField * f = fd->getField(this, i);
    if (f != delay) {
      newfd->addField(this, fd->getFieldName(i).getString(), f);
    }
  }
  newfd->addField(this, "children", delay);
  return newfd;
}

#undef PRIVATE

#endif // HAVE_X3D
