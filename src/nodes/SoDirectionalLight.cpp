/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

/*!
  \class SoDirectionalLight SoDirectionalLight.h Inventor/nodes/SoDirectionalLight.h
  \brief The SoDirectionalLight class is a node type for specifying directional light sources.
  \ingroup nodes

  A directional light source provides a model of light sources which
  are at infinite distance from the geometry it illuminates, thereby
  having no set position and consisting of an infinite volume of
  parallel rays.

  This is of course a simplified model of far-away light sources, as
  "infinite distance" is impossible.

  The sun shining on objects on earth is a good example of something
  which can be modeled rather well for the most common purposes with a
  directional light source.

  See also documentation of parent class for important information
  regarding light sources in general.
*/

#include <Inventor/nodes/SoDirectionalLight.h>

#include <Inventor/SbColor4f.h>
#include <Inventor/SbVec4f.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoEnvironmentElement.h>
#include <Inventor/elements/SoGLLightIdElement.h>

#ifdef _WIN32
#include <windows.h> // Needed for stuff that GL/gl.h depends on.
#endif // _WIN32
#include <GL/gl.h>

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

/*!
  \var SoSFVec3f SoDirectionalLight::direction

  The direction of the light source. Defaults to pointing along the
  negative z-axis.
*/


// *************************************************************************

SO_NODE_SOURCE(SoDirectionalLight);

/*!
  Constructor.
*/
SoDirectionalLight::SoDirectionalLight(void)
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoDirectionalLight);

  SO_NODE_ADD_FIELD(direction, (0.0f, 0.0f, -1.0f));
}

/*!
  Destructor.
*/
SoDirectionalLight::~SoDirectionalLight()
{
}

// Doc from superclass.
void
SoDirectionalLight::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoDirectionalLight);
}

// Doc from superclass.
void
SoDirectionalLight::GLRender(SoGLRenderAction * action)
{
  if (!this->on.getValue()) return;

  SoState * state = action->getState();
  int idx = SoGLLightIdElement::increment(state);

  if (idx < 0) {
#if COIN_DEBUG
    SoDebugError::postWarning("SoDirectionalLight::GLRender",
                              "Max # of OpenGL lights exceeded :(");
#endif // COIN_DEBUG
    return;
  }

  GLenum light = (GLenum) (idx + GL_LIGHT0);

  SbColor4f lightcolor(0.0f, 0.0f, 0.0f, 1.0f);
  lightcolor.setRGB(this->color.getValue());
  lightcolor *= this->intensity.getValue();
  
  glLightfv(light, GL_DIFFUSE, lightcolor.getValue());
  glLightfv(light, GL_SPECULAR, lightcolor.getValue());

  // GL directional light is specified towards light source
  SbVec3f dir = - this->direction.getValue();
  dir.normalize();

  // directional when w = 0.0
  SbVec4f dirvec(dir[0], dir[1], dir[2], 0.0f);
  glLightfv(light, GL_POSITION, dirvec.getValue());

  // FIXME: is this needed for directional lights?
  // turn off spot light properties for ordinary lights
  glLightf(light, GL_SPOT_EXPONENT, 0.0);
  glLightf(light, GL_SPOT_CUTOFF, 180.0);
  glLightf(light, GL_CONSTANT_ATTENUATION, 1);
  glLightf(light, GL_LINEAR_ATTENUATION, 0);
  glLightf(light, GL_QUADRATIC_ATTENUATION, 0);
}
