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

#ifndef COIN_SOX3DGROUP_H
#define COIN_SOX3DGROUP_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/X3Dnodes/SoX3DGroupingNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec3f.h>

class SoState;
class SoX3DGroupP;

class COIN_DLL_API SoX3DGroup : public SoX3DGroupingNode
{
  typedef SoX3DGroupingNode inherited;
  SO_NODE_HEADER(SoX3DGroup);

public:
  static void initClass(void);

  SoX3DGroup(void);
  SoX3DGroup(int numChildren);

  enum CacheEnabled {
    OFF,
    ON,
    AUTO
  };

  SoSFEnum renderCaching;
  SoSFEnum boundingBoxCaching;
  SoSFEnum renderCulling;
  SoSFEnum pickCulling;

  static void setNumRenderCaches(int num);
  static int getNumRenderCaches(void);

  virtual void doAction(SoAction * action);
  virtual void callback(SoX3DCallbackAction * action);
  virtual void GLRender(SoX3DGLRenderAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void getMatrix(SoGetMatrixAction * action);
  virtual void rayPick(SoRayPickAction * action);
  virtual void search(SoSearchAction * action);
  virtual void write(SoWriteAction * action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);
  virtual void audioRender(SoAudioRenderAction * action);

  virtual void GLRenderBelowPath(SoX3DGLRenderAction * action);
  virtual void GLRenderInPath(SoX3DGLRenderAction * action);
  virtual void GLRenderOffPath(SoX3DGLRenderAction * action);

  virtual void notify(SoNotList * list);

protected:
  virtual ~SoX3DGroup();

  virtual SbBool cullTest(SoState * state);

  static int numRenderCaches;

private:
  SoX3DGroupP * pimpl;

  SbBool cullTestNoPush(SoState * state);
  void commonConstructor(void);

}; // class SoX3DGroup

#endif // ! COIN_SOX3DGROUP_H
