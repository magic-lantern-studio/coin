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
  \class SoTextureCoordinateFunction SoTextureCoordinateFunction.h Inventor/nodes/SoTextureCoordinateFunction.h
  \brief The SoTextureCoordinateFunction class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/nodes/SoTextureCoordinateFunction.h>



// *************************************************************************

SO_NODE_ABSTRACT_SOURCE(SoTextureCoordinateFunction);

/*!
  Constructor.
*/
SoTextureCoordinateFunction::SoTextureCoordinateFunction()
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoTextureCoordinateFunction);
}

/*!
  Destructor.
*/
SoTextureCoordinateFunction::~SoTextureCoordinateFunction()
{
}

/*!
  Does initialization common for all objects of the
  SoTextureCoordinateFunction class. This includes setting up the
  type system, among other things.
*/
void
SoTextureCoordinateFunction::initClass(void)
{
  SO_NODE_INTERNAL_INIT_ABSTRACT_CLASS(SoTextureCoordinateFunction);
}
