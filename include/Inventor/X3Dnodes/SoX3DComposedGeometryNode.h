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

#ifndef COIN_SOX3DCOMPOSEDGEOMETRYNODE_H
#define COIN_SOX3DCOMPOSEDGEOMETRYNODE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/X3Dnodes/SoX3DGeometryNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/elements/SoMaterialBindingElement.h>

class SoNormalCache;
class SoNormalBundle;
class SoState;
class SoCoordinateElement;
class SoX3DGLRenderAction;
class SoX3DCallbackAction;
class SoX3DComposedGeometryNodeP;

class COIN_DLL_API SoX3DComposedGeometryNode : public SoX3DGeometryNode
{
  typedef SoX3DGeometryNode inherited;
  SO_NODE_ABSTRACT_HEADER(SoX3DComposedGeometryNode);

public:
  static void initClass(void);

  SoSFNode coord;
  SoSFNode texCoord;
  SoSFNode normal;
  SoSFNode color;
  SoSFBool colorPerVertex;
  SoSFBool normalPerVertex;
  SoSFBool ccw;
  SoSFBool solid;

  enum Binding {
    OVERALL             = SoMaterialBindingElement::OVERALL,
    PER_PART            = SoMaterialBindingElement::PER_PART,
    PER_PART_INDEXED    = SoMaterialBindingElement::PER_PART_INDEXED,
    PER_FACE            = SoMaterialBindingElement::PER_FACE,
    PER_FACE_INDEXED    = SoMaterialBindingElement::PER_FACE_INDEXED,
    PER_VERTEX          = SoMaterialBindingElement::PER_VERTEX,
    PER_VERTEX_INDEXED  = SoMaterialBindingElement::PER_VERTEX_INDEXED
  };

  virtual SbBool generateDefaultNormals(SoState * s, SoNormalBundle * nb);
  virtual SbBool generateDefaultNormals(SoState * s, SoNormalCache * nc);

  virtual void doAction(SoAction * action);
  virtual void GLRender(SoX3DGLRenderAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void callback(SoX3DCallbackAction * action);
  virtual void pick(SoPickAction * action);

  virtual void notify(SoNotList * list);

protected:
  SoX3DComposedGeometryNode(void);
  virtual ~SoX3DComposedGeometryNode();

  virtual SbBool shouldGLRender(SoX3DGLRenderAction * action);

  void setNormalCache(SoState * s, int numNormals, SbVec3f * normals);
  SoNormalCache * getNormalCache(void) const;

  SoNormalCache * generateAndReadLockNormalCache(SoState * const state);
  void getVertexData(SoState * state,
                     const SoCoordinateElement *& coords,
                     const SbVec3f *& normals,
                     const SbBool neednormals);

  void readLockNormalCache(void);
  void readUnlockNormalCache(void);

private:

  void writeLockNormalCache(void);
  void writeUnlockNormalCache(void);
  
  SoX3DComposedGeometryNodeP * pimpl;
  
}; // class SoX3DComposedGeometryNode

#endif // ! COIN_SOX3DCOMPOSEDGEOMETRYNODE_H
