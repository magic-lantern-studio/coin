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

#ifndef COIN_SOX3DBOUNDEDOBJECT_H
#define COIN_SOX3DBOUNDEDOBJECT_H

//#include <Inventor/fields/SoFieldContainer.h>
//#include <Inventor/fields/SoFieldData.h>
//#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/SoType.h>

class SoX3DBoundedObjectP;

//class COIN_DLL_API SoX3DBoundedObject : public SoFieldContainer
class COIN_DLL_API SoX3DBoundedObject
{
public:
  SoX3DBoundedObject(void);

  //SoSFVec3f bboxCenter;
  //SoSFVec3f bboxSize;
  // FIXME: Coin does not support multiple inheritace for SoNodes.
  // Therefore we can't implement this X3D abstract class as a SoNode
  // since SoX3DboundedObject is used for nodes that require bboxCenter
  // and bboxSize and the X3D specifiation defines this as an inherited
  // interface/abstract class. The Coin implementation of SoFieldContainer
  // also cause issues with multiple inheritance. Thus, SoX3DBoundedObject
  // becomes an empty class and bboxCenter and bboxSize need to be
  // directly implemented in the SoNode classes that require them.
  // 2026-03-11 msm (WizzerWorks)

protected:
  virtual ~SoX3DBoundedObject();

private:
//  static SoFieldData * fieldData;

  SoX3DBoundedObjectP * pimpl;

}; // class SoX3DBoundedObject

#endif // COIN_SOX3DBOUNDEDOBJECT_H
