/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2000 by Systems in Motion. All rights reserved.
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
  \class SoAmbientColorElement Inventor/elements/SoAmbientColorElement.h
  \brief The SoAmbientColorElement class is yet to be documented.
*/

#include <Inventor/elements/SoAmbientColorElement.h>
#include <Inventor/SbColor.h>
#include <assert.h>

// Dynamically allocated to avoid problems on systems which doesn't
// handle static constructors.
static SbColor * defaultambientcolor = NULL;


/*!
  \fn SoAmbientColorElement::numColors

  This is the number of ambient colors.
*/

/*!
  \fn SoAmbientColorElement::colors

  This is an array of ambient colors.
*/

SO_ELEMENT_SOURCE(SoAmbientColorElement);

/*!
  This static method initializes static data for the
  SoAmbientColorElement class.
*/

void
SoAmbientColorElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoAmbientColorElement, inherited);
  defaultambientcolor = new SbColor; // FIXME: deallocate on exit. 20000406 mortene.
  defaultambientcolor->setValue(0.2f, 0.2f, 0.2f);
}

//! FIXME: write doc.

void
SoAmbientColorElement::init(SoState * /* state */)
{
  this->colors = defaultambientcolor;
  this->numColors = 1;
}

/*!
  The destructor.
*/

SoAmbientColorElement::~SoAmbientColorElement()
{
}

//! FIXME: write doc.

void
SoAmbientColorElement::set(SoState * const state, SoNode * const node,
                           const int32_t numColors,
                           const SbColor * const colors)
{
  SoAmbientColorElement *elem = (SoAmbientColorElement*)
    SoReplacedElement::getElement(state, classStackIndex, node);
  if (numColors > 0)
    elem->setElt(numColors, colors);
  else
    elem->setElt(1, defaultambientcolor);
}

//! FIXME: write doc.

void
SoAmbientColorElement::setElt(const int32_t numColors,
                              const SbColor * const colors)
{
  this->colors = colors;
  this->numColors = numColors;
}

//! FIXME: write doc.

//$ EXPORT INLINE
int32_t
SoAmbientColorElement::getNum() const
{
  return this->numColors;
}

//! FIXME: write doc.

const SbColor &
SoAmbientColorElement::get(const int index) const
{
  assert(index >= 0 && index <= this->numColors);
  return this->colors[index];
}

/*!
  Return a pointer to the color array. This method is not part of the OIV API.
*/
const SbColor *
SoAmbientColorElement::getArrayPtr() const
{
  return this->colors;
}

//! FIXME: write doc.

//$ EXPORT INLINE
const SoAmbientColorElement *
SoAmbientColorElement::getInstance(SoState *state)
{
  return (const SoAmbientColorElement *)
    SoElement::getConstElement(state, classStackIndex);
}
