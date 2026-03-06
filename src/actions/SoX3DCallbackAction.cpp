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
  \class SoX3DCallbackAction SoX3DCallbackAction.h Inventor/actions/SoX3DCallbackAction.h
  \brief The SoX3DCallbackAction class invokes callbacks at specific nodes.

  \ingroup coin_actions

  This action has mechanisms for tracking traversal position and
  traversal state.  In combination with the ability to pass geometry
  primitives to callback actions set by the user, this does for
  instance make it rather straightforward to extract the geometry of a
  scene graph.

  You should be able to use this action for most of your "simple"
  traversal needs, instead of cooking up your own code, as the
  SoX3DCallbackAction is rather flexible.

  A common use of this action is to extract geometry of non-primitive
  shapes as triangles.  A full-fledged example that demonstrates this
  on a scene graph with two spheres follows:

  \code
   #include <Inventor/SoDB.h>
   #include <Inventor/SoPrimitiveVertex.h>
   #include <Inventor/actions/SoX3DCallbackAction.h>
   #include <Inventor/nodes/SoCoordinate3.h>
   #include <Inventor/nodes/SoIndexedFaceSet.h>
   #include <Inventor/nodes/SoSeparator.h>
   #include <Inventor/X3Dnodes/SoX3DGeometryNode.h>
   #include <Inventor/nodes/SoSphere.h>
   #include <Inventor/nodes/SoTranslation.h>


   static SoCoordinate3 * coord3 = NULL;
   static SoIndexedFaceSet * ifs = NULL;

   static int coord3idx = 0;


   static void
   triangle_cb(void * userdata, SoX3DCallbackAction * action,
               const SoPrimitiveVertex * v1,
               const SoPrimitiveVertex * v2,
               const SoPrimitiveVertex * v3)
   {
     const SbVec3f vtx[] = { v1->getPoint(), v2->getPoint(), v3->getPoint() };
     const SbMatrix mm = action->getModelMatrix();

     SbVec3f vx[3];
     for (int j=0; j < 3; j++) { mm.multVecMatrix(vtx[j], vx[j]); }

     // (This is sub-optimal -- should scan for the same vertex
     // coordinates already being present in the SoCoordinate3
     // node. We'll get lots of duplicate coordinates from this.)
     coord3->point.setNum(coord3->point.getNum() + 3);
     coord3->point.setValues(coord3idx, 3, vx);

     int32_t indices[] = { coord3idx, coord3idx + 1, coord3idx + 2, -1 };
     coord3idx += 3;

     int oldsize = ifs->coordIndex.getNum();
     ifs->coordIndex.setNum(oldsize + 4);
     ifs->coordIndex.setValues(oldsize, 4, indices);

     // (Note that it would likely be desirable to grab normal vectors,
     // materials and / or texture coordinates in a real-world
     // application. How to do this is not shown by the above code,
     // but it is not much different from the extraction of vertex
     // coordinates.)
   }


   int
   main(void)
   {
     SoDB::init();

     SoSeparator * root = new SoSeparator;
     root->addChild(new SoSphere);
     SoTranslation * trans = new SoTranslation;
     trans->translation.setValue(10, 0, 0);
     root->addChild(trans);
     SoSphere * ss = new SoSphere;
     ss->radius = 3;
     root->addChild(ss);

     root->ref();

     coord3 = new SoCoordinate3;
     coord3->point.setNum(0);
     ifs = new SoIndexedFaceSet;
     ifs->coordIndex.setNum(0);

     SoX3DCallbackAction ca;
     ca.addTriangleCallback(SoX3DGeometryNode::getClassTypeId(), triangle_cb, NULL);
     ca.apply(root);

     root->unref();

     // [the generated SoCoordinate3 and SoIndexedFaceSet nodes would now
     // typically be used in a scene graph in a viewer, or written to disk
     // or something]

     return 0;
   }
  \endcode
*/

/*!
  \typedef void SoX3DTriangleCB(void *userdata, SoX3DCallbackAction *action, const SoPrimitiveVertex *v1, const SoPrimitiveVertex *v2, const SoPrimitiveVertex *v3)
  
  \param userdata is a void pointer to any data the application need to
  know of in the callback function (like for instance a \e this
  pointer).
  \param action the action which invoked the callback
  \param v1 first vertex of the triangle
  \param v2 second vertex of the triangle
  \param v3 third vertex of the triangle

  \sa SoX3DLineSegmentCB, SoX3DPointCB
*/

/*!
  \typedef void SoX3DLineSegmentCB(void *userdata, SoX3DCallbackAction *action, const SoPrimitiveVertex *v1, const SoPrimitiveVertex *v2)
  
  \param userdata is a void pointer to any data the application need to
  know of in the callback function (like for instance a \e this
  pointer).
  \param action the action which invoked the callback
  \param v1 first vertex of the line
  \param v2 second vertex of the line

  \sa setPassCallback() SoX3DPointCB
*/

/*!
  \typedef void SoX3DPointCB(void *userdata, SoX3DCallbackAction *action, const SoPrimitiveVertex *v)
  
  \param userdata is a void pointer to any data the application need to
  know of in the callback function (like for instance a \e this
  pointer).
  \param action the action which invoked the callback
  \param v the vertex of the point

  \sa setPassCallback()
*/


#include <Inventor/actions/SoX3DCallbackAction.h>

#include <Inventor/SoPath.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/elements/SoCreaseAngleElement.h>
#include <Inventor/elements/SoDecimationPercentageElement.h>
#include <Inventor/elements/SoFocalDistanceElement.h>
#include <Inventor/elements/SoFontNameElement.h>
#include <Inventor/elements/SoFontSizeElement.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/elements/SoLightAttenuationElement.h>
#include <Inventor/elements/SoLinePatternElement.h>
#include <Inventor/elements/SoLineWidthElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoNormalElement.h>
#include <Inventor/elements/SoOverrideElement.h>
#include <Inventor/elements/SoPickStyleElement.h>
#include <Inventor/elements/SoPointSizeElement.h>
#include <Inventor/elements/SoProfileCoordinateElement.h>
#include <Inventor/elements/SoProfileElement.h>
#include <Inventor/elements/SoProjectionMatrixElement.h>
#include <Inventor/elements/SoShapeHintsElement.h>
#include <Inventor/elements/SoSwitchElement.h>
#include <Inventor/elements/SoMultiTextureCoordinateElement.h>
#include <Inventor/elements/SoMultiTextureMatrixElement.h>
#include <Inventor/elements/SoTextureOverrideElement.h>
#include <Inventor/elements/SoUnitsElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoCullElement.h>
#include <Inventor/lists/SoEnabledElementsList.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/X3Dnodes/SoX3DGeometryNode.h>
#include <Inventor/SbViewportRegion.h>

#include "actions/SoSubActionP.h"
#include "SbBasicP.h"

#ifndef DOXYGEN_SKIP_THIS

class SoX3DCallbackData { //internal class
public:
  SoX3DCallbackData(void * cbfunc = NULL, void * userdata = NULL)
    : func(cbfunc), data(userdata), next(NULL) {}


  void append(SoX3DCallbackData * newdata) {
    SoX3DCallbackData * cbdata = this;
    while (cbdata->next != NULL) cbdata = cbdata->next;
    cbdata->next = newdata;
  }

  void deleteAll(void) {
    SoX3DCallbackData * cbdata = this;
    SoX3DCallbackData * nextptr;
    while (cbdata) {
      nextptr = cbdata->next;
      delete cbdata;
      cbdata = nextptr;
    }
  }

  SoX3DCallbackAction::Response doNodeCallbacks(SoX3DCallbackAction * action,
                                                const SoNode * node);
  void doTriangleCallbacks(SoX3DCallbackAction * action,
                           const SoPrimitiveVertex * const v1,
                           const SoPrimitiveVertex * const v2,
                           const SoPrimitiveVertex * const v3);

  void doLineSegmentCallbacks(SoX3DCallbackAction * action,
                              const SoPrimitiveVertex * const v1,
                              const SoPrimitiveVertex * const v2);
  void doPointCallbacks(SoX3DCallbackAction * action,
                        const SoPrimitiveVertex * v);

public:
  void * func;
  void * data;
  SoX3DCallbackData * next;
};


SoX3DCallbackAction::Response
SoX3DCallbackData::doNodeCallbacks(SoX3DCallbackAction * action,
                                const SoNode * node)
{
  SoX3DCallbackData * cbdata = this;
  SoX3DCallbackAction::Response response = SoX3DCallbackAction::CONTINUE;
  while (cbdata) {
    assert(cbdata->func != NULL);
    SoX3DCallbackAction::SoX3DCallbackActionCB * cbfunc =
      object_to_function_cast<SoX3DCallbackAction::SoX3DCallbackActionCB *>( cbdata->func);
    SoX3DCallbackAction::Response ret = cbfunc(cbdata->data, action, node);
    if (ret == SoX3DCallbackAction::ABORT) return SoX3DCallbackAction::ABORT;
    if (ret == SoX3DCallbackAction::PRUNE) response = ret;
    cbdata = cbdata->next;
  }
  return response;
}

void
SoX3DCallbackData::doTriangleCallbacks(SoX3DCallbackAction * action,
                                    const SoPrimitiveVertex * const v1,
                                    const SoPrimitiveVertex * const v2,
                                    const SoPrimitiveVertex * const v3)
{
  SoX3DCallbackData * cbdata = this;
  while (cbdata) {
    assert(cbdata->func != NULL);
    SoX3DTriangleCB * tricb = object_to_function_cast<SoX3DTriangleCB *> (cbdata->func);
    tricb(cbdata->data, action, v1, v2, v3);
    cbdata = cbdata->next;
  }
}

void
SoX3DCallbackData::doLineSegmentCallbacks(SoX3DCallbackAction * action,
                                       const SoPrimitiveVertex * const v1,
                                       const SoPrimitiveVertex * const v2)
{
  SoX3DCallbackData * cbdata = this;
  while (cbdata) {
    assert(cbdata->func != NULL);
    SoX3DLineSegmentCB * linecb = object_to_function_cast<SoX3DLineSegmentCB *>( cbdata->func);
    linecb(cbdata->data, action, v1, v2);
    cbdata = cbdata->next;
  }
}

void
SoX3DCallbackData::doPointCallbacks(SoX3DCallbackAction * action,
                                    const SoPrimitiveVertex * v)
{
  SoX3DCallbackData * cbdata = this;
  while (cbdata) {
    assert(cbdata->func != NULL);
    SoX3DPointCB * ptcb = object_to_function_cast<SoX3DPointCB *>( cbdata->func);
    ptcb(cbdata->data, action, v);
    cbdata = cbdata->next;
  }
}

// class to hold private, hidden data
class SoX3DCallbackActionP {
public:
  SbBool viewportset;
  SbViewportRegion viewport;
  SoX3DCallbackAction::Response response;
  SoNode * currentnode;

  SbList <SoX3DCallbackData *> precallback;
  SbList <SoX3DCallbackData *> postcallback;

  SoX3DCallbackData * pretailcallback;
  SoX3DCallbackData * posttailcallback;

  SbList <SoX3DCallbackData *> trianglecallback;
  SbList <SoX3DCallbackData *> linecallback;
  SbList <SoX3DCallbackData *> pointcallback;

  SbBool callbackall;
};

#endif // !DOXYGEN_SKIP_THIS


// ***********************************************************************

/*!
  \typedef Response SoX3DCallbackAction::SoX3DCallbackActionCB(void * userdata, SoX3DCallbackAction * action, const SoNode * node)

  Callback functions need to be of this type. \a node is at the
  current traversal point in the scene graph.
 */

/*!
  \enum SoX3DCallbackAction::Response
  Response values for callback function.
 */
/*!
  \var SoX3DCallbackAction::Response SoX3DCallbackAction::CONTINUE
  Continue traversal as usual.
 */
/*!
  \var SoX3DCallbackAction::Response SoX3DCallbackAction::ABORT
  Abort traversal immediately.  No other callbacks are called after
  this has been returned.
 */
/*!
  \var SoX3DCallbackAction::Response SoX3DCallbackAction::PRUNE
  Don't do traversal of neither the current node (if returning from a
  pre-traversal callback) nor its children.

  If returned from a pre-callback, the post-callbacks will still be
  called.  If returned from a post-callback, the behaviour will be the
  same as for returning CONTINUE.
*/

// ***********************************************************************


SO_ACTION_SOURCE(SoX3DCallbackAction);


/*!
  \copydetails SoAction::initClass(void)
*/
void
SoX3DCallbackAction::initClass(void)
{
  SO_ACTION_INTERNAL_INIT_CLASS(SoX3DCallbackAction, SoAction);

  SO_ENABLE(SoX3DCallbackAction, SoViewportRegionElement);
  SO_ENABLE(SoX3DCallbackAction, SoDecimationTypeElement);
  SO_ENABLE(SoX3DCallbackAction, SoDecimationPercentageElement);
  SO_ENABLE(SoX3DCallbackAction, SoOverrideElement);
  SO_ENABLE(SoX3DCallbackAction, SoTextureOverrideElement);
  SO_ENABLE(SoX3DCallbackAction, SoLazyElement);
  SO_ENABLE(SoX3DCallbackAction, SoCacheElement);

  // view frustum culling is normally not used for this action, but
  // the application programmer can manually add any number of culling
  // planes to optimize callback action traversal. This is used by the
  // SoExtSelection node.
  SO_ENABLE(SoX3DCallbackAction, SoCullElement);
}

#define PRIVATE(obj) ((obj)->pimpl)

/*!
  Default constructor. Will set the viewport to a standard
  viewport with size 640x512.
*/
SoX3DCallbackAction::SoX3DCallbackAction(void)
{
  this->commonConstructor();
}

/*!
  Constructor which lets you specify the viewport.

  This constructor is an extension versus the Open Inventor API.
*/
SoX3DCallbackAction::SoX3DCallbackAction(const SbViewportRegion & vp)
{
  this->commonConstructor();
  PRIVATE(this)->viewport = vp;
  PRIVATE(this)->viewportset = TRUE;
}

void
SoX3DCallbackAction::commonConstructor(void)
{
  SO_ACTION_CONSTRUCTOR(SoX3DCallbackAction);

  PRIVATE(this)->pretailcallback = NULL;
  PRIVATE(this)->posttailcallback = NULL;
  PRIVATE(this)->viewportset = FALSE;
  PRIVATE(this)->callbackall = FALSE;
}

/*!
  Sets the viewport region for this action. When set, the viewport
  element is initialized right before a traversal starts, making it
  the current viewport.

  This method is an extension versus the Open Inventor API.
*/
void
SoX3DCallbackAction::setViewportRegion(const SbViewportRegion & vp)
{
  PRIVATE(this)->viewport = vp;
  PRIVATE(this)->viewportset = TRUE;
}

static void
delete_list_elements(SbList<SoX3DCallbackData *> & cl)
{
  int n = cl.getLength();
  for (int i = 0; i < n; i++) {
    if (cl[i] != NULL) {
      cl[i]->deleteAll();
    }
  }
}

/*!
  Destructor.
*/
SoX3DCallbackAction::~SoX3DCallbackAction()
{
  delete_list_elements(PRIVATE(this)->precallback);
  delete_list_elements(PRIVATE(this)->postcallback);
  delete_list_elements(PRIVATE(this)->trianglecallback);
  delete_list_elements(PRIVATE(this)->linecallback);
  delete_list_elements(PRIVATE(this)->pointcallback);

  if (PRIVATE(this)->pretailcallback) {
    PRIVATE(this)->pretailcallback->deleteAll();
  }
  if (PRIVATE(this)->posttailcallback) {
    PRIVATE(this)->posttailcallback->deleteAll();
  }
}

//
// for setting node callbacks. makes sure NULLs are filled in where not set
//
static void
set_callback_data_idx(SbList<SoX3DCallbackData *> & list, const int idx,
                      void * func, void * data)
{
  int n = list.getLength();
  while (n <= idx) {
    list.append(NULL);
    n++;
  }
  if (list[idx] == NULL) list[idx] = new SoX3DCallbackData(func, data);
  else list[idx]->append(new SoX3DCallbackData(func, data));
}

static void
set_callback_data(SbList<SoX3DCallbackData *> & list, const SoType type,
                  void * func, void * data)
{
  SoTypeList derivedtypes;
  int n = SoType::getAllDerivedFrom(type, derivedtypes);
  for (int i = 0; i < n; i++) {
    set_callback_data_idx(list, static_cast<int>(derivedtypes[i].getData()),
                          func, data);
  }
}

/*!
  Set a function \a cb to call before every node of \a type is
  traversed. \a cb will be called with \a userdata.
 */
void
SoX3DCallbackAction::addPreCallback(const SoType type, SoX3DCallbackActionCB * cb,
                                 void * userdata)
{
  set_callback_data(PRIVATE(this)->precallback, type, function_to_object_cast<void *>(cb), userdata);
}

/*!
  Set a function \a cb to call after every node of \a type has been
  traversed. \a cb will be called with \a userdata.
 */
void
SoX3DCallbackAction::addPostCallback(const SoType type, SoX3DCallbackActionCB * cb,
                                  void * userdata)
{
  set_callback_data(PRIVATE(this)->postcallback, type, function_to_object_cast<void *>(cb), userdata);
}

/*!
  Set a function \a cb to call before the tail of a path is
  traversed. \a cb will be called with \a userdata.
 */
void
SoX3DCallbackAction::addPreTailCallback(SoX3DCallbackActionCB * cb, void * userdata)
{
  if (PRIVATE(this)->pretailcallback == NULL)
    PRIVATE(this)->pretailcallback = new SoX3DCallbackData(function_to_object_cast<void *>(cb), userdata);
  else
    PRIVATE(this)->pretailcallback->append(new SoX3DCallbackData(function_to_object_cast<void *>(cb), userdata));
}

/*!
  Set a function \a cb to call after the tail of a path has been
  traversed. \a cb will be called with \a userdata.
 */
void
SoX3DCallbackAction::addPostTailCallback(SoX3DCallbackActionCB * cb, void * userdata)
{
  if (PRIVATE(this)->posttailcallback == NULL)
    PRIVATE(this)->posttailcallback = new SoX3DCallbackData(function_to_object_cast<void *>(cb), userdata);
  else
    PRIVATE(this)->posttailcallback->append(new SoX3DCallbackData(function_to_object_cast<void *>(cb), userdata));
}

/*!
  Set a function \a cb to call when traversing a node of \a type which
  generates triangle primitives for rendering. \a cb will be called
  with \a userdata.
 */
void
SoX3DCallbackAction::addTriangleCallback(const SoType type,
					 SoX3DTriangleCB * cb,
                                         void * userdata)
{
  set_callback_data(PRIVATE(this)->trianglecallback, type, function_to_object_cast<void *>(cb), userdata);
}

/*!
  Set a function \a cb to call when traversing a node of \a type which
  generates line primitives for rendering. \a cb will be called with
  \a userdata.
 */
void
SoX3DCallbackAction::addLineSegmentCallback(const SoType type,
					    SoX3DLineSegmentCB * cb,
                                            void * userdata)
{
  set_callback_data(PRIVATE(this)->linecallback, type, function_to_object_cast<void *>(cb), userdata);
}

/*!
  Set a function \a cb to call when traversing a node of \a type which
  generates single point primitives for rendering. \a cb will be
  called with \a userdata.
 */
void
SoX3DCallbackAction::addPointCallback(const SoType type, SoX3DPointCB * cb,
                                      void * userdata)
{
  set_callback_data(PRIVATE(this)->pointcallback, type, function_to_object_cast<void *>(cb), userdata);
}

/************************************************************************************/

/*!
  Returns current decimation type setting.
 */
SoDecimationTypeElement::Type
SoX3DCallbackAction::getDecimationType(void) const
{
  return SoDecimationTypeElement::get(this->state);
}

/*!
  Returns current decimation percentage setting.
 */
float
SoX3DCallbackAction::getDecimationPercentage(void) const
{
  return SoDecimationPercentageElement::get(this->state);
}

/*!
  Returns current complexity setting.
 */
float
SoX3DCallbackAction::getComplexity(void) const
{
  return SoComplexityElement::get(this->state);
}

/*!
  Returns current complexity type setting.
*/
SoComplexity::Type
SoX3DCallbackAction::getComplexityType(void) const
{
  return static_cast<SoComplexity::Type>(SoComplexityTypeElement::get(this->state));
}

/*!
  Returns current number of coordinates in the state.
*/
int32_t
SoX3DCallbackAction::getNumCoordinates(void) const
{
  return SoCoordinateElement::getInstance(this->state)->getNum();
}

/*!
  Returns a coordinate triplet from the current state pool of
  coordinates.
*/
const SbVec3f &
SoX3DCallbackAction::getCoordinate3(const int index) const
{
  return SoCoordinateElement::getInstance(this->state)->get3(index);
}

/*!
  Returns a coordinate quadruplet from the current state pool of
  coordinates.
*/
const SbVec4f &
SoX3DCallbackAction::getCoordinate4(const int index) const
{
  return SoCoordinateElement::getInstance(this->state)->get4(index);
}

/*!
  Returns current draw style setting.
*/
SoDrawStyle::Style
SoX3DCallbackAction::getDrawStyle(void) const
{
  return static_cast<SoDrawStyle::Style>(SoDrawStyleElement::get(this->state));
}

/*!
  Returns current line pattern setting.
*/
unsigned short
SoX3DCallbackAction::getLinePattern(void) const
{
  return SoLinePatternElement::get(this->state);
}

/*!
  Returns current line width setting.
*/
float
SoX3DCallbackAction::getLineWidth(void) const
{
  return SoLineWidthElement::get(this->state);
}

/*!
  Returns current point size setting.
*/
float
SoX3DCallbackAction::getPointSize(void) const
{
  return SoPointSizeElement::get(this->state);
}

/*!
  Returns current font name setting.
*/
const SbName &
SoX3DCallbackAction::getFontName(void) const
{
  return SoFontNameElement::get(this->state);
}

/*!
  Returns current font size setting.
*/
float
SoX3DCallbackAction::getFontSize(void) const
{
  return SoFontSizeElement::get(this->state);
}

/*!
  Returns current light model setting.
*/
SoLightModel::Model
SoX3DCallbackAction::getLightModel(void) const
{
  return static_cast<SoLightModel::Model>(SoLazyElement::getLightModel(this->state));
}

/*!
  Returns current light attenuation setting.
*/
const SbVec3f &
SoX3DCallbackAction::getLightAttenuation(void) const
{
  return SoLightAttenuationElement::get(this->state);
}


/*!
  Returns current material settings.
*/
void
SoX3DCallbackAction::getMaterial(SbColor & ambient, SbColor & diffuse,
                              SbColor & specular, SbColor & emission,
                              float & shininess, float & transparency,
                              const int index) const
{
  ambient = SoLazyElement::getAmbient(this->state);
  diffuse = SoLazyElement::getDiffuse(this->state, index);
  emission = SoLazyElement::getEmissive(this->state);
  specular = SoLazyElement::getSpecular(this->state);
  shininess = SoLazyElement::getShininess(this->state);
  transparency = SoLazyElement::getTransparency(this->state, index);
}

/*!
  Returns current material binding setting.
*/
SoMaterialBinding::Binding
SoX3DCallbackAction::getMaterialBinding(void) const
{
  return static_cast<SoMaterialBinding::Binding>(
    SoMaterialBindingElement::get(this->state)
    );
}

/*!
  Returns current number of normals in the state.
*/
uint32_t
SoX3DCallbackAction::getNumNormals(void) const
{
  return SoNormalElement::getInstance(this->state)->getNum();
}

/*!
  Returns the normal vectors at \a index from the current state.
*/
const SbVec3f &
SoX3DCallbackAction::getNormal(const int index) const
{
  return SoNormalElement::getInstance(this->state)->get(index);
}

/*!
  Returns current normal binding setting.
*/
SoNormalBinding::Binding
SoX3DCallbackAction::getNormalBinding(void) const
{
  return static_cast<SoNormalBinding::Binding>(
    SoNormalBindingElement::get(this->state)
    );
}

/*!
  Returns current number of profile coordinates in the state.
*/
int32_t
SoX3DCallbackAction::getNumProfileCoordinates(void) const
{
  return SoProfileCoordinateElement::getInstance(this->state)->getNum();
}

/*!
  Returns current number of SbVec2f profile coordinates in the state.
*/
const SbVec2f &
SoX3DCallbackAction::getProfileCoordinate2(const int index) const
{
  return SoProfileCoordinateElement::getInstance(this->state)->get2(index);
}

/*!
  Returns current number of SbVec3f profile coordinates in the state.
*/
const SbVec3f &
SoX3DCallbackAction::getProfileCoordinate3(const int index) const
{
  return SoProfileCoordinateElement::getInstance(this->state)->get3(index);
}

/*!
  Returns current list of profile nodes.
*/
const SoNodeList &
SoX3DCallbackAction::getProfile(void) const
{
  return SoProfileElement::get(this->state);
}

/*!
  Returns current vertex ordering shape hint setting.

  Please note that this is the vertex ordering set by the SoShapeHints
  node. If you want to find the vertex ordering for X3D nodes you'll
  need to read this directly from the \a ccw field in those
  nodes.
*/
SoShapeHints::VertexOrdering
SoX3DCallbackAction::getVertexOrdering(void) const
{
  return static_cast<SoShapeHints::VertexOrdering>(
    SoShapeHintsElement::getVertexOrdering(this->state)
    );
}

/*!
  Returns current shape type hint setting.

  Please note that this is the shape type set by the SoShapeHints
  node. If you want to find the shape type for VRML nodes you'll
  need to read this directly from the \a solid field in those
  nodes.
*/
SoShapeHints::ShapeType
SoX3DCallbackAction::getShapeType(void) const
{
  return static_cast<SoShapeHints::ShapeType>(
    SoShapeHintsElement::getShapeType(this->state)
    );
}

/*!
  Returns current face type hint setting.

  Please note that this is the face type set by the SoShapeHints
  node. If you want to find the face type for VRML nodes you'll
  need to read this directly from the \a convex field in those
  nodes.

*/
SoShapeHints::FaceType
SoX3DCallbackAction::getFaceType(void) const
{
  return static_cast<SoShapeHints::FaceType>(
    SoShapeHintsElement::getFaceType(this->state)
    );
}

/*!
  Returns current crease angle setting. Please note that this is the
  crease angle value set by the SoShapeHints node. If you want to find
  the crease angle for VRML nodes you'll need to read this directly
  from the creaseAngle field in those nodes.
*/
float
SoX3DCallbackAction::getCreaseAngle(void) const
{
  return SoCreaseAngleElement::get(this->state);
}

/*!
  Returns current number of texture coordinates in the traversal
  state.
*/
int32_t
SoX3DCallbackAction::getNumTextureCoordinates(void) const
{
  return SoMultiTextureCoordinateElement::getInstance(this->state)->getNum(0);
}

/*!
  Returns SbVec2f texture coordinate at \a index from the texture
  coordinate pool of the traversal state.
*/
const SbVec2f &
SoX3DCallbackAction::getTextureCoordinate2(const int index) const
{
  return SoMultiTextureCoordinateElement::getInstance(this->state)->get2(0, index);
}

/*!
  Returns SbVec3f texture coordinate at \a index from the texture
  coordinate pool of the traversal state.

  \COIN_FUNCTION_EXTENSION

  \since Coin 2.0
*/
const SbVec3f &
SoX3DCallbackAction::getTextureCoordinate3(const int index) const
{
  return SoMultiTextureCoordinateElement::getInstance(this->state)->get3(0, index);
}

/*!
  Returns SbVec4f texture coordinate at \a index from the texture
  coordinate pool of the traversal state.
*/
const SbVec4f &
SoX3DCallbackAction::getTextureCoordinate4(const int index) const
{
  return SoMultiTextureCoordinateElement::getInstance(this->state)->get4(0, index);
}

/*!
  Returns current texture coordinate binding setting.
*/
SoTextureCoordinateBinding::Binding
SoX3DCallbackAction::getTextureCoordinateBinding(void) const
{
  return static_cast<SoTextureCoordinateBinding::Binding>(
    SoTextureCoordinateBindingElement::get(this->state)
    );
}

/*!
  Returns current texture blend color setting.
*/
const SbColor &
SoX3DCallbackAction::getTextureBlendColor(void) const
{
  return SoMultiTextureImageElement::getBlendColor(this->state, 0);
}

/*!
  Returns current texture image settings.
*/
const unsigned char *
SoX3DCallbackAction::getTextureImage(SbVec2s & size, int & numcomps) const
{
  return SoMultiTextureImageElement::getImage(state, 0, size, numcomps);
}

/*!
  Returns current 3D texture image settings.

  \COIN_FUNCTION_EXTENSION

  \since Coin 2.0
*/
const unsigned char *
SoX3DCallbackAction::getTextureImage(SbVec3s & size, int & numcomps) const
{
  return SoMultiTextureImageElement::getImage(state, 0, size, numcomps);
}

/*!
  Returns current texture transformation matrix setting.
*/
const SbMatrix &
SoX3DCallbackAction::getTextureMatrix(void) const
{
  return SoMultiTextureMatrixElement::get(this->state, 0);
}

/*!
  Returns current texture mapping model setting.
*/
SoTexture2::Model
SoX3DCallbackAction::getTextureModel(void) const
{
  return static_cast<SoTexture2::Model>( SoMultiTextureImageElement::getModel(this->state, 0));
}

/*!
  Returns current texture wrapping setting for the \c S coordinate.
*/
SoTexture2::Wrap
SoX3DCallbackAction::getTextureWrapS(void) const
{
  return static_cast<SoTexture2::Wrap>( SoMultiTextureImageElement::getWrapS(this->state,0));
}

/*!
  Returns current texture wrapping setting for the \c T coordinate.
*/
SoTexture2::Wrap
SoX3DCallbackAction::getTextureWrapT(void) const
{
  return static_cast<SoTexture2::Wrap>(SoMultiTextureImageElement::getWrapT(this->state, 0));
}

/*!
  Returns current texture wrapping setting for the \c R coordinate.

  \COIN_FUNCTION_EXTENSION

  \since Coin 2.0
*/
SoTexture2::Wrap
SoX3DCallbackAction::getTextureWrapR(void) const
{
  return static_cast<SoTexture2::Wrap>(SoMultiTextureImageElement::getWrapR(this->state, 0));
}

/*!
  Returns current model matrix.
*/
const SbMatrix &
SoX3DCallbackAction::getModelMatrix(void) const
{
  return SoModelMatrixElement::get(this->state);
}

/*!
  Returns current units setting.
*/
SoUnits::Units
SoX3DCallbackAction::getUnits(void) const
{
  return static_cast<SoUnits::Units>(SoUnitsElement::get(this->state));
}

/*!
  Returns current camera focal distance setting.
*/
float
SoX3DCallbackAction::getFocalDistance(void) const
{
  return SoFocalDistanceElement::get(this->state);
}

/*!
  Returns current projection matrix.
*/
const SbMatrix &
SoX3DCallbackAction::getProjectionMatrix(void) const
{
  return SoProjectionMatrixElement::get(this->state);
}

/*!
  Returns current viewing matrix.
*/
const SbMatrix &
SoX3DCallbackAction::getViewingMatrix(void) const
{
  return SoViewingMatrixElement::get(this->state);
}

/*!
  Returns current view volume setting.
*/
const SbViewVolume &
SoX3DCallbackAction::getViewVolume(void) const
{
  return SoViewVolumeElement::get(this->state);
}

/*!
  Returns current viewport region setting.

  This method is an extension versus the Open Inventor API.
*/
const SbViewportRegion &
SoX3DCallbackAction::getViewportRegion(void) const
{
  return SoViewportRegionElement::get(this->getState());
}

/*!
  Returns current pick style setting.
*/
SoPickStyle::Style
SoX3DCallbackAction::getPickStyle(void) const
{
  return static_cast<SoPickStyle::Style>(SoPickStyleElement::get(this->state));
}

/*!
  Returns last SoSwitch::whichChild setting during the traversal.
*/
int32_t
SoX3DCallbackAction::getSwitch(void) const
{
  return SoSwitchElement::get(this->state);
}

/************************************************************************************/

/*!
  \COININTERNAL
 */
SoX3DCallbackAction::Response
SoX3DCallbackAction::getCurrentResponse(void) const
{
  return PRIVATE(this)->response;
}

/*!
  \COININTERNAL

  Invoke all "pre traversal" callbacks.
 */
void
SoX3DCallbackAction::invokePreCallbacks(const SoNode * const node)
{
  // reset response if previous node was pruned
  if (PRIVATE(this)->response == PRUNE) PRIVATE(this)->response = CONTINUE;

  int idx = static_cast<int>(node->getTypeId().getData());

  if (idx < PRIVATE(this)->precallback.getLength() && PRIVATE(this)->precallback[idx] != NULL) {
    PRIVATE(this)->response = PRIVATE(this)->precallback[idx]->doNodeCallbacks(this, node);
    if (PRIVATE(this)->response == SoX3DCallbackAction::ABORT) {
      this->setTerminated(TRUE);
      return;
    }
  }

  if (this->getWhatAppliedTo() == SoAction::PATH &&
      this->getPathAppliedTo()->getTail() == node && PRIVATE(this)->pretailcallback != NULL) {
    PRIVATE(this)->response = PRIVATE(this)->pretailcallback->doNodeCallbacks(this, node);
    if (PRIVATE(this)->response == SoX3DCallbackAction::ABORT) {
      this->setTerminated(TRUE);
      return;
    }
  }
  // FIXME: add code to handle pathlist traversal callbacks
  // pederb, 19991209
}

/*!
  \COININTERNAL

  Invoke all "post traversal" callbacks.
 */
void
SoX3DCallbackAction::invokePostCallbacks(const SoNode * const node)
{
  // reset response if previous node was pruned
  if (PRIVATE(this)->response == PRUNE) PRIVATE(this)->response = CONTINUE;

  int idx = static_cast<int>(node->getTypeId().getData());
  if (idx < PRIVATE(this)->postcallback.getLength() && PRIVATE(this)->postcallback[idx] != NULL) {
    PRIVATE(this)->response = static_cast<Response>(PRIVATE(this)->postcallback[idx]->doNodeCallbacks(this, node));
    if (PRIVATE(this)->response == SoX3DCallbackAction::ABORT) {
      this->setTerminated(TRUE);
      return;
    }
  }

  if (this->getWhatAppliedTo() == SoAction::PATH &&
      this->getPathAppliedTo()->getTail() == node && PRIVATE(this)->posttailcallback) {
    PRIVATE(this)->response = PRIVATE(this)->posttailcallback->doNodeCallbacks(this, node);
    if (PRIVATE(this)->response == SoX3DCallbackAction::ABORT) {
      this->setTerminated(TRUE);
      return;
    }
  }
  // FIXME: add code to handle pathlist traversal callbacks
  // pederb, 19991209
}

/*!
  \COININTERNAL

  Invoke all "triangle generation" callbacks.
 */
void
SoX3DCallbackAction::invokeTriangleCallbacks(const SoX3DGeometryNode * const shape,
                                          const SoPrimitiveVertex * const v1,
                                          const SoPrimitiveVertex * const v2,
                                          const SoPrimitiveVertex * const v3)
{
  int idx = static_cast<int>(shape->getTypeId().getData());
  if (idx < PRIVATE(this)->trianglecallback.getLength() && PRIVATE(this)->trianglecallback[idx] != NULL)
    PRIVATE(this)->trianglecallback[idx]->doTriangleCallbacks(this, v1, v2, v3);
}

/*!
  \COININTERNAL

  Invoke all "line segment generation" callbacks.
 */
void
SoX3DCallbackAction::invokeLineSegmentCallbacks(const SoX3DGeometryNode * const shape,
                                             const SoPrimitiveVertex * const v1,
                                             const SoPrimitiveVertex * const v2)
{
  int idx = static_cast<int>(shape->getTypeId().getData());
  if (idx < PRIVATE(this)->linecallback.getLength() && PRIVATE(this)->linecallback[idx] != NULL)
    PRIVATE(this)->linecallback[idx]->doLineSegmentCallbacks(this, v1, v2);
}

/*!
  \COININTERNAL

  Invoke all "point" callbacks.
 */
void
SoX3DCallbackAction::invokePointCallbacks(const SoX3DGeometryNode * const shape,
                                       const SoPrimitiveVertex * const v)
{
  int idx = static_cast<int>(shape->getTypeId().getData());
  if (idx < PRIVATE(this)->pointcallback.getLength() && PRIVATE(this)->pointcallback[idx] != NULL)
    PRIVATE(this)->pointcallback[idx]->doPointCallbacks(this, v);
}

/*!
  \COININTERNAL

  Check from the shape nodes whether or not to generate primitives
  from the complex shapes. If there are no callbacks attached to the
  node types, making the primitives would only be a waste of CPU.
 */
SbBool
SoX3DCallbackAction::shouldGeneratePrimitives(const SoX3DGeometryNode * shape) const
{
  int idx = static_cast<int>(shape->getTypeId().getData());
  if (idx < PRIVATE(this)->trianglecallback.getLength() && PRIVATE(this)->trianglecallback[idx])
    return TRUE;
  if (idx < PRIVATE(this)->linecallback.getLength() && PRIVATE(this)->linecallback[idx])
    return TRUE;
  if (idx < PRIVATE(this)->pointcallback.getLength() && PRIVATE(this)->pointcallback[idx])
    return TRUE;
  return FALSE;
}

/*!
  Returns the current tail of the traversal path for the callback
  action.
 */
SoNode *
SoX3DCallbackAction::getCurPathTail(void)
{
  return PRIVATE(this)->currentnode;
}

/*!
  Used from nodes during traversal to keep a current node pointer in
  the action.
 */
void
SoX3DCallbackAction::setCurrentNode(SoNode * const node)
{
  PRIVATE(this)->currentnode = node;
}

// Documented in superclass. Overridden from parent class to
// initialize variables which need to be reset for each traversal.
void
SoX3DCallbackAction::beginTraversal(SoNode * node)
{
  PRIVATE(this)->response = SoX3DCallbackAction::CONTINUE;
  // we set the viewport region element here. This element is not enabled
  // for SoX3DCallbackAction in Inventor, bu we think it should be.
  // It makes it possible to calculate screen space stuff in
  // the callback action callbacks.
  if (PRIVATE(this)->viewportset) {
    SoViewportRegionElement::set(this->getState(), PRIVATE(this)->viewport);
  }
  this->traverse(node);
}

void SoX3DCallbackAction::setCallbackAll(SbBool callbackall)
{
  PRIVATE(this)->callbackall = callbackall;
}

SbBool SoX3DCallbackAction::isCallbackAll(void) const
{
  return PRIVATE(this)->callbackall;
}

#undef PRIVATE

#ifdef COIN_TEST_SUITE

#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoCube.h>

static SoX3DCallbackAction::Response
preCB(void * userdata, SoX3DCallbackAction *, const SoNode * node)
{
  SbString *str = (SbString *)userdata;
  (*str) += node->getName();
  return SoX3DCallbackAction::CONTINUE;
}

BOOST_AUTO_TEST_CASE(callbackall)
{
  SbString str;
  SoSwitch * sw = new SoSwitch;
  sw->setName("switch");
  SoCube * cube = new SoCube;
  cube->setName("cube"); 
  sw->addChild(cube);
  sw->ref();

  SoX3DCallbackAction cba;
  cba.addPreCallback(SoNode::getClassTypeId(), preCB, &str);
  cba.apply(sw);
  BOOST_CHECK_MESSAGE(str == "switch", "Should not traverse under switch node");

  str = "";
  cba.setCallbackAll(true);
  cba.apply(sw);
  BOOST_CHECK_MESSAGE(str == "switchcube", "Should traverse under switch node");

  sw->unref();
}

#endif // COIN_TEST_SUITE
