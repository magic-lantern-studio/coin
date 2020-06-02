#ifndef COIN_SOTRANSFORMER2DRAGGER_H
#define COIN_SOTRANSFORMER2DRAGGER_H

#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/lists/SoNodeList.h>

class SoSensor;
class SoFieldSensor;
class SoSurroundScale;


class COIN_DLL_API SoTransformer2Dragger : public SoDragger {
  typedef SoDragger inherited;

  SO_KIT_HEADER(SoTransformer2Dragger);

  // No construction aid

  SO_KIT_CATALOG_ENTRY_HEADER(overallStyle);

  SO_KIT_CATALOG_ENTRY_HEADER(rotator1);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator1Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator1LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator1Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator2Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator3Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator4);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator4Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator4LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator4Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator5);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator5Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator5LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator5Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator6);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator6Active);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator6LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(rotator6Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(rotatorSep);

  SO_KIT_CATALOG_ENTRY_HEADER(translateToCenter);

  // circular feeback
  SO_KIT_CATALOG_ENTRY_HEADER(circleFeedbackAntiSquish);
  SO_KIT_CATALOG_ENTRY_HEADER(circleFeedbackSep);
  SO_KIT_CATALOG_ENTRY_HEADER(circleFeedbackTransform);
  SO_KIT_CATALOG_ENTRY_HEADER(circleFeedbackTransformSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(xCircleFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(xCircleFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(yCircleFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(yCircleFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(zCircleFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(zCircleFeedbackSwitch);

  // For making the dragger surround what lies above it.
  SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);

  SO_KIT_CATALOG_ENTRY_HEADER(translator1);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator1Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator2Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator3Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator4Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator5Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6Active);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(translator6Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(translatorSep);

  SO_KIT_CATALOG_ENTRY_HEADER(scale1);
  SO_KIT_CATALOG_ENTRY_HEADER(scale1Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale1LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale1Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale2);
  SO_KIT_CATALOG_ENTRY_HEADER(scale2Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale2LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale2Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale3);
  SO_KIT_CATALOG_ENTRY_HEADER(scale3Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale3LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale3Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale4);
  SO_KIT_CATALOG_ENTRY_HEADER(scale4Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale4LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale4Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale5);
  SO_KIT_CATALOG_ENTRY_HEADER(scale5Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale5LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale5Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale6);
  SO_KIT_CATALOG_ENTRY_HEADER(scale6Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale6LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale6Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale7);
  SO_KIT_CATALOG_ENTRY_HEADER(scale7Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale7LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale7Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scale8);
  SO_KIT_CATALOG_ENTRY_HEADER(scale8Active);
  SO_KIT_CATALOG_ENTRY_HEADER(scale8LocateGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(scale8Switch);
  SO_KIT_CATALOG_ENTRY_HEADER(scaleSep);

  SO_KIT_CATALOG_ENTRY_HEADER(axisFeedbackLocation);
  SO_KIT_CATALOG_ENTRY_HEADER(axisFeedbackSep);
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisFeedbackActive);
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisFeedbackSelect);
  SO_KIT_CATALOG_ENTRY_HEADER(xAxisFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(xCrosshairFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisFeedbackActive);
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisFeedbackSelect);
  SO_KIT_CATALOG_ENTRY_HEADER(yAxisFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(yCrosshairFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(zAxisFeedbackActive);
  SO_KIT_CATALOG_ENTRY_HEADER(zAxisFeedbackSelect);
  SO_KIT_CATALOG_ENTRY_HEADER(zAxisFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(zCrosshairFeedback);

  SO_KIT_CATALOG_ENTRY_HEADER(translateBoxFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(translateBoxFeedbackRotation);
  SO_KIT_CATALOG_ENTRY_HEADER(translateBoxFeedbackSep);
  SO_KIT_CATALOG_ENTRY_HEADER(translateBoxFeedbackSwitch);

  SO_KIT_CATALOG_ENTRY_HEADER(scaleBoxFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(scaleBoxFeedbackSwitch);

  SO_KIT_CATALOG_ENTRY_HEADER(posXRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posXWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posXWallFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(posYRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posYWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posYWallFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(posZRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posZWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(posZWallFeedbackSwitch);

  SO_KIT_CATALOG_ENTRY_HEADER(negXRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negXWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negXWallFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(negYRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negYWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negYWallFeedbackSwitch);
  SO_KIT_CATALOG_ENTRY_HEADER(negZRoundWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negZWallFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(negZWallFeedbackSwitch);

  SO_KIT_CATALOG_ENTRY_HEADER(radialFeedback);
  SO_KIT_CATALOG_ENTRY_HEADER(radialFeedbackSwitch);

public:
  static void initClass(void);
  SoTransformer2Dragger(void);

  SoSFRotation rotation;
  SoSFVec3f translation;
  SoSFVec3f scaleFactor;
  SoSFVec3f center;
  SoSFFloat minDiscRotDot;

  enum State {
    INACTIVE,

    RIT_X_ROTATE,
    TOP_Y_ROTATE,
    FNT_Z_ROTATE,
    LFT_X_ROTATE,
    BOT_Y_ROTATE,
    BAK_Z_ROTATE,

    PX_PY_PZ_3D_SCALE,
    PX_PY_NZ_3D_SCALE,
    PX_NY_PZ_3D_SCALE,
    PX_NY_NZ_3D_SCALE,
    NX_PY_PZ_3D_SCALE,
    NX_PY_NZ_3D_SCALE,
    NX_NY_PZ_3D_SCALE,
    NX_NY_NZ_3D_SCALE,

    RIT_TRANSLATE,
    TOP_TRANSLATE,
    FNT_TRANSLATE,
    LFT_TRANSLATE,
    BOT_TRANSLATE,
    BAK_TRANSLATE
  };

  State getCurrentState(void);

  void unsquishKnobs(void);

  SbBool isLocateHighlighting(void);
  void setLocateHighlighting(SbBool onoff);

  static void setColinearThreshold(int newval);
  static int getColinearThreshold(void);

  SbVec3f getBoxPointInWorldSpace(const SbVec3f & pointonunitbox);
  SbVec3f getBoxDirInWorldSpace(const SbVec3f & dironunitbox);
  SbVec3f getWorldPointInBoxSpace(const SbVec3f & pointinworldspace);
  SbVec2f getWorldPointInPixelSpace(const SbVec3f & thepoint);

  SbVec3f getInteractiveCenterInBoxSpace(void);

  // This recalculates the translation value of the 'translateToCenter' 
  // node.   
  void recalcTranslateToCenter();
  SbVec3f getCenterInBoxSpace();
  void saveStartParameters();

protected:
  ~SoTransformer2Dragger();
  virtual SbBool setUpConnections(SbBool onoff, SbBool doitalways = FALSE);
  virtual void setDefaultOnNonWritingFields(void);

  void setSwitchValue(SoNode *node, const int which);

  static void startCB(void * f, SoDragger * d);
  static void motionCB(void * f, SoDragger * d);
  static void finishCB(void * f, SoDragger * d);
  static void metaKeyChangeCB(void *, SoDragger *);
  static void fieldSensorCB(void * f, SoSensor * s);
  static void valueChangedCB(void * f, SoDragger * d);
  // Callback to invoke recalcTranslateToCenter when the surroundScale
  // changes
  static void surroundScaleChangeCB( void *, SoSurroundScale * );

  void dragStart(void);
  void drag(void);
  void dragFinish(void);

  void updateAntiSquishList(void);
  void setAllPartSwitches(int scalewhich, int rotatewhich, int translatewhich);
  int getMouseGestureDirection(SbBool x_ok, SbBool y_ok, SbBool z_ok);
  static int getIgnoreAxis(SbVec2f axis[3][2],
                           SbBool x_ok, SbBool y_ok, SbBool z_ok);
  static void makeMinorAxisPerpendicularIfColinear(SbVec2f origin, SbVec2f axisends[3][2], int index_a, int index_b);
  static SbBool isColinear(SbVec2f a1[2], SbVec2f a2[2], int pixels);

  SoFieldSensor * translFieldSensor;
  SoFieldSensor * scaleFieldSensor;
  SoFieldSensor * rotateFieldSensor;
  SoFieldSensor * centerFieldSensor;
  SoNodeList antiSquishList;

private:
  void getSurroundScaleMatrices(SbMatrix &matrix, SbMatrix &inv);
  SoNode *getNodeFieldNode(const char *fieldname);

  void build_catalog1(void);
  void build_catalog2(void);
  void build_catalog3(void);
  void build_catalog4(void);
  void build_catalog5(void);
  void build_catalog6(void);

  SbMatrix getWorkingToWorldMatrix(void);
  SbMatrix getWorldToWorkingMatrix(void);
  SbVec3f localToWorking(const SbVec3f &v);
  SbVec3f workingToLocal(const SbVec3f &v);
  SbVec3f calcCtrlOffset(const SbVec3f &startpt);
  void setSwitchValue(const char *str, const int which);

  SbBool setDynamicTranslatorSwitches(const SoEvent *event);
  SbBool setDynamicRotatorSwitches(const SoEvent *event);
  SbBool setDynamicScaleSwitches(const SoEvent *event);

  void dragTranslate();
  void dragScale();
  void dragRotate();

  class SbPlaneProjector *planeProj;
  class SbLineProjector *lineProj;
  class SbSphereProjector *sphereProj;
  class SbCylinderProjector *cylProj;

  State state;

  // Used to save initial matrix of the 'translateToCenter' part when the
  // center dragger begins to move.
  SbMatrix startCenterMatrix;

  class SoTransformer2DraggerP * pimpl;
  friend class SoTransformer2DraggerP;
};

#endif // !COIN_SOTRANSFORMER2DRAGGER_H
