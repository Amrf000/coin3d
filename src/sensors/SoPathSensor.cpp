/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
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
 *  See <URL:http://www.coin3d.org> for  more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

/*!
  \class SoPathSensor SoPathSensor.h Inventor/sensors/SoPathSensor.h
  \brief The SoPathSensor class detects changes to paths.
  \ingroup sensors

  If you need to know when a path changes (i.e. nodes in the path has
  been removed, or new nodes is added), use this sensor to get a
  notification.

  You can also use this sensor to detect when some node in the path
  is changed.
*/

#define PRIVATE(p) (p)->pimpl

#include <Inventor/sensors/SoPathSensor.h>
#include <Inventor/SoFullPath.h>
#include <Inventor/nodes/SoNode.h>

class SoPathSensorP {
public:
  SoFullPath * path; // to audit path
  SoNode * headnode; // to audit nodes in path
};


/*!
  Default constructor. Use setFunction() to set up a callback function
  later.
*/
SoPathSensor::SoPathSensor(void)
{
  this->commonConstructor();
}

/*!
  Constructor taking as parameters the sensor callback function and
  the userdata which will be passed the callback.

  \sa setFunction(), setData()
 */
SoPathSensor::SoPathSensor(SoSensorCB * func, void * data)
  : inherited(func, data)
{
  this->commonConstructor();
}

void 
SoPathSensor::commonConstructor(void)
{
  PRIVATE(this) = new SoPathSensorP;
  PRIVATE(this)->path = NULL;
  PRIVATE(this)->headnode = NULL;
}


/*!
  Destructor.
*/
SoPathSensor::~SoPathSensor(void)
{
  this->detach();
  delete PRIVATE(this);
}

/*!
  Attach sensor to a path. Whenever the path changes, the sensor will
  be triggered and call the callback function.

  \sa detach()
 */
void
SoPathSensor::attach(SoPath * path)
{
  this->detach();

  PRIVATE(this)->path = (SoFullPath*) path;
  PRIVATE(this)->path->addAuditor(this, SoNotRec::SENSOR);

  PRIVATE(this)->headnode = path->getHead();
  if (PRIVATE(this)->headnode) {
    PRIVATE(this)->headnode->addAuditor(this, SoNotRec::SENSOR);
  }
}

/*!
  Detach sensor from path. As long as an SoPathSensor is detached, it
  will never invoke its callback function.

  \sa attach()
 */
void
SoPathSensor::detach(void)
{
  if (PRIVATE(this)->path) {
    PRIVATE(this)->path->removeAuditor(this, SoNotRec::SENSOR);
    PRIVATE(this)->path = NULL;
  }
  if (PRIVATE(this)->headnode) {
    PRIVATE(this)->headnode->removeAuditor(this, SoNotRec::SENSOR);
    PRIVATE(this)->headnode = NULL;
  }
  // unschedule so that we don't trigger a new callback
  if (this->isScheduled()) this->unschedule();
}

/*!
  Returns a pointer to the path connected to the sensor.

  \sa attach(), detach()
 */
SoPath *
SoPathSensor::getAttachedPath(void) const
{
  return PRIVATE(this)->path;
}

// Doc from superclass.
void
SoPathSensor::notify(SoNotList * l)
{
  SoBase * firstbase = l->getLastRec()->getBase();
  SoBase * lastbase = l->getFirstRec()->getBase();

  if ((lastbase != firstbase) && (lastbase == (SoBase*) PRIVATE(this)->path)) {
    // some node in/off the path was changed, wait for the
    // notification from the head node so that we only do the
    // processing once.
    return;
  }
  // if the path triggered the notification, we should always trigger
  if (firstbase == (SoBase*) (PRIVATE(this)->path)) {
    inherited::notify(l);
  } 
  else {
    // we came here because the root node notified us. For now we
    // always schedule (by calling SoDataSensor::notify()), but this
    // will be fixed soon. pederb, 2002-02-25
    inherited::notify(l);
  }
}

// Doc from superclass.
void
SoPathSensor::dyingReference(void)
{
  // store the attached path, and only detach if the delete callback
  // didn't attach this sensor to a new path.

  SoPath * deadpath = this->getAttachedPath();
  if (deadpath) deadpath->ref

  this->invokeDeleteCallback();
  
  if (this->getAttachedPath() == deadpath) {
    this->detach();
  }
}

#undef PRIVATE
