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

#ifndef COIN_SOSUBNODE_H
#define COIN_SOSUBNODE_H

#include <Inventor/SbName.h>
#include <Inventor/SoType.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/nodes/SoNode.h>


#define PRIVATE_NODE_TYPESYSTEM_HEADER( ) \
public: \
  static SoType getClassTypeId(void); \
  virtual SoType getTypeId(void) const; \
private: \
  static SoType classTypeId



// FIXME: document. 20000103 mortene.
#define SO_NODE_ABSTRACT_HEADER(_class_) \
  PRIVATE_NODE_TYPESYSTEM_HEADER(); \
protected: \
  static const SoFieldData ** getFieldDataPtr(void); \
  virtual const SoFieldData * getFieldData(void) const; \
private: \
  static const SoFieldData ** parentclassfielddata; \
  static SoFieldData * classfielddata; \
  /* Counts number of instances of subclasses aswell as "direct" */ \
  /* instances from non-abstract classes. */ \
  static unsigned int classinstances



// FIXME: document. 20000103 mortene.
#define SO_NODE_HEADER(_class_) \
  SO_NODE_ABSTRACT_HEADER(_class_); \
private: \
  static void * createInstance(void)



#define PRIVATE_NODE_TYPESYSTEM_SOURCE(_class_) \
SoType _class_::classTypeId = SoType::badType(); \
SoType _class_::getClassTypeId(void) { return _class_::classTypeId; } \
SoType _class_::getTypeId(void) const { return _class_::classTypeId; }



// FIXME: document. 20000103 mortene.
#define SO_NODE_ABSTRACT_SOURCE(_class_) \
PRIVATE_NODE_TYPESYSTEM_SOURCE(_class_); \
 \
unsigned int _class_::classinstances = 0; \
const SoFieldData ** _class_::parentclassfielddata = NULL; \
SoFieldData * _class_::classfielddata = NULL; \
 \
const SoFieldData ** \
_class_::getFieldDataPtr(void) \
{ \
  return (const SoFieldData **)(&_class_::classfielddata); \
} \
 \
const SoFieldData * \
_class_::getFieldData(void) const \
{ \
  return _class_::classfielddata; \
}



// FIXME: document. 20000103 mortene.
#define SO_NODE_SOURCE(_class_) \
SO_NODE_ABSTRACT_SOURCE(_class_); \
 \
void * \
_class_::createInstance(void) \
{ \
  return new _class_; \
}



// FIXME: document. 20000103 mortene.
#define SO_NODE_IS_FIRST_INSTANCE() \
  (classinstances == 1)



// FIXME: document. 20000103 mortene.
#define SO_NODE_CONSTRUCTOR(_class_) \
  do { \
    _class_::classinstances++; \
    /* Catch attempts to use a node class which has not been initialized. */ \
    assert(_class_::classTypeId != SoType::badType()); \
    /* Initialize a fielddata container for the class only once. */ \
    if (!_class_::classfielddata) { \
      _class_::classfielddata = \
        new SoFieldData(_class_::parentclassfielddata ? \
                        *_class_::parentclassfielddata : NULL); \
    } \
    /* Extension classes from the application programmers should not be \
       considered native. This is important to get the export code to do \
       the Right Thing. */ \
    this->isBuiltIn = FALSE; \
  } while (0)



#define PRIVATE_COMMON_INIT_CODE(_class_, _classname_, _createfunc_, _parentclass_) \
  do { \
    /* Make sure we only initialize once. */ \
    assert(_class_::classTypeId == SoType::badType()); \
    /* Make sure superclass gets initialized before subclass. */ \
    assert(_parentclass_::getClassTypeId() != SoType::badType()); \
 \
    /* Set up entry in the type system. */ \
    _class_::classTypeId = \
      SoType::createType(_parentclass_::getClassTypeId(), \
                         _classname_, \
                         _createfunc_, \
                         SoNode::nextActionMethodIndex++); \
 \
    /* Store parent's fielddata pointer for later use in the constructor. */ \
    _class_::parentclassfielddata = _parentclass_::getFieldDataPtr(); \
  } while (0)


// FIXME: document. 20000103 mortene.
#define SO_NODE_INIT_CLASS(_class_, _parentclass_, _parentname_) \
  do { \
    const char * classname = SO__QUOTE(_class_); \
    PRIVATE_COMMON_INIT_CODE(_class_, classname, &_class_::createInstance, _parentclass_); \
  } while (0)



// FIXME: document. 20000103 mortene.
#define SO_NODE_INIT_ABSTRACT_CLASS(_class_, _parentclass_, _parentname_) \
  do { \
    const char * classname = SO__QUOTE(_class_); \
    PRIVATE_COMMON_INIT_CODE(_class_, classname, NULL, _parentclass_); \
  } while (0)



// FIXME: document. 20000103 mortene.
#define SO_NODE_ADD_FIELD(_field_, _defaultval_) \
  do { \
    this->_field_.setValue _defaultval_;\
    this->_field_.setContainer(this); \
    if (SO_NODE_IS_FIRST_INSTANCE()) { \
      classfielddata->addField(this, SO__QUOTE(_field_), &this->_field_);\
    } \
  } while (0)


// FIXME: document. 20000103 mortene.
#define SO_NODE_DEFINE_ENUM_VALUE(_enumname_, _enumval_) \
  do { \
    if (SO_NODE_IS_FIRST_INSTANCE()) \
      classfielddata->addEnumValue(SO__QUOTE(_enumname_), \
                                   SO__QUOTE(_enumval_), _enumval_); \
  } while (0)


#endif // !COIN_SOSUBNODE_H
