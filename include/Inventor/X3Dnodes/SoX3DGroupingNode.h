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

#ifndef COIN_SOX3DGROUPINGNODE_H
#define COIN_SOX3DGROUPINGNODE_H

#include <Inventor/X3Dnodes/SoX3DChildNode.h>
#include <Inventor/X3Dnodes/SoX3DBoundedObject.h>

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFVec3f.h>

class SoX3DGroupingNodeP;
class SoSensor;

class COIN_DLL_API SoX3DGroupingNode : public SoX3DChildNode, public SoX3DBoundedObject
{
  typedef SoX3DChildNode inherited;
  SO_NODE_HEADER(SoX3DGroupingNode);

public:
  static void initClass(void);

  SoMFNode children;

  SoSFVec3f bboxCenter;
  SoSFVec3f bboxSize;
  // FIXME: bboxCenter and bboxSize should be implemented in the
  // SoX3DBoundedObject. Unfortuantely, Coin does not handle multiple
  // inhertance very well due to the mechanism/macros used to determine
  // node type and field management (ambiguous method errors). For now, 
  // place these fields here.
  // 2026-03-11 msm (WizzerWorks)

  virtual SbBool affectsState(void) const;
  virtual void addChild(SoNode * child);
  virtual void insertChild(SoNode * child, int idx);
  virtual SoNode * getChild(int idx) const;
  virtual int findChild(const SoNode * child) const;
  virtual int getNumChildren(void) const;
  virtual void removeChild(int idx);
  virtual void removeChild(SoNode * child);
  virtual void removeAllChildren(void);
  virtual void replaceChild(int idx, SoNode * child);
  virtual void replaceChild(SoNode * old, SoNode * child);
  virtual SoChildList * getChildren(void) const;

  virtual void doAction(SoAction * action);
  virtual void search(SoSearchAction * action);
  virtual void write(SoWriteAction * action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);

  static void updateChildList(const SoNode * const * nodes, const int numnodes,
                              SoChildList & cl);
  static void updateChildList(SoNode * nodewithsfnode,
                              SoChildList & cl);

protected:
  SoX3DGroupingNode(void);
  SoX3DGroupingNode(int approxchildren);
  virtual ~SoX3DGroupingNode();

  SoMFNode addChildren;
  SoMFNode removeChildren;

  virtual void notify(SoNotList * list);
  virtual SbBool readInstance(SoInput * in, unsigned short flags);
  virtual void copyContents(const SoFieldContainer * from, SbBool copyConn);

private:
  static void field_sensor_cb(void * data, SoSensor * sensor);
  void commonConstructor(void);
  void processAddChildren(void);
  void processRemoveChildren(void);
  SoFieldData * makeWriteData(void);

  SoX3DGroupingNodeP * pimpl;

}; // class SoX3DGroupingNode

#endif // ! COIN_SOX3DGROUPINGNODE_H
