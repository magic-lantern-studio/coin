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
  \class SoX3DFontStyle SoX3DFontStyle.h Inventor/X3Dnodes/SoX3DFontStyle.h
  \brief The SoX3DFontStyle class is used to define the current font.

  \ingroup coin_X3Dnodes

  Important note: currently, the SoX3DText node implementation is not
  complete, and some of the features mentioned in the documentation
  below may not be working yet.

  \WEB3DCOPYRIGHT
  
  \verbatim
  FontStyle {
    exposedField SoSFNode metadata     MULL
    field        MFString family       "SERIF"
    field        SFBool   horizontal   TRUE
    field        MFString justify      "BEGIN"      # ["BEGIN"|"END"|"FIRST"|"MIDDLE"|""]
    field        SFString language     ""
    field        SFBool   leftToRight  TRUE
    field        SFFloat  size         1.0          # (0, inf)
    field        SFFloat  spacing      1.0          # [0, inf)
    field        SFString style        "PLAIN"      # "PLAIN" ["PLAIN"|"BOLD"|"ITALIC"|"BOLDITALIC"|""]
    field        SFBool   topToBottom  TRUE
  }
  \endverbatim

  The FontStyle node defines the size, family, and style used for Text
  nodes, 15.2.2 Text formatting (see https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/text.html#TextFormatting) as well as the direction of the text strings and any
  language-specific rendering techniques used for non-English
  text. See SoX3DText, for a description of the Text node.

  The size field specifies the nominal height, in the local coordinate
  system of the Text node, of glyphs rendered and determines the
  spacing of adjacent lines of text. Values of the size field shall be
  greater than zero.

  The spacing field determines the line spacing between adjacent lines
  of text. The distance between the baseline of each line of text is
  (spacing ? size) in the appropriate direction (depending on other
  fields described below). The effects of the size and spacing field
  are depicted in Figure 15.2 (spacing greater than 1.0). Values of the
  spacing field shall be non-negative.

  FontStyle node example

  <center>
  <img src="https://www.web3d.org/documents/specifications/19775-1/V3.0/Images/FontStylespacing.gif">
  Figure 15.2 -- Text size and spacing fields
  </center>

*/

/*!
  SoSFFloat SoX3DFontStyle::size
  Size of font.
*/

/*!
  SoMFString SoX3DFontStyle::family
  Font family. All browsers must support "SANS", "SERIF" and "TYPEWRITER". Default value is "SERIF".
*/

/*!
  SoMFString SoX3DFontStyle::style
  Font style. Can be one of "PLAIN", "BOLD", "ITALIC" or "BOLDITALIC". Default value is "PLAIN".
*/

/*!
  SoSFBool SoX3DFontStyle::horizontal
  TRUE if strings should be rendered horizontally. Default value is TRUE.
*/

/*!
  SoSFBool SoX3DFontStyle::leftToRight
  TRUE if strings should be rendered left to right. Default value is TRUE.
*/

/*!
  SoSFBool SoX3DFontStyle::topToBottom
  True if strings should be rendered top to bottom. Default value is TRUE.
*/

/*!
  SoSFString SoX3DFontStyle::language
  Text language. Empty by default.
*/

/*!
  SoMFString SoX3DFontStyle::justify
  Text justification. Can be "BEGIN", "FIRST" "MIDDLE" or "END". Default value is "BEGIN".
*/

/*!
  SoSFFloat SoX3DFontStyle::spacing
  Spacing constant. Default value is 1.0.
*/

/*!
  \var SoSFNode SoX3DFontStyple::metadata

  Can contain an SoX3DMetadataObject. Is NULL by default.
*/

#include <Inventor/X3Dnodes/SoX3DFontStyle.h>
#include "coindefs.h"

#include <Inventor/X3Dnodes/SoX3DMacros.h>

#include "nodes/SoSubNodeP.h"

SO_NODE_SOURCE(SoX3DFontStyle);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DFontStyle::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DFontStyle, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DFontStyle::SoX3DFontStyle(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DFontStyle);

  SO_X3DNODE_ADD_EXPOSED_FIELD(metadata, (NULL));

  SO_X3DNODE_ADD_FIELD(family, ("SERIF"));
  SO_X3DNODE_ADD_FIELD(horizontal, (TRUE));
  SO_X3DNODE_ADD_FIELD(justify, ("BEGIN"));
  SO_X3DNODE_ADD_FIELD(language, (""));
  SO_X3DNODE_ADD_FIELD(leftToRight, (TRUE));
  SO_X3DNODE_ADD_FIELD(size, (1.0f));
  SO_X3DNODE_ADD_FIELD(spacing, (1.0f));
  SO_X3DNODE_ADD_FIELD(style, ("PLAIN"));
  SO_X3DNODE_ADD_FIELD(topToBottom, (TRUE));
}

/*!
  Destructor.
*/
SoX3DFontStyle::~SoX3DFontStyle()
{
}

SbString
SoX3DFontStyle::getFontName(void)
{
  return SbString("");
}

// doc in parent
void
SoX3DFontStyle::doAction(SoAction * COIN_UNUSED_ARG(action))
{
}

// doc in parent
void
SoX3DFontStyle::callback(SoCallbackAction * COIN_UNUSED_ARG(action))
{
}

// doc in parent
void
SoX3DFontStyle::GLRender(SoGLRenderAction * COIN_UNUSED_ARG(action))
{
}

// doc in parent
void
SoX3DFontStyle::getBoundingBox(SoGetBoundingBoxAction * COIN_UNUSED_ARG(action))
{
}

// doc in parent

void
SoX3DFontStyle::pick(SoPickAction * COIN_UNUSED_ARG(action))
{
}

// doc in parent
void
SoX3DFontStyle::getPrimitiveCount(SoGetPrimitiveCountAction * COIN_UNUSED_ARG(action))
{
}

#endif // HAVE_X3D
