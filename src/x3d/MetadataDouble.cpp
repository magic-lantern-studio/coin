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
  \class SoX3DMetadataDouble SoX3DMetadataDouble.h Inventor/X3Dnodes/SoX3DMetadataDouble.h
  \brief The SoX3DMetadataDouble class holds double-precision floating point values.

  \ingroup coin_X3Dnodes

  \WEBX3DCOPYRIGHT

  \verbatim
  MetadataDouble : X3DNode, X3DMetadataObject {
    SFNode   [in,out] metadata  NULL [X3DMetadataObject]
    SFString [in,out] name      ""
    SFString [in,out] reference ""
    MFDouble [in,out] value     []
  }

  The metadata provided by this node is contained in the double-precision floating point numbers of the value field.
*/

/*!
  \var SoSFNode SoX3DMetadataDouble::metadata

  Can contain an SoX3DMetadataObject. Is NULL by default.
*/

/*!
  \var SoSFString SoX3DMetadataDouble::name

  The name of the metadata standard. An empty string by default.
*/

/*!
  \var SoSFString SoX3DMetadataDouble::reference

  Optional string describing the metadata standard. An empty string by default.
*/

/*!
  \var SoMFDouble SoX3DMetadataDouble::value

  An array of double-precision, floating point values.
*/


#include <Inventor/X3Dnodes/SoX3DMetadataDouble.h>

#include <cstddef>

#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "nodes/SoSubNodeP.h"

// *************************************************************************

class SoX3DMetadataDoubleP {
};

// *************************************************************************

SO_NODE_SOURCE(SoX3DMetadataDouble);

// *************************************************************************

/*!
  \copydetails SoX3DNode::initClass(void)
*/
void
SoX3DMetadataDouble::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DMetadataDouble, SO_X3D_NODE_TYPE); 
}

#define PRIVATE(thisp) ((thisp)->pimpl)

SoX3DMetadataDouble::SoX3DMetadataDouble(void)
  : SoX3DNode(), SoX3DMetadataObject()
{
  PRIVATE(this) = new SoX3DMetadataDoubleP;

  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DMetadataDouble);

  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(value);
}

SoX3DMetadataDouble::~SoX3DMetadataDouble()
{
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
