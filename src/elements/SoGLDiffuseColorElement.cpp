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
  \class SoGLDiffuseColorElement Inventor/elements/SoGLDiffuseColorElement.h
  \brief The SoGLDiffuseColorElement class is yet to be documented.

  FIXME: write doc.
*/

#include <Inventor/elements/SoGLDiffuseColorElement.h>

#include <Inventor/SbColor.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H
#if HAVE_WINDOWS_H
#include <windows.h>
#endif // HAVE_WINDOWS_H
#include <GL/gl.h>

#include <assert.h>

SO_ELEMENT_SOURCE(SoGLDiffuseColorElement);

/*!
  This static method initializes static data for the
  SoGLDiffuseColorElement class.
*/

void
SoGLDiffuseColorElement::initClass()
{
  SO_ELEMENT_INIT_CLASS(SoGLDiffuseColorElement, inherited);
}

/*!
  The destructor.
*/

SoGLDiffuseColorElement::~SoGLDiffuseColorElement()
{
}

//! FIXME: write doc.

void
SoGLDiffuseColorElement::init(SoState *state)
{
  inherited::init(state);
  this->alpha = 1.0f;
  this->updategl(SbVec4f(0.8f, 0.8f, 0.8f, 1.0f));
}

//! FIXME: write doc.

void
SoGLDiffuseColorElement::push(SoState * state)
{
  inherited::push(state);
}

//! FIXME: write doc.

void
SoGLDiffuseColorElement::pop(SoState *state, const SoElement * prevTopElement)
{
  inherited::pop(state, prevTopElement);
}

//! FIXME: write doc.

static void
convert_packed(uint32_t packed, SbVec4f &v)
{
  static float DIV255 = 1.0f / 255.0f;
  v[3] = float(packed&0xff)*DIV255;
  packed >>= 8;
  v[2] = float(packed & 0xff)*DIV255;
  packed >>= 8;
  v[1] = float(packed & 0xff)*DIV255;
  v[0] = float(packed >> 8)*DIV255;
}

//! FIXME: write doc.

void
SoGLDiffuseColorElement::send(const int index, const float alpha)
{
  assert(this->numColors > 0);
  int realindex = index < this->numColors ? index : this->numColors - 1;
  if (realindex < 0) realindex = 0;

  if (this->colors) {
    this->alpha = alpha;
    const SbVec3f & c = this->colors[realindex];
    SbVec4f col(c[0], c[1], c[2], alpha);
    this->updategl(col);
  }
  else if (this->packedColors) {
    SbVec4f color;
    convert_packed(this->packedColors[realindex], color);
    this->updategl(color);
  }
}

/*!
  FIXME: write doc.
*/
void
SoGLDiffuseColorElement::send(const int index)
{
  this->send(index, this->alpha);
}

/*!
  Do not use. Provided only to support SoGLLazyElement.
*/
void
SoGLDiffuseColorElement::sendOnePacked(const uint32_t packedcol)
{
  SbVec4f color;
  convert_packed(packedcol, color);
  this->updategl(color);
}

//! FIXME: write doc.

void
SoGLDiffuseColorElement::updategl(const SbVec4f & color)
{
#if 1 // if using GL_COLOR_MATERIAL
  glColor4fv((const GLfloat*)&color);
#else
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &color);
#endif
}
