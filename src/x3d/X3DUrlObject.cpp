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
  \class SoX3DUrlObject SoX3DUrlObject.h Inventor/X3Dnodes/SoX3DUrlObject.h
  \brief The SoX3DUrlObject is an abstract interface and is inherited by all metadata nodes in the X3D specification.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  X3DUrlObject {
    MFString [in,out] url [] [urn]
  }
  \endverbatim

  This abstract interface is inherited by all nodes that contain data located on the World Wide Web, such as AudioClip, ImageTexture and Inline.

All url fields can hold multiple string values. The strings in these fields indicate multiple locations to search for data in decreasing order of preference. If the browser cannot locate or interpret the data specified by the first location, it shall try the second and subsequent locations in order until a location containing interpretable data is encountered. X3D browsers only have to interpret a single string. If no interpretable locations are found, the node type defines the resultant default behaviour.

For more information on URLs, see "9.2.1 URLs" (https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/networking.html#URLs).

*/

#include <Inventor/X3Dnodes/SoX3DUrlObject.h>

#include <cstddef>

// *************************************************************************

class SoX3DUrlObjectP {
};

// *************************************************************************

#define PRIVATE(thisp) ((thisp)->pimpl)

SoX3DUrlObject::SoX3DUrlObject(void)
{
  PRIVATE(this) = new SoX3DUrlObjectP;

  //url.setValue("");
  // FIXME: Not sure how to set an empty field yet.
}

SoX3DUrlObject::~SoX3DUrlObject()
{
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
