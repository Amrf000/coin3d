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
  \class SoPickRayElement Inventor/elements/SoPickRayElement.h
  \brief The SoPickRayElement class is yet to be documented.

  FIXME: write doc.
*/

#include <Inventor/elements/SoPickRayElement.h>

#include <Inventor/SbName.h>

#include <assert.h>

/*!
  \fn SoPickRayElement::volume

  FIXME: write doc.
*/

//$ BEGIN TEMPLATE ElementSource( SoPickRayElement )

/*!
  \var SoPickRayElement::classTypeId

  This is the static class type identifier for the
  SoPickRayElement class.
*/

SoType SoPickRayElement::classTypeId = SoType::badType();

/*!
  This method returns the SoType object for the element class of
  the instance.
*/
SoType
SoPickRayElement::getClassTypeId(void)
{
  return SoPickRayElement::classTypeId;
}

/*!
  This static method creates an object instance of the SoPickRayElement class.
*/
void *
SoPickRayElement::createInstance(void)
{
  return (void *) new SoPickRayElement;
}

/*!
  \var SoPickRayElement::classStackIndex

  This is the static state stack index for the
  SoPickRayElement class.
*/
int SoPickRayElement::classStackIndex;

/*!
  This static method returns the state stack index for the SoPickRayElement class.
*/
int
SoPickRayElement::getClassStackIndex(void)
{
  return SoPickRayElement::classStackIndex;
}
//$ END TEMPLATE ElementSource

/*!
  This static method initializes static data for the SoPickRayElement class.
*/

void
SoPickRayElement::initClass( // static
    void )
{
//$ BEGIN TEMPLATE InitElementSource( SoPickRayElement )
  assert(SoPickRayElement::classTypeId == SoType::badType());
  assert(inherited::getClassTypeId() != SoType::badType());

  SoPickRayElement::classTypeId = SoType::createType(
    inherited::getClassTypeId(),
    "SoPickRayElement",
    &SoPickRayElement::createInstance);

  if (inherited::classStackIndex < 0) {
    SoPickRayElement::classStackIndex =
      createStackIndex( SoPickRayElement::classTypeId );
  } else {
    SoPickRayElement::classStackIndex =
      inherited::classStackIndex;
  }
//$ END TEMPLATE InitElementSource
} // initClass()

/*!
  This static method cleans up static data for the SoPickRayElement class.
*/

void
SoPickRayElement::cleanClass( // static
    void )
{
//$ BEGIN TEMPLATE CleanElementSource( SoPickRayElement )
//$ END TEMPLATE CleanElementSource
} // cleanClass()

/*!
  A constructor.  Can't be used directly.

  \sa void * SoPickRayElement::createInstance( void )
*/

SoPickRayElement::SoPickRayElement(
    void )
  : volume()
{
    setTypeId( SoPickRayElement::classTypeId );
    setStackIndex( SoPickRayElement::classStackIndex );
} // SoPickRayElement()

/*!
  The destructor.
*/

SoPickRayElement::~SoPickRayElement( // virtual
    void )
{
} // ~SoPickRayElement()

//! FIXME: write doc.

void
SoPickRayElement::init( // virtual
    SoState * state )
{
    inherited::init( state );
} // init()

//! FIXME: write doc.

SbBool
SoPickRayElement::matches( // virtual
    const SoElement * element ) const
{
  // should always return false; not part of cache consideration 
  return FALSE;
} // matches()

//! FIXME: write doc.

SoElement *
SoPickRayElement::copyMatchInfo() const
{
  assert(getTypeId().canCreateInstance());
  SoPickRayElement *element =
    (SoPickRayElement *)(getTypeId().createInstance());
  // no use copying any data. matches() will always return false.
  return (SoElement*)element;
} // copyMatchInfo()

//! FIXME: write doc.

void
SoPickRayElement::set(SoState * const state,
		      const SbViewVolume & volume)
{
  SoPickRayElement *elem = (SoPickRayElement*)
    SoElement::getElement(state, classStackIndex);
  elem->volume = volume;
} // set()

//! FIXME: write doc.

const SbViewVolume &
SoPickRayElement::get(SoState * const state)
{
  SoPickRayElement *elem = (SoPickRayElement*)
    SoElement::getConstElement(state, classStackIndex);
  return elem->volume;
} // get()

//! FIXME: write doc.

void
SoPickRayElement::print(FILE * file) const
{
  assert(0 && "FIXME: not imlemented");
} // print()

