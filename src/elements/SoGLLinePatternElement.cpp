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
  \class SoGLLinePatternElement Inventor/elements/SoGLLinePatternElement.h
  \brief The SoGLLinePatternElement class is yet to be documented.
  \ingroup elements

  FIXME: write doc.
*/

#include <Inventor/elements/SoGLLinePatternElement.h>


#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/system/gl.h>

#include <assert.h>

SO_ELEMENT_SOURCE(SoGLLinePatternElement);

/*!
  This static method initializes static data for the
  SoGLLinePatternElement class.
*/

void
SoGLLinePatternElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoGLLinePatternElement, inherited);
}

/*!
  The destructor.
*/

SoGLLinePatternElement::~SoGLLinePatternElement(void)
{
}

//! FIXME: write doc.

void
SoGLLinePatternElement::init(SoState * state)
{
  inherited::init(state);
  updategl();
}

//! FIXME: write doc.

void
SoGLLinePatternElement::push(SoState * state)
{
  inherited::push(state);
  this->data = ((SoGLLinePatternElement*)this->getNextInStack())->data;
}

//! FIXME: write doc.

void
SoGLLinePatternElement::pop(SoState * state,
                            const SoElement * prevTopElement)
{
  SoGLLinePatternElement * prev = (SoGLLinePatternElement*) prevTopElement;
  if (this->data != prev->data) this->updategl();
  inherited::pop(state, prevTopElement);
}

//! FIXME: write doc.

void
SoGLLinePatternElement::setElt(int32_t pattern)
{
  if (pattern != this->data) {
    this->data = pattern;
    updategl();
  }
}

//! FIXME: write doc.

void
SoGLLinePatternElement::updategl()
{
  //
  // FIXME: store flag to keep enable/disable state, pederb 990624
  //
  if (this->data == (int32_t) CONTINUOUS) {
    glDisable(GL_LINE_STIPPLE);
  }
  else {
    glLineStipple(1, (GLushort) this->data);
    glEnable(GL_LINE_STIPPLE);
  }
}
