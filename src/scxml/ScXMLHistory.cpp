/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2008 by Kongsberg SIM.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg SIM about acquiring
 *  a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg SIM, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#include <Inventor/scxml/ScXMLHistory.h>

#include <assert.h>
#include <string.h>

#include <Inventor/scxml/ScXML.h>
#include <Inventor/scxml/ScXMLTransition.h>

#include "scxml/ScXMLCommonP.h"

/*!
  \class ScXMLHistory Inventor/scxml/ScXMLHistory.h
  \brief not implemented...
*/

SCXML_OBJECT_SOURCE(ScXMLHistory);

void
ScXMLHistory::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLHistory, ScXMLStateBase, SCXML_DEFAULT_NS, "history");
}

ScXMLHistory::ScXMLHistory(void)
  : type(NULL),
    transitionptr(NULL)
{
}

ScXMLHistory::~ScXMLHistory(void)
{
  this->setTypeXMLAttr(NULL);

  if (this->transitionptr) {
    delete this->transitionptr;
    this->transitionptr = NULL;
  }
}

void
ScXMLHistory::setTypeXMLAttr(const char * typestr)
{
  if (this->type && this->type != this->getAttribute("type")) {
    delete [] const_cast<char *>(this->type);
  }
  this->type = NULL;
  if (typestr) {
    char * buffer = new char [ strlen(typestr) + 1 ];
    strcpy(buffer, typestr);
    this->type = buffer;
  }
}

SbBool
ScXMLHistory::handleXMLAttributes(void)
{
  if (!inherited::handleXMLAttributes()) return FALSE;

  this->type = this->getAttribute("type");

  if (this->type) {
    if ((strcmp(this->type, "deep") != 0) && (strcmp(this->type, "shallow") != 0)) {
      return FALSE;
    }
  }

  return TRUE;
}

// *************************************************************************

SCXML_SINGLE_OBJECT_API_IMPL(ScXMLHistory, ScXMLTransition, transitionptr, Transition);
