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
  \class SoVertexProperty SoVertexProperty.h Inventor/nodes/SoVertexProperty.h
  \brief The SoVertexProperty class ...
  \ingroup nodes

  FIXME: write class doc
*/


//
// FIXME: this class is really not correctly implemented. Each
// vertex shape node should support this node internally.
// Right now we just push its values on the stack.
//

#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoSubNodeP.h>


#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoCallbackAction.h>

#include <Inventor/actions/SoGetPrimitiveCountAction.h>

#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoGLNormalElement.h>
#include <Inventor/elements/SoGLTextureCoordinateElement.h>
#include <Inventor/elements/SoDiffuseColorElement.h>
#include <Inventor/elements/SoOverrideElement.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoGLPolygonStippleElement.h>

/*!
  \enum SoVertexProperty::Binding
  FIXME: write documentation for enum
*/
/*!
  \var SoVertexProperty::Binding SoVertexProperty::OVERALL
  FIXME: write documentation for enum definition
*/
/*!
  \var SoVertexProperty::Binding SoVertexProperty::PER_PART
  FIXME: write documentation for enum definition
*/
/*!
  \var SoVertexProperty::Binding SoVertexProperty::PER_PART_INDEXED
  FIXME: write documentation for enum definition
*/
/*!
  \var SoVertexProperty::Binding SoVertexProperty::PER_FACE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoVertexProperty::Binding SoVertexProperty::PER_FACE_INDEXED
  FIXME: write documentation for enum definition
*/
/*!
  \var SoVertexProperty::Binding SoVertexProperty::PER_VERTEX
  FIXME: write documentation for enum definition
*/
/*!
  \var SoVertexProperty::Binding SoVertexProperty::PER_VERTEX_INDEXED
  FIXME: write documentation for enum definition
*/


/*!
  \var SoMFVec3f SoVertexProperty::vertex
  FIXME: write documentation for field
*/
/*!
  \var SoMFVec2f SoVertexProperty::texCoord
  FIXME: write documentation for field
*/
/*!
  \var SoMFVec3f SoVertexProperty::normal
  FIXME: write documentation for field
*/
/*!
  \var SoSFEnum SoVertexProperty::normalBinding
  FIXME: write documentation for field
*/
/*!
  \var SoMFUInt32 SoVertexProperty::orderedRGBA
  FIXME: write documentation for field
*/
/*!
  \var SoSFEnum SoVertexProperty::materialBinding
  FIXME: write documentation for field
*/


SO_NODE_SOURCE(SoVertexProperty);

/*!
  Constructor.
*/
SoVertexProperty::SoVertexProperty()
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoVertexProperty);

  SO_NODE_ADD_FIELD(vertex, (0));
  SO_NODE_ADD_FIELD(normal, (0));
  SO_NODE_ADD_FIELD(texCoord, (0));
  SO_NODE_ADD_FIELD(orderedRGBA, (0));
  // FIXME: is this the correct way of making empty multifields?
  // 19990301 mortene.
  vertex.setNum(0);
  texCoord.setNum(0);
  normal.setNum(0);
  orderedRGBA.setNum(0);

  SO_NODE_ADD_FIELD(normalBinding, (SoVertexProperty::PER_VERTEX_INDEXED));
  SO_NODE_ADD_FIELD(materialBinding, (SoVertexProperty::OVERALL));

  SO_NODE_DEFINE_ENUM_VALUE(Binding, OVERALL);
  SO_NODE_DEFINE_ENUM_VALUE(Binding, PER_PART);
  SO_NODE_DEFINE_ENUM_VALUE(Binding, PER_PART_INDEXED);
  SO_NODE_DEFINE_ENUM_VALUE(Binding, PER_FACE);
  SO_NODE_DEFINE_ENUM_VALUE(Binding, PER_FACE_INDEXED);
  SO_NODE_DEFINE_ENUM_VALUE(Binding, PER_VERTEX);
  SO_NODE_DEFINE_ENUM_VALUE(Binding, PER_VERTEX_INDEXED);

  SO_NODE_SET_SF_ENUM_TYPE(normalBinding, Binding);
  SO_NODE_SET_SF_ENUM_TYPE(materialBinding, Binding);

  this->checktransparent = FALSE;
  this->transparent = FALSE;
}

/*!
  Destructor.
*/
SoVertexProperty::~SoVertexProperty()
{
}

// doc from parent
void
SoVertexProperty::initClass()
{
  SO_NODE_INTERNAL_INIT_CLASS(SoVertexProperty);

  SO_ENABLE(SoGetBoundingBoxAction, SoCoordinateElement);

  SO_ENABLE(SoGLRenderAction, SoGLCoordinateElement);
  SO_ENABLE(SoGLRenderAction, SoMaterialBindingElement);
  SO_ENABLE(SoGLRenderAction, SoNormalBindingElement);
  SO_ENABLE(SoGLRenderAction, SoGLNormalElement);
  SO_ENABLE(SoGLRenderAction, SoGLTextureCoordinateElement);

  SO_ENABLE(SoPickAction, SoCoordinateElement);
  SO_ENABLE(SoPickAction, SoMaterialBindingElement);
  SO_ENABLE(SoPickAction, SoNormalBindingElement);
  SO_ENABLE(SoPickAction, SoNormalElement);
  SO_ENABLE(SoPickAction, SoTextureCoordinateElement);

  SO_ENABLE(SoCallbackAction, SoCoordinateElement);
  SO_ENABLE(SoCallbackAction, SoMaterialBindingElement);
  SO_ENABLE(SoCallbackAction, SoNormalBindingElement);
  SO_ENABLE(SoCallbackAction, SoNormalElement);
  SO_ENABLE(SoCallbackAction, SoTextureCoordinateElement);

  SO_ENABLE(SoGetPrimitiveCountAction, SoCoordinateElement);
  SO_ENABLE(SoGetPrimitiveCountAction, SoMaterialBindingElement);
  SO_ENABLE(SoGetPrimitiveCountAction, SoNormalBindingElement);
  SO_ENABLE(SoGetPrimitiveCountAction, SoNormalElement);
  SO_ENABLE(SoGetPrimitiveCountAction, SoTextureCoordinateElement);
}

/*!
  FIXME: write function documentation
*/
void
SoVertexProperty::getBoundingBox(SoGetBoundingBoxAction * action)
{
  if (vertex.getNum() > 0) {
    SoCoordinateElement::set3(action->getState(), this,
                              vertex.getNum(), vertex.getValues(0));
  }
}

/*!
  FIXME: write function documentation
*/
void
SoVertexProperty::GLRender(SoGLRenderAction * action)
{
  SoState *state = action->getState();

  if (SoShapeStyleElement::isScreenDoor(state) &&
      ! this->orderedRGBA.isIgnored() &&
      this->orderedRGBA.getNum() &&
      ! SoOverrideElement::getTransparencyOverride(state)) {
    float t = (255 - (this->orderedRGBA[0] & 0xff)) / 255.0f;
    SoGLPolygonStippleElement::setTransparency(state, t);
    SoGLPolygonStippleElement::set(state, t >= 1.0f/255.0f);
  }

  if (this->texCoord.getNum() > 0) {
    SoGLTextureCoordinateElement::setTexGen(state,
                                            this, NULL);
  }
  SoVertexProperty::doAction(action);
}

/*!
  FIXME: write doc
 */
void
SoVertexProperty::doAction(SoAction *action)
{
  if (this->checktransparent) {
    this->checktransparent = FALSE;
    this->transparent = FALSE;
    int n = this->orderedRGBA.getNum();
    for (int i = 0; i < n; i++) {
      if ((this->orderedRGBA[i] & 0xff) != 0xff) {
        this->transparent = TRUE;
        break;
      }
    }
  }

  SoState * state = action->getState();
  if (this->vertex.getNum() > 0)
    SoCoordinateElement::set3(state, this, this->vertex.getNum(),
                              this->vertex.getValues(0));

  if (this->texCoord.getNum() > 0) {
    SoTextureCoordinateElement::set2(state, this, this->texCoord.getNum(),
                                     this->texCoord.getValues(0));
  }
  if (this->normal.getNum() > 0) {
    SoNormalElement::set(state, this, this->normal.getNum(),
                         this->normal.getValues(0));
  }
  if (this->normal.getNum() && !this->normalBinding.isIgnored()) {
    SoNormalBindingElement::set(state, this,
                                (SoNormalBindingElement::Binding)
                                this->normalBinding.getValue());
  }
  if (this->orderedRGBA.getNum() > 0
      && !SoOverrideElement::getDiffuseColorOverride(state)) {
    SoDiffuseColorElement::set(state, this, this->orderedRGBA.getNum(),
                               this->orderedRGBA.getValues(0),
                               this->transparent);
    if (this->isOverride()) {
      SoOverrideElement::setDiffuseColorOverride(state, this, TRUE);
    }
  }
  if (this->orderedRGBA.getNum() && !this->materialBinding.isIgnored()
      && !SoOverrideElement::getMaterialBindingOverride(state)) {
    SoMaterialBindingElement::set(state, this,
                                  (SoMaterialBindingElement::Binding)
                                  this->materialBinding.getValue());
    if (this->isOverride()) {
      SoOverrideElement::setMaterialBindingOverride(state, this, TRUE);
    }
  }
}

/*!
  FIXME: write doc
 */
void
SoVertexProperty::callback(SoCallbackAction *action)
{
  SoVertexProperty::doAction((SoAction*)action);
}

/*!
  FIXME: write doc
 */
void
SoVertexProperty::pick(SoPickAction *action)
{
  SoVertexProperty::doAction((SoAction*)action);
}

/*!
  FIXME: write doc
 */
void
SoVertexProperty::getPrimitiveCount(SoGetPrimitiveCountAction *action)
{
  SoVertexProperty::doAction((SoAction*)action);
}

/*!
  Overloaded to check for transparency when orderedRGBA changes
*/
void
SoVertexProperty::notify(SoNotList *list)
{
  SoField *f = list->getLastField();
  if (f == &this->orderedRGBA) {
    this->checktransparent = TRUE;
  }
  SoNode::notify(list);
}
