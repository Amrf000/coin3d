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

/*!
  \class SoGLViewingMatrixElement Inventor/elements/SoGLViewingMatrixElement.h
  \brief The SoGLViewingMatrixElement class is yet to be documented.

  FIXME: write doc.
*/

#include <Inventor/elements/SoGLViewingMatrixElement.h>

#include <Inventor/elements/SoModelMatrixElement.h>
#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

#ifdef _WIN32
#include <windows.h>
#endif // !_WIN32

#include <GL/gl.h>

SO_ELEMENT_SOURCE(SoGLViewingMatrixElement);

/*!
  This static method initializes static data for the
  SoGLViewingMatrixElement class.
*/

void
SoGLViewingMatrixElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoGLViewingMatrixElement, inherited);
}

/*!
  The destructor.
*/

SoGLViewingMatrixElement::~SoGLViewingMatrixElement(void)
{
}

//! FIXME: write doc.

void
SoGLViewingMatrixElement::init(SoState * state)
{
  inherited::init(state);
  this->state = state;
  //  glLoadIdentity(); // maybe not strictly necessary?
}

//! FIXME: write doc.

void
SoGLViewingMatrixElement::push(SoState * state)
{
  inherited::push(state);
  SoGLViewingMatrixElement *elem = (SoGLViewingMatrixElement*)
    this->next;
  elem->state = state;
}

//! FIXME: write doc.

void
SoGLViewingMatrixElement::pop(SoState * state,
                              const SoElement * prevTopElement)
{
  inherited::pop(state, prevTopElement);
  ((SoGLViewingMatrixElement*)prevTopElement)->updategl();
}

//! FIXME: write doc.

uint32_t
SoGLViewingMatrixElement::getNodeId(SoState * const state)
{
  const SoReplacedElement *elem = (const SoReplacedElement*)
    SoElement::getConstElement(state, classStackIndex);
  return elem->getNodeId();
}

//! FIXME: write doc.

void
SoGLViewingMatrixElement::setElt(const SbMatrix & matrix)
{
  inherited::setElt(matrix);
  this->updategl();
}

//! FIXME: write doc.

void
SoGLViewingMatrixElement::updategl()
{
  SbMatrix vm = this->viewingMatrix;
  SbBool isIdentity = FALSE;
  const SbMatrix &mm = SoModelMatrixElement::get(this->state, isIdentity);
  if (!isIdentity) {
    vm.multRight(mm);
  }
  glLoadMatrixf((float*)vm);
}
