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

#ifndef COIN_SOROTATESPHERICALDRAGGER_H
#define COIN_SOROTATESPHERICALDRAGGER_H

#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/SbMatrix.h>
#include <Inventor/SbVec3f.h>

class SoSensor;
class SoFieldSensor;
class SbSphereProjector;


class SoRotateSphericalDragger : public SoDragger {
  typedef SoDragger inherited;

  SO_KIT_HEADER(SoRotateSphericalDragger);

  SO_KIT_CATALOG_ENTRY_HEADER(feedback);
  SO_KIT_CATALOG_ENTRY_HEADER(feedbackActive);
  SO_KIT_CATALOG_ENTRY_HEADER(feedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator);
  SO_KIT_CATALOG_ENTRY_HEADER(rotatorActive);
  SO_KIT_CATALOG_ENTRY_HEADER(rotatorSwitch);


public:
  static void initClass(void);
  SoRotateSphericalDragger(void);

  SoSFRotation rotation;

  void setProjector(SbSphereProjector * p);
  const SbSphereProjector * getProjector(void) const;

protected:
  ~SoRotateSphericalDragger();
  virtual SbBool setUpConnections(SbBool onoff, SbBool doitalways = FALSE);

  virtual void copyContents(const SoFieldContainer * fromfc,
                            SbBool copyconnections);

  static void startCB(void * f, SoDragger * d);
  static void motionCB(void * f, SoDragger * d);
  static void doneCB(void * f, SoDragger * d);
  static void fieldSensorCB(void * f, SoSensor * s);
  static void valueChangedCB(void * f, SoDragger * d);

  void dragStart(void);
  void drag(void);
  void dragFinish(void);

  SoFieldSensor * fieldSensor;
  SbMatrix prevMotionMatrix;
  SbVec3f prevWorldHitPt;
  SbSphereProjector * sphereProj;
  SbBool userProj;
};

#endif // !COIN_SOROTATESPHERICALDRAGGER_H
