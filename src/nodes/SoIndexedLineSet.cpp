/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

/*!
  \class SoIndexedLineSet SoIndexedLineSet.h Inventor/nodes/SoIndexedLineSet.h
  \brief The SoIndexedLineSet class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/SbName.h>


#include <Inventor/caches/SoNormalCache.h>
#include <Inventor/misc/SoState.h>

#if !defined(COIN_EXCLUDE_SOMATERIALBUNDLE)
#include <Inventor/bundles/SoMaterialBundle.h>
#endif // !COIN_EXCLUDE_SOMATERIALBUNDLE

#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/misc/SoGL.h>
#include <GL/gl.h>
#endif // !COIN_EXCLUDE_SOGLRENDERACTION

#if !defined(COIN_EXCLUDE_SONORMALBINDINGELEMENT)
#include <Inventor/elements/SoNormalBindingElement.h>
#endif // !COIN_EXCLUDE_SONORMALBINDINGELEMENT
#if !defined(COIN_EXCLUDE_SOMATERIALBINDINGELEMENT)
#include <Inventor/elements/SoMaterialBindingElement.h>
#endif // !COIN_EXCLUDE_SOMATERIALBINDINGELEMENT
#if !defined(COIN_EXCLUDE_SOTEXTURECOORDINATEELEMENT)
#include <Inventor/elements/SoTextureCoordinateElement.h>
#endif // !COIN_EXCLUDE_SOTEXTURECOORDINATEELEMENT
#if !defined(COIN_EXCLUDE_SOLIGHTMODELELEMENT)
#include <Inventor/elements/SoLightModelElement.h>
#endif // !COIN_EXCLUDE_SOLIGHTMODELELEMENT
#if !defined(COIN_EXCLUDE_SOCOORDINATEELEMENT)
#include <Inventor/elements/SoCoordinateElement.h>
#endif // !COIN_EXCLUDE_SOCOORDINATEELEMENT
#if !defined(COIN_EXCLUDE_SONORMALELEMENT)
#include <Inventor/elements/SoNormalElement.h>
#endif // !COIN_EXCLUDE_SONORMALELEMENT
#if !defined(COIN_EXCLUDE_SOGLTEXTUREENABLEDELEMENT)
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#endif // !COIN_EXCLUDE_SOGLTEXTUREENABLEDELEMENT
#if !defined(COIN_EXCLUDE_SOGLSHAPEHINTSELEMENT)
#include <Inventor/elements/SoGLShapeHintsElement.h>
#endif // !COIN_EXCLUDE_SOSHAPEHINTSELEMENT
#if !defined(COIN_EXCLUDE_SOTEXTURECOORDINATEBINDINGELEMENT)
#include <Inventor/elements/SoTextureCoordinateBindingElement.h>
#endif // !COIN_EXCLUDE_SOTEXTURECOORDINATEBINDINGELEMENT
#if !defined(COIN_EXCLUDE_SODRAWSTYLEELEMENT)
#include <Inventor/elements/SoDrawStyleElement.h>
#endif
#if !defined(COIN_EXCLUDE_SOGLLIGHTMODELELEMENT)
#include <Inventor/elements/SoGLLightModelElement.h>
#endif // !COIN_EXCLUDE_SOGLLIGHTMODELELEMENT

#include <assert.h>

#include <Inventor/bundles/SoTextureCoordinateBundle.h>

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif

#include <GL/gl.h>


/*!
  \enum SoIndexedLineSet::Binding
  FIXME: write documentation for enum
*/
/*!
  \var SoIndexedLineSet::Binding SoIndexedLineSet::OVERALL
  FIXME: write documentation for enum definition
*/
/*!
  \var SoIndexedLineSet::Binding SoIndexedLineSet::PER_SEGMENT
  FIXME: write documentation for enum definition
*/
/*!
  \var SoIndexedLineSet::Binding SoIndexedLineSet::PER_SEGMENT_INDEXED
  FIXME: write documentation for enum definition
*/
/*!
  \var SoIndexedLineSet::Binding SoIndexedLineSet::PER_LINE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoIndexedLineSet::Binding SoIndexedLineSet::PER_LINE_INDEXED
  FIXME: write documentation for enum definition
*/
/*!
  \var SoIndexedLineSet::Binding SoIndexedLineSet::PER_VERTEX
  FIXME: write documentation for enum definition
*/
/*!
  \var SoIndexedLineSet::Binding SoIndexedLineSet::PER_VERTEX_INDEXED
  FIXME: write documentation for enum definition
*/


// *************************************************************************

//$ BEGIN TEMPLATE NodeSource(SoIndexedLineSet)
SoType SoIndexedLineSet::classTypeId = SoType::badType();

/*!
  Returns a new instance of the SoIndexedLineSet node class.
*/
void *
SoIndexedLineSet::createInstance(void)
{
  return new SoIndexedLineSet;
}

/*!
  Returns the unique type identifier for the SoIndexedLineSet class.
*/
SoType
SoIndexedLineSet::getClassTypeId(void)
{
  return SoIndexedLineSet::classTypeId;
}

/*!
  Returns type identifier for an object.
*/
SoType
SoIndexedLineSet::getTypeId(void) const
{
  return SoIndexedLineSet::classTypeId;
}
//$ END TEMPLATE NodeSource

/*!
  Constructor.
*/
SoIndexedLineSet::SoIndexedLineSet()
{
//$ BEGIN TEMPLATE NodeConstructor(SoIndexedLineSet)
  // Make sure the class has been initialized.
  assert(SoIndexedLineSet::classTypeId != SoType::badType());
//$ END TEMPLATE NodeConstructor
}

/*!
  Destructor.
*/
SoIndexedLineSet::~SoIndexedLineSet()
{
}

/*!
  Does initialization common for all objects of the
  SoIndexedLineSet class. This includes setting up the
  type system, among other things.
*/
void
SoIndexedLineSet::initClass(void)
{
//$ BEGIN TEMPLATE InitNodeSource(IndexedLineSet)
  // Make sure we only initialize once.
  assert(SoIndexedLineSet::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoIndexedLineSet::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "IndexedLineSet",
                       &SoIndexedLineSet::createInstance,
                       SoNode::nextActionMethodIndex++);
//$ END TEMPLATE InitNodeSource
}

/*!
  Clean out all statically allocated resources.
  This method is only useful for debugging purposes.
*/
void
SoIndexedLineSet::cleanClass(void)
{
}

/*!
  \internal
*/
int 
SoIndexedLineSet::numLines() const
{
  int i, n = coordIndex.getNum();
  int cnt = 0;
  for (i = 0; i < n ; i++) {
    if (coordIndex.getValues(0)[i] < 0) cnt++;
  }
  return cnt;
}

/*!
  \internal
*/
int 
SoIndexedLineSet::numLineSegments() const
{
  int i = 0, n = coordIndex.getNum();
  int cnt = 0;
  int tmpcnt;
  while (i < n) {
    tmpcnt = 0;
    // i < n not necessary if the array is guaranteed to be terminated
    // with -1.
    while (i < n && coordIndex.getValues(0)[i] >= 0) {
      tmpcnt++;
      i++;
    }
    cnt += tmpcnt - 1;
    i++;
  }
  return cnt;
}

/*!
  \internal
*/
SoIndexedLineSet::Binding 
SoIndexedLineSet::findNormalBinding(SoState * state)
{
  Binding binding = PER_VERTEX_INDEXED;
  
#if !defined(COIN_EXCLUDE_SONORMALBINDINGELEMENT)
  SoNormalBindingElement::Binding normbind =
    (SoNormalBindingElement::Binding) SoNormalBindingElement::get(state);
  
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
    binding = PER_SEGMENT;
    break;
  case SoNormalBindingElement::PER_PART_INDEXED:
    binding = PER_SEGMENT_INDEXED;
    break;
  case SoNormalBindingElement::PER_FACE:
    binding = PER_LINE;
    break;
  case SoNormalBindingElement::PER_FACE_INDEXED:
    binding = PER_LINE_INDEXED;
    break;
  default:
#if COIN_DEBUG
    SoDebugError::postWarning("SoIndexedLineSet::findNormalBinding",
			      "unknown normal binding setting");
#endif // COIN_DEBUG
    break;
  }
#endif // !COIN_EXCLUDE_SONORMALBINDINGELEMENT
  
  return binding;
}

/*!
  \internal
*/
SoIndexedLineSet::Binding 
SoIndexedLineSet::findMaterialBinding(SoState * state)
{
  Binding binding = OVERALL;
  
#if !defined(COIN_EXCLUDE_SOMATERIALBINDINGELEMENT)
  SoMaterialBindingElement::Binding matbind =
    (SoMaterialBindingElement::Binding) SoMaterialBindingElement::get(state);
  
  switch (matbind) {
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
    binding = PER_SEGMENT;
    break;
  case SoNormalBindingElement::PER_PART_INDEXED:
    binding = PER_SEGMENT_INDEXED;
    break;
  case SoNormalBindingElement::PER_FACE:
    binding = PER_LINE;
    break;
  case SoNormalBindingElement::PER_FACE_INDEXED:
    binding = PER_LINE_INDEXED;
    break;
  default:
#if COIN_DEBUG
    SoDebugError::postWarning("SoIndexedFaceSet::findNormalBinding",
			      "unknown normal binding setting");
#endif // COIN_DEBUG
    break;
  }
#endif // !COIN_EXCLUDE_SOMATERIALBINDINGELEMENT
  
  return binding;
}


#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
/*!
  FIXME: write function documentation
*/
void 
SoIndexedLineSet::GLRender(SoGLRenderAction * action)
{
  SoState * state = action->getState();

  if (this->vertexProperty.getValue()) {
    state->push();
    this->vertexProperty.getValue()->GLRender(action);
  }

  if (!this->shouldGLRender(action)) {
    if (this->vertexProperty.getValue())
      state->pop();
    return;
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
  SbBool doTextures;
  SbBool sendNormals;
  SbBool normalCacheUsed;

  getGLData(state, coords, normals, cindices, 
	    nindices, tindices, mindices, numindices, 
	    sendNormals, normalCacheUsed);

  if (normals == NULL) sendNormals = FALSE;
  
  SoTextureCoordinateBundle tb(action, TRUE, FALSE);
  doTextures = tb.needCoordinates();

  Binding tbind = PER_VERTEX_INDEXED; // most common
  if (doTextures) {
    if (SoTextureCoordinateBindingElement::get(state) ==
	SoTextureCoordinateBindingElement::PER_VERTEX) {
      tbind = PER_VERTEX;
      tindices = NULL; // just in case
    }
    else if (tindices == NULL) {
      tindices = cindices;
    }
  }

  if (!sendNormals) {
    nbind = OVERALL;
#if !defined(COIN_EXCLUDE_SOGLLIGHTMODELELEMENT)
    const SoGLLightModelElement * lm = (SoGLLightModelElement *)
      state->getConstElement(SoGLLightModelElement::getClassStackIndex());
    lm->forceSend(SoLightModelElement::BASE_COLOR);
#endif // !COIN_EXCLUDE_SOGLLIGHTMODELELEMENT
  }
  else if (nbind == OVERALL) {
    glNormal3fv((const GLfloat *)normals);
  }  
  SoMaterialBundle mb(action);
  mb.sendFirst(); // make sure we have the correct material
  
  SbBool drawPoints = FALSE;
#if !defined(COIN_EXCLUDE_SODRAWSTYLEELEMENT)
  drawPoints = SoDrawStyleElement::get(state) ==
    SoDrawStyleElement::POINTS;
#endif
  
#if !defined(COIN_EXCLUDE_SOGLSHAPEHINTSELEMENT)
  const SoGLShapeHintsElement * sh = (SoGLShapeHintsElement *)
    action->getState()->getConstElement(SoGLShapeHintsElement::getClassStackIndex());
  sh->forceSend(TRUE, FALSE, TRUE); // enable twoside lighting
#endif
  
  sogl_render_lineset((SoGLCoordinateElement *)coords,
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
		      doTextures?1:0,
		      drawPoints?1:0);

  if (this->vertexProperty.getValue()) {
    state->pop();
  }
}

/*!
  FIXME: write function documentation
*/
SbBool 
SoIndexedLineSet::willSetShapeHints(void) const
{
  return TRUE;
}

#endif // COIN_EXCLUDE_SOGLRENDERACTION

/*!
  FIXME: write function documentation
*/
SbBool 
SoIndexedLineSet::generateDefaultNormals(SoState * ,
					 SoNormalCache * nc)
{
  // not possible to generate normals for IndexedLineSet
  nc->set(0, NULL);
  return TRUE;
}


#if !defined(COIN_EXCLUDE_SOGETBOUNDINGBOXACTION)
/*!
  FIXME: write doc
*/
void
SoIndexedLineSet::getBoundingBox(SoGetBoundingBoxAction * action)
{
  inherited::getBoundingBox(action);
  // FIXME: tell cache that geometry contain lines
}
#endif // !COIN_EXCLUDE_SOGETBOUNDINGBOXACTION

#if !defined(COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION)
/*!
  FIXME: write doc
*/
void
SoIndexedLineSet::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION

#if !defined(COIN_EXCLUDE_SOACTION)
/*!
  FIXME: write doc
*/
void
SoIndexedLineSet::generatePrimitives(SoAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOACTION

#if !defined(COIN_EXCLUDE_SORAYPICKACTION)
/*!
  FIXME: write doc
*/
SoDetail *
SoIndexedLineSet::createLineSegmentDetail(SoRayPickAction * action,
					  const SoPrimitiveVertex * v1,
					  const SoPrimitiveVertex * v2,
					  SoPickedPoint * pp)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SORAYPICKACTION
