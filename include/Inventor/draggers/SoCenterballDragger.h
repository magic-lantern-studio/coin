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

#ifndef COIN_SOCENTERBALLDRAGGER_H
#define COIN_SOCENTERBALLDRAGGER_H

#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>

class SoSensor;
class SoFieldSensor;


class SoCenterballDragger : public SoDragger {
  typedef SoDragger inherited;

  SO_KIT_HEADER(SoCenterballDragger);

  SO_KIT_CATALOG_ENTRY_HEADER(XAxis);
  SO_KIT_CATALOG_ENTRY_HEADER(XAxisSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(XCenterChanger);
  SO_KIT_CATALOG_ENTRY_HEADER(XRotator);
  SO_KIT_CATALOG_ENTRY_HEADER(YAxis);
  SO_KIT_CATALOG_ENTRY_HEADER(YAxisSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(YCenterChanger);
  SO_KIT_CATALOG_ENTRY_HEADER(YRotator);
  SO_KIT_CATALOG_ENTRY_HEADER(ZAxis);
  SO_KIT_CATALOG_ENTRY_HEADER(ZAxisSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(ZCenterChanger);
  SO_KIT_CATALOG_ENTRY_HEADER(ZRotator);
  SO_KIT_CATALOG_ENTRY_HEADER(antiSquish);
  SO_KIT_CATALOG_ENTRY_HEADER(lightModel);
  SO_KIT_CATALOG_ENTRY_HEADER(rot2X90);
  SO_KIT_CATALOG_ENTRY_HEADER(rotX90);
  SO_KIT_CATALOG_ENTRY_HEADER(rotY90);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator);
  SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);
  SO_KIT_CATALOG_ENTRY_HEADER(translateToCenter);

public:
  static void initClass(void);
  SoCenterballDragger(void);

  virtual void saveStartParameters(void);

  SoSFRotation rotation;
  SoSFVec3f center;

protected:
  ~SoCenterballDragger();
  void transferCenterDraggerMotion(SoDragger * childdragger);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void getMatrix(SoGetMatrixAction * action);
  void setSwitches(SoDragger * activechild);
  virtual SbBool setUpConnections(SbBool onoff, SbBool doitalways = FALSE);
  virtual void setDefaultOnNonWritingFields(void);

  static void fieldSensorCB(void * f, SoSensor * s);
  static void valueChangedCB(void * f, SoDragger * d);
  static void kidStartCB(void * f, SoDragger * d);
  static void kidFinishCB(void * f, SoDragger * d);

  SoFieldSensor * rotFieldSensor;
  SoFieldSensor * centerFieldSensor;
};

#endif // !COIN_SOCENTERBALLDRAGGER_H
