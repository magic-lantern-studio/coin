/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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

#ifndef __SOSFINT32_H__
#define __SOSFINT32_H__

#include <Inventor/fields/SoSField.h>
#include <Inventor/fields/SoSubField.h>


class SoSFInt32 : public SoSField {
  typedef SoSField inherited;

  SO_SFIELD_HEADER(SoSFInt32, int32_t, const int32_t);

public:
  static void initClass(void);

private:
  virtual void convertTo(SoField * dest) const;

  friend class SoMFInt32; // For readValue() & writeValue().
};

#endif // !__SOSFINT32_H__
