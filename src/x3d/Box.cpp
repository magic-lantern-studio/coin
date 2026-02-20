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
  \class SoX3DBox SoX3DBox.h Inventor/X3Dnodes/SoX3DBox.h
  \brief The SoX3DBox class is used for representing a 3D box.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT

  \verbatim
  Box {
    exposedField SFNode  metadata NULL
    field        SFVec3f size     2 2 2        # (0, inf)
    field        SFBool  solid    TRUE
  }
  \endverbatim

  The Box node specifies a rectangular parallelepiped box centred at (0, 0, 0)
  in the local coordinate system and aligned with the local coordinate axes.
  By default, the box measures 2 units in each dimension, from -1 to +1. The
  size field specifies the extents of the box along the X-, Y-, and
  Z-axes respectively and each component value shall be greater than zero.
  Figure 6.2 illustrates the Box node.

  <center>
  <img src="https://www.web3d.org/documents/specifications/19775-1/V3.0/Images/box.gif">
  Figure 13.1 - Box node
  </center>

  Textures are applied individually to each face of the box. On the
  front (+Z), back (-Z), right (+X), and left (-X) faces of the box,
  when viewed from the outside with the +Y-axis up, the texture is
  mapped onto each face with the same orientation as if the image were
  displayed normally in 2D.  On the top face of the box (+Y), when
  viewed from above and looking down the Y-axis toward the origin with
  the -Z-axis as the view up direction, the texture is mapped onto the
  face with the same orientation as if the image were displayed
  normally in 2D. On the bottom face of the box (-Y), when viewed from
  below looking up the Y-axis toward the origin with the +Z-axis as
  the view up direction, the texture is mapped onto the face with the
  same orientation as if the image were displayed normally in
  2D. SoX3DTextureTransform affects the texture coordinates of the
  Box (see 18.4.8 TextureTransform).

  The solid field determines whether the box is visible when viewed from the inside. 11.2.3 Common geometry fields provides a complete description of the solid field.  
*/

/*!
  \var SoSFNode SoX3DBox::metadata

  Can contain an SoX3DMetadataObject. Is NULL by default.
*/

/*!
  \var SoX3DBox::size

  Box size vector. Default value is (2,2,2).
*/

/*!
  \var SoX3DBox::solid

  Determines whether the Box is visible when viewed from the inside.
  Default value is TRUE.
*/

#include <Inventor/X3Dnodes/SoX3DBox.h>
#include "coindefs.h"

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/elements/SoGLMultiTextureEnabledElement.h>
#include <Inventor/elements/SoMultiTextureCoordinateElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/bundles/SoMaterialBundle.h>
#include <Inventor/misc/SoState.h>

#include "nodes/SoSubNodeP.h"
#include "rendering/SoGL.h"
#include "misc/SoGenerate.h"
#include "misc/SoPick.h"

SO_NODE_SOURCE(SoX3DBox);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DBox::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DBox, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DBox::SoX3DBox(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DBox);

  SO_X3DNODE_ADD_EXPOSED_FIELD(metadata, (NULL));
  SO_X3DNODE_ADD_FIELD(size, (2.0f, 2.0f, 2.0f));
  SO_X3DNODE_ADD_FIELD(solid, (TRUE));
}

/*!
  Destructor.
*/
SoX3DBox::~SoX3DBox()
{
}

// Doc in parent
void
SoX3DBox::GLRender(SoGLRenderAction * action)
{
 if (!this->shouldGLRender(action)) return;
  SoState * state = action->getState();

  SbBool doTextures = SoGLMultiTextureEnabledElement::get(state);

  SoMaterialBundle mb(action);
  mb.sendFirst();

  SbBool sendNormals = !mb.isColorOnly() ||
    (SoMultiTextureCoordinateElement::getType(state) == SoMultiTextureCoordinateElement::FUNCTION);

  unsigned int flags = 0;
  if (doTextures) flags |= SOGL_NEED_TEXCOORDS;
  if (sendNormals) flags |= SOGL_NEED_NORMALS;

  SbVec3f s = this->size.getValue();

  sogl_render_cube(s[0],
                   s[1],
                   s[2],
                   &mb,
                   flags, state);
}

// Doc in parent
void
SoX3DBox::rayPick(SoRayPickAction * action)
{
  if (!shouldRayPick(action)) return;

  SbVec3f s = this->size.getValue();
  sopick_pick_cube(s[0],
                   s[1],
                   s[2],
                   0,
                   this, action);
}

// Doc in parent
void
SoX3DBox::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  if (!this->shouldPrimitiveCount(action)) return;
  action->addNumTriangles(12);
}

// Doc in parent
void
SoX3DBox::generatePrimitives(SoAction * action)
{
  SbVec3f s = this->size.getValue();
  sogen_generate_cube(s[0],
                      s[1],
                      s[2],
                      0,
                      this,
                      action);
}

// Doc in parent
void
SoX3DBox::computeBBox(SoAction * action,
                       SbBox3f & COIN_UNUSED_ARG(box),
                       SbVec3f & center)
{
  center.setValue(0.0f, 0.0f, 0.0f);
  SbVec3f s = this->size.getValue();
  float w = s[0] * 0.5f;
  float h = s[1] * 0.5f;
  float d = s[2] * 0.5f;

  // Allow negative values.
  if (w < 0.0f) w = -w;
  if (h < 0.0f) h = -h;
  if (d < 0.0f) d = -d;

  box.setBounds(-w, -h, -d, w, h, d);
}

#endif // HAVE_X3D
