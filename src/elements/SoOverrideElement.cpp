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
 *  LGPL, please contact SIM to aquire a Professional Edition license.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
\**************************************************************************/

/*!
  \class SoOverrideElement Inventor/elements/SoOverrideElement.h
  \brief The SoOverrideElement maintains a list of overridable elements and a list over which elements should be overridden.

  Only certain elements can be overridden.
*/

#include <Inventor/elements/SoOverrideElement.h>

#include <assert.h>

#define SO_GET_OVERRIDE(flag) \
const SoOverrideElement * const element = \
  (const SoOverrideElement *) getConstElement(state, classStackIndex); \
return (element->flags & flag)

#define SO_SET_OVERRIDE(flag) \
SoOverrideElement * const element = \
  (SoOverrideElement *) getElement(state, classStackIndex); \
if (override) \
  element->flags |= flag; \
else \
  element->flags &= ~flag


/*!
\enum SoOverrideElement::FlagBits

FIXME: write doc.
*/

SO_ELEMENT_SOURCE(SoOverrideElement);

/*!
This static method initializes static data for the
SoOverrideElement class.
*/

void
SoOverrideElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoOverrideElement, inherited);
}

/*!
  The destructor.
*/

SoOverrideElement::~SoOverrideElement(void)
{
}

//! FIXME: write doc.

void
SoOverrideElement::init(SoState * state)
{
  inherited::init(state);
  this->flags = 0;
}

//! FIXME: write doc.

void
SoOverrideElement::push(SoState * state)
{
  inherited::push(state);
  SoOverrideElement *next = (SoOverrideElement*) this->next;
  next->flags = this->flags;
}

//! FIXME: write doc.

SbBool
SoOverrideElement::matches(const SoElement *element) const
{
  return ((SoOverrideElement*)element)->flags == this->flags;
}

//! FIXME: write doc.

SoElement *
SoOverrideElement::copyMatchInfo(void) const
{
  SoOverrideElement *elem = (SoOverrideElement*)
    this->getTypeId().createInstance();
  elem->flags = this->flags;
  return elem;
}

//! FIXME: write doc.

void
SoOverrideElement::print(FILE * /* file */) const
{
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getAmbientColorOverride(SoState * const state)
{
  SO_GET_OVERRIDE(AMBIENT_COLOR);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getColorIndexOverride(SoState * const state)
{
  SO_GET_OVERRIDE(COLOR_INDEX);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getComplexityOverride(SoState * const state)
{
  SO_GET_OVERRIDE(COMPLEXITY);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getComplexityTypeOverride(SoState * const state)
{
  SO_GET_OVERRIDE(COMPLEXITY_TYPE);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getCreaseAngleOverride(SoState * const state)
{
  SO_GET_OVERRIDE(CREASE_ANGLE);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getDiffuseColorOverride(SoState * const state)
{
  SO_GET_OVERRIDE(DIFFUSE_COLOR);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getDrawStyleOverride(SoState * const state)
{
  SO_GET_OVERRIDE(DRAW_STYLE);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getEmissiveColorOverride(SoState * const state)
{
  SO_GET_OVERRIDE(EMISSIVE_COLOR);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getFontNameOverride(SoState * const state)
{
  SO_GET_OVERRIDE(FONT_NAME);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getFontSizeOverride(SoState * const state)
{
  SO_GET_OVERRIDE(FONT_SIZE);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getLightModelOverride(SoState * const state)
{
  SO_GET_OVERRIDE(LIGHT_MODEL);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getLinePatternOverride(SoState * const state)
{
  SO_GET_OVERRIDE(LINE_PATTERN);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getLineWidthOverride(SoState * const state)
{
  SO_GET_OVERRIDE(LINE_WIDTH);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getMaterialBindingOverride(SoState * const state)
{
  SO_GET_OVERRIDE(MATERIAL_BINDING);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getPointSizeOverride(SoState * const state)
{
  SO_GET_OVERRIDE(POINT_SIZE);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getPickStyleOverride(SoState * const state)
{
  SO_GET_OVERRIDE(PICK_STYLE);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getShapeHintsOverride(SoState * const state)
{
  SO_GET_OVERRIDE(SHAPE_HINTS);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getShininessOverride(SoState * const state)
{
  SO_GET_OVERRIDE(SHININESS);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getSpecularColorOverride(SoState * const state)
{
  SO_GET_OVERRIDE(SPECULAR_COLOR);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getTransparencyOverride(SoState * const state)
{
  SO_GET_OVERRIDE(TRANSPARENCY);
}

/*!
  FIXME: write doc.
*/

SbBool
SoOverrideElement::getPolygonOffsetOverride(SoState * const state)
{
  SO_GET_OVERRIDE(POLYGON_OFFSET);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setAmbientColorOverride(SoState * const state,
                                           SoNode * const /* node */,
                                           const SbBool override)
{
  SO_SET_OVERRIDE(AMBIENT_COLOR);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setColorIndexOverride(SoState * const state,
                                         SoNode * const /* node */,
                                         const SbBool override)
{
  SO_SET_OVERRIDE(COLOR_INDEX);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setComplexityOverride(SoState * const state,
                                         SoNode * const /* node */,
                                         const SbBool override)
{
  SO_SET_OVERRIDE(COMPLEXITY);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setComplexityTypeOverride(SoState * const state,
                                             SoNode * const /* node */,
                                             const SbBool override)
{
  SO_SET_OVERRIDE(COMPLEXITY_TYPE);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setCreaseAngleOverride(SoState * const state,
                                          SoNode * const /* node */,
                                          const SbBool override)
{
  SO_SET_OVERRIDE(CREASE_ANGLE);
}

//! FIXME: write doc.

void
SoOverrideElement::setDiffuseColorOverride(SoState * const state,
                                           SoNode * const /* node */,
                                           const SbBool override)
{
  SO_SET_OVERRIDE(DIFFUSE_COLOR);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setDrawStyleOverride(SoState * const state,
                                        SoNode * const /* node */,
                                        const SbBool override)
{
  SO_SET_OVERRIDE(DRAW_STYLE);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setEmissiveColorOverride(SoState * const state,
                                            SoNode * const /* node */,
                                            const SbBool override)
{
  SO_SET_OVERRIDE(EMISSIVE_COLOR);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setFontNameOverride(SoState * const state,
                                       SoNode * const /* node */,
                                       const SbBool override)
{
  SO_SET_OVERRIDE(FONT_NAME);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setFontSizeOverride(SoState * const state,
                                       SoNode * const /* node */,
                                       const SbBool override)
{
  SO_SET_OVERRIDE(FONT_SIZE);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setLightModelOverride(SoState * const state,
                                         SoNode * const /* node */,
                                         const SbBool override)
{
  SO_SET_OVERRIDE(LIGHT_MODEL);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setLinePatternOverride(SoState * const state,
                                          SoNode * const /* node */,
                                          const SbBool override)
{
  SO_SET_OVERRIDE(LINE_PATTERN);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setLineWidthOverride(SoState * const state,
                                        SoNode * const /* node */,
                                        const SbBool override)
{
  SO_SET_OVERRIDE(LINE_WIDTH);
}

//! FIXME: write doc.

void
SoOverrideElement::setMaterialBindingOverride(SoState * const state,
                                              SoNode * const /* node */,
                                              const SbBool override)
{
  SO_SET_OVERRIDE(MATERIAL_BINDING);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setPickStyleOverride(SoState * const state,
                                        SoNode * const /* node */,
                                        const SbBool override)
{
  SO_SET_OVERRIDE(PICK_STYLE);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setPointSizeOverride(SoState * const state,
                                        SoNode * const /* node */,
                                        const SbBool override)
{
  SO_SET_OVERRIDE(POINT_SIZE);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setPolygonOffsetOverride(SoState * const state,
                                            SoNode * const /* node */,
                                            const SbBool override)
{
  SO_SET_OVERRIDE(POLYGON_OFFSET);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setShapeHintsOverride(SoState * const state,
                                         SoNode * const /* node */,
                                         const SbBool override)
{
  SO_SET_OVERRIDE(SHAPE_HINTS);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setShininessOverride(SoState * const state,
                                        SoNode * const /* node */,
                                        const SbBool override)
{
  SO_SET_OVERRIDE(SHININESS);
}

/*!
  FIXME: write doc.
*/

void
SoOverrideElement::setSpecularColorOverride(SoState * const state,
                                            SoNode * const /* node */,
                                            const SbBool override)
{
  SO_SET_OVERRIDE(SPECULAR_COLOR);
}

//! FIXME: write doc.

void
SoOverrideElement::setTransparencyOverride(SoState * const state,
                                           SoNode * const /* node */,
                                           const SbBool override)
{
  SO_SET_OVERRIDE(TRANSPARENCY);
}
