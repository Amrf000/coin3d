/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation. See the
 *  file LICENSE.LGPL at the root directory of the distribution for
 *  more details.
 *
 *  If you want to use Coin for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition license.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
\**************************************************************************/

/*!
  \class SoMFRotation SoMFRotation.h Inventor/fields/SoMFRotation.h
  \brief The SoMFRotation class is a container for SbRotation values.
  \ingroup fields

  This field is used where nodes, engines or other field containers
  needs to store multiple rotation definitions.

  \sa SoSFRotation

*/

#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoSubFieldP.h>
#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG


SO_MFIELD_SOURCE(SoMFRotation, SbRotation, const SbRotation &);


// Override parent class.
void
SoMFRotation::initClass(void)
{
  SO_MFIELD_INTERNAL_INIT_CLASS(SoMFRotation);
}

// No need to document readValue() and writeValue() here, as the
// necessary information is provided by the documentation of the
// parent classes.
#ifndef DOXYGEN_SKIP_THIS

// These are implemented in the SoSFRotation class.
extern SbBool sosfrotation_read_value(SoInput * in, SbRotation & val);
extern void sosfrotation_write_value(SoOutput * out, const SbRotation & val);

SbBool
SoMFRotation::read1Value(SoInput * in, int idx)
{
  SbRotation r;
  if (!sosfrotation_read_value(in, r)) return FALSE;
  this->set1Value(idx, r);
  return TRUE;
}

void
SoMFRotation::write1Value(SoOutput * out, int idx) const
{
  sosfrotation_write_value(out, (*this)[idx]);
}

#endif // DOXYGEN_SKIP_THIS


/*!
  Set the values of \a num rotations, starting from index \a start,
  using the quaternion quadruples from \a q.
*/
void
SoMFRotation::setValues(const int start, const int num, const float q[][4])
{
  if(start+num > this->maxNum) this->allocValues(start+num);
  else if(start+num > this->num) this->num = start+num;

  for(int i=0; i < num; i++) this->values[i+start].setValue(q[i]);
  this->valueChanged();
}

/*!
  Set the rotation at \a idx from the quaternion values.
*/
void
SoMFRotation::set1Value(const int idx, const float q0, const float q1,
                        const float q2, const float q3)
{
  this->set1Value(idx, SbRotation(q0, q1, q2, q3));
}

/*!
  Set the rotation at \a idx from the quaternion quadruple \a q.
*/
void
SoMFRotation::set1Value(const int idx, const float q[4])
{
  this->set1Value(idx, SbRotation(q));
}

/*!
  Set the rotation at \a idx from the rotation \a axis and \a angle.
*/
void
SoMFRotation::set1Value(const int idx, const SbVec3f & axis, const float angle)
{
  this->set1Value(idx, SbRotation(axis, angle));
}

/*!
  Set the field to a single rotation from the quaternion values.
*/
void
SoMFRotation::setValue(const float q0, const float q1,
                       const float q2, const float q3)
{
  this->setValue(SbRotation(q0, q1, q2, q3));
}

/*!
  Set the field to a single rotation from the quaternion quadruple \a q.
*/
void
SoMFRotation::setValue(const float q[4])
{
  this->setValue(SbRotation(q[0], q[1], q[2], q[3]));
}

/*!
  Set the field to a single rotation from the \a axis and \a angle.
*/
void
SoMFRotation::setValue(const SbVec3f & axis, const float angle)
{
  this->setValue(SbRotation(axis, angle));
}
