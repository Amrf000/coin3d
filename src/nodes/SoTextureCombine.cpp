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
  \class SoTextureCombine SoTextureCombine.h Inventor/nodes/SoTextureCombine.h
  \brief The SoTextureCombine class is a node for setting texture combine functions.
  \ingroup nodes

  This node is more or less an exact mapping of the OpenGL
  ARB_texture_env_combine extension (included in OpenGL in OpenGL
  v1.3). See
  http://oss.sgi.com/projects/ogl-sample/registry/ARB/texture_env_combine.txt
  for more information about this extension.

  Basically this node lets you specify up to three sources, and a
  function to combine those sources. In addition to the function, it's
  possible to apply simple operands on the sources. In the
  documentation below, the sources will be called Arg0, Arg1, and
  Arg2, just like in the ARB_texture_env_mode specification.

  It's possible to specify both a color and an alpha operation.

  This node has many fields, but usually it is sufficient to set only
  one or very few fields. FIXME: more doc, pederb, 2004-01-27
  
  \since 2004-01-27
*/

/*!
  \enum SoTextureCombine::Source
  For enumerating combiner sources.
*/

/*!
  \enum SoTextureCombine::Operand
  For enumerating source operands.
*/

/*!
  \enum SoTextureCombine::Operation
  For enumerating combiner operations/functions.
*/


/*!
  \var SoTextureCombine::Source SoTextureCombine::PRIMARY_COLOR

  Choose primary color as source.
*/

/*!
  \var SoTextureCombine::Source SoTextureCombine::TEXTURE

  Choose texture as source.
*/

/*!
  \var SoTextureCombine::Source SoTextureCombine::CONSTANT

  Choose the constantColor field as source.
*/

/*!
  \var SoTextureCombine::Source SoTextureCombine::PREVIOUS

  Choose the previous unit's texture as source.
*/

/*!
  \var SoTextureCombine::Operand SoTextureCombine::SRC_COLOR

  Use the source color as operand.
*/

/*!
  \var SoTextureCombine::Operand SoTextureCombine::ONE_MINUS_SRC_COLOR
  
  Use one minus source color as operand.
*/

/*!
  \var SoTextureCombine::Operand SoTextureCombine::SRC_ALPHA

  Use the source alpha as operand.
*/

/*!
  \var SoTextureCombine::Operand SoTextureCombine::ONE_MINUS_SRC_ALPHA

  Use one minus source alpha as operand.
*/

/*!
  \var SoTextureCombine::Operation SoTextureCombine::REPLACE
  
  dst = Arg0
*/

/*!
  \var SoTextureCombine::Operation SoTextureCombine::MODULATE

  dst = Arg0 * Arg1
*/

/*!
  \var SoTextureCombine::Operation SoTextureCombine::ADD

  dst = Arg0 + Arg1
*/

/*!
  \var SoTextureCombine::Operation SoTextureCombine::ADD_SIGNED

  dst = Arg0 + Arg1 - 0.5
*/

/*!
  \var SoTextureCombine::Operation SoTextureCombine::SUBTRACT

  dst = Arg0 - Arg1
*/

/*!
  \var SoTextureCombine::Operation SoTextureCombine::INTERPOLATE

  dst = Arg0 * (Arg2) + Arg1 * (1-Arg2)
*/

/*!
  \var SoTextureCombine::Operation SoTextureCombine::DOT3_RGB

  Dot product of Arg0 and Arg1
*/

/*!
  \var SoTextureCombine::Operation SoTextureCombine::DOT3_RGBA

  Dot product (including alpha) of Arg0 and Arg1
*/

/*!
  SoTextureCombine::rgbSource

  The color sources. This field is empty by default, but you can
  insert up to three values [Arg0, Arg1, Arg2]. When the field
  contains less than three values, the default [TEXTURE, PREVIOUS,
  CONSTANT], will be used for missing values.

  For texture unit 0, PREVIOUS maps to PRIMARY_COLOR,
*/

/*!
  SoTextureCombine::alphaSource

  The alpha sources. This field is empty by default, but you can
  insert up to three values [Arg0, Arg1, Arg2]. When the field
  contains less than three values, the default [TEXTURE, PREVIOUS,
  CONSTANT], will be used for missing values.

  For texture unit 0, PREVIOUS maps to PRIMARY_COLOR,
*/

/*!
  SoTextureCombine::rgbOperand

  The color operands. This field is empty by default, but you can
  insert up to three values. When the field contains less than three
  values, the default [SRC_COLOR, SRC_COLOR, SRC_COLOR] will be used
  for missing values.
*/

/*!
  SoTextureCombine::alphaOperand

  The alpha operands. This field is empty by default, but you can
  insert up to three values. When the field contains less than three
  values, the default [SRC_ALPHA, SRC_ALPHA, SRC_ALPHA] will be used
  for missing values. Please not that only SRC_ALPHA and
  ONE_MINUS_SRC_ALPHA are valid operands for alpha operations.
*/

/*!
  SoTextureCombine::rgbOperation

  The color operation. Default value is MODULATE.
*/

/*!
  SoTextureCombine::alphaOperation

  The alpha operation. Default value is MODULATE.
*/

/*!
  SoTextureCombine::rgbScale

  Scale color result by this value. Supported values are 1, 2, and 4.
*/

/*!
  SoTextureCombine::alphaScale

  Scale alpha result by this value. Supported values are 1, 2, and 4.
*/

/*!
  SoTextureCombine::constantColor
  
  The constant color (when CONSTANT is used as source). Default value
  is (1,1,1,1).
*/


#include <Inventor/nodes/SoTextureCombine.h>
#include <Inventor/nodes/SoSubNodeP.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/elements/SoTextureCombineElement.h>
#include <Inventor/elements/SoTextureUnitElement.h>
#include <Inventor/errors/SoDebugError.h>


// *************************************************************************

SO_NODE_SOURCE(SoTextureCombine);

/*!
  Constructor.
*/
SoTextureCombine::SoTextureCombine(void)
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoTextureCombine);

  SO_NODE_ADD_FIELD(rgbSource, (TEXTURE));
  SO_NODE_ADD_FIELD(alphaSource, (TEXTURE));
  SO_NODE_ADD_FIELD(rgbOperand, (SRC_COLOR));
  SO_NODE_ADD_FIELD(alphaOperand, (SRC_ALPHA));
  
  this->rgbSource.setNum(0);
  this->rgbSource.setDefault(TRUE);
  this->alphaSource.setNum(0);
  this->alphaSource.setDefault(TRUE);
  this->rgbOperand.setNum(0);
  this->rgbOperand.setDefault(TRUE);
  this->alphaOperand.setNum(0);
  this->alphaOperand.setDefault(TRUE);

  SO_NODE_ADD_FIELD(rgbOperation, (MODULATE));
  SO_NODE_ADD_FIELD(alphaOperation, (MODULATE));
  
  SO_NODE_ADD_FIELD(rgbScale, (1.0f));
  SO_NODE_ADD_FIELD(alphaScale, (1.0f));

  SO_NODE_ADD_FIELD(constantColor, (1.0f, 1.0f, 1.0f, 1.0f));

  SO_NODE_DEFINE_ENUM_VALUE(Source, PRIMARY_COLOR);
  SO_NODE_DEFINE_ENUM_VALUE(Source, TEXTURE);
  SO_NODE_DEFINE_ENUM_VALUE(Source, CONSTANT);
  SO_NODE_DEFINE_ENUM_VALUE(Source, PREVIOUS);

  SO_NODE_DEFINE_ENUM_VALUE(Operand, SRC_COLOR);
  SO_NODE_DEFINE_ENUM_VALUE(Operand, ONE_MINUS_SRC_COLOR);
  SO_NODE_DEFINE_ENUM_VALUE(Operand, SRC_ALPHA);
  SO_NODE_DEFINE_ENUM_VALUE(Operand, ONE_MINUS_SRC_ALPHA);

  SO_NODE_DEFINE_ENUM_VALUE(Operation, REPLACE);
  SO_NODE_DEFINE_ENUM_VALUE(Operation, MODULATE);
  SO_NODE_DEFINE_ENUM_VALUE(Operation, ADD);
  SO_NODE_DEFINE_ENUM_VALUE(Operation, ADD_SIGNED);
  SO_NODE_DEFINE_ENUM_VALUE(Operation, SUBTRACT);
  SO_NODE_DEFINE_ENUM_VALUE(Operation, INTERPOLATE);
  SO_NODE_DEFINE_ENUM_VALUE(Operation, DOT3_RGB);
  SO_NODE_DEFINE_ENUM_VALUE(Operation, DOT3_RGBA);

  SO_NODE_SET_MF_ENUM_TYPE(rgbSource, Source);
  SO_NODE_SET_MF_ENUM_TYPE(alphaSource, Source);
  SO_NODE_SET_MF_ENUM_TYPE(rgbOperand, Operand);
  SO_NODE_SET_MF_ENUM_TYPE(alphaOperand, Operand);

  SO_NODE_SET_SF_ENUM_TYPE(rgbOperation, Operation);
  SO_NODE_SET_SF_ENUM_TYPE(alphaOperation, Operation);
}

/*!
  Destructor.
*/
SoTextureCombine::~SoTextureCombine()
{
}

// Doc from superclass.
void
SoTextureCombine::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoTextureCombine, SO_FROM_COIN_2_2);

  SO_ENABLE(SoGLRenderAction, SoTextureCombineElement);
}

// Doc from superclass.
void
SoTextureCombine::GLRender(SoGLRenderAction * action)
{
  SoTextureCombine::doAction((SoAction*)action);
}

// Doc from superclass.
void
SoTextureCombine::doAction(SoAction * action)
{
  SoState * state = action->getState();
  int unit = SoTextureUnitElement::get(state); 
  
  SoTextureCombineElement::Source rgbsource[3] = { 
    SoTextureCombineElement::TEXTURE, 
    SoTextureCombineElement::PREVIOUS, 
    SoTextureCombineElement::CONSTANT 
  };
  SoTextureCombineElement::Operand rgboperand[3] = { 
    SoTextureCombineElement::SRC_COLOR, 
    SoTextureCombineElement::SRC_COLOR, 
    SoTextureCombineElement::SRC_COLOR 
  };

  SoTextureCombineElement::Source alphasource[3] = { 
    SoTextureCombineElement::TEXTURE, 
    SoTextureCombineElement::PREVIOUS, 
    SoTextureCombineElement::CONSTANT
  };
  SoTextureCombineElement::Operand alphaoperand[3] = { 
    SoTextureCombineElement::SRC_ALPHA, 
    SoTextureCombineElement::SRC_ALPHA, 
    SoTextureCombineElement::SRC_ALPHA 
  };
  int i;
  for (i = 0; i < this->rgbSource.getNum() && i < 3; i++) {
    rgbsource[i] = (SoTextureCombineElement::Source) this->rgbSource.getValues(0)[i];
  }
  for (i = 0; i < this->alphaSource.getNum() && i < 3; i++) {
    alphasource[i] = (SoTextureCombineElement::Source) this->alphaSource.getValues(0)[i];
  }
  for (i = 0; i < this->rgbOperand.getNum() && i < 3; i++) {
    rgboperand[i] = (SoTextureCombineElement::Operand) this->rgbOperand.getValues(0)[i];
  }
  for (i = 0; i < this->alphaOperand.getNum() && i < 3; i++) {
    alphaoperand[i] = (SoTextureCombineElement::Operand) this->alphaOperand.getValues(0)[i];
  }

  SbColor4f col;
  SbVec4f tmp = this->constantColor.getValue();
  col[0] = tmp[0];
  col[1] = tmp[1];
  col[2] = tmp[2];
  col[3] = tmp[3];

  SoTextureCombineElement::set(state, this, unit,
                               (SoTextureCombineElement::Operation) this->rgbOperation.getValue(),
                               (SoTextureCombineElement::Operation) this->alphaOperation.getValue(),
                               rgbsource, alphasource,
                               rgboperand, alphaoperand,
                               col,
                               this->rgbScale.getValue(),
                               this->alphaScale.getValue());
}


// Doc from superclass.
void
SoTextureCombine::callback(SoCallbackAction * action)
{
  // So far only SoGLRenderAction supports SoTextureCombineElement.  We
  // may never support multiple texture units for SoCallbackAction,
  // but we reimplement the method just in case
  inherited::callback(action);
}

// Doc from superclass.
void
SoTextureCombine::pick(SoPickAction * action)
{
  // So far only SoGLRenderAction supports SoTextureCombineElement.  We
  // may never support multiple texture units for SoPickAction, but we
  // reimplement the method just in case
  inherited::pick(action);
}

