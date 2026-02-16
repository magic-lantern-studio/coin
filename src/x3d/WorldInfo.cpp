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
  \class SoX3DWorldInfo SoX3DWorldInfo.h Inventor/X3Dnodes/SoX3DWorldInfo.h
  \brief The SoX3DWorldInfo class contains information about the X3D scene.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT

  \verbatim
  WorldInfo {
    field MFString info  []
    field SFString title ""
  }
  \endverbatim
 
  The WorldInfo node contains information about the world. This node
  is strictly for documentation purposes and has no effect on the
  visual appearance or behaviour of the world. The \e title field is
  intended to store the name or title of the world so that browsers
  can present this to the user (perhaps in the window border). Any
  other information about the world can be stored in the \e info
  field, such as author information, copyright, and usage
  instructions.

*/

/*!
  \var SoSFString SoX3DWorldInfo::title
  World title strings.
*/

/*!
  \var SoMFString SoX3DWorldInfo::info
  Info strings.
*/

#include <Inventor/X3Dnodes/SoX3DWorldInfo.h>

#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "nodes/SoSubNodeP.h"

SO_NODE_SOURCE(SoX3DWorldInfo);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DWorldInfo::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DWorldInfo, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DWorldInfo::SoX3DWorldInfo(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DWorldInfo);

  SO_X3DNODE_ADD_FIELD(title, (""));
  SO_X3DNODE_ADD_EMPTY_MFIELD(info);
}

/*!
  Destructor.
*/
SoX3DWorldInfo::~SoX3DWorldInfo()
{
}

#endif // HAVE_X3D
