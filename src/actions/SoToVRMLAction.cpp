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
  \class SoToVRMLAction Inventor/include/SoToVRMLAction.h
  \brief The SoToVRMLAction class builds a new scene graph using only VRML 1.0 nodes.
  \ingroup actions

  FIXME: more class doc, describe the basics of how the conversion is
  done. 20020705 mortene.

  \sa SoToVRML2Action
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/SbName.h>
#include <Inventor/actions/SoToVRMLAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoNodes.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SbBSPTree.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/lists/SbList.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/lists/SoPathList.h>
#include <Inventor/lists/SoNodeList.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_VRML97
#include <Inventor/VRMLnodes/SoVRMLNodes.h>
#include <Inventor/VRMLnodes/SoVRML.h>
#endif // HAVE_VRML97

// FIXME: currently only VRML2-nodes to VRML1-nodes is
// supported. Inventor/Coin nodes must also be supported. It's quite
// easy to add support new nodes though. pederb, 2002-07-17

SO_ACTION_SOURCE(SoToVRMLAction);

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

class SoToVRMLActionP {
public:
  SoToVRMLActionP(SoToVRMLAction * master)
  {
    this->master = master;
    this->expandsofile = FALSE;
    this->urlname = "";
    this->writetexcoords = FALSE;
    this->expandtexture2node = FALSE;
    // FIXME: don't know if this is correct default value. 20020705 mortene.
    this->keepunknownnodes = TRUE;
    this->convertinlinenodes = TRUE;
    this->conditionalconversion = FALSE;
    // FIXME: don't know if this is correct default value. 20020705 mortene.
    this->isverbose = FALSE;

    this->nodefuse = FALSE; // for optimizing bad scene graphs

    this->bsptree = NULL;
    this->bsptreetex = NULL;
    this->bsptreenormal = NULL;
    this->coordidx = NULL;
    this->normalidx = NULL;
    this->texidx = NULL;
    this->coloridx = NULL;
    this->vrmlpath = NULL;
    this->vrmlroot = NULL;
  }

  void init(void) {
    if (this->vrmlpath) {
      this->vrmlpath->unref();
    }
    this->vrmlpath = (SoFullPath*) new SoPath;
    this->vrmlpath->ref();

    if (this->vrmlroot) {
      this->vrmlroot->unref();
    }
    this->vrmlroot = new SoSeparator;
    this->vrmlroot->ref();
    this->vrmlpath->setHead(this->vrmlroot);
  }

  SoToVRMLAction * master;
  SbBool expandsofile;
  SbString urlname;
  SbBool writetexcoords;
  SbBool expandtexture2node;
  SbBool keepunknownnodes;
  SbBool convertinlinenodes;
  SbBool conditionalconversion;
  SbBool isverbose;
  SbBool nodefuse;
  SoCallbackAction cbaction;
  SoSearchAction searchaction;
  SoFullPath * vrmlpath;
  SoSeparator * vrmlroot;

  SbBSPTree * bsptree;
  SbBSPTree * bsptreetex;
  SbBSPTree * bsptreenormal;

  SbList <int32_t> * coordidx;
  SbList <int32_t> * normalidx;
  SbList <int32_t> * texidx;
  SbList <int32_t> * coloridx;

  static SoCallbackAction::Response pop_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response push_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response post_primitives_cb(void *, SoCallbackAction *, const SoNode *);
  static void triangle_cb(void * userdata, SoCallbackAction * action,
                          const SoPrimitiveVertex * v1,
                          const SoPrimitiveVertex * v2,
                          const SoPrimitiveVertex * v3);
  static SoCallbackAction::Response unsupported_cb(void *, SoCallbackAction *, const SoNode *);
  SoNode * search_for_node(SoNode * root, const SbName & name, const SoType & type);
  SoGroup * get_current_tail(void);
  SoMaterial * find_or_create_material(void);
  void init_gen(const SbBool color);

#ifdef HAVE_VRML97
  static SoCallbackAction::Response vrmlshape_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmltransform_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmldirlight_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlpointlight_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlspotlight_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlpixeltex_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlimagetex_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmllod_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlmaterial_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlswitch_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmltextransform_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlviewpoint_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlbox_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlcone_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlcylinder_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlifs_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlils_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlsphere_cb(void *, SoCallbackAction *, const SoNode *);

  static SoCallbackAction::Response vrmlelevation_cb(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response vrmlextrusion_cb(void *, SoCallbackAction *, const SoNode *);
#endif // HAVE_VRML97
};

#endif // DOXYGEN_SKIP_THIS


#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->master)
#define THISP(p) ((SoToVRMLActionP*)p)

// *************************************************************************

// Overridden from parent class.
void
SoToVRMLAction::initClass(void)
{
  SO_ACTION_INIT_CLASS(SoToVRMLAction, SoAction);
}


/*!
  Constructor.
*/

SoToVRMLAction::SoToVRMLAction(void)
{
  PRIVATE(this) = new SoToVRMLActionP(this);

#define ADD_PRE_CB(_node_, _cb_) \
  PRIVATE(this)->cbaction.addPreCallback(_node_::getClassTypeId(), SoToVRMLActionP::_cb_, PRIVATE(this))
#define ADD_POST_CB(_node_, _cb_) \
  PRIVATE(this)->cbaction.addPostCallback(_node_::getClassTypeId(), SoToVRMLActionP::_cb_, PRIVATE(this))
#define ADD_UNSUPPORTED(_node_) \
  PRIVATE(this)->cbaction.addPreCallback(_node_::getClassTypeId(), SoToVRMLActionP::unsupported_cb, PRIVATE(this))

#ifdef HAVE_VRML97
  ADD_PRE_CB(SoVRMLShape, vrmlshape_cb);
  ADD_POST_CB(SoVRMLShape, pop_cb);
  ADD_PRE_CB(SoVRMLGroup, push_cb);
  ADD_POST_CB(SoVRMLGroup, pop_cb);
  ADD_PRE_CB(SoVRMLTransform, vrmltransform_cb);
  ADD_POST_CB(SoVRMLTransform, pop_cb);
  ADD_PRE_CB(SoVRMLDirectionalLight, vrmldirlight_cb);
  ADD_PRE_CB(SoVRMLPointLight, vrmlpointlight_cb);
  ADD_PRE_CB(SoVRMLSpotLight, vrmlspotlight_cb);
  ADD_PRE_CB(SoVRMLPixelTexture, vrmlpixeltex_cb);
  ADD_PRE_CB(SoVRMLImageTexture, vrmlimagetex_cb);
  ADD_PRE_CB(SoVRMLLOD, vrmllod_cb);
  ADD_POST_CB(SoVRMLLOD, pop_cb);
  ADD_PRE_CB(SoVRMLMaterial, vrmlmaterial_cb);
  ADD_PRE_CB(SoVRMLSwitch, vrmlswitch_cb);
  ADD_POST_CB(SoVRMLSwitch, pop_cb);
  ADD_PRE_CB(SoVRMLTextureTransform, vrmltextransform_cb);
  ADD_PRE_CB(SoVRMLViewpoint, vrmlviewpoint_cb);

  // misc geometry nodes
  ADD_PRE_CB(SoVRMLBox, vrmlbox_cb);
  ADD_PRE_CB(SoVRMLCone, vrmlcone_cb);
  ADD_PRE_CB(SoVRMLCylinder, vrmlcylinder_cb);
  ADD_PRE_CB(SoVRMLIndexedFaceSet, vrmlifs_cb);
  ADD_PRE_CB(SoVRMLIndexedLineSet, vrmlils_cb);
  ADD_PRE_CB(SoVRMLSphere, vrmlsphere_cb);

  // unsupported node
  ADD_UNSUPPORTED(SoVRMLInline);  // convert to WWWInline
  ADD_UNSUPPORTED(SoVRMLMovieTexture);
  ADD_UNSUPPORTED(SoVRMLAnchor); // convert to WWWAnchor
  ADD_UNSUPPORTED(SoVRMLAudioClip);
  ADD_UNSUPPORTED(SoVRMLBackground);
  ADD_UNSUPPORTED(SoVRMLCylinderSensor);
  ADD_UNSUPPORTED(SoVRMLColorInterpolator);
  ADD_UNSUPPORTED(SoVRMLCoordinateInterpolator);
  ADD_UNSUPPORTED(SoVRMLFog);
  ADD_UNSUPPORTED(SoVRMLFontStyle);
  ADD_UNSUPPORTED(SoVRMLNavigationInfo);
  ADD_UNSUPPORTED(SoVRMLNormalInterpolator);
  ADD_UNSUPPORTED(SoVRMLPositionInterpolator);
  ADD_UNSUPPORTED(SoVRMLProximitySensor);
  ADD_UNSUPPORTED(SoVRMLScalarInterpolator);
  ADD_UNSUPPORTED(SoVRMLScript);
  ADD_UNSUPPORTED(SoVRMLSound);
  ADD_UNSUPPORTED(SoVRMLSphereSensor);
  ADD_UNSUPPORTED(SoVRMLText);
  ADD_UNSUPPORTED(SoVRMLTimeSensor);
  ADD_UNSUPPORTED(SoVRMLTouchSensor);
  ADD_UNSUPPORTED(SoVRMLVisibilitySensor);
  ADD_UNSUPPORTED(SoVRMLWorldInfo);  // convert to Info

  // these are converted to IndexedFaceSet
  ADD_PRE_CB(SoVRMLExtrusion, vrmlextrusion_cb);
  ADD_POST_CB(SoVRMLExtrusion, post_primitives_cb);
  ADD_PRE_CB(SoVRMLElevationGrid, vrmlelevation_cb);
  ADD_POST_CB(SoVRMLElevationGrid, post_primitives_cb);
  PRIVATE(this)->cbaction.addTriangleCallback(SoVRMLElevationGrid::getClassTypeId(),
                                              SoToVRMLActionP::triangle_cb, PRIVATE(this));
  PRIVATE(this)->cbaction.addTriangleCallback(SoVRMLExtrusion::getClassTypeId(),
                                              SoToVRMLActionP::triangle_cb, PRIVATE(this));
#endif // HAVE_VRML97

#undef ADD_PRE_CB
#undef ADD_POST_CB
#undef ADD_UNSUPPORTED
}

/*!
  The destructor.
*/

SoToVRMLAction::~SoToVRMLAction(void)
{
  if (PRIVATE(this)->vrmlpath) {
    PRIVATE(this)->vrmlpath->unref();
  }
  if (PRIVATE(this)->vrmlroot) {
    PRIVATE(this)->vrmlroot->unref();
  }

  delete PRIVATE(this);
}

// Documented in superclass.
void
SoToVRMLAction::apply(SoNode * root)
{
  PRIVATE(this)->init();
  PRIVATE(this)->cbaction.apply(root);
}

// Documented in superclass.
void
SoToVRMLAction::apply(SoPath * path)
{
  PRIVATE(this)->init();
  PRIVATE(this)->cbaction.apply(path);
}

// Documented in superclass.
void
SoToVRMLAction::apply(const SoPathList & pathlist, SbBool obeysrules)
{
  PRIVATE(this)->init();
  PRIVATE(this)->cbaction.apply(pathlist, obeysrules);
}

// Documented in superclass.
void
SoToVRMLAction::beginTraversal(SoNode * node)
{
  assert(0 && "should never get here");
}

SoNode *
SoToVRMLAction::getVRMLSceneGraph(void) const
{
  return PRIVATE(this)->vrmlroot;
}

void
SoToVRMLAction::expandSoFile(SbBool flag)
{
  PRIVATE(this)->expandsofile = flag;
}

SbBool
SoToVRMLAction::areSoFileExpanded(void) const
{
  return PRIVATE(this)->expandsofile;
}

void
SoToVRMLAction::setUrlName(const SbString name)
{
  PRIVATE(this)->urlname = name;
}

SbString
SoToVRMLAction::getUrlName(void) const
{
  return PRIVATE(this)->urlname;
}

void
SoToVRMLAction::writeTexCoords(SbBool flag)
{
  PRIVATE(this)->writetexcoords = flag;
}

SbBool
SoToVRMLAction::areTexCoordWritten(void) const
{
  return PRIVATE(this)->writetexcoords;
}

void
SoToVRMLAction::expandTexture2Node(SbBool flag)
{
  PRIVATE(this)->expandtexture2node = flag;
}

SbBool
SoToVRMLAction::areTexture2NodeExpanded(void) const
{
  return PRIVATE(this)->expandtexture2node;
}

void
SoToVRMLAction::keepUnknownNodes(SbBool flag)
{
  PRIVATE(this)->keepunknownnodes = flag;
}

SbBool
SoToVRMLAction::areUnknownNodeKept(void) const
{
  return PRIVATE(this)->keepunknownnodes;
}

void
SoToVRMLAction::convertInlineNodes(SbBool flag)
{
  PRIVATE(this)->convertinlinenodes = flag;
}

SbBool
SoToVRMLAction::doConvertInlineNodes(void) const
{
  return PRIVATE(this)->convertinlinenodes;
}

void
SoToVRMLAction::conditionalConversion(SbBool flag)
{
  PRIVATE(this)->conditionalconversion = flag;
}

SbBool
SoToVRMLAction::doConditionalConversion(void) const
{
  return PRIVATE(this)->conditionalconversion;
}

void
SoToVRMLAction::setVerbosity(SbBool flag)
{
  PRIVATE(this)->isverbose = flag;
}

SbBool
SoToVRMLAction::isVerbose(void) const
{
  return PRIVATE(this)->isverbose;
}

SoNode *
SoToVRMLActionP::search_for_node(SoNode * root, const SbName & name, const SoType & type)
{
  SoNodeList mylist;
  if (name == SbName("")) return NULL;

  mylist.truncate(0);
  int num = SoNode::getByName(name, mylist);
  int cnt = 0;
  SoNode * retnode = NULL;
  for (int i = 0; i < num; i++) {
    SoNode * node = mylist[i];
    if (node->getTypeId() == type) {
      retnode = node;
      cnt++;
    }
  }

  // if there is only one node with that name, return it
  if (retnode && cnt == 1) return retnode;
  if (!retnode) return NULL;

  this->searchaction.setSearchingAll(TRUE);
  this->searchaction.setName(name);
  this->searchaction.setType(type);
  this->searchaction.setInterest(SoSearchAction::LAST);
  this->searchaction.setFind(SoSearchAction::TYPE|SoSearchAction::NAME);
  this->searchaction.apply(root);
  SoNode * tail = NULL;
  SoFullPath * path = (SoFullPath*) this->searchaction.getPath();
  if (path) {
    tail = path->getTail();
  }
  this->searchaction.reset();
  return tail;
}

SoGroup *
SoToVRMLActionP::get_current_tail(void)
{
  SoNode * node = this->vrmlpath->getTail();
  assert(node->isOfType(SoGroup::getClassTypeId()));
  return (SoGroup*) node;
}

SoMaterial *
SoToVRMLActionP::find_or_create_material(void)
{
  SoMaterial * mat = NULL;
  SoGroup * tail = this->get_current_tail();

  int num = tail->getNumChildren();
  while (--num >= 0 && mat == NULL) {
    SoNode * node = tail->getChild(num);
    if (node->isOfType(SoMaterial::getClassTypeId())) {
      mat = (SoMaterial*) node;
    }
  }
  if (mat == NULL) {
    mat = new SoMaterial;
    tail->addChild(mat);
  }
  return mat;
}

SoCallbackAction::Response
SoToVRMLActionP::push_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoToVRMLActionP * thisp = (SoToVRMLActionP*) closure;

  SoSeparator * newsep = new SoSeparator;
  SoGroup * prevgroup = THISP(closure)->get_current_tail();
  prevgroup->addChild(newsep);
  thisp->vrmlpath->append(newsep);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::pop_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  THISP(closure)->vrmlpath->pop();
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::unsupported_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoInfo * info = new SoInfo;
  SbString str;
  str.sprintf("Unsupported node: %s",
              node->getTypeId().getName().getString());
  info->string = str;
  THISP(closure)->get_current_tail()->addChild(info);
  return SoCallbackAction::CONTINUE;
}

void
SoToVRMLActionP::init_gen(const SbBool color)
{
  SbBool dotex = FALSE;
  SoGroup * tail = this->get_current_tail();
  const int n = tail->getNumChildren();
  for (int i = 0; i < n; i++) {
    if (tail->getChild(i)->isOfType(SoTexture2::getClassTypeId())) {
      dotex = TRUE;
      break;
    }
  }

  this->bsptree = new SbBSPTree;
  if (dotex) this->bsptreetex = new SbBSPTree;
  this->bsptreenormal = new SbBSPTree;

  this->coordidx = new SbList <int>;
  this->normalidx = new SbList <int>;
  if (dotex) this->texidx = new SbList <int>;
  if (color) this->coloridx = new SbList <int>;
}

SoCallbackAction::Response
SoToVRMLActionP::post_primitives_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoToVRMLActionP * thisp = (SoToVRMLActionP*) closure;

  int i, n;
  SoGroup * tail = thisp->get_current_tail();
  SoCoordinate3 * coord = new SoCoordinate3;
  coord->point.setValues(0, thisp->bsptree->numPoints(),
                         thisp->bsptree->getPointsArrayPtr());
  tail->addChild(coord);

  SoIndexedFaceSet * ifs = new SoIndexedFaceSet;
  SoNormal * normal = new SoNormal;
  normal->vector.setValues(0, thisp->bsptreenormal->numPoints(),
                           thisp->bsptreenormal->getPointsArrayPtr());
  tail->addChild(normal);

  ifs->coordIndex.setValues(0, thisp->coordidx->getLength(),
                            thisp->coordidx->getArrayPtr());
  ifs->normalIndex.setValues(0, thisp->normalidx->getLength(),
                             thisp->normalidx->getArrayPtr());
  if (thisp->texidx) {
    SoTextureCoordinate2 * tex = new SoTextureCoordinate2;
    ifs->textureCoordIndex.setValues(0, thisp->texidx->getLength(),
                                     thisp->texidx->getArrayPtr());
    tail->addChild(tex);
    n = thisp->bsptreetex->numPoints();
    tex->point.setNum(n);
    SbVec2f * ptr = tex->point.startEditing();
    for (int i = 0; i < n; i++) {
      SbVec3f p = thisp->bsptreetex->getPoint(i);
      ptr[i] = SbVec2f(p[0], p[1]);
    }
    tex->point.finishEditing();
  }

  if (thisp->coloridx) {
    SoMaterialBinding * bind = new SoMaterialBinding;
    bind->value = SoMaterialBinding::PER_VERTEX_INDEXED;
    tail->addChild(bind);
    ifs->materialIndex.setValues(0, thisp->coloridx->getLength(),
                                 thisp->coloridx->getArrayPtr());
  }

  tail->addChild(ifs);

  delete thisp->bsptree; thisp->bsptree = NULL;
  delete thisp->bsptreetex; thisp->bsptreetex = NULL;
  delete thisp->bsptreenormal; thisp->bsptreenormal = NULL;

  delete thisp->coordidx; thisp->coordidx = NULL;
  delete thisp->normalidx; thisp->normalidx = NULL;
  delete thisp->texidx; thisp->texidx = NULL;
  delete thisp->coloridx; thisp->coloridx = NULL;

  return SoCallbackAction::CONTINUE;
}

void
SoToVRMLActionP::triangle_cb(void * closure, SoCallbackAction * action,
                             const SoPrimitiveVertex * v1,
                             const SoPrimitiveVertex * v2,
                             const SoPrimitiveVertex * v3)
{
  SoToVRMLActionP * thisp = (SoToVRMLActionP*) closure;
  assert(thisp->bsptree);
  assert(thisp->bsptreenormal);

  SoPrimitiveVertex const * const arr[3] = {v1, v2, v3};
  for (int i = 0; i < 3; i++) {
    const SoPrimitiveVertex * v = arr[i];
    thisp->coordidx->append(thisp->bsptree->addPoint(v->getPoint()));
    thisp->normalidx->append(thisp->bsptreenormal->addPoint(v->getNormal()));
    if (thisp->texidx) {
      assert(thisp->bsptreetex);
      const SbVec4f & tc = v->getTextureCoords();
      thisp->texidx->append(thisp->bsptreetex->addPoint(SbVec3f(tc[0], tc[1], 0.0f)));
    }
    if (thisp->coloridx) thisp->coloridx->append(v->getMaterialIndex());
  }
  thisp->coordidx->append(-1);
  thisp->normalidx->append(-1);
  if (thisp->texidx) thisp->texidx->append(-1);
  if (thisp->coloridx) thisp->coloridx->append(-1);
}

#ifdef HAVE_VRML97

SoCallbackAction::Response
SoToVRMLActionP::vrmlshape_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  push_cb(closure, action, node);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmltransform_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  push_cb(closure, action, node);
  const SoVRMLTransform * oldt = (const SoVRMLTransform*) node;
  SoTransform * newt = new SoTransform;

  newt->translation = oldt->translation.getValue();
  newt->rotation = oldt->rotation.getValue();
  newt->scaleFactor = oldt->scale.getValue();
  newt->scaleOrientation = oldt->scaleOrientation.getValue();
  newt->center = oldt->center.getValue();
  THISP(closure)->get_current_tail()->addChild(newt);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmldirlight_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  return unsupported_cb(closure, action, node);
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlpointlight_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  return unsupported_cb(closure, action, node);
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlspotlight_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  return unsupported_cb(closure, action, node);
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlpixeltex_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoTexture2 * tex = new SoTexture2;
  const SoVRMLPixelTexture * oldtex = (const SoVRMLPixelTexture*) node;
  SbVec2s size;
  int nc;
  const unsigned char * bytes = oldtex->image.getValue(size, nc);
  tex->image.setValue(size, nc, bytes);
  THISP(closure)->get_current_tail()->addChild(tex);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlimagetex_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoTexture2 * tex = new SoTexture2;
  const SoVRMLImageTexture * oldtex = (const SoVRMLImageTexture*) node;
  if (oldtex->url.getNum()) {
    tex->filename = oldtex->url[0];
  }
  THISP(closure)->get_current_tail()->addChild(tex);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmllod_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoLOD * lod = new SoLOD;
  const SoVRMLLOD * oldlod = (const SoVRMLLOD*) node;
  lod->center = oldlod->center.getValue();
  lod->range.setValues(0, oldlod->range.getNum(),
                       oldlod->range.getValues(0));
  THISP(closure)->get_current_tail()->addChild(lod);
  THISP(closure)->vrmlpath->append(lod);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlmaterial_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoMaterial * mat = new SoMaterial;
  const SoVRMLMaterial * oldmat = (const SoVRMLMaterial*) node;
  SbColor diffuse = oldmat->diffuseColor.getValue();
  mat->diffuseColor = diffuse;
  diffuse *= oldmat->ambientIntensity.getValue();
  mat->ambientColor = diffuse;

  mat->emissiveColor = oldmat->emissiveColor.getValue();
  mat->specularColor = oldmat->specularColor.getValue();
  mat->shininess = oldmat->shininess.getValue();
  mat->transparency = oldmat->transparency.getValue();

  THISP(closure)->get_current_tail()->addChild(mat);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlswitch_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoSwitch * sw = new SoSwitch;
  const SoVRMLSwitch * oldsw = (const SoVRMLSwitch*) node;
  sw->whichChild = oldsw->whichChoice.getValue();
  THISP(closure)->get_current_tail()->addChild(sw);
  THISP(closure)->vrmlpath->append(sw);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmltextransform_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  return unsupported_cb(closure, action, node);
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlviewpoint_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  return unsupported_cb(closure, action, node);
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlbox_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoCube * cube = new SoCube;
  const SoVRMLBox * box = (const SoVRMLBox*) node;
  cube->width = box->size.getValue()[0];
  cube->height = box->size.getValue()[1];
  cube->depth = box->size.getValue()[2];
  THISP(closure)->get_current_tail()->addChild(cube);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlcone_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoCone * cone = new SoCone;
  const SoVRMLCone * oldcone = (const SoVRMLCone*) node;
  cone->bottomRadius = oldcone->bottomRadius.getValue();
  cone->height = oldcone->height.getValue();

  int parts = 0;
  if (oldcone->bottom.getValue()) parts |= SoCone::BOTTOM;
  if (oldcone->side.getValue()) parts |= SoCone::SIDES;
  cone->parts = (SoCone::Part) parts;
  THISP(closure)->get_current_tail()->addChild(cone);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlcylinder_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoCylinder * cyl = new SoCylinder;
  const SoVRMLCylinder * oldcyl = (const SoVRMLCylinder*) node;
  cyl->radius = oldcyl->radius.getValue();
  cyl->height = oldcyl->height.getValue();
  int parts = 0;
  if (oldcyl->side.getValue()) parts |= SoCylinder::SIDES;
  if (oldcyl->top.getValue()) parts |= SoCylinder::TOP;
  if (oldcyl->bottom.getValue()) parts |= SoCylinder::BOTTOM;
  cyl->parts = (SoCylinder::Part) parts;
  THISP(closure)->get_current_tail()->addChild(cyl);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlifs_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  const SoVRMLIndexedFaceSet * oldifs = (const SoVRMLIndexedFaceSet*) node;

  if (oldifs->coordIndex.getNum() == 0 ||
      oldifs->coordIndex[0] < 0)
    return SoCallbackAction::CONTINUE;

  SoToVRMLActionP * thisp = (SoToVRMLActionP*) closure;

  SoIndexedFaceSet * ifs = new SoIndexedFaceSet;

  SoVRMLColor * color = (SoVRMLColor*) oldifs->color.getValue();
  SoVRMLCoordinate * coord = (SoVRMLCoordinate*) oldifs->coord.getValue();
  SoVRMLNormal * normal = (SoVRMLNormal*) oldifs->normal.getValue();
  SoVRMLTextureCoordinate * texcoord = (SoVRMLTextureCoordinate*) oldifs->texCoord.getValue();

  SoShapeHints * sh = new SoShapeHints;
  sh->creaseAngle = oldifs->creaseAngle.getValue();
  sh->vertexOrdering = oldifs->ccw.getValue() ?
    SoShapeHints::COUNTERCLOCKWISE : SoShapeHints::CLOCKWISE;
  sh->shapeType = oldifs->solid.getValue() ?
    SoShapeHints::SOLID : SoShapeHints::UNKNOWN_SHAPE_TYPE;
  sh->faceType = oldifs->convex.getValue() ?
    SoShapeHints::CONVEX : SoShapeHints::UNKNOWN_FACE_TYPE;

  SoGroup * tail = thisp->get_current_tail();
  tail->addChild(sh);

  if (coord) {
    SbName name = coord->getName();
    SoCoordinate3 * newcoord = (SoCoordinate3*)
      thisp->search_for_node(thisp->vrmlpath->getHead(),
                             name,
                             SoCoordinate3::getClassTypeId());
    if (!newcoord) {
      newcoord = new SoCoordinate3;
      newcoord->setName(name);
      newcoord->point.setValues(0, coord->point.getNum(),
                                coord->point.getValues(0));
    }
    tail->addChild(newcoord);
  }

  if (normal) {
    if (oldifs->normalPerVertex.getValue() != TRUE) {
      SoNormalBinding * bind = new SoNormalBinding;
      if (oldifs->normalIndex.getNum()) {
        bind->value = SoMaterialBinding::PER_FACE_INDEXED;
      }
      else bind->value = SoMaterialBinding::PER_FACE;
      tail->addChild(bind);
    }
    SbName name = normal->getName();
    SoNormal * newnormal =
      (SoNormal*) thisp->search_for_node(thisp->vrmlpath->getHead(),
                                         name,
                                         SoNormal::getClassTypeId());
    if (!newnormal) {
      newnormal = new SoNormal;
      newnormal->setName(name);
      newnormal->vector.setValues(0, normal->vector.getNum(),
                                  normal->vector.getValues(0));
    }
    tail->addChild(newnormal);
  }
  if (color) {
    SoMaterialBinding * bind = new SoMaterialBinding;
    if (oldifs->colorPerVertex.getValue()) {
      bind->value = SoMaterialBinding::PER_VERTEX_INDEXED;
    }
    else {
      if (oldifs->colorIndex.getNum()) {
        bind->value = SoMaterialBinding::PER_FACE_INDEXED;
      }
      else {
        bind->value = SoMaterialBinding::PER_FACE;
      }
      tail->addChild(bind);
    }

    SoMaterial * mat = thisp->find_or_create_material();
    mat->diffuseColor.setValues(0, color->color.getNum(),
                                color->color.getValues(0));
  }
  if (texcoord) {
    SbName name = texcoord->getName();
    SoTextureCoordinate2 * newtc = (SoTextureCoordinate2*)
      thisp->search_for_node(thisp->vrmlpath->getHead(),
                             name,
                             SoTextureCoordinate2::getClassTypeId());
    if (!newtc) {
      newtc = new SoTextureCoordinate2;
      newtc->setName(name);
      newtc->point.setValues(0, texcoord->point.getNum(),
                             texcoord->point.getValues(0));
    }
    tail->addChild(newtc);
  }

  ifs->coordIndex.setValues(0, oldifs->coordIndex.getNum(),
                            oldifs->coordIndex.getValues(0));
  if (oldifs->texCoordIndex.getNum()) {
    ifs->textureCoordIndex.setValues(0, oldifs->texCoordIndex.getNum(),
                                     oldifs->texCoordIndex.getValues(0));
  }
  if (oldifs->colorIndex.getNum()) {
    ifs->materialIndex.setValues(0, oldifs->colorIndex.getNum(),
                                 oldifs->colorIndex.getValues(0));
  }
  if (oldifs->normalIndex.getNum()) {
    ifs->normalIndex.setValues(0, oldifs->normalIndex.getNum(),
                               oldifs->normalIndex.getValues(0));
  }
  tail->addChild(ifs);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlils_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoToVRMLActionP * thisp = (SoToVRMLActionP*) closure;

  const SoVRMLIndexedLineSet * oldils = (const SoVRMLIndexedLineSet*) node;

  if (oldils->coordIndex.getNum() == 0 ||
      oldils->coordIndex[0] < 0) return SoCallbackAction::CONTINUE;

  SoIndexedLineSet * ils = new SoIndexedLineSet;

  SoVRMLColor * color = (SoVRMLColor*) oldils->color.getValue();
  SoVRMLCoordinate * coord = (SoVRMLCoordinate*) oldils->coord.getValue();
  SoGroup * tail = thisp->get_current_tail();

  SoCoordinate3 * newcoord = NULL;

  if (coord) {
    if (thisp->nodefuse) {
      newcoord = new SoCoordinate3;
    }
    else {
      SbName name = coord->getName();
      newcoord = (SoCoordinate3*)
        thisp->search_for_node(thisp->vrmlpath->getHead(),
                               name,
                               SoCoordinate3::getClassTypeId());
      if (!newcoord) {
        newcoord = new SoCoordinate3;
        newcoord->setName(name);
        newcoord->point.setValues(0, coord->point.getNum(),
                                  coord->point.getValues(0));
      }
    }
    tail->addChild(newcoord);
  }

  if (color) {
    SoMaterialBinding * bind = new SoMaterialBinding;
    if (oldils->colorPerVertex.getValue()) {
      bind->value = SoMaterialBinding::PER_VERTEX_INDEXED;
    }
    else {
      if (oldils->colorIndex.getNum()) {
        bind->value = SoMaterialBinding::PER_FACE_INDEXED;
      }
      else {
        bind->value = SoMaterialBinding::PER_FACE;
      }
      tail->addChild(bind);
    }

    SoMaterial * mat = thisp->find_or_create_material();
    mat->diffuseColor.setValues(0, color->color.getNum(),
                                color->color.getValues(0));
  }

  if (thisp->nodefuse && coord) {
    SbBSPTree bsp;
    int n = oldils->coordIndex.getNum();
    const int32_t * src = oldils->coordIndex.getValues(0);

    const SbVec3f * c = coord->point.getValues(0);

    ils->coordIndex.setNum(n);
    int32_t * dst = ils->coordIndex.startEditing();

    for (int i = 0; i < n; i++) {
      int idx = src[i];
      if (idx >= 0) {
        dst[i] = bsp.addPoint(c[idx]);
      }
      else dst[i] = -1;
    }
    ils->coordIndex.finishEditing();
    newcoord->point.setValues(0, bsp.numPoints(),
                              bsp.getPointsArrayPtr());

  }
  else {
    ils->coordIndex.setValues(0, oldils->coordIndex.getNum(),
                              oldils->coordIndex.getValues(0));
  }
  if (oldils->colorIndex.getNum()) {
    ils->materialIndex.setValues(0, oldils->colorIndex.getNum(),
                                 oldils->colorIndex.getValues(0));
  }
  tail->addChild(ils);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlsphere_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoSphere * sphere = new SoSphere;
  const SoVRMLSphere * oldsphere = (const SoVRMLSphere*) node;
  sphere->radius = oldsphere->radius.getValue();
  THISP(closure)->get_current_tail()->addChild(sphere);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlelevation_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoToVRMLActionP * thisp = (SoToVRMLActionP*) closure;

  SoGroup * tail = thisp->get_current_tail();

  const SoVRMLElevationGrid * grid = (const SoVRMLElevationGrid*) node;
  SoShapeHints * sh = new SoShapeHints;
  sh->creaseAngle = grid->creaseAngle.getValue();
  sh->vertexOrdering = grid->ccw.getValue() ?
    SoShapeHints::COUNTERCLOCKWISE : SoShapeHints::CLOCKWISE;
  sh->shapeType = grid->solid.getValue() ?
    SoShapeHints::SOLID : SoShapeHints::UNKNOWN_SHAPE_TYPE;
  sh->faceType = SoShapeHints::CONVEX;
  tail->addChild(sh);

  SoVRMLColor * color = (SoVRMLColor*) grid->color.getValue();

  if (color) {
    SoMaterial * mat = thisp->find_or_create_material();
    mat->diffuseColor.setValues(0, color->color.getNum(),
                                color->color.getValues(0));
  }

  thisp->init_gen(color != NULL);
  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
SoToVRMLActionP::vrmlextrusion_cb(void * closure, SoCallbackAction * action, const SoNode * node)
{
  SoToVRMLActionP * thisp = (SoToVRMLActionP*) closure;

  SoGroup * tail = thisp->get_current_tail();

  const SoVRMLExtrusion * ext = (const SoVRMLExtrusion*) node;
  SoShapeHints * sh = new SoShapeHints;
  sh->creaseAngle = ext->creaseAngle.getValue();
  sh->vertexOrdering = ext->ccw.getValue() ?
    SoShapeHints::COUNTERCLOCKWISE : SoShapeHints::CLOCKWISE;
  sh->shapeType = ext->solid.getValue() ?
    SoShapeHints::SOLID : SoShapeHints::UNKNOWN_SHAPE_TYPE;
  sh->faceType = ext->convex.getValue() ?
    SoShapeHints::CONVEX : SoShapeHints::UNKNOWN_FACE_TYPE;
  tail->addChild(sh);

  thisp->init_gen(FALSE);
  return SoCallbackAction::CONTINUE;
}

#endif // HAVE_VRML97
