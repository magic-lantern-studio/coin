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

#ifndef COIN_SOX3DSCRIPT_H
#define COIN_SOX3DSCRIPT_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFString.h>

class SoX3DScript;
class SoX3DScriptP;
class SoSensor;

typedef void SoX3DScriptEvaluateCB(void * closure, SoX3DScript * node);

class COIN_DLL_API SoX3DScript : public SoNode
{
  typedef SoNode inherited;

public:
  static void initClass(void);
  SoX3DScript(void);

  static SoType getClassTypeId(void);
  virtual SoType getTypeId(void) const;

  SoMFString url;
  SoSFBool directOutput;
  SoSFBool mustEvaluate;

  virtual void doAction(SoAction * action);
  virtual void callback(SoCallbackAction * action);
  virtual void GLRender(SoGLRenderAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void pick(SoPickAction * action);
  virtual void handleEvent(SoHandleEventAction * action);
  virtual void write(SoWriteAction * action);

  static void setScriptEvaluateCB(SoX3DScriptEvaluateCB * cb,
                                  void * closure);

protected:
  virtual ~SoX3DScript();
  virtual void copyContents(const SoFieldContainer * from, SbBool copyconn);
  virtual void notify(SoNotList * list);
private:
  static SoType classTypeId;
  static void * createInstance(void);
  SoFieldData * fielddata;
  virtual const SoFieldData * getFieldData(void) const;

private:
  virtual SbBool readInstance(SoInput * in, unsigned short flags);

  static void eval_cb(void * data, SoSensor *);
  void initFieldData(void);
  SoX3DScriptP * pimpl;
  friend class SoX3DScriptP;
}; // class SoX3DScript

#endif // ! COIN_SOX3DSCRIPT_H
