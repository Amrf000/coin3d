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

/*!
  \class SoOneShotSensor SoOneShotSensor.h Inventor/sensors/SoOneShotSensor.h
  \brief The SoOneShotSensor class is a sensor which will trigger once.
  \ingroup sensors

  TODO: doc
 */

#include <Inventor/sensors/SoOneShotSensor.h>
#include <assert.h>

/*!
  Constructor.
 */
SoOneShotSensor::SoOneShotSensor(void)
{
}

/*!
  Constructor taking as parameters the sensor callback function and the
  userdata which will be passed the callback.

  \sa setFunction(), setData()
 */
SoOneShotSensor::SoOneShotSensor(SoSensorCB *func, void *data)
  : inherited(func, data)
{
}

/*!
  Destructor.
*/
SoOneShotSensor::~SoOneShotSensor(void)
{
}
