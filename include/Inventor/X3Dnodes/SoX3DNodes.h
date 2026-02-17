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

#ifndef COIN_SOX3DNODES_H
#define COIN_SOX3DNODES_H

#include <Inventor/X3Dnodes/SoX3DAnchor.h>
#include <Inventor/X3Dnodes/SoX3DAppearance.h>
#include <Inventor/X3Dnodes/SoX3DAudioClip.h>
#include <Inventor/X3Dnodes/SoX3DBackground.h>
#include <Inventor/X3Dnodes/SoX3DBillboard.h>
#include <Inventor/X3Dnodes/SoX3DBox.h>
#include <Inventor/X3Dnodes/SoX3DCollision.h>
#include <Inventor/X3Dnodes/SoX3DColor.h>
#include <Inventor/X3Dnodes/SoX3DColorInterpolator.h>
#include <Inventor/X3Dnodes/SoX3DCone.h>
#include <Inventor/X3Dnodes/SoX3DCoordinate.h>
#include <Inventor/X3Dnodes/SoX3DCoordinateInterpolator.h>
#include <Inventor/X3Dnodes/SoX3DCylinder.h>
#include <Inventor/X3Dnodes/SoX3DCylinderSensor.h>
#include <Inventor/X3Dnodes/SoX3DDirectionalLight.h>
#include <Inventor/X3Dnodes/SoX3DElevationGrid.h>
#include <Inventor/X3Dnodes/SoX3DExtrusion.h>
#include <Inventor/X3Dnodes/SoX3DFog.h>
#include <Inventor/X3Dnodes/SoX3DFontStyle.h>
#include <Inventor/X3Dnodes/SoX3DGeometry.h>
#include <Inventor/X3Dnodes/SoX3DGroup.h>
#include <Inventor/X3Dnodes/SoX3DImageTexture.h>
#include <Inventor/X3Dnodes/SoX3DIndexedFaceSet.h>
#include <Inventor/X3Dnodes/SoX3DIndexedLine.h>
#include <Inventor/X3Dnodes/SoX3DIndexedLineSet.h>
#include <Inventor/X3Dnodes/SoX3DIndexedShape.h>
#include <Inventor/X3Dnodes/SoX3DInline.h>
//#include <Inventor/X3Dnodes/SoX3DInterpOutput.h>
//#include <Inventor/X3Dnodes/SoX3DInterpOutputData.h>
#include <Inventor/X3Dnodes/SoX3DInterpolator.h>
#include <Inventor/X3Dnodes/SoX3DLOD.h>
#include <Inventor/X3Dnodes/SoX3DLight.h>
#include <Inventor/X3Dnodes/SoX3DMaterial.h>
#include <Inventor/X3Dnodes/SoX3DMovieTexture.h>
#include <Inventor/X3Dnodes/SoX3DNavigationInfo.h>
#include <Inventor/X3Dnodes/SoX3DNormal.h>
#include <Inventor/X3Dnodes/SoX3DNormalInterpolator.h>
#include <Inventor/X3Dnodes/SoX3DOrientationInterpolator.h>
// #include <Inventor/X3Dnodes/SoX3DOutputData.h>
#include <Inventor/X3Dnodes/SoX3DParent.h>
#include <Inventor/X3Dnodes/SoX3DPixelTexture.h>
#include <Inventor/X3Dnodes/SoX3DPlaneSensor.h>
#include <Inventor/X3Dnodes/SoX3DPointLight.h>
#include <Inventor/X3Dnodes/SoX3DPointSet.h>
#include <Inventor/X3Dnodes/SoX3DPositionInterpolator.h>
#include <Inventor/X3Dnodes/SoX3DProximitySensor.h>
#include <Inventor/X3Dnodes/SoX3DScalarInterpolator.h>
#include <Inventor/X3Dnodes/SoX3DScript.h>
#include <Inventor/X3Dnodes/SoX3DShape.h>
#include <Inventor/X3Dnodes/SoX3DSound.h>
#include <Inventor/X3Dnodes/SoX3DSphere.h>
#include <Inventor/X3Dnodes/SoX3DSphereSensor.h>
#include <Inventor/X3Dnodes/SoX3DSpotLight.h>
#include <Inventor/X3Dnodes/SoX3DSwitch.h>
#include <Inventor/X3Dnodes/SoX3DText.h>
#include <Inventor/X3Dnodes/SoX3DTexture.h>
#include <Inventor/X3Dnodes/SoX3DTextureCoordinate.h>
#include <Inventor/X3Dnodes/SoX3DTextureTransform.h>
#include <Inventor/X3Dnodes/SoX3DTimeSensor.h>
#include <Inventor/X3Dnodes/SoX3DTouchSensor.h>
#include <Inventor/X3Dnodes/SoX3DTransform.h>
#include <Inventor/X3Dnodes/SoX3DVertexLine.h>
#include <Inventor/X3Dnodes/SoX3DVertexPoint.h>
#include <Inventor/X3Dnodes/SoX3DVertexShape.h>
#include <Inventor/X3Dnodes/SoX3DViewpoint.h>
#include <Inventor/X3Dnodes/SoX3DVisibilitySensor.h>
#include <Inventor/X3Dnodes/SoX3DWorldInfo.h>

#endif // COIN_SOX3DNODES
