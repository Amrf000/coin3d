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
  \class SoBumpMap SoBumpMap.h Inventor/nodes/SoBumpMap.h
  \brief The SoBumpMap class is used to map a bump map onto subsequent shapes.
  \ingroup nodes

  \since Coin 2.2
*/

#include <assert.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/nodes/SoBumpMap.h>
#include <coindefs.h> // COIN_OBSOLETED()
#include <Inventor/SoInput.h>
#include <Inventor/nodes/SoSubNodeP.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/elements/SoBumpMapElement.h>
#include <Inventor/errors/SoReadError.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/lists/SbStringList.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SbImage.h>
#include <Inventor/misc/SoGLImage.h>


/*!
  \var SoSFString SoBumpMap::filename

  Texture filename, referring to a file on disk in a supported image
  bitmap format.

  By default contains an empty string, which means the texture will be
  fetched from SoTexture2::image and not from disk. (Specify either
  this field or use SoTexture2::image, not both.)

  For reading texture image files from disk, Coin uses the "simage"
  library from Systems in Motion. This library must be installed for
  it to be possible to load any image files at all.

  The set of image formats you can actually read with the simage
  library depends on how the simage library was built, as simage is
  again dependent on a few other low-level file import/export
  libraries (for instance for JPEG, GIF, TIFF and PNG support).  To
  make sure all wanted formats are supported, you should build the
  simage library yourself.

  The set of image formats guaranteed to be supported by simage is
  Targa (.tga), PIC (.pic), SGI RGB (.rgb, .bw) and XWD (.xwd).

  For more information about the simage library, including download
  and build instructions, see the <a href="http://www.coin3d.org">Coin
  www-pages</a>.
*/
/*!
  \var SoSFImage SoBumpMap::image

  Inline image data. Defaults to contain an empty image.

  See documentation of the SoSFImage class for a very detailed
  description of how the format specification for the image data is
  layed out, and what different image formats for color textures,
  semi-transparent textures, grayscale textures, etc etc, are
  supported.
*/

// *************************************************************************

class SoBumpMapP {
public:
  SoFieldSensor * filenamesensor;
  SoGLImage * glimage;
  SbBool glimagevalid;
};


#undef PRIVATE
#define PRIVATE(p) (p->pimpl)

SO_NODE_SOURCE(SoBumpMap);

/*!
  Constructor.
*/
SoBumpMap::SoBumpMap(void)
{
  PRIVATE(this) = new SoBumpMapP;
  PRIVATE(this)->glimage = new SoGLImage;
  PRIVATE(this)->glimagevalid = FALSE;

  SO_NODE_INTERNAL_CONSTRUCTOR(SoBumpMap);

  SO_NODE_ADD_FIELD(filename, (""));
  SO_NODE_ADD_FIELD(image, (SbVec2s(0, 0), 0, NULL));

  // use field sensor for filename since we will load an image if
  // filename changes. This is a time-consuming task which should
  // not be done in notify().
  PRIVATE(this)->filenamesensor = new SoFieldSensor(filenameSensorCB, this);
  PRIVATE(this)->filenamesensor->setPriority(0);
  PRIVATE(this)->filenamesensor->attach(&this->filename);
}

/*!
  Destructor. Frees up internal resources used to store texture image
  data.
*/
SoBumpMap::~SoBumpMap()
{
  PRIVATE(this)->glimage->unref(NULL);
  delete PRIVATE(this)->filenamesensor;
  delete PRIVATE(this);
}

// Documented in superclass.
void
SoBumpMap::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoBumpMap, SO_FROM_COIN_2_2);
  
  SO_ENABLE(SoGLRenderAction, SoBumpMapElement);
}


// Documented in superclass. Overridden to check if texture file (if
// any) can be found and loaded.
SbBool
SoBumpMap::readInstance(SoInput * in, unsigned short flags)
{
  PRIVATE(this)->filenamesensor->detach();
  SbBool readOK = inherited::readInstance(in, flags);
  if (readOK && !filename.isDefault() && filename.getValue() != "") {
    if (!this->loadFilename()) {
      SoReadError::post(in, "Could not read texture file '%s'",
                        filename.getValue().getString());
    }
  }
  PRIVATE(this)->filenamesensor->attach(&this->filename);
  PRIVATE(this)->glimagevalid = FALSE;
  return readOK;
}

// Documented in superclass.
void
SoBumpMap::GLRender(SoGLRenderAction * action)
{
  SoState * state = action->getState();

  int nc;
  SbVec2s size;
  const unsigned char * bytes = this->image.getValue(size, nc);
  
  if (bytes && size != SbVec2s(0,0)) {
    if (!PRIVATE(this)->glimagevalid) {
      PRIVATE(this)->glimage->setData(bytes, size, nc,
                                      SoGLImage::CLAMP_TO_EDGE,
                                      SoGLImage::CLAMP_TO_EDGE,
                                      0.4f);
      PRIVATE(this)->glimagevalid = TRUE;
    }
    SoBumpMapElement::set(state, this, PRIVATE(this)->glimage);
  }
}

// Documented in superclass.
void
SoBumpMap::doAction(SoAction * action)
{
}

// doc from parent
void
SoBumpMap::callback(SoCallbackAction * action)
{
  // SoBumpMap::doAction(action);
}

// doc from parent
void
SoBumpMap::rayPick(SoRayPickAction * action)
{
  // SoBumpMap::doAction(action);
}

// Documented in superclass. Overridden to detect when fields change.
void
SoBumpMap::notify(SoNotList * l)
{
  SoField * f = l->getLastField();
  if (f == &this->image) {
    // write image, not filename
    this->filename.setDefault(TRUE);
    this->image.setDefault(FALSE);
  }
  PRIVATE(this)->glimagevalid = FALSE;
  inherited::notify(l);
}

//
// Called from readInstance() or when user changes the
// filename field.
//
SbBool
SoBumpMap::loadFilename(void)
{
  SbBool retval = FALSE;
  if (this->filename.getValue().getLength()) {
    SbImage tmpimage;
    const SbStringList & sl = SoInput::getDirectories();
    if (tmpimage.readFile(this->filename.getValue(),
                          sl.getArrayPtr(), sl.getLength())) {
      int nc;
      SbVec2s size;
      unsigned char * bytes = tmpimage.getValue(size, nc);
      // disable notification on image while setting data from filename
      // as a notify will cause a filename.setDefault(TRUE).
      SbBool oldnotify = this->image.enableNotify(FALSE);
      this->image.setValue(size, nc, bytes);
      this->image.enableNotify(oldnotify);
      retval = TRUE;
    }
  }
  this->image.setDefault(TRUE); // write filename, not image
  return retval;
}

//
// called when filename changes
//
void
SoBumpMap::filenameSensorCB(void * data, SoSensor *)
{
  SoBumpMap * thisp = (SoBumpMap*) data;

  if (thisp->filename.getValue().getLength() &&
      !thisp->loadFilename()) {
    SoDebugError::postWarning("SoBumpMap::filenameSensorCB",
                              "Image file '%s' could not be read",
                              thisp->filename.getValue().getString());
  }
}

#undef PRIVATE
