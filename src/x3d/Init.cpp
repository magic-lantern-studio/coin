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

#include <Inventor/X3Dnodes/SoX3D.h>
#include <Inventor/X3Dnodes/SoX3DNodes.h>

void
so_x3d_init(void)
{
  SoX3DNode::initClass();

  SoX3DMetadataDouble::initClass();
  SoX3DMetadataFloat::initClass();
  SoX3DMetadataInteger::initClass();
  SoX3DMetadataSet::initClass();
  SoX3DMetadataString::initClass();

  SoX3DParent::initClass();
  SoX3DGroup::initClass();

  SoX3DChildNode::initClass();
  SoX3DGroupingNode::initClass();
  SoX3DBindableNode::initClass();
  SoX3DGeometryNode::initClass();
  SoX3DComposedGeometryNode::initClass();

  SoX3DTexture::initClass();

  SoX3DInterpolator::initClass();

  SoX3DLight::initClass();
  
  SoX3DSensor::initClass();
  SoX3DDragSensor::initClass();

  SoX3DAnchor::initClass();
  SoX3DAppearanceNode::initClass();
  SoX3DAppearance::initClass();
  SoX3DAudioClip::initClass();
  SoX3DBackgroundNode::initClass();
  SoX3DBackground::initClass();
  SoX3DBillboard::initClass();
  SoX3DBox::initClass();
  SoX3DCollision::initClass();
  SoX3DColor::initClass();
  SoX3DColorInterpolator::initClass();
  SoX3DCone::initClass();
  SoX3DCoordinate::initClass();
  SoX3DCoordinateInterpolator::initClass();
  SoX3DCylinder::initClass();
  SoX3DCylinderSensor::initClass();
  SoX3DDirectionalLight::initClass();
  SoX3DElevationGrid::initClass();
  SoX3DExtrusion::initClass();
  SoX3DFog::initClass();
  SoX3DFontStyle::initClass();
  SoX3DImageTexture::initClass();

  SoX3DVertexLine::initClass();
  SoX3DIndexedLine::initClass();
  SoX3DIndexedLineSet::initClass();
  SoX3DIndexedFaceSet::initClass();

  SoX3DInline::initClass();
  SoX3DLOD::initClass();
  SoX3DShape::initClass();
  SoX3DMaterial::initClass();
  SoX3DMovieTexture::initClass();
  SoX3DNavigationInfo::initClass();
  SoX3DNormal::initClass();
  SoX3DNormalInterpolator::initClass();
  SoX3DOrientationInterpolator::initClass();
  SoX3DPixelTexture::initClass();
  SoX3DPlaneSensor::initClass();
  SoX3DPointLight::initClass();
  SoX3DPointSet::initClass();
  SoX3DPositionInterpolator::initClass();
  SoX3DProximitySensor::initClass();
  SoX3DScalarInterpolator::initClass();
  SoX3DScript::initClass();
  SoX3DSound::initClass();
  SoX3DSphere::initClass();
  SoX3DSphereSensor::initClass();
  SoX3DSpotLight::initClass();
  SoX3DSwitch::initClass();
  SoX3DText::initClass();
  SoX3DTextureCoordinate::initClass();
  SoX3DTextureTransform::initClass();
  SoX3DTimeSensor::initClass();
  SoX3DTouchSensor::initClass();
  SoX3DTransform::initClass();
  SoX3DViewpoint::initClass();
  SoX3DVisibilitySensor::initClass();
  SoX3DWorldInfo::initClass();
}

#endif // HAVE_X3D
