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
  \class SoX3DChildNode SoX3DChildNode.h Inventor/X3Dnodes/SoX3DChildNode.h
  \brief The SoX3DChildNode is a base node type for the child nodes of X3DChildNode type.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT

  \verbatim
  X3DChildNode : X3DNode {
    SFNode [in,out] metadata NULL [X3DMetadataObject]
  }
  \endverbatim

  This abstract node type indicates that the concrete nodes which are instantiated based on it may be used in children, addChildren, and removeChildren fields.

  More details on the children, addChildren, and removeChildren fields can be found in 10.2.1 Grouping and children node types (see https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Groupingandchildrennodes)

*/

#include <Inventor/X3Dnodes/SoX3DChildNode.h>

#include <cstddef>

#include <Inventor/X3Dnodes/SoX3DMacros.h>

// *************************************************************************

class SoX3DChildNodeP {
}

// *************************************************************************

SO_NODE_SOURCE(SoX3DChildNode);

// *************************************************************************

/*!
  \copydetails SoX3DNode::initClass(void)
*/
void
SoX3DChildNode::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DChildNode, SO_X3D_NODE_TYPE);
}

#define PRIVATE(thisp) ((thisp)->pimpl)

SoX3DChildNode::SoX3DChildNode(void)
  : SoX3DNode()
{
  PRIVATE(this) = new SoX3DChildNodeP;

  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DChildNode);
}

SoX3DChildNode::~SoX3DChildNode()
{
  delete PRIVATE(this);
}

#undef PRIVATE

#endif // HAVE_X3D
