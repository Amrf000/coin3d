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
  \class SoIndexedShape SoIndexedShape.h Inventor/nodes/SoIndexedShape.h
  \brief The SoIndexedShape class is the superclass for all indexed vertex shapes.
  \ingroup nodes

  It holds four field for storing indices to coordinates, normals,
  materials and texture coordinates, and also has some convenience
  methods which can be used by subclasses.  
*/

#include <Inventor/nodes/SoIndexedShape.h>
#include <Inventor/nodes/SoSubNodeP.h>
#include <coindefs.h> // COIN_STUB()
#include <Inventor/actions/SoAction.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/elements/SoShapeHintsElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoTextureCoordinateBindingElement.h>
#include <Inventor/caches/SoNormalCache.h>
#include <Inventor/nodes/SoVertexProperty.h>

/*!
  \var SoMFInt32 SoIndexedShape::coordIndex
  Coordinate indices.
*/
/*!
  \var SoMFInt32 SoIndexedShape::materialIndex
  Material indices.
*/
/*!
  \var SoMFInt32 SoIndexedShape::normalIndex
  Normal indices.
*/
/*!
  \var SoMFInt32 SoIndexedShape::textureCoordIndex
  Texture coordinate indices.
*/


SO_NODE_ABSTRACT_SOURCE(SoIndexedShape);

/*!
  Constructor.
*/
SoIndexedShape::SoIndexedShape()
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoIndexedShape);

  SO_NODE_ADD_FIELD(coordIndex,(0));
  SO_NODE_ADD_FIELD(materialIndex,(-1));
  SO_NODE_ADD_FIELD(normalIndex,(-1));
  SO_NODE_ADD_FIELD(textureCoordIndex,(-1));
}

/*!
  Destructor.
*/
SoIndexedShape::~SoIndexedShape()
{
}

// doc from parent
void
SoIndexedShape::initClass()
{
  SO_NODE_INTERNAL_INIT_ABSTRACT_CLASS(SoIndexedShape);
}

/*!
  Overloaded to calculate bounding box of all indexed coordinates, 
  using the coordIndex field.
*/
void
SoIndexedShape::computeBBox(SoAction * action, SbBox3f & box,
                            SbVec3f & center)
{
  SoState * state = action->getState();

  const SoCoordinateElement *coordelem = SoCoordinateElement::getInstance(state);
  SoVertexProperty * vp = (SoVertexProperty *) this->vertexProperty.getValue();
  assert(!vp ||
         vp->getTypeId().isDerivedFrom(SoVertexProperty::getClassTypeId()));
  SbBool vpvtx = vp && (vp->vertex.getNum() > 0);

  int numCoords = vpvtx ?
    vp->vertex.getNum() :
    coordelem->getNum();

  if (vpvtx || coordelem->is3D()) {
    const SbVec3f * coords = vpvtx ?
      vp->vertex.getValues(0) :
      coordelem->getArrayPtr3();
    assert(coords);
    box.makeEmpty();
    const int32_t * ptr = coordIndex.getValues(0);
    const int32_t * endptr = ptr + coordIndex.getNum();
    while (ptr < endptr) {
      int idx = *ptr++;
      assert(idx < numCoords);
      if (idx >= 0) box.extendBy(coords[idx]);
    }
  }
  else {
    const SbVec4f * coords =
      coordelem->getArrayPtr4();
    assert(coords);
    const int32_t * ptr = coordIndex.getValues(0);
    const int32_t * endptr = ptr + coordIndex.getNum();
    while (ptr < endptr) {
      int idx = *ptr++;
      assert(idx < numCoords);
      if (idx >= 0) {
        SbVec4f tmp = coords[idx];
        box.extendBy(SbVec3f(tmp[0], tmp[1], tmp[2]));
      }
    }
  }

  if (!box.isEmpty()) center = box.getCenter();
}

/*!
  Returns whether texture coordinates should be indexed or not.
*/
SbBool
SoIndexedShape::areTexCoordsIndexed(SoAction * action)
{
  return SoTextureCoordinateBindingElement::get(action->getState()) ==
    SoTextureCoordinateBindingElement::PER_VERTEX_INDEXED;
}

/*!  
  Starting at index position \a startCoord, returns the number of
  indices until either the end of index array or a separator index (-1).  
*/
int
SoIndexedShape::getNumVerts(const int startCoord)
{
  const int32_t * ptr = coordIndex.getValues(0);
  const int32_t * endptr = ptr + coordIndex.getNum();
  ptr += startCoord;
  int cnt = 0;
  while (ptr < endptr && *ptr >= 0) cnt++, ptr++;
  return cnt;
}

/*!
  Not implemented. Probably only used internally in OIV.
  Let us know if you need this method and we'll implement it.
*/
void
SoIndexedShape::setupIndices(const int /* numParts */,
                             const int /* numFaces */,
                             const SbBool /* needNormals */,
                             const SbBool /* needTexCoords */)
{
  COIN_STUB();
}

/*!
  Not implemented. Probably only used internally in OIV.
  Let us know if you need this method and we'll implement it.
*/
const int32_t *
SoIndexedShape::getNormalIndices()
{
  COIN_STUB();
  return NULL;
}

/*!
  Not implemented. Probably only used internally in OIV.
  Let us know if you need this method and we'll implement it.
*/
const int32_t *
SoIndexedShape::getColorIndices()
{
  COIN_STUB();
  return NULL;
}

/*!
  Not implemented. Probably only used internally in OIV.
  Let us know if you need this method and we'll implement it.
*/
const int32_t *
SoIndexedShape::getTexCoordIndices()
{
  COIN_STUB();
  return NULL;
}

/*!
  Convenience method that will fetch data needed for rendering or
  generating primitives. Takes care of normal cache. This method
  is not part of the OIV API.
*/
SbBool
SoIndexedShape::getVertexData(SoState * state,
                              const SoCoordinateElement *& coords,
                              const SbVec3f *& normals,
                              const int32_t *& cindices,
                              const int32_t *& nindices,
                              const int32_t *& tindices,
                              const int32_t *& mindices,
                              int & numcindices,
                              const SbBool needNormals,
                              SbBool & normalCacheUsed)
{
  SoVertexShape::getVertexData(state, coords, normals, needNormals);
  
  cindices = this->coordIndex.getValues(0);
  numcindices = this->coordIndex.getNum();

  mindices = this->materialIndex.getValues(0);
  if (this->materialIndex.getNum() <= 0 || mindices[0] < 0) mindices = NULL;

  tindices = this->textureCoordIndex.getValues(0);
  if (this->textureCoordIndex.getNum() <= 0 || tindices[0] < 0) tindices = NULL;

  if (needNormals) {
    nindices = this->normalIndex.getValues(0);
    if (this->normalIndex.getNum() <= 0 || nindices[0] < 0) nindices = NULL;

    normalCacheUsed = FALSE;
    if (normals == NULL) {
      if (this->getNormalCache() == NULL ||
          !this->getNormalCache()->isValid(state)) {
          this->generateNormals(state);
      }
      normals = this->getNormalCache()->getNormals();
      nindices = this->getNormalCache()->getIndices();
      normalCacheUsed = TRUE;
    }
  }
  return TRUE;
}
