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

/*!
  \class SoSwitchElement Inventor/elements/SoSwitchElement.h
  \brief The SoSwitchElement class is yet to be documented.
  \ingroup elements

  FIXME: write doc.
*/

#include <Inventor/elements/SoSwitchElement.h>


#include <assert.h>

SO_ELEMENT_SOURCE(SoSwitchElement);

/*!
  This static method initializes static data for the SoSwitchElement class.
*/

void
SoSwitchElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoSwitchElement, inherited);
}

/*!
  The destructor.
*/

SoSwitchElement::~SoSwitchElement(void)
{
}

//! FIXME: write doc.

void
SoSwitchElement::set(SoState * const state,
                     SoNode * const node,
                     const int32_t index)
{
  SoInt32Element::set(classStackIndex, state, node, index);
}

//! FIXME: write doc.

void
SoSwitchElement::init(SoState * state)
{
  inherited::init(state);
  this->data = getDefault();
}

//! FIXME: write doc.

//$ EXPORT INLINE
void
SoSwitchElement::set(SoState * const state, const int32_t index)
{
  set(state, NULL, index);
}

//! FIXME: write doc.

//$ EXPORT INLINE
int32_t
SoSwitchElement::get(SoState * const state)
{
  return SoInt32Element::get(classStackIndex, state);
}

//! FIXME: write doc.

//$ EXPORT INLINE
int32_t
SoSwitchElement::getDefault()
{
  return -1;
}
