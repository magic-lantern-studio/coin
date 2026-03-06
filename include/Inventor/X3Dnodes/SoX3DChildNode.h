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

#ifndef COIN_SOX3DCHILDNODE_H
#define COIN_SOX3DCHILDNODE_H

#include <Inventor/X3Dnodes/SoX3DNode.h>

// This X3D abstract class is essentially equivalent to the Coin SoGroup
// node. However, being abstract, it is not meant to be constructed as a
// concrete object.
// FIXME: Make it truely an abstract class.
// 2026-03-13 msm (WizzerWorks)

class SoX3DChildNodeP;

class COIN_DLL_API SoX3DChildNode : public SoX3DNode
{
  typedef SoX3DNode inherited;
  SO_NODE_HEADER(SoX3DChildNode);

public:
  static void initClass(void);
  SoX3DChildNode(void);
  SoX3DChildNode(int nchildren);

  virtual void addChild(SoNode * node);
  virtual void insertChild(SoNode * child, int newchildindex);
  virtual SoNode * getChild(int index) const;
  virtual int findChild(const SoNode * node) const;
  virtual int getNumChildren(void) const;
  virtual void removeChild(int childindex);
  virtual void removeChild(SoNode * child);
  virtual void removeAllChildren(void);
  virtual void replaceChild(int index, SoNode * newchild);
  virtual void replaceChild(SoNode * oldchild, SoNode * newchild);

  virtual void doAction(SoAction * action);
  virtual void GLRender(SoGLRenderAction * action);
  virtual void callback(SoCallbackAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void getMatrix(SoGetMatrixAction * action);
  virtual void handleEvent(SoHandleEventAction * action);
  virtual void pick(SoPickAction * action);
  virtual void search(SoSearchAction * action);
  virtual void write(SoWriteAction * action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);
  virtual void audioRender(SoAudioRenderAction * action);
  virtual SoChildList * getChildren(void) const;
  virtual void addWriteReference(SoOutput * out, SbBool isfromfield = FALSE);

protected:
  virtual ~SoX3DChildNode();

  virtual SbBool readInstance(SoInput * in, unsigned short flags);
  virtual SbBool readChildren(SoInput * in);

  virtual void copyContents(const SoFieldContainer * from,
			    SbBool copyconnections);

  virtual SoNotRec createNotRec(void);

  void setOperation(const SoNotRec::OperationType opType = SoNotRec::UNSPECIFIED,
		    const SoNode * cc = NULL,
		    const SoNode * pc = NULL,
		    const int ci = -1);

  SoChildList * children;

private:
  friend class SoUnknownNode; // Let SoUnknownNode access readChildren().

  SoX3DChildNodeP * pimpl;

  int changedIndex;
  const SoNode * changedChild;
  const SoNode * changedPrevChild;
  SoNotRec::OperationType operationType;

}; // class SoX3DChildNode

#endif // ! COIN_SOX3DCHILDNODE_H
