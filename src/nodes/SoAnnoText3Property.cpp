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
  \class SoAnnoText3Property SoAnnoText3Property.h Inventor/nodes/SoAnnoText3Property.h
  \brief The SoAnnoText3Property class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/nodes/SoAnnoText3Property.h>
#include <Inventor/nodes/SoSubNodeP.h>

#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoAnnoText3FontSizeHintElement.h>
#include <Inventor/elements/SoAnnoText3RenderPrintElement.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>

/*!
  \enum SoAnnoText3Property::RenderPrintType
  FIXME: write documentation for enum
*/
/*!
  \var SoAnnoText3Property::RenderPrintType SoAnnoText3Property::RENDER3D_PRINT_VECTOR
  FIXME: write documentation for enum definition
*/
/*!
  \var SoAnnoText3Property::RenderPrintType SoAnnoText3Property::RENDER3D_PRINT_RASTER
  FIXME: write documentation for enum definition
*/
/*!
  \var SoAnnoText3Property::RenderPrintType SoAnnoText3Property::RENDER2D_PRINT_RASTER
  FIXME: write documentation for enum definition
*/

/*!
  \enum SoAnnoText3Property::FontSizeHint
  FIXME: write documentation for enum
*/
/*!
  \var SoAnnoText3Property::FontSizeHint SoAnnoText3Property::ANNOTATION
  FIXME: write documentation for enum definition
*/
/*!
  \var SoAnnoText3Property::FontSizeHint SoAnnoText3Property::FIT_VECTOR_TEXT
  FIXME: write documentation for enum definition
*/


/*!
  \var SoSFEnum SoAnnoText3Property::renderPrintType
  FIXME: write documentation for field
*/
/*!
  \var SoSFBool SoAnnoText3Property::isCharOrientedRasterPrint
  FIXME: write documentation for field
*/
/*!
  \var SoSFEnum SoAnnoText3Property::fontSizeHint
  FIXME: write documentation for field
*/



// *************************************************************************

SO_NODE_SOURCE(SoAnnoText3Property);

/*!
  Constructor.
*/
SoAnnoText3Property::SoAnnoText3Property()
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoAnnoText3Property);

  SO_NODE_ADD_FIELD(fontSizeHint, (FIT_VECTOR_TEXT));
  SO_NODE_ADD_FIELD(renderPrintType, (RENDER3D_PRINT_VECTOR));
  SO_NODE_ADD_FIELD(isCharOrientedRasterPrint, (TRUE));

  SO_NODE_DEFINE_ENUM_VALUE(FontSizeHint, ANNOTATION);
  SO_NODE_DEFINE_ENUM_VALUE(FontSizeHint, FIT_VECTOR_TEXT);
  SO_NODE_SET_SF_ENUM_TYPE(fontSizeHint, FontSizeHint);

  SO_NODE_DEFINE_ENUM_VALUE(RenderPrintType, RENDER3D_PRINT_VECTOR);
  SO_NODE_DEFINE_ENUM_VALUE(RenderPrintType, RENDER3D_PRINT_RASTER);
  SO_NODE_DEFINE_ENUM_VALUE(RenderPrintType, RENDER2D_PRINT_RASTER);
  SO_NODE_SET_SF_ENUM_TYPE(renderPrintType, RenderPrintType);
}

/*!
  Destructor.
*/
SoAnnoText3Property::~SoAnnoText3Property()
{
}

/*!
  Does initialization common for all objects of the
  SoAnnoText3Property class. This includes setting up the
  type system, among other things.
*/
void
SoAnnoText3Property::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoAnnoText3Property);

  SO_ENABLE(SoGLRenderAction, SoAnnoText3FontSizeHintElement);
  SO_ENABLE(SoGLRenderAction, SoAnnoText3RenderPrintElement);

  SO_ENABLE(SoGetBoundingBoxAction, SoAnnoText3FontSizeHintElement);
  SO_ENABLE(SoGetBoundingBoxAction, SoAnnoText3RenderPrintElement);

  SO_ENABLE(SoCallbackAction, SoAnnoText3FontSizeHintElement);
  SO_ENABLE(SoCallbackAction, SoAnnoText3RenderPrintElement);

  SO_ENABLE(SoPickAction, SoAnnoText3FontSizeHintElement);
  SO_ENABLE(SoPickAction, SoAnnoText3RenderPrintElement);

  SO_ENABLE(SoGetPrimitiveCountAction, SoAnnoText3FontSizeHintElement);
  SO_ENABLE(SoGetPrimitiveCountAction, SoAnnoText3RenderPrintElement);
}

/*!
  FIXME: write function documentation
*/
void
SoAnnoText3Property::getBoundingBox(SoGetBoundingBoxAction * action)
{
  SoAnnoText3Property::doAction(action);
}

/*!
  FIXME: write doc
*/
void
SoAnnoText3Property::doAction(SoAction *action)
{
  SoState * state = action->getState();

  SoAnnoText3FontSizeHintElement::FontSizeHint hint;
  switch (fontSizeHint.getValue()) {
  case ANNOTATION:
    hint = SoAnnoText3FontSizeHintElement::ANNOTATION;
    break;
  case FIT_VECTOR_TEXT:
    hint = SoAnnoText3FontSizeHintElement::FIT_TEXT_VECTOR;
    break;
  default:
    assert(0); // FIXME: do something a bit more elegant here. 19990315 mortene.
    // Unnecessary, but kills a compiler warning.
    hint = SoAnnoText3FontSizeHintElement::ANNOTATION;
    break;
  }

  SoAnnoText3RenderPrintElement::RenderPrintType print;
  switch (renderPrintType.getValue()) {
  case RENDER3D_PRINT_VECTOR:
    print = SoAnnoText3RenderPrintElement::RENDER3D_PRINT_VECTOR;
    break;
  case RENDER3D_PRINT_RASTER:
    print = SoAnnoText3RenderPrintElement::RENDER3D_PRINT_RASTER;
    break;
  case RENDER2D_PRINT_RASTER:
    print = SoAnnoText3RenderPrintElement::RENDER2D_PRINT_RASTER;
    break;
  default:
    assert(0); // FIXME: do something a bit more elegant here. 19990315 mortene.
    // Unnecessary, but kills a compiler warning.
    print = SoAnnoText3RenderPrintElement::RENDER3D_PRINT_VECTOR;
    break;
  }

  SoAnnoText3FontSizeHintElement::set(state, hint);
  SoAnnoText3RenderPrintElement::set(state, print);
}

/*!
  FIXME: write doc
*/
void
SoAnnoText3Property::GLRender(SoGLRenderAction *action)
{
  SoAnnoText3Property::doAction(action);
}

/*!
  FIXME: write doc
*/
void
SoAnnoText3Property::callback(SoCallbackAction *action)
{
  SoAnnoText3Property::doAction(action);
}

/*!
  FIXME: write doc
*/
void
SoAnnoText3Property::pick(SoPickAction *action)
{
  SoAnnoText3Property::doAction(action);
}

/*!
  FIXME: write doc
*/
void
SoAnnoText3Property::getPrimitiveCount(SoGetPrimitiveCountAction *action)
{
  SoAnnoText3Property::doAction(action);
}
