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
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

#ifndef __SODATASENSOR_H__
#define __SODATASENSOR_H__

#include <Inventor/sensors/SoDelayQueueSensor.h>
#include <stdlib.h> // for NULL definition

#if defined(COIN_EXCLUDE_SODATASENSOR)
#error "Configuration settings not respected, should not include this file!"
#endif // COIN_EXCLUDE_SODATASENSOR

class SoNode;
class SoField;
class SoPath;
class SoNotList;

class SoDataSensor : public SoDelayQueueSensor {
  typedef SoDelayQueueSensor inherited;

public:
  SoDataSensor(void);
  SoDataSensor(SoSensorCB * func, void * data);
  virtual ~SoDataSensor(void);

  void setDeleteCallback(SoSensorCB * function, void * data = NULL);
  SoNode * getTriggerNode(void) const;
  SoField * getTriggerField(void) const;
  SoPath * getTriggerPath(void) const;
  void setTriggerPathFlag(SbBool flag);
  SbBool getTriggerPathFlag(void) const;

  virtual void notify(SoNotList * list);
  virtual void dyingReference(void) = 0;

protected:
  void invokeDeleteCallback(void);

private:
  SoSensorCB * cbfunc;
  void * cbdata;
  SbBool findpath;
};

#endif // !__SODATASENSOR_H__
