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
  \class SoX3DPointSet SoX3DPointSet.h Inventor/X3Dnodes/SoX3DPointSet.h
  \brief The SoX3DPointSet class is used to represent a set of 3D points.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT

  \verbatim
  PointSet {
    exposedField  SFNode  color      NULL
    exposedField  SFNode  coord      NULL
  }
  \endverbatim
  
  The PointSet node specifies a set of 3D points, in the local
  coordinate system, with associated colours at each point. The coord
  field specifies a SoX3DCoordinate node (or instance of a Coordinate
  node). The results are undefined if the coord field specifies any
  other type of node. PointSet uses the coordinates in order. If the
  coord field is NULL, the point set is considered empty.  PointSet
  nodes are not lit, not texture-mapped, nor do they participate in
  collision detection. The size of each point is implementation-
  dependent.  If the color field is not NULL, it shall specify a
  SoX3DColor node that contains at least the number of points
  contained in the coord node. The results are undefined if the color
  field specifies any other type of node. Colours shall be applied to
  each point in order. The results are undefined if the number of
  values in the Color node is less than the number of values specified
  in the Coordinate node.  If the color field is NULL and there is a
  SoX3DMaterial node defined for the SoX3DAppearance node affecting
  this PointSet node, the emissiveColor of the Material node shall be
  used to draw the points. More details on lighting equations can be
  found in 4.14, Lighting model
  (<http://www.web3d.org/x3d/specifications/vrml/ISO-IEC-14772-X3D/part1/concepts.html#4.14>).

*/

#include <Inventor/X3Dnodes/SoX3DPointSet.h>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/X3Dnodes/SoX3DCoordinate.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/misc/SoGLDriverDatabase.h>
#include <Inventor/bundles/SoTextureCoordinateBundle.h>
#include <Inventor/SoPrimitiveVertex.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/system/gl.h>

#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoMultiTextureEnabledElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/bundles/SoMaterialBundle.h>
#include <Inventor/caches/SoNormalCache.h>
#include <Inventor/details/SoPointDetail.h>
#include <Inventor/caches/SoBoundingBoxCache.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbColor4f.h>
#include <Inventor/elements/SoOverrideElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoGLVBOElement.h>
#include <Inventor/elements/SoGLLazyElement.h>
#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

#include "nodes/SoSubNodeP.h"
#include "rendering/SoGL.h"
#include "rendering/SoVBO.h"

static SbBool
is_material_per_vertex(SoX3DPointSet * ps, SoState * state)
{
  if (SoOverrideElement::getMaterialBindingOverride(state)) {
    if (SoMaterialBindingElement::get(state) !=
        SoMaterialBindingElement::OVERALL) return TRUE;
    return FALSE;
  }
  return ps->color.getValue() != NULL;
}

SO_NODE_SOURCE(SoX3DPointSet);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DPointSet::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DPointSet, SO_X3D_NODE_TYPE);
}

/*!
  Constructor.
*/
SoX3DPointSet::SoX3DPointSet(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DPointSet);
}

/*!
  Destructor.
*/
SoX3DPointSet::~SoX3DPointSet()
{
}

// Doc in parent
void
SoX3DPointSet::GLRender(SoGLRenderAction * action)
{
  SoState * state = action->getState();

  SoLazyElement::setLightModel(state, SoLazyElement::BASE_COLOR);
  SoMultiTextureEnabledElement::disableAll(state);

  SoX3DVertexPoint::GLRender(action);

  if (!this->shouldGLRender(action)) return;

  const SoCoordinateElement * coords;
  coords = SoCoordinateElement::getInstance(state);

  SoMaterialBundle mb(action);

  SbBool matpervertex = is_material_per_vertex(this, state);
  if (!matpervertex) {
    const SbColor & col = SoLazyElement::getEmissive(state);
    SbColor4f c(col[0], col[1], col[2], 1.0f);
    SoGLLazyElement::sendPackedDiffuse(state, c.getPackedValue());
  }
  else {
    mb.sendFirst();
  }

  const cc_glglue * glue = sogl_glue_instance(state);

  const int numpts = coords->getNum();
  const uint32_t contextid = action->getCacheContext();

  // no point setting up OpenGL for vertex arrays for fewer than 20 points
  SbBool dova = 
    SoVBO::shouldRenderAsVertexArrays(state, contextid, numpts) && 
    SoGLDriverDatabase::isSupported(glue, SO_GL_VERTEX_ARRAY);
  
  if (dova && matpervertex) {
    const SoGLVBOElement * vboelem = SoGLVBOElement::getInstance(state);
    if (vboelem->getColorVBO() == NULL) {
      dova = FALSE;
      // we might be able to do VA-rendering, but need to check the
      // diffuse color type first.
      SoGLLazyElement * lelem = (SoGLLazyElement*) SoLazyElement::getInstance(state);
      if (!lelem->isPacked() && lelem->getNumTransparencies() <= 1) {
        dova = TRUE;
      }
    }
  }
  SbBool didrenderasvbo = FALSE;
  if (dova) {
    SbBool vbo = this->startVertexArray(action,
                                        coords,
                                        NULL,
                                        FALSE,
                                        matpervertex);
    didrenderasvbo = vbo;
    cc_glglue_glDrawArrays(glue, GL_POINTS, 0, numpts);
    this->finishVertexArray(action, vbo,
                            FALSE,
                            FALSE,
                            matpervertex);
  }
  else {
    sogl_render_pointset((SoGLCoordinateElement*) coords,
                         NULL,
                         matpervertex ? &mb : NULL,
                         NULL,
                         numpts, 0);
  }

  // send approx number of points for autocache handling
  sogl_autocache_update(state, numpts, didrenderasvbo); 
}

// Doc in parent
void
SoX3DPointSet::getBoundingBox(SoGetBoundingBoxAction * action)
{
  inherited::getBoundingBox(action);
  // notify open (if any) bbox caches about points in this shape
  SoBoundingBoxCache::setHasLinesOrPoints(action->getState());
}

// Doc in parent
void
SoX3DPointSet::generatePrimitives(SoAction * action)
{
  SoX3DCoordinate * coordnode = (SoX3DCoordinate*) this->coord.getValue();
  if (!coordnode || coordnode->point.getNum() == 0) return;
  const SbVec3f * coords = coordnode->point.getValues(0);

  SoPrimitiveVertex vertex;
  SoPointDetail pointDetail;
  vertex.setDetail(&pointDetail);

  int32_t numpts = coordnode->point.getNum();

  int matnr = 0;
  int idx = 0;

  SbBool matpervertex = is_material_per_vertex(this, action->getState());

  this->beginShape(action, SoShape::POINTS);
  for (int i = 0; i < numpts; i++) {
    if (matpervertex) {
      pointDetail.setMaterialIndex(matnr);
      vertex.setMaterialIndex(matnr++);
    }
    pointDetail.setCoordinateIndex(idx);
    vertex.setPoint(coords[idx++]);
    this->shapeVertex(&vertex);
  }
  this->endShape();
}

#endif // HAVE_X3D
