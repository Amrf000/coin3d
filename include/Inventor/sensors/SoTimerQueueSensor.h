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

#ifndef COIN_SOTIMERQUEUESENSOR_H
#define COIN_SOTIMERQUEUESENSOR_H

#include <Inventor/sensors/SoSensor.h>
#include <Inventor/SbTime.h>


class COIN_DLL_EXPORT SoTimerQueueSensor : public SoSensor {
  typedef SoSensor inherited;

public:
  SoTimerQueueSensor(void);
  SoTimerQueueSensor(SoSensorCB * func, void * data);
  virtual ~SoTimerQueueSensor(void);

  const SbTime & getTriggerTime(void) const;
  virtual void schedule(void);
  virtual void unschedule(void);
  virtual SbBool isScheduled(void) const;

protected:
  void setTriggerTime(const SbTime & time);
  SbBool scheduled;

private:
  virtual SbBool isBefore(const SoSensor * s) const;
  SbTime triggertime;
};

#endif // !COIN_SOTIMERQUEUESENSOR_H
