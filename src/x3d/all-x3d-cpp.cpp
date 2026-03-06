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
#include "config.h"
#endif // HAVE_CONFIG_H

#ifdef HAVE_X3D

#include "x3d/Anchor.cpp"
#include "x3d/Appearance.cpp"
#include "x3d/AudioClip.cpp"
#include "x3d/Background.cpp"
#include "x3d/Billboard.cpp"
#include "x3d/Box.cpp"
#include "x3d/Collision.cpp"
#include "x3d/Color.cpp"
#include "x3d/ColorInterpolator.cpp"
#include "x3d/Cone.cpp"
#include "x3d/Coordinate.cpp"
#include "x3d/CoordinateInterpolator.cpp"
#include "x3d/Cylinder.cpp"
#include "x3d/CylinderSensor.cpp"
#include "x3d/DirectionalLight.cpp"
#include "x3d/DragSensor.cpp"
#include "x3d/ElevationGrid.cpp"
#include "x3d/Extrusion.cpp"
#include "x3d/Fog.cpp"
#include "x3d/FontStyle.cpp"
#include "x3d/Geometry.cpp"
#include "x3d/Group.cpp"
#include "x3d/ImageTexture.cpp"
#include "x3d/IndexedFaceSet.cpp"
#include "x3d/IndexedLine.cpp"
#include "x3d/IndexedLineSet.cpp"
#include "x3d/IndexedShape.cpp"
#include "x3d/Init.cpp"
#include "x3d/Inline.cpp"
#include "x3d/Interpolator.cpp"
#include "x3d/LOD.cpp"
#include "x3d/Light.cpp"
#include "x3d/Material.cpp"
#include "x3d/MovieTexture.cpp"
#include "x3d/NavigationInfo.cpp"
#include "x3d/Normal.cpp"
#include "x3d/NormalInterpolator.cpp"
#include "x3d/OrientationInterpolator.cpp"
#include "x3d/Parent.cpp"
#include "x3d/PixelTexture.cpp"
#include "x3d/PlaneSensor.cpp"
#include "x3d/PointLight.cpp"
#include "x3d/PointSet.cpp"
#include "x3d/PositionInterpolator.cpp"
#include "x3d/ProximitySensor.cpp"
#include "x3d/ScalarInterpolator.cpp"
#include "x3d/Script.cpp"
#include "x3d/Sensor.cpp"
#include "x3d/Shape.cpp"
#include "x3d/Sound.cpp"
#include "x3d/Sphere.cpp"
#include "x3d/SphereSensor.cpp"
#include "x3d/SpotLight.cpp"
#include "x3d/Switch.cpp"
#include "x3d/Text.cpp"
#include "x3d/Texture.cpp"
#include "x3d/TextureCoordinate.cpp"
#include "x3d/TextureTransform.cpp"
#include "x3d/TimeSensor.cpp"
#include "x3d/TouchSensor.cpp"
#include "x3d/Transform.cpp"
#include "x3d/VertexLine.cpp"
#include "x3d/VertexPoint.cpp"
#include "x3d/VertexShape.cpp"
#include "x3d/Viewpoint.cpp"
#include "x3d/VisibilitySensor.cpp"
#include "x3d/WorldInfo.cpp"
#include "x3d/JS_X3DClasses.cpp"
#include "x3d/X3DAppearanceNode.cpp"
#include "x3d/X3DAppearanceChildNode.cpp"
#include "x3d/X3DBackgroundNode.cpp"
#include "x3d/X3DBindableNode.cpp"
#include "x3d/X3DBoundedObject.cpp"
#include "x3d/X3DChildNode.cpp"
#include "x3d/X3DGeometryNode.cpp"
#include "x3d/X3DGroupingNode.cpp"
#include "x3d/X3DMaterialNode.cpp"
#include "x3d/X3DMetadataDouble.cpp"
#include "x3d/X3DMetadataFloat.cpp"
#include "x3d/X3DMetadataInteger.cpp"
#include "x3d/X3DMetadataSet.cpp"
#include "x3d/X3DMetadataString.cpp"
#include "x3d/X3DMetadataObject.cpp"
#include "x3d/X3DNetworkSensorNode.cpp"
#include "x3d/X3DNode.cpp"
#include "x3d/X3DPrototypeInstance.cpp"
#include "x3d/X3DSensorNode.cpp"
#include "x3d/X3DShapeNode.cpp"
#include "x3d/X3DUrlObject.cpp"
#include "x3d/sox3dshape_bigtexture.cpp"
#include "x3d/sox3dshape_bumprender.cpp"
#include "x3d/sox3dshape_primdata.cpp"
#include "x3d/sox3dshape_trianglesort.cpp"

#endif // HAVE_X3D
