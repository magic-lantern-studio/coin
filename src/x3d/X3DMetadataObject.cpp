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
  \class SoX3DMetadataObject SoX3DMetadataObject.h Inventor/X3Dnodes/SoX3DMetadataObject.h
  \brief The SoX3DMetadataObject is an abstract interface and is inherited by all metadata nodes in the X3D specification.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  X3DMetadataObject {
    SFString [in,out] name      ""
    SFString [in,out] reference ""
  }
  \endverbatim

  This abstract interface is the basis for all metadata nodes. The interface is inherited by all metadata nodes.

  The specification of the reference field is optional. If provided, it identifies the metadata standard or other specification that defines the name field. If the reference field is not provided or is empty, the meaning of the name field is considered implicit to the characters in the string.

*/

#include <Inventor/X3Dnodes/SoX3DMetadataObject.h>

#include <cstddef>

// *************************************************************************

class SoX3DMetadataObjectP {
};

// *************************************************************************

#define PRIVATE(thisp) ((thisp)->pimpl)

SoX3DMetadataObject::SoX3DMetadataObject(void)
{
  PRIVATE(this) = new SoX3DMetadataObjectP;

  name.setValue("");
  reference.setValue("");
}

SoX3DMetadataObject::~SoX3DMetadataObject()
{
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
