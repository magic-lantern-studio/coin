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

#ifndef COIN_SOX3DINDEXEDLINESET_H
#define COIN_SOX3DINDEXEDLINESET_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/X3Dnodes/SoX3DGeometryNode.h>

#ifndef SO_END_LINE_INDEX // also defined in SoIndexedLineSet.h
#define SO_END_LINE_INDEX (-1)
#endif // !SO_END_LINE_INDEX

class SoX3DIndexedLineSetP;

class COIN_DLL_API SoX3DIndexedLineSet : public SoX3DGeometryNode
{
  typedef SoX3DGeometryNode inherited;
  SO_NODE_HEADER(SoX3DIndexedLineSet);

public:
  static void initClass(void);
  SoX3DIndexedLineSet(void);

  SoMFInt32 set_colorIndex;
  SoMFInt32 set_coordIndex;
  SoSFNode  color;
  SoSFNode  coord;
  SoMFInt32 coordIndex;
  SoSFBool  colorPerVertex;
  SoMFInt32 colorIndex;

  virtual void GLRender(SoX3DGLRenderAction * action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void callback(SoX3DCallbackAction * action);
  virtual void pick(SoPickAction * action);

 protected:
  virtual ~SoX3DIndexedLineSet();
  virtual void generatePrimitives(SoAction * action);

  virtual void computeBBox(SoAction * action,
                           SbBox3f & box, SbVec3f & center);
  
  int getNumVerts( int startCoord );
  void setupIndices( int numFaces );
  const int32_t * getColorIndices(void);

  virtual SbBool shouldGLRender(SoX3DGLRenderAction * action);

  virtual void notify(SoNotList * list);

 private:
  SoX3DIndexedLineSetP * pimpl;
};

#endif // ! COIN_SOX3DINDEXEDLINESET_H
