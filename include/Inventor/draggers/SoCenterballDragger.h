/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion.  All rights reserved.
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use Coin with software that is incompatible
 *  licensewise with the GPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef COIN_SOCENTERBALLDRAGGER_H
#define COIN_SOCENTERBALLDRAGGER_H

#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>

class SoSensor;
class SoFieldSensor;


class COIN_DLL_API SoCenterballDragger : public SoDragger {
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
  void setSwitches(SoDragger * activechild);
  virtual SbBool setUpConnections(SbBool onoff, SbBool doitalways = FALSE);
  virtual void setDefaultOnNonWritingFields(void);

  static void fieldSensorCB(void * f, SoSensor * s);
  static void valueChangedCB(void * f, SoDragger * d);
  static void kidStartCB(void * f, SoDragger * d);
  static void kidFinishCB(void * f, SoDragger * d);

  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void getMatrix(SoGetMatrixAction * action);

  SoFieldSensor * rotFieldSensor;
  SoFieldSensor * centerFieldSensor;

private:
  SbVec3f savedtransl;
  SbVec3f savedcenter;
  void addChildDragger(SoDragger *child);
  void removeChildDragger(const char *childname);
};

#endif // !COIN_SOCENTERBALLDRAGGER_H
