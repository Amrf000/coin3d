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
  \class SoMultiTextureEnabledElement Inventor/elements/SoMultiTextureEnabledElement.h
  \brief The SoMultiTextureEnabledElement class is an element which stores whether texturing is enabled or not.
  \ingroup elements

  \COIN_CLASS_EXTENSION

  \sa SoMultiTexture3EnabledElement
  \since Coin 2.0
*/


#include <Inventor/elements/SoMultiTextureEnabledElement.h>

#define MAX_UNITS 16

class SoMultiTextureEnabledElementP {
public:
  SbBool enabled[MAX_UNITS];
};

#define PRIVATE(obj) obj->pimpl

SO_ELEMENT_CUSTOM_CONSTRUCTOR_SOURCE(SoMultiTextureEnabledElement);

// doc from parent
void
SoMultiTextureEnabledElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoMultiTextureEnabledElement, inherited);
}

/*!
  The constructor.
*/
SoMultiTextureEnabledElement::SoMultiTextureEnabledElement(void)
{
  PRIVATE(this) = new SoMultiTextureEnabledElementP;

  this->setTypeId(SoMultiTextureEnabledElement::classTypeId);
  this->setStackIndex(SoMultiTextureEnabledElement::classStackIndex);
}

/*!
  The destructor.
*/
SoMultiTextureEnabledElement::~SoMultiTextureEnabledElement(void)
{
  delete PRIVATE(this);
}

/*!
  Sets the state of this element.
*/
void
SoMultiTextureEnabledElement::set(SoState * const state,
                                  SoNode * const node,
                                  const int unit,
                                  const SbBool enabled)
{
  SoMultiTextureEnabledElement * elem = (SoMultiTextureEnabledElement *)
    state->getElement(classStackIndex);
  
  elem->setElt(unit, enabled);
}


// doc from parent
void
SoMultiTextureEnabledElement::init(SoState * state)
{
  for (int i = 0; i < MAX_UNITS; i++) {
    PRIVATE(this)->enabled[i] = FALSE;
  }
}

/*!
  Return current state of this element.
*/
SbBool
SoMultiTextureEnabledElement::get(SoState * const state, const int unit)
{
  SoMultiTextureEnabledElement * elem = (SoMultiTextureEnabledElement *)
    state->getConstElement(classStackIndex);

  assert(unit >= 0 && unit < MAX_UNITS);
  return PRIVATE(elem)->enabled[unit];
}

void
SoMultiTextureEnabledElement::setElt(const int unit, const SbBool enabled)
{
  assert(unit >= 0 && unit < MAX_UNITS);
  PRIVATE(this)->enabled[unit] = enabled;
}

void
SoMultiTextureEnabledElement::push(SoState * state)
{
  SoMultiTextureEnabledElement * prev = (SoMultiTextureEnabledElement *)
    this->getNextInStack();
  
  for (int i = 0; i < MAX_UNITS; i++) {
    PRIVATE(this)->enabled[i] = PRIVATE(prev)->enabled[i];
  }
}

SbBool 
SoMultiTextureEnabledElement::matches(const SoElement * elem) const
{
  SoMultiTextureEnabledElement * e =
    (SoMultiTextureEnabledElement *) elem;
  for (int i = 0; i < MAX_UNITS; i++) {
    if (PRIVATE(e)->enabled[i] != PRIVATE(this)->enabled[i]) {
      return FALSE;
    }
  }
  return TRUE;
}

SoElement * 
SoMultiTextureEnabledElement::copyMatchInfo(void) const
{
  SoMultiTextureEnabledElement * elem =
    (SoMultiTextureEnabledElement *)(getTypeId().createInstance());
  for (int i = 0; i < MAX_UNITS; i++) {
    PRIVATE(elem)->enabled[i]= PRIVATE(this)->enabled[i];
  }
  return elem;
}


#undef MAX_UNITS
#undef PRIVATE

