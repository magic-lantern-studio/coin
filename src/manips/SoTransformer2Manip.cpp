
/*!
  \class SoTransformer2Manip SoTransformer2Manip.h Inventor/manips/SoTransformer2Manip.h
  \brief The SoTransformer2Manip wraps an SoTransformer2Dragger for convenience.
  \ingroup manips

  <center>
  <img src="http://doc.coin3d.org/images/Coin/draggers/transformer.png">
  </center>

  The manipulator class takes care of wrapping up the
  SoTransformer2Dragger in a simple and convenient API for the
  application programmer, making it automatically surround the
  geometry it influences and taking care of the book-keeping routines
  for it's interaction with the relevant fields of an SoTransformation
  node.
*/

#include <Inventor/manips/SoTransformer2Manip.h>
//#include <Inventor/nodes/SoSubNodeP.h>
#include "nodes/SoSubNodeP.h"
#include <Inventor/nodes/SoSurroundScale.h>
#include <Inventor/draggers/SoTransformer2Dragger.h>

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

SO_NODE_SOURCE(SoTransformer2Manip);


// doc in super
void
SoTransformer2Manip::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoTransformer2Manip, SO_FROM_INVENTOR_1);
}

/*!
  Default constructor. Allocates an SoTransformer2Dragger and an
  SoSurroundScale node to surround the geometry within our part of the
  scenegraph.
*/
SoTransformer2Manip::SoTransformer2Manip(void)
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoTransformer2Manip);

  SoTransformer2Dragger *dragger = new SoTransformer2Dragger;
  this->setDragger(dragger);

  SoSurroundScale *ss = (SoSurroundScale*) dragger->getPart("surroundScale", TRUE);
  ss->numNodesUpToContainer = 4;
  ss->numNodesUpToReset = 3;
}

/*!
  Destructor.
*/
SoTransformer2Manip::~SoTransformer2Manip()
{
}

/*!
  Convenience function to use the
  SoTransformer2Dragger::isLocateHighlighting() method of the embedded
  dragger. See documentation of that method.
*/
SbBool
SoTransformer2Manip::isLocateHighlighting(void)
{
  SoDragger *dragger = this->getDragger();
  if (dragger && dragger->isOfType(SoTransformer2Dragger::getClassTypeId())) {
    return ((SoTransformer2Dragger*)dragger)->isLocateHighlighting();
  }
#if COIN_DEBUG
  SoDebugError::postWarning("SoTransformer2Manip::isLocateHighlighting",
                            "Not a valid dragger in manipulator");
#endif // debug
  return FALSE;
}

/*!
  Convenience function to use the
  SoTransformer2Dragger::setLocateHighlighting() method of the embedded
  dragger. See documentation of that method.
*/
void
SoTransformer2Manip::setLocateHighlighting(SbBool onoff)
{
  SoDragger *dragger = this->getDragger();
  if (dragger && dragger->isOfType(SoTransformer2Dragger::getClassTypeId())) {
    ((SoTransformer2Dragger*)dragger)->setLocateHighlighting(onoff);
  }
  else {
#if COIN_DEBUG
    SoDebugError::postWarning("SoTransformer2Manip::setLocateHighlighting",
                              "Not a valid dragger in manipulator");
#endif // debug
  }
}

/*!
  Convenience function to use the SoTransformer2Dragger::unsquishKnobs()
  method of the embedded dragger. See documentation of that method.
*/
void
SoTransformer2Manip::unsquishKnobs(void)
{
  SoDragger *dragger = this->getDragger();
  if (dragger && dragger->isOfType(SoTransformer2Dragger::getClassTypeId())) {
    ((SoTransformer2Dragger*)dragger)->unsquishKnobs();
  }
  else {
#if COIN_DEBUG
    SoDebugError::postWarning("SoTransformer2Manip::setLocateHighlighting",
                              "Not a valid dragger in manipulator");
#endif // debug
  }
}
