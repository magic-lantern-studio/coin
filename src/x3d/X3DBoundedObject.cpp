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
  \class SoX3DBoundedObject SoX3DBoundedObject.h Inventor/X3Dnodes/SoX3DBoundedObject.h
  \brief The SoX3DBoundedObject is an abstract node type used for node types requiring bounded limits.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT

  \verbatim
  X3DBoundedObject { 
    SFVec3f [] bboxCenter 0 0 0    (-∞,∞)
    SFVec3f [] bboxSize   -1 -1 -1 [0,∞) or −1 −1 −1
  }
  \endverbatim

  This abstract node type is basis for all node types that have bounds specified as part of the definition.

  The bboxCenter and bboxSize fields specify a bounding box that encloses the Group node's children. This is a hint that may be used for optimization purposes. The results are undefined if the specified bounding box is smaller than the actual bounding box of the children at any time. A default bboxSize value, (-1, -1, -1), implies that the bounding box is not specified and, if needed, is calculated by the browser. A description of the bboxCenter and bboxSize fields is contained in 10.2.2 Bounding boxes (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#BoundingBoxes).

*/

#include <Inventor/X3Dnodes/SoX3DBoundedObject.h>

#include <cstddef>

//#include <Inventor/X3Dnodes/SoX3DMacros.h>

// *************************************************************************

class SoX3DBoundedObjectP {
};

// *************************************************************************

#define PRIVATE(thisp) ((thisp)->pimpl)

//SoFieldData * SoX3DBoundedObject::fieldData = NULL; 

SoX3DBoundedObject::SoX3DBoundedObject(void)
{
  PRIVATE(this) = new SoX3DBoundedObjectP;

  /*
  if (!SoX3DBoundedObject::fieldData) {
    SoX3DBoundedObject::fieldData =
      new SoFieldData(nullptr);
  }

  SO_X3DNODE_ADD_FIELD(bboxCenter, (0, 0, 0));
  SO_X3DNODE_ADD_FIELD(bboxCenter, (-1, -1, -1));
  */
}

SoX3DBoundedObject::~SoX3DBoundedObject()
{
  //  delete SoX3DBoundedObject::fieldData;
  //SoX3DBoundedObject::fieldData = NULL;
  
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
