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

/*!
  \class SoGLRenderPassElement Inventor/elements/SoGLRenderPassElement.h
  \brief The SoGLRenderPassElement class is yet to be documented.

  \ingroup coin_elements

  FIXME: write doc.
*/

#include <Inventor/elements/SoGLRenderPassElement.h>

/*!
  \fn SoGLRenderPassElement::passnr

  FIXME: write doc.
*/

SO_ELEMENT_SOURCE(SoGLRenderPassElement);

/*!
  \copydetails SoElement::initClass(void)
*/

void
SoGLRenderPassElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoGLRenderPassElement, inherited);
}

/*!
  Destructor.
*/

SoGLRenderPassElement::~SoGLRenderPassElement(void)
{
}

//! FIXME: write doc.

void
SoGLRenderPassElement::init(SoState * state)
{
  inherited::init(state);
  this->passnr = 0;
}

//! FIXME: write doc.

SbBool
SoGLRenderPassElement::matches(const SoElement * element) const
{
  return this->passnr == ((SoGLRenderPassElement*)element)->passnr;
}

//! FIXME: write doc.

SoElement *
SoGLRenderPassElement::copyMatchInfo(void) const
{
  SoGLRenderPassElement * elem = (SoGLRenderPassElement*) this->getTypeId().createInstance();
  elem->passnr = this->passnr;
  return elem;
}

//! FIXME: write doc.

void
SoGLRenderPassElement::set(SoState * const state,
                           const int pass)
{
  SoGLRenderPassElement * element = (SoGLRenderPassElement *)
    getElement(state, classStackIndex);
  if (element) {
    element->passnr = pass;
  }
}

//! FIXME: write doc.

int
SoGLRenderPassElement::get(SoState * const state)
{
  const SoGLRenderPassElement * element = (const SoGLRenderPassElement *)
    getConstElement(state, classStackIndex);
  return element->passnr;
}
