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
  \class SoMFShort SoMFShort.h Inventor/fields/SoMFShort.h
  \brief The SoMFShort class ...
  \ingroup fields

  FIXME: write class doc
*/

#include <Inventor/fields/SoMFShort.h>
#if !defined(COIN_EXCLUDE_SOSFSHORT)
#include <Inventor/fields/SoSFShort.h>
#endif // !COIN_EXCLUDE_SOSFSHORT
#include <Inventor/SbName.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <assert.h>
#if !defined(COIN_EXCLUDE_SOSFSTRING)
#include <Inventor/fields/SoSFString.h>
#endif // !COIN_EXCLUDE_SOSFSTRING
#include <strstream.h>
#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

// *************************************************************************

//$ BEGIN TEMPLATE MField( SoMFShort, short, short )

SoType SoMFShort::classTypeId = SoType::badType();

/*!
  Virtual method which returns the type identifier for an object.

  \sa getClassTypeId()
*/
SoType
SoMFShort::getTypeId(void) const
{
  return SoMFShort::classTypeId;
}

/*!
  Returns a unique type identifier for the SoMFShort class.

  \sa getTypeId(), SoType
 */
SoType
SoMFShort::getClassTypeId(void)
{
  return SoMFShort::classTypeId;
}

/*!
  Constructs and returns a new instance of the SoMFShort class.
*/
void *
SoMFShort::createInstance(void)
{
  return new SoMFShort;
}
/*!
  Copy all data from \a field into this object. \a field \e must
  be of the same type as the field we are copying into.
*/
void
SoMFShort::copyFrom(const SoField & field)
{
#if 0 // COIN_DEBUG
  // Calling field.getTypeId() here fails when "this" is connected to "field"
  // and "field" is destructed. The error message is "pure virtual method
  // called" with egcs 1.0.2 under Linux.
  if (field.getTypeId() != this->getTypeId()) {
    SoDebugError::postWarning("SoMFShort::copyFrom",
                              "not of the same type: (this) '%s' (from) '%s'",
                              this->getTypeId().getName().getString(),
                              field.getTypeId().getName().getString());
    return;
  }
#endif // COIN_DEBUG

  this->operator=((const SoMFShort &)field);
}

/*!
  Tests \a field against this field for equality. Returns \a FALSE if they
  are not of the same type, or if they do not contain the same data.
*/
SbBool
SoMFShort::isSame(const SoField & field) const
{
  if (field.getTypeId() != this->getTypeId()) return FALSE;
  return this->operator==((const SoMFShort &) field);
}

/*!
  Copy all field values from \a field into this object.
*/
const SoMFShort &
SoMFShort::operator = (const SoMFShort & field)
{
  if (field.getNum() < this->getNum()) this->deleteAllValues();
  this->setValues(0, field.getNum(), field.getValues(0));
  return *this;
}

/*!
  Constructor.
*/
SoMFShort::SoMFShort(void)
{
  this->values = NULL;
}

/*!
  Destructor.
*/
SoMFShort::~SoMFShort(void)
{
  this->deleteAllValues();
}

/*!
  FIXME: write function documentation
*/
int
SoMFShort::fieldSizeof(void) const
{
  return sizeof(short);
}

/*!
  FIXME: write function documentation
*/
void *
SoMFShort::valuesPtr(void)
{
  return (void *)this->values;
}

/*!
  FIXME: write function documentation
*/
void
SoMFShort::setValuesPtr(void * ptr)
{
  this->values = (short *)ptr;
}

/*!
  FIXME: write function documentation
*/
int
SoMFShort::find(short value, SbBool addIfNotFound)
{
  for (int i=0; i < this->num; i++) if (this->values[i] == value) return i;

  if (addIfNotFound) this->set1Value(this->num, value);
  return -1;
}

/*!
  FIXME: write function documentation
*/
void
SoMFShort::setValues(const int start, const int num,
                       const short * newValues)
{
  if (start+num > this->maxNum) this->allocValues(start+num);
  else if (start+num > this->num) this->num = start+num;

  for (int i=0; i < num; i++)
    this->values[i+start] = (short) newValues[i];
  this->valueChanged();
}

/*!
  FIXME: write function documentation
*/
void
SoMFShort::set1Value(const int idx, short value)
{
  if (idx+1 > this->maxNum) this->allocValues(idx+1);
  else if (idx+1 > this->num) this->num = idx+1;
  this->values[idx] = value;
  this->valueChanged();
}

/*!
  FIXME: write function documentation
*/
void
SoMFShort::setValue(short value)
{
  this->allocValues(1);
  this->values[0] = value;
  this->valueChanged();
}

/*!
  FIXME: write function documentation
*/
SbBool
SoMFShort::operator == (const SoMFShort & field) const
{
  if (this == &field) return TRUE;
  if (this->getNum() != field.getNum()) return FALSE;

  const short * const lhs = this->getValues(0);
  const short * const rhs = field.getValues(0);
  for (int i = 0; i < num; i++) if (lhs[i] != rhs[i]) return FALSE;
  return TRUE;
}

/*!
  FIXME: write function documentation
*/
void
SoMFShort::deleteAllValues(void)
{
  this->allocValues(0);
}

/*!
  FIXME: write function documentation
*/
void
SoMFShort::copyValue(int to, int from)
{
  assert(this->values && SbMax(to, from) < num);
  this->values[to] = this->values[from];
  this->valueChanged();
}
//$ END TEMPLATE MField

// *************************************************************************

/*!
  Does initialization common for all objects of the
  SoMFShort class. This includes setting up the
  type system, among other things.
*/
void
SoMFShort::initClass(void)
{
//$ BEGIN TEMPLATE FieldInitClass( MFShort )
  // Make sure we only initialize once.
  assert(SoMFShort::classTypeId == SoType::badType());
  // Make sure superclass has been initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoMFShort::classTypeId =
    SoType::createType(SoMFShort::getClassTypeId(),
                       "MFShort", &SoMFShort::createInstance);
//$ END TEMPLATE FieldInitClass
}

/*!
  Clean out all statically allocated resources.
  This method is only useful for debugging purposes.
*/
void
SoMFShort::cleanClass(void)
{
}

// *************************************************************************

/*!
  FIXME: write function documentation
*/
SbBool
SoMFShort::read1Value(SoInput * in, int index)
{
  return in->read(values[index]);
}

/*!
  FIXME: write function documentation
*/
void
SoMFShort::write1Value(SoOutput * out, int idx) const
{
  out->write(this->values[idx]);
}

/*!
  FIXME: write function documentation
*/
int
SoMFShort::getNumValuesPerLine(void) const
{
  return 8;
}

void
SoMFShort::convertTo(SoField * dest) const
{
  if (0);
#if !defined(COIN_EXCLUDE_SOSFSHORT)
  else if (dest->getTypeId()==SoSFShort::getClassTypeId()) {
    if (this->getNum()>0)
      ((SoSFShort *)dest)->setValue((*this)[0]);
  }
#endif // !COIN_EXCLUDE_SOSFSHORT
#if !defined(COIN_EXCLUDE_SOSFSTRING)
  else if (dest->getTypeId()==SoSFString::getClassTypeId()) {
    const int num=this->getNum();
    ostrstream ostr;
    if (num!=1) ostr << "[ ";
    for (int i=0;i<num;i++) {
      ostr << (*this)[i];
      if (i<num-1) ostr << ", ";
    }
    if (num!=1) ostr << " ]";
    ostr << ends; 
    ((SoSFString *)dest)->setValue(ostr.str());
  }
#endif // !COIN_EXCLUDE_SOSFSTRING
#if COIN_DEBUG
  else {
    SoDebugError::post("SoMFRotation::convertTo",
		       "Can't convert from %s to %s",
		       this->getTypeId().getName().getString(),
		       dest->getTypeId().getName().getString());
  }
#endif // COIN_DEBUG
}
