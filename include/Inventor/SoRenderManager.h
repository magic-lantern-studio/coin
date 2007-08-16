#ifndef COIN_SORENDERMANAGER_H
#define COIN_SORENDERMANAGER_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2007 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#include <Inventor/SbColor.h>
#include <Inventor/SbVec2s.h>

class SbViewportRegion;
class SoEvent;
class SoGLRenderAction;
class SoAudioRenderAction;
class SoNode;
class SoCamera;
class SoNodeSensor;
class SoOneShotSensor;
class SoSensor;

typedef void SoRenderManagerRenderCB(void * userdata, class SoRenderManager * mgr);

class COIN_DLL_API Superimposition {
public:
  enum StateFlags {
    AUTOREDRAW   = 0x0000,
    ZBUFFERON    = 0x0001,
    CLEARZBUFFER = 0x0002
  };

  Superimposition(SoNode * scene,
                  SbBool enabled,
                  SoRenderManager * manager,
                  uint32_t flags);
  ~Superimposition();
  
  void render(void);
  void setEnabled(SbBool yes);
  
private:
  static void changeCB(void * data, SoSensor * sensor);
  class SuperimpositionP * pimpl;
};


class COIN_DLL_API SoRenderManager {
public:
  enum RenderMode {
    AS_IS,
    WIREFRAME,
    POINTS,
    WIREFRAME_OVERLAY,
    HIDDEN_LINE,
    BOUNDING_BOX
  };

  enum StereoMode {
    MONO,
    ANAGLYPH,
    QUAD_BUFFER,
    INTERLEAVED_ROWS,
    INTERLEAVED_COLUMNS
  };

  enum BufferType {
    BUFFER_SINGLE,
    BUFFER_DOUBLE
  };

  enum AutoClippingStrategy {
    NO_AUTO_CLIPPING,
    FIXED_NEAR_PLANE,
    VARIABLE_NEAR_PLANE
  };

  SoRenderManager(void);
  virtual ~SoRenderManager();

  virtual void render(const SbBool clearwindow = TRUE,
                      const SbBool clearzbuffer = TRUE);
  
  virtual void render(SoGLRenderAction * action,
                      const SbBool initmatrices = TRUE,
                      const SbBool clearwindow = TRUE,
                      const SbBool clearzbuffer = TRUE);

  Superimposition * addSuperimposition(SoNode * scene, 
                                       SbBool enabled = TRUE, 
                                       uint32_t flags = 
                                       Superimposition::AUTOREDRAW | 
                                       Superimposition::ZBUFFERON  |
                                       Superimposition::CLEARZBUFFER);
  
  void removeSuperimposition(Superimposition * s);

  virtual void setSceneGraph(SoNode * const sceneroot);
  virtual SoNode * getSceneGraph(void) const;

  void setCamera(SoCamera * camera);
  SoCamera * getCamera(void) const;

  void setAutoClipping(AutoClippingStrategy autoclipping);
  void attachRootSensor(SoNode * const sceneroot);
  void attachClipSensor(SoNode * const sceneroot);
  void detachRootSensor(void);
  void detachClipSensor(void);

  AutoClippingStrategy getAutoClipping(void) const;
  void setNearPlaneValue(float value);
  float getNearPlaneValue(void) const;
  void setTexturesEnabled(const SbBool onoff);
  SbBool isTexturesEnabled(void) const;
  void setDoubleBuffer(const SbBool enable);
  SbBool isDoubleBuffer(void) const;
  void setRenderMode(const RenderMode mode);
  RenderMode getRenderMode(void) const;
  void setStereoMode(const StereoMode mode);
  StereoMode getStereoMode(void) const;
  void setStereoOffset(const float offset);
  float getStereoOffset(void) const;

  void setRenderCallback(SoRenderManagerRenderCB * f,
                         void * const userData = NULL);

  SbBool isAutoRedraw(void) const;
  void setRedrawPriority(const uint32_t priority);
  uint32_t getRedrawPriority(void) const;

  static void nodesensorCB(void * data, SoSensor * sensor);
  static void prerendercb(void * userdata, SoGLRenderAction * action);

  void reinitialize(void);
  void scheduleRedraw(void);
  void setWindowSize(const SbVec2s & newsize);
  const SbVec2s & getWindowSize(void) const;
  void setSize(const SbVec2s & newsize);
  const SbVec2s & getSize(void) const;
  void setOrigin(const SbVec2s & newOrigin);
  const SbVec2s & getOrigin(void) const;
  void setViewportRegion(const SbViewportRegion & newRegion);
  const SbViewportRegion & getViewportRegion(void) const;
  void setBackgroundColor(const SbColor & color);
  const SbColor & getBackgroundColor(void) const;
  void setBackgroundIndex(const int index);
  int getBackgroundIndex(void) const;
  void setRGBMode(const SbBool onOrOff);
  SbBool isRGBMode(void) const;
  virtual void activate(void);
  virtual void deactivate(void);

  void setAntialiasing(const SbBool smoothing, const int numPasses);
  void getAntialiasing(SbBool & smoothing, int & numPasses) const;
  void setGLRenderAction(SoGLRenderAction * const action);
  SoGLRenderAction * getGLRenderAction(void) const;
  void setAudioRenderAction(SoAudioRenderAction * const action);
  SoAudioRenderAction * getAudioRenderAction(void) const;

  static void enableRealTimeUpdate(const SbBool flag);
  static SbBool isRealTimeUpdateEnabled(void);
  static uint32_t getDefaultRedrawPriority(void);

protected:
  int isActive(void) const;
  void redraw(void);

  void actuallyRender(SoGLRenderAction * action,
                      const SbBool initmatrices = TRUE,
                      const SbBool clearwindow = TRUE,
                      const SbBool clearzbuffer = TRUE);
  
  void renderSingle(SoGLRenderAction * action,
                    SbBool initmatrices,
                    SbBool clearwindow,
                    SbBool clearzbuffer);
  
  void renderStereo(SoGLRenderAction * action,
                    SbBool initmatrices,
                    SbBool clearwindow,
                    SbBool clearzbuffer);

  void initStencilBufferForInterleavedStereo(void);
  void clearBuffers(SbBool color, SbBool depth);  

private:
  class SoRenderManagerP * pimpl;
  friend class SoRenderManagerP;
  friend class SoSceneManager;
};


#endif // !COIN_SORENDERMANAGER_H