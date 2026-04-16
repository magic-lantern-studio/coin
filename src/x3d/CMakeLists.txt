# source files
set(COIN_X3D_FILES
	Anchor.cpp
	Appearance.cpp
	AudioClip.cpp
	Background.cpp
	Billboard.cpp
	Box.cpp
	Collision.cpp
	Color.cpp
	ColorInterpolator.cpp
	Cone.cpp
	Coordinate.cpp
	CoordinateInterpolator.cpp
	Cylinder.cpp
	CylinderSensor.cpp
	DirectionalLight.cpp
	DragSensor.cpp
	ElevationGrid.cpp
	Extrusion.cpp
	Fog.cpp
	FontStyle.cpp
	Group.cpp
	ImageTexture.cpp
	IndexedFaceSet.cpp
	IndexedLine.cpp
	IndexedLineSet.cpp
	Init.cpp
	Inline.cpp
	Interpolator.cpp
	LOD.cpp
	Light.cpp
	Material.cpp
	MovieTexture.cpp
	NavigationInfo.cpp
	Normal.cpp
	NormalInterpolator.cpp
	OrientationInterpolator.cpp
	Parent.cpp
	PixelTexture.cpp
	PlaneSensor.cpp
	PointLight.cpp
	PointSet.cpp
	PositionInterpolator.cpp
	ProximitySensor.cpp
	ScalarInterpolator.cpp
	Script.cpp
	Sensor.cpp
	Shape.cpp
	Sound.cpp
	Sphere.cpp
	SphereSensor.cpp
	SpotLight.cpp
	Switch.cpp
	Text.cpp
	Texture.cpp
	TextureCoordinate.cpp
	TextureTransform.cpp
	TimeSensor.cpp
	TouchSensor.cpp
	Transform.cpp
	VertexLine.cpp
	Viewpoint.cpp
	VisibilitySensor.cpp
	WorldInfo.cpp
	JS_X3DClasses.cpp
	X3DAppearanceNode.cpp
	X3DAppearanceChildNode.cpp
	X3DBackgroundNode.cpp
	X3DBindableNode.cpp
	X3DBoundedObject.cpp
	X3DChildNode.cpp
	X3DGeometryNode.cpp
	X3DGroupingNode.cpp
	X3DMaterialNode.cpp
	X3DMetadataObject.cpp
	X3DNetworkSensorNode.cpp
	X3DNode.cpp
	X3DPrototypeInstance.cpp
	X3DShapeNode.cpp
	X3DSensorNode.cpp
	X3DUrlObject.cpp
	MetadataDouble.cpp
	MetadataFloat.cpp
	MetadataInteger.cpp
	MetadataSet.cpp
	MetadataString.cpp
	SoX3DNodeEngine.cpp
	sox3dshape_bigtexture.cpp
	sox3dshape_bumprender.cpp
	sox3dshape_primdata.cpp
	sox3dshape_trianglesort.cpp
)

# Files excluded from public API documentation, included in complete documentation.
set(COIN_X3D_INTERNAL_FILES
	JS_X3DClasses.h
	JS_X3DClasses.cpp
	SoX3DSubInterpolatorP.h
	SoX3DNodeEngine.h
	sox3dshape_bigtexture.h
	sox3dshape_bumprender.h
	sox3dshape_primdata.h
	sox3dshape_trianglesort.h
)

# build library
if(COIN_BUILD_SINGLE_LIB)
	foreach(SRCFILE ${COIN_X3D_FILES})
		set(COIN_SOURCE ${COIN_SOURCE} x3d/${SRCFILE} CACHE INTERNAL "COIN_SOURCE")
	endforeach(SRCFILE)
else()
	add_library(x3d OBJECT ${COIN_X3D_FILES})
endif()

# define documentation
foreach(SRCFILE ${COIN_X3D_FILES})
	set(COIN_DOCUMENTATION_FILES ${COIN_DOCUMENTATION_FILES} ${PROJECT_SOURCE_DIR}/src/x3d/${SRCFILE} CACHE INTERNAL "COIN_DOCUMENTATION_FILES")
endforeach(SRCFILE)
foreach(SRCFILE ${COIN_X3D_INTERNAL_FILES})
	set(COIN_INTERNAL_DOCUMENTATION_FILES ${COIN_INTERNAL_DOCUMENTATION_FILES} ${PROJECT_SOURCE_DIR}/src/x3d/${SRCFILE} CACHE INTERNAL "COIN_INTERNAL_DOCUMENTATION_FILES")
endforeach(SRCFILE)
