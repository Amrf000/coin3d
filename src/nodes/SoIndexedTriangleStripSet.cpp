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
  \class SoIndexedTriangleStripSet SoIndexedTriangleStripSet.h Inventor/nodes/SoIndexedTriangleStripSet.h
  \brief The SoIndexedTriangleStripSet class keeps data for rendering and otherwise representing triangle strips.
  \ingroup nodes

  Use nodes of this type as an effective way of drawing triangles
  which are strung together.

  For more information, see the documentation of the \c
  GL_TRIANGLE_STRIP primitive rendering type in OpenGL.

  For more information about indexed shapes, see documentation in
  SoIndexedShape and SoIndexedFaceSet.
*/

#include <Inventor/nodes/SoIndexedTriangleStripSet.h>
#include <Inventor/nodes/SoSubNodeP.h>

#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>
#include <Inventor/bundles/SoMaterialBundle.h>
#include <Inventor/bundles/SoTextureCoordinateBundle.h>
#include <Inventor/caches/SoNormalCache.h>
#include <Inventor/details/SoFaceDetail.h>
#include <Inventor/details/SoPointDetail.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/elements/SoCreaseAngleElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoLightModelElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoShapeHintsElement.h>
#include <Inventor/elements/SoGLShadeModelElement.h>
#include <Inventor/elements/SoTextureCoordinateBindingElement.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/misc/SoGL.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoVertexProperty.h>
#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H
#include <Inventor/system/gl.h>

#include <assert.h>


SO_NODE_SOURCE(SoIndexedTriangleStripSet);

/*!
  Constructor. Default field values will equal those set in the
  SoIndexedShape parent class.
*/
SoIndexedTriangleStripSet::SoIndexedTriangleStripSet(void)
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoIndexedTriangleStripSet);
}

/*!
  Destructor.
*/
SoIndexedTriangleStripSet::~SoIndexedTriangleStripSet()
{
}

// doc from superclass
void
SoIndexedTriangleStripSet::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoIndexedTriangleStripSet);
}

// private
SoIndexedTriangleStripSet::Binding
SoIndexedTriangleStripSet::findMaterialBinding(SoState * const state) const
{
  Binding binding = OVERALL;

  SoMaterialBindingElement::Binding matbind =
    SoMaterialBindingElement::get(state);

  switch (matbind) {
  case SoMaterialBindingElement::OVERALL:
    binding = OVERALL;
    break;
  case SoMaterialBindingElement::PER_VERTEX:
    binding = PER_VERTEX;
    break;
  case SoMaterialBindingElement::PER_VERTEX_INDEXED:
    binding = PER_VERTEX_INDEXED;
    break;
  case SoMaterialBindingElement::PER_PART:
    binding = PER_STRIP;
    break;
  case SoMaterialBindingElement::PER_FACE:
    binding = PER_TRIANGLE;
    break;
  case SoMaterialBindingElement::PER_PART_INDEXED:
    binding = PER_STRIP_INDEXED;
    break;
  case SoMaterialBindingElement::PER_FACE_INDEXED:
    binding = PER_TRIANGLE_INDEXED;
    break;
  default:
#if COIN_DEBUG
    SoDebugError::postWarning("SoIndexedTriangleStripSet::findMaterialBinding",
                              "unknown material binding setting");
#endif // COIN_DEBUG
    break;
  }
  return binding;
}

// private
SoIndexedTriangleStripSet::Binding
SoIndexedTriangleStripSet::findNormalBinding(SoState * const state) const
{
  Binding binding = PER_VERTEX_INDEXED;
  SoNormalBindingElement::Binding normbind =
    SoNormalBindingElement::get(state);

  switch (normbind) {
  case SoNormalBindingElement::OVERALL:
    binding = OVERALL;
    break;
  case SoNormalBindingElement::PER_VERTEX:
    binding = PER_VERTEX;
    break;
  case SoNormalBindingElement::PER_VERTEX_INDEXED:
    binding = PER_VERTEX_INDEXED;
    break;
  case SoNormalBindingElement::PER_PART:
    binding = PER_STRIP;
    break;
  case SoNormalBindingElement::PER_FACE:
    binding = PER_TRIANGLE;
    break;
  case SoNormalBindingElement::PER_PART_INDEXED:
    binding = PER_STRIP_INDEXED;
    break;
  case SoNormalBindingElement::PER_FACE_INDEXED:
    binding = PER_TRIANGLE_INDEXED;
    break;
  default:
#if COIN_DEBUG
    SoDebugError::postWarning("SoIndexedTriangleStripSet::findNormalBinding",
                              "unknown normal binding setting");
#endif // COIN_DEBUG
    break;
  }
  return binding;
}

// doc from superclass
void
SoIndexedTriangleStripSet::GLRender(SoGLRenderAction * action)
{
  // Note: default coordIndex field setting is [ 0 ] so this check is
  // absolutely necessary.
  if (this->coordIndex.getNum() < 3) return;

  SbBool didpush = FALSE;
  SoState * state = action->getState();

  if (this->vertexProperty.getValue()) {
    state->push();
    didpush = TRUE;
    this->vertexProperty.getValue()->GLRender(action);
  }

  Binding mbind = this->findMaterialBinding(state);
  Binding nbind = this->findNormalBinding(state);

  if ((nbind == PER_TRIANGLE) || (nbind == PER_TRIANGLE_INDEXED) ||
      (mbind == PER_TRIANGLE) || (mbind == PER_TRIANGLE_INDEXED)) {
    if (!didpush) {
      state->push();
      didpush = TRUE;
    }
    // enable flat shading before calling shouldGLRender()
    SoGLShadeModelElement::set(state, TRUE);
  }

  if (!this->shouldGLRender(action)) {
    if (didpush) {
      state->pop();
    }
    return;
  }

  const SoCoordinateElement * coords;
  const SbVec3f * normals;
  const int32_t * cindices;
  int32_t numindices;
  const int32_t * nindices;
  const int32_t * tindices;
  const int32_t * mindices;
  SbBool dotextures;
  SbBool normalcacheused;

  SbBool sendnormals =
    (SoLightModelElement::get(state) != SoLightModelElement::BASE_COLOR);

  this->getVertexData(state, coords, normals, cindices,
                      nindices, tindices, mindices, numindices,
                      sendnormals, normalcacheused);

  SoTextureCoordinateBundle tb(action, TRUE, FALSE);
  dotextures = tb.needCoordinates();

  if (dotextures) {
    if (tb.isFunction()) {
      tindices = NULL;
    }
    else if (SoTextureCoordinateBindingElement::get(state) ==
             SoTextureCoordinateBindingElement::PER_VERTEX) {
      tindices = NULL;
    }
    else if (tindices == NULL) {
      tindices = cindices;
    }
  }

  if (!sendnormals) nbind = OVERALL;
  else if (nbind == OVERALL) {
    if (normals) glNormal3fv(normals[0].getValue());
    else glNormal3f(0.0f, 0.0f, 1.0f);
  }
  else if (normalcacheused && nbind == PER_VERTEX) {
    nbind = PER_VERTEX_INDEXED;
  }
  else if (normalcacheused && nbind == PER_TRIANGLE_INDEXED) {
    nbind = PER_TRIANGLE;
  }
  else if (normalcacheused && nbind == PER_STRIP_INDEXED) {
    nbind = PER_STRIP;
  }

  SoMaterialBundle mb(action);

  mb.sendFirst(); // make sure we have the correct material

  sogl_render_tristrip((SoGLCoordinateElement *)coords,
                       cindices,
                       numindices,
                       normals,
                       nindices,
                       &mb,
                       mindices,
                       &tb,
                       tindices,
                       (int)nbind,
                       (int)mbind,
                       dotextures?1:0);

  if (didpush) {
    state->pop();
  }
}

/*!
  Overloaded to return FALSE. Normals are generated directly in normal cache.
*/
SbBool
SoIndexedTriangleStripSet::generateDefaultNormals(SoState *, SoNormalBundle *)
{
  return FALSE;
}

// doc in SoVertexShape
SbBool
SoIndexedTriangleStripSet::generateDefaultNormals(SoState * state,
                                                  SoNormalCache * nc)
{
  // Note: default coordIndex field setting is [ 0 ] so this check is
  // absolutely necessary.
  if (this->coordIndex.getNum() < 3) return FALSE;

  SbBool ccw = TRUE;
  const SoCoordinateElement * coordelem =
    SoCoordinateElement::getInstance(state);

  if (SoShapeHintsElement::getVertexOrdering(state) == SoShapeHintsElement::CLOCKWISE)
    ccw = FALSE;

  SoVertexProperty * vp = (SoVertexProperty *) this->vertexProperty.getValue();
  assert(!vp ||
         vp->getTypeId().isDerivedFrom(SoVertexProperty::getClassTypeId()));
  SbBool vpvtx = vp && (vp->vertex.getNum() > 0);
  SbBool vpnorm = vp && (vp->normal.getNum() > 0);

  const SbVec3f * coords = vpvtx ?
    vp->vertex.getValues(0) :
    coordelem->getArrayPtr3();
  assert(coords);

  SoNormalBindingElement::Binding normbind = vpnorm ?
    (SoNormalBindingElement::Binding) vp->normalBinding.getValue() :
    SoNormalBindingElement::get(state);


  switch (normbind) {
  case SoNormalBindingElement::PER_VERTEX:
  case SoNormalBindingElement::PER_VERTEX_INDEXED:
    nc->generatePerVertex(coords,
                          this->coordIndex.getValues(0),
                          this->coordIndex.getNum(),
                          SoCreaseAngleElement::get(state),
                          NULL,
                          ccw,
                          TRUE);
    break;
  case SoNormalBindingElement::PER_FACE:
  case SoNormalBindingElement::PER_FACE_INDEXED:
    nc->generatePerFaceStrip(coords,
                             this->coordIndex.getValues(0),
                             this->coordIndex.getNum(),
                             ccw);
    break;

  case SoNormalBindingElement::PER_PART:
  case SoNormalBindingElement::PER_PART_INDEXED:
    nc->generatePerStrip(coords,
                         this->coordIndex.getValues(0),
                         this->coordIndex.getNum(),
                         ccw);
    break;
  default:
    break;
  }
  return TRUE;
}

// private
void
SoIndexedTriangleStripSet::countPrimitives(int & strips, int & tris)
{
  strips = 0;
  tris = 0;

  if (this->coordIndex.getNum() < 3) return;

  const int32_t * ptr = this->coordIndex.getValues(0);
  const int32_t * endptr = ptr + this->coordIndex.getNum();

  int tmpcnt = 0;
  while (ptr < endptr) {
    if (*ptr++ >= 0) tmpcnt++;
    else {
      strips++;
      tris += tmpcnt - 2;
      tmpcnt = 0;
    }
  }
  // in case array wasn't terminated by a -1
  if (tmpcnt >= 3) {
    strips++;
    tris += tmpcnt-2;
  }
}

// doc from superclass
void
SoIndexedTriangleStripSet::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  if (!this->shouldPrimitiveCount(action)) return;

  // Note: default coordIndex field setting is [ 0 ] so this check is
  // absolutely necessary.
  int n = this->coordIndex.getNum();
  if (n < 3) return;

  if (action->canApproximateCount()) {
    action->addNumTriangles(n - 2); // assumes one strip
  }
  else {
    int tris, strips;
    this->countPrimitives(strips, tris);
    action->addNumTriangles(tris);
  }
}

/*!
  Overloaded to return TRUE, since shade model must be set to flat
  if normal or material binding is PER_FACE or PER_FACE_INDEXED.
*/
SbBool
SoIndexedTriangleStripSet::willSetShadeModel(void) const
{
  return TRUE;
}

/*!
  FIXME: write doc
*/
void
SoIndexedTriangleStripSet::generatePrimitives(SoAction * action)
{
  // Note: default coordIndex field setting is [ 0 ] so this check is
  // absolutely necessary.
  if (this->coordIndex.getNum() < 3) return;

  SoState * state = action->getState();

  if (this->vertexProperty.getValue()) {
    state->push();
    this->vertexProperty.getValue()->doAction(action);
  }

  Binding mbind = this->findMaterialBinding(state);
  Binding nbind = this->findNormalBinding(state);

  const SoCoordinateElement * coords;
  const SbVec3f * normals;
  const int32_t * cindices;
  int32_t numindices;
  const int32_t * nindices;
  const int32_t * tindices;
  const int32_t * mindices;
  SbBool dotextures;
  SbBool sendnormals = TRUE;
  SbBool normalcacheused;

  this->getVertexData(state, coords, normals, cindices,
                      nindices, tindices, mindices, numindices,
                      sendnormals, normalcacheused);

  SoTextureCoordinateBundle tb(action, FALSE, FALSE);
  dotextures = tb.needCoordinates();

  if (dotextures) {
    if (tb.isFunction()) {
      tindices = NULL;
    }
    else if (SoTextureCoordinateBindingElement::get(state) ==
             SoTextureCoordinateBindingElement::PER_VERTEX) {
      tindices = NULL;
    }
    else if (tindices == NULL) {
      tindices = cindices;
    }
  }

  if (nbind == PER_VERTEX_INDEXED && nindices == NULL) {
    nindices = cindices;
  }
  if (mbind == PER_VERTEX_INDEXED && mindices == NULL) {
    mindices = cindices;
  }

  SbVec3f dummynormal(0.0f, 0.0f, 1.0f);
  const SbVec3f * currnormal = &dummynormal;
  if (!sendnormals) nbind = OVERALL;
  else if (nbind == OVERALL) {
    if (normals) currnormal = normals;
  }
  else if (normalcacheused && nbind == PER_VERTEX) {
    nbind = PER_VERTEX_INDEXED;
  }
  else if (normalcacheused && nbind == PER_TRIANGLE_INDEXED) {
    nbind = PER_TRIANGLE;
  }
  else if (normalcacheused && nbind == PER_STRIP_INDEXED) {
    nbind = PER_STRIP;
  }

  int texidx = 0;
  int matnr = 0;
  int normnr = 0;

  const int32_t * viptr = cindices;
  const int32_t * viendptr = viptr + numindices;
  int32_t v1, v2, v3;

  SoPrimitiveVertex vertex;
  SoPointDetail pointdetail;
  SoFaceDetail facedetail;

  vertex.setNormal(*currnormal);
  vertex.setDetail(&pointdetail);

  while (viptr < viendptr) {
    facedetail.setFaceIndex(0);

    v1 = *viptr++;
    v2 = *viptr++;
    v3 = *viptr++;
    assert(v1 >= 0 && v2 >= 0 && v3 >= 0);

    this->beginShape(action, TRIANGLE_STRIP, &facedetail);

    if (mbind == PER_VERTEX || mbind == PER_TRIANGLE || mbind == PER_STRIP) {
      pointdetail.setMaterialIndex(matnr);
      vertex.setMaterialIndex(matnr++);
    }
    else if (mbind == PER_VERTEX_INDEXED || mbind == PER_STRIP_INDEXED ||
             mbind == PER_TRIANGLE_INDEXED) {
      pointdetail.setMaterialIndex(*mindices);
      vertex.setMaterialIndex(*mindices++);
    }
    if (nbind == PER_VERTEX || nbind == PER_TRIANGLE || nbind == PER_STRIP) {
      pointdetail.setNormalIndex(normnr);
      currnormal = &normals[normnr++];
      vertex.setNormal(*currnormal);
    }
    else if (nbind == PER_VERTEX_INDEXED ||
             nbind == PER_TRIANGLE_INDEXED ||
             nbind == PER_STRIP_INDEXED) {
      pointdetail.setNormalIndex(*nindices);
      currnormal = &normals[*nindices++];
      vertex.setNormal(*currnormal);
    }
    if (dotextures) {
      if (tb.isFunction()) {
        vertex.setTextureCoords(tb.get(coords->get3(v1), *currnormal));
      }
      else {
        pointdetail.setTextureCoordIndex(tindices ? *tindices : texidx);
        vertex.setTextureCoords(tb.get(tindices ? *tindices++ : texidx++));
      }
    }
    pointdetail.setCoordinateIndex(v1);
    vertex.setPoint(coords->get3(v1));
    this->shapeVertex(&vertex);

    /* vertex 2 *********************************************************/
    if (mbind == PER_VERTEX) {
      pointdetail.setMaterialIndex(matnr);
      vertex.setMaterialIndex(matnr++);
    }
    else if (mbind == PER_VERTEX_INDEXED) {
      pointdetail.setMaterialIndex(*mindices);
      vertex.setMaterialIndex(*mindices++);
    }
    if (nbind == PER_VERTEX) {
      pointdetail.setNormalIndex(normnr);
      currnormal = &normals[normnr++];
      vertex.setNormal(*currnormal);
    }
    else if (nbind == PER_VERTEX_INDEXED) {
      pointdetail.setNormalIndex(*nindices);
      currnormal = &normals[*nindices++];
      vertex.setNormal(*currnormal);
    }

    if (dotextures) {
      if (tb.isFunction()) {
        vertex.setTextureCoords(tb.get(coords->get3(v2), *currnormal));
      }
      else {
        pointdetail.setTextureCoordIndex(tindices?*tindices:texidx);
        vertex.setTextureCoords(tb.get(tindices ? *tindices++ : texidx++));
      }
    }
    pointdetail.setCoordinateIndex(v2);
    vertex.setPoint(coords->get3(v2));
    this->shapeVertex(&vertex);

    // vertex 3
    if (mbind == PER_VERTEX) {
      pointdetail.setMaterialIndex(matnr);
      vertex.setMaterialIndex(matnr++);
    }
    else if (mbind == PER_VERTEX_INDEXED) {
      pointdetail.setMaterialIndex(*mindices);
      vertex.setMaterialIndex(*mindices++);
    }
    if (nbind == PER_VERTEX) {
      pointdetail.setNormalIndex(normnr);
      currnormal = &normals[normnr++];
      vertex.setNormal(*currnormal);
    }
    else if (nbind == PER_VERTEX_INDEXED) {
      pointdetail.setNormalIndex(*nindices);
      currnormal = &normals[*nindices++];
      vertex.setNormal(*currnormal);
    }

    if (dotextures) {
      if (tb.isFunction()) {
        vertex.setTextureCoords(tb.get(coords->get3(v3), *currnormal));
      }
      else {
        pointdetail.setTextureCoordIndex(tindices?*tindices:texidx);
        vertex.setTextureCoords(tb.get(tindices ? *tindices++ : texidx++));
      }
    }
    pointdetail.setCoordinateIndex(v3);
    vertex.setPoint(coords->get3(v3));
    this->shapeVertex(&vertex);
    facedetail.incFaceIndex();

    v1 = *viptr++;
    while (v1 >= 0) {
      if (mbind == PER_VERTEX || mbind == PER_TRIANGLE) {
        pointdetail.setMaterialIndex(matnr);
        vertex.setMaterialIndex(matnr++);
      }
      else if (mbind == PER_VERTEX_INDEXED || mbind == PER_TRIANGLE_INDEXED) {
        pointdetail.setMaterialIndex(*mindices);
        vertex.setMaterialIndex(*mindices++);
      }
      if (nbind == PER_VERTEX || nbind == PER_TRIANGLE) {
        pointdetail.setNormalIndex(normnr);
        currnormal = &normals[normnr++];
        vertex.setNormal(*currnormal);
      }
      else if (nbind == PER_VERTEX_INDEXED || nbind == PER_TRIANGLE_INDEXED) {
        pointdetail.setNormalIndex(*nindices);
        currnormal = &normals[*nindices++];
        vertex.setNormal(*currnormal);
      }

      if (dotextures) {
        if (tb.isFunction()) {
          vertex.setTextureCoords(tb.get(coords->get3(v1), *currnormal));
        }
        else {
          pointdetail.setTextureCoordIndex(tindices?*tindices:texidx);
          vertex.setTextureCoords(tb.get(tindices ? *tindices++ : texidx++));
        }
      }
      pointdetail.setCoordinateIndex(v1);
      vertex.setPoint(coords->get3(v1));
      this->shapeVertex(&vertex);
      facedetail.incFaceIndex();

      v1 = *viptr++;
    }
    this->endShape();
    facedetail.incPartIndex();

    if (mbind == PER_VERTEX_INDEXED || mbind == PER_TRIANGLE_INDEXED)
      mindices++;
    if (nbind == PER_VERTEX_INDEXED || nbind == PER_TRIANGLE_INDEXED)
      nindices++;
    if (tindices) tindices++;
  }
  if (this->vertexProperty.getValue()) {
    state->pop();
  }
}
