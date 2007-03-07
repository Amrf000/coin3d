/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
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
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

/*!
  \class SoShadowStyle SoShadowStyle.h Inventor/annex/FXViz/nodes/SoShadowStyle.h
  \brief The SoShadowStyle class is a node for setting the shadow style on nodes.
  \ingroup nodes

  <b>FILE FORMAT/DEFAULTS:</b>
  \code
    ShadowStyle {
        style CASTS_SHADOW_AND_SHADOWED
    }
  \endcode

  \since Coin 2.5
*/

// *************************************************************************

#include <Inventor/annex/FXViz/nodes/SoShadowStyle.h>
#include <Inventor/nodes/SoSubNodeP.h>

#include <Inventor/actions/SoGLRenderAction.h>

// *************************************************************************

/*!
  \enum SoShadowStyle::Style

  Enumerates the available style settings.
*/

/*!
  \var SoSFEnum SoShadowStyle::style

  The units which will be used for nodes following this node in the
  traversal (until the next SoUnit node, if any). Default value of the
  field is SoShadowStyle::CASTS_SHADOW_AND_SHADOWED.
*/

/*!
  \var SoShadowStyle::Style SoShadowStyle::NO_SHADOWING
  Neither casts or recieves shadows.
*/

/*!
  \var SoShadowStyle::Style SoShadowStyle::CASTS_SHADOW
  Casts shadow, but will no recieve any shadows.
*/

/*!
  \var SoShadowStyle::Style SoShadowStyle::SHADOWED
  Receives shadows, but will not cast any shadow.
*/

/*!
  \var SoShadowStyle::Style SoShadowStyle::CAST_SHADOW_AND_SHADOWED
  Will cast and recieve shadows.
*/

// *************************************************************************


SO_NODE_SOURCE(SoShadowStyle);

/*!
  Constructor.
*/
SoShadowStyle::SoShadowStyle(void)
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoShadowStyle);
  
  SO_NODE_ADD_FIELD(style, (SoShadowStyle::CASTS_SHADOW_AND_SHADOWED));
  
  SO_NODE_DEFINE_ENUM_VALUE(Style, NO_SHADOWING);
  SO_NODE_DEFINE_ENUM_VALUE(Style, CASTS_SHADOW);
  SO_NODE_DEFINE_ENUM_VALUE(Style, SHADOWED);
  SO_NODE_DEFINE_ENUM_VALUE(Style, CASTS_SHADOW_AND_SHADOWED);
  SO_NODE_SET_SF_ENUM_TYPE(style, Style);
}

/*!
  Destructor.
*/
SoShadowStyle::~SoShadowStyle()
{
}

// Doc from superclass.
void
SoShadowStyle::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoShadowStyle, SO_FROM_COIN_2_4); // FIXME: add define for 2.5
  SO_ENABLE(SoGLRenderAction, SoShadowStyleElement);
}

// Doc from superclass.
void
SoShadowStyle::GLRender(SoGLRenderAction * action)
{
  SoShadowStyleElement::set(action->getState(),
                            this,
                            (SoShadowStyleElement::Style) this->style.getValue());

}


