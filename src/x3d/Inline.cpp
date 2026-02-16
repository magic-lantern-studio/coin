/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#ifdef HAVE_X3D

/*!
  \class SoX3DInline SoX3DInline.h Inventor/X3Dnodes/SoX3DInline.h
  \brief The SoX3DInline class is used to insert X3D files into a scene.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT
  
  \verbatim
  Inline {
    exposedField MFString url        []
    field        SFVec3f  bboxCenter 0 0 0     # (-,)
    field        SFVec3f  bboxSize   -1 -1 -1  # (0,) or -1,-1,-1
  }
  \endverbatim

  The Inline node is a grouping node that reads its children data from
  a location in the World Wide Web. Exactly when its children are read
  and displayed is not defined (e.g. reading the children may be
  delayed until the Inline node's bounding box is visible to the
  viewer). The url field specifies the URL containing the children. An
  Inline node with an empty URL does nothing.  

  Each specified URL shall refer to a valid X3D file that contains a
  list of children nodes, prototypes, and routes at the top level as
  described in 4.6.5, Grouping and children nodes.  

  The results are undefined if the URL refers to a file that is not
  X3D or if the X3D file contains non-children nodes at the top
  level.  

  If multiple URLs are specified, the browser may display a URL of a
  lower preference X3D file while it is obtaining, or if it is unable
  to obtain, the higher preference X3D file. Details on the url field
  and preference order can be found in 4.5, X3D and the World Wide
  Web
  (<http://www.web3d.org/x3d/specifications/vrml/ISO-IEC-14772-X3D/part1/concepts.html#4.5>).  

  The results are undefined if the contents of the URL change after it
  has been loaded.  

  The bboxCenter and bboxSize fields specify a bounding box that
  encloses the Inline node's children. This is a hint that may be used
  for optimization purposes. The results are undefined if the
  specified bounding box is smaller than the actual bounding box of
  the children at any time. A default bboxSize value, (-1, -1, -1),
  implies that the bounding box is not specified and if needed shall
  be calculated by the browser. A description of the bboxCenter and
  bboxSize fields is in 4.6.4, Bounding boxes
  (<http://www.web3d.org/x3d/specifications/vrml/ISO-IEC-14772-X3D/part1/concepts.html#4.6.4>).  

*/

/*!
  SoSFVec3f SoX3DInline::bboxCenter
  Center of bounding box.
*/

/*!
  SoSFVec3f SoX3DInline::bboxSize
  Size of bounding box.
*/

/*!
  SoMFString SoX3DInline::url
  The X3D file URL.
*/

/*!
  enum SoX3DInline::BboxVisibility
  Used to enumerate bounding box visibility settings.
*/

/*!
  \var SoX3DInline::BboxVisibility SoX3DInline::NEVER
  Never display bounding box.
*/

/*!
  \var SoX3DInline::BboxVisibility SoX3DInline::UNTIL_LOADED
  Display bounding box until file is loaded.
*/

/*!
  \var SoX3DInline::BboxVisibility SoX3DInline::ALWAYS
  Always display bounding box.
*/

#include <Inventor/X3Dnodes/SoX3DInline.h>
#include "coindefs.h"

#include <cstdlib>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/SbColor.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoDB.h>
#include <Inventor/SbBox3f.h>
#include <Inventor/errors/SoReadError.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/misc/SoChildList.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/elements/SoGLMultiTextureEnabledElement.h>
#include <Inventor/system/gl.h>

#include "nodes/SoSubNodeP.h"
#include "tidbitsp.h"

class SoX3DInlineP {
public:
  SbString fullurlname;
  SbBool isrequested;
  SoChildList * children;
  SoFieldSensor * urlsensor;
};

static SoX3DInline::BboxVisibility
sovrmlinline_bboxvisibility = SoX3DInline::UNTIL_LOADED;
static SoX3DInlineFetchURLCB * sovrmlinline_fetchurlcb = NULL;
static void * sovrmlinline_fetchurlcbclosure;

static SbColor * sovrmlinline_bboxcolor = NULL;
static SbBool sovrmlinline_readassofile = TRUE;

static void
sovrmlinline_cleanup(void)
{
  delete sovrmlinline_bboxcolor;
  sovrmlinline_bboxcolor = NULL;
  sovrmlinline_bboxvisibility = SoX3DInline::UNTIL_LOADED;
  sovrmlinline_fetchurlcb = NULL;  
  sovrmlinline_readassofile = TRUE;
}

SO_NODE_SOURCE(SoX3DInline);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DInline::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DInline, SO_X3D_NODE_TYPE);
  sovrmlinline_bboxcolor = new SbColor(0.8f, 0.8f, 0.8f);
  coin_atexit((coin_atexit_f*) sovrmlinline_cleanup, CC_ATEXIT_NORMAL);
  SoAudioRenderAction::addMethod(SoX3DInline::getClassTypeId(),
                                 SoAudioRenderAction::callDoAction);
}

#define PRIVATE(obj) ((obj)->pimpl)

/*!
  Constructor
*/
SoX3DInline::SoX3DInline(void)
{
  PRIVATE(this) = new SoX3DInlineP;
  PRIVATE(this)->isrequested = FALSE;
  PRIVATE(this)->children = new SoChildList(this);

  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DInline);

  SO_X3DNODE_ADD_FIELD(bboxCenter, (0.0f, 0.0f, 0.0f));
  SO_X3DNODE_ADD_FIELD(bboxSize, (-1.0f, -1.0f, -1.0f));
  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(url);

  PRIVATE(this)->urlsensor = new SoFieldSensor(SoX3DInline::urlFieldModified, this);
  PRIVATE(this)->urlsensor->setPriority(0); // immediate sensor
  PRIVATE(this)->urlsensor->attach(& this->url);
}

/*!
  Destructor.
*/
SoX3DInline::~SoX3DInline()
{
  delete PRIVATE(this)->urlsensor;
  delete PRIVATE(this)->children;
  delete PRIVATE(this);
}

/*!
  Sets the full (non-relative) URL name.
*/
void
SoX3DInline::setFullURLName(const SbString & urlref)
{
  PRIVATE(this)->fullurlname = urlref;
}

/*!
  Returns the full URL name.
*/
const SbString &
SoX3DInline::getFullURLName(void)
{
  return PRIVATE(this)->fullurlname;
}

/*!
  Returns a copy of the children.
*/
SoGroup *
SoX3DInline::copyChildren(void) const
{
  if (PRIVATE(this)->children->getLength() == 0) return NULL;
  assert(PRIVATE(this)->children->getLength() == 1);
  SoNode * rootcopy = (*(PRIVATE(this)->children))[0]->copy();
  assert(rootcopy->isOfType(SoGroup::getClassTypeId()));
  return (SoGroup *)rootcopy;
}

// Doc in parent
SoChildList *
SoX3DInline::getChildren(void) const
{
  return PRIVATE(this)->children;
}

/*!
  Request URL data.
*/
void
SoX3DInline::requestURLData(void)
{
  PRIVATE(this)->isrequested = TRUE;
  if (sovrmlinline_fetchurlcb) {
    sovrmlinline_fetchurlcb(PRIVATE(this)->fullurlname,
                            sovrmlinline_fetchurlcbclosure,
                            this);
  }
}

/*!
  Returns TRUE if the URL data have been requested.
*/
SbBool
SoX3DInline::isURLDataRequested(void) const
{
  return PRIVATE(this)->isrequested;
}

/*!
  Returns TRUE if the data have been loaded.
*/
SbBool
SoX3DInline::isURLDataHere(void) const
{
  return this->getChildData() != NULL;
}

/*!
  Cancel the URL data request.
*/
void
SoX3DInline::cancelURLDataRequest(void)
{
  PRIVATE(this)->isrequested = FALSE;
}

/*!
  Sets the child data. Can be used by the URL fetch callback.
*/
void
SoX3DInline::setChildData(SoNode * urldata)
{
  PRIVATE(this)->isrequested = FALSE;
  PRIVATE(this)->children->truncate(0);
  if (urldata) {
    PRIVATE(this)->children->append(urldata);
  }
}

/*!
  Returns the child data (the scene loaded from the URL).
*/
SoNode *
SoX3DInline::getChildData(void) const
{
  if (PRIVATE(this)->children->getLength()) {
    return (*PRIVATE(this)->children)[0];
  }
  return NULL;
}

/*!
  Sets the callback used to handle URL loading.
*/
void
SoX3DInline::setFetchURLCallBack(SoX3DInlineFetchURLCB * f,
                                  void * closure)
{
  sovrmlinline_fetchurlcb = f;
  sovrmlinline_fetchurlcbclosure = closure;
}

/*!
  Sets the bounding box visibility strategy.
*/
void
SoX3DInline::setBoundingBoxVisibility(BboxVisibility b)
{
  sovrmlinline_bboxvisibility = b;
}

/*!
  Returns the bounding box visibility strategy.
*/
SoX3DInline::BboxVisibility
SoX3DInline::getBoundingBoxVisibility(void)
{
  return sovrmlinline_bboxvisibility;
}

/*!
  Sets the color of the bounding box.
*/
void
SoX3DInline::setBoundingBoxColor(SbColor & color)
{
  sovrmlinline_bboxcolor->setValue(color[0], color[1], color[2]);
}

/*!
  Returns the color of the bounding box.
*/
SbColor &
SoX3DInline::getBoundingBoxColor(void)
{
  return *sovrmlinline_bboxcolor;
}

/*!
  Sets whether Inline nodes should be treated as a normal Inventor SoFile node.
*/
void
SoX3DInline::setReadAsSoFile(SbBool enable)
{
  sovrmlinline_readassofile = enable;
}

/*!
  Returns whether Inline nodes are read as SoFile nodes.
*/
SbBool
SoX3DInline::getReadAsSoFile(void)
{
  return sovrmlinline_readassofile;
}

// Doc in parent
void
SoX3DInline::doAction(SoAction * action)
{
  int numindices;
  const int * indices;
  if (action->getPathCode(numindices, indices) == SoAction::IN_PATH) {
    PRIVATE(this)->children->traverseInPath(action, numindices, indices);
  }
  else {
    PRIVATE(this)->children->traverse(action);
  }
}

// Doc in parent
void
SoX3DInline::callback(SoCallbackAction * action)
{
  SoX3DInline::doAction((SoAction*)action);
}

// Doc in parent
void
SoX3DInline::GLRender(SoGLRenderAction * action)
{
  BboxVisibility vis = sovrmlinline_bboxvisibility;
  SbVec3f size = this->bboxSize.getValue();
  SoNode * child = this->getChildData();
  if ((size[0] >= 0.0f && size[1] >= 0.0f && size[2] >= 0.0f) &&
      ((vis == ALWAYS) || 
       (vis == UNTIL_LOADED && child == NULL))) {
    SoState * state = action->getState();
    state->push();

    SoGLMultiTextureEnabledElement::disableAll(state);
    
    uint32_t packedcolor = sovrmlinline_bboxcolor->getPackedValue();
    SoGLLazyElement::sendLightModel(state, SoLazyElement::BASE_COLOR);
    SoGLLazyElement::sendPackedDiffuse(state, packedcolor);
    
    SbVec3f center = this->bboxCenter.getValue();
    SbVec3f minv = center - size*0.5f;
    SbVec3f maxv = center + size*0.5f;
    
    SbVec3f p[8];
    for (int i = 0; i < 8; i++) {
      p[i][0] = i & 1 ? minv[0] : maxv[0];
      p[i][1] = i & 2 ? minv[1] : maxv[1];
      p[i][2] = i & 4 ? minv[2] : maxv[2];
    }

    glBegin(GL_LINE_LOOP);
    glVertex3fv(p[0].getValue());
    glVertex3fv(p[1].getValue());
    glVertex3fv(p[3].getValue());
    glVertex3fv(p[2].getValue());
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3fv(p[4].getValue());
    glVertex3fv(p[5].getValue());
    glVertex3fv(p[7].getValue());
    glVertex3fv(p[6].getValue());
    glEnd();

    glBegin(GL_LINES);

    glVertex3fv(p[0].getValue());
    glVertex3fv(p[4].getValue());

    glVertex3fv(p[2].getValue());
    glVertex3fv(p[6].getValue());

    glVertex3fv(p[3].getValue());
    glVertex3fv(p[7].getValue());

    glVertex3fv(p[1].getValue());
    glVertex3fv(p[5].getValue());

    glEnd();
    state->pop();
  }
  SoX3DInline::doAction(action);
}

// Doc in parent
void
SoX3DInline::getBoundingBox(SoGetBoundingBoxAction * action)
{
  SbVec3f size = this->bboxSize.getValue();
  if (size[0] > 0.0f || size[1] > 0.0f || size[2] > 0) {
    size[0] = SbMax(size[0], 0.0f);
    size[1] = SbMax(size[1], 0.0f);
    size[2] = SbMax(size[2], 0.0f);
    SbVec3f center = this->bboxCenter.getValue();
    size *= 0.5f;
    SbBox3f box(center[0]-size[0],
                center[1]-size[1],
                center[2]-size[2],
                center[0]+size[0],
                center[1]+size[1],
                center[2]+size[2]);
    if (!box.isEmpty()) {
      action->extendBy(box);
      action->setCenter(center, TRUE);
    }
  }
  else {
    int numindices;
    const int * indices;
    int lastchildindex;
    
    if (action->getPathCode(numindices, indices) == SoAction::IN_PATH)
      lastchildindex = indices[numindices-1];
    else
      lastchildindex = this->getChildren()->getLength() - 1;
  
    assert(lastchildindex < this->getChildren()->getLength());
    
    // Initialize accumulation variables.
    SbVec3f acccenter(0.0f, 0.0f, 0.0f);
    int numcenters = 0;
    
    for (int i = 0; i <= lastchildindex; i++) {
      this->getChildren()->traverse(action, i);
      
      // If center point is set, accumulate.
      if (action->isCenterSet()) {
        acccenter += action->getCenter();
        numcenters++;
        action->resetCenter();
      }
    }
    
    if (numcenters != 0)
      action->setCenter(acccenter / float(numcenters), FALSE);
  }
}

// Doc in parent
void
SoX3DInline::getMatrix(SoGetMatrixAction * action)
{
  SoX3DInline::doAction((SoAction*)action);
}

// Doc in parent
void
SoX3DInline::handleEvent(SoHandleEventAction * action)
{
  SoX3DInline::doAction((SoAction*)action);
}

// Doc in parent
void
SoX3DInline::search(SoSearchAction * action)
{
  SoNode::search(action);
  if (action->isFound()) return;

  SoX3DInline::doAction(action);
}

// Doc in parent
void
SoX3DInline::pick(SoPickAction * action)
{
  SoX3DInline::doAction((SoAction*)action);
}

// Doc in parent
void
SoX3DInline::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  SoX3DInline::doAction((SoAction*)action);
}

void
SoX3DInline::addBoundingBoxChild(SbVec3f COIN_UNUSED_ARG(center),
                                  SbVec3f COIN_UNUSED_ARG(size))
{
  // FIXME: implement
}

// Doc in parent
SbBool
SoX3DInline::readInstance(SoInput * in,
                           unsigned short flags)
{
  SbBool ret = TRUE;

  PRIVATE(this)->urlsensor->detach();
  if (sovrmlinline_readassofile) {
    PRIVATE(this)->fullurlname.makeEmpty();
    ret = inherited::readInstance(in, flags);
    ret = ret && this->readLocalFile(in);
  }
  else {
    ret = inherited::readInstance(in, flags);
    if (ret) this->requestURLData();
  }
  PRIVATE(this)->urlsensor->attach(&this->url);

  return ret; 
}

// Doc in parent
void
SoX3DInline::copyContents(const SoFieldContainer * from,
                           SbBool copyconnections)
{
  PRIVATE(this)->children->truncate(0);
  inherited::copyContents(from, copyconnections);

  SoX3DInline * inlinenode = (SoX3DInline *)from;
  PRIVATE(this)->fullurlname = inlinenode->pimpl->fullurlname;
  // the request will go to the original node, not this one.
  PRIVATE(this)->isrequested = FALSE;

  if (inlinenode->pimpl->children->getLength() == 0) return;

  assert(inlinenode->pimpl->children->getLength() == 1);

  SoNode * cp = (SoNode *)
    SoFieldContainer::findCopy((*(inlinenode->pimpl->children))[0],
                               copyconnections);
  PRIVATE(this)->children->append(cp);
}

/*!
  Read the (local) file named in the SoX3DInline::url field.
*/
SbBool
SoX3DInline::readLocalFile(SoInput * in)
{
  if (this->url.getNum() == 0) {
    return TRUE;
  }

  SbString filename = this->url[0];

  // If we can't find file, ignore it. Note that this does not match
  // the way Inventor works, which will make the whole read process
  // exit with a failure code.
  if (!in->pushFile(filename.getString())) return TRUE;

  PRIVATE(this)->fullurlname = in->getCurFileName();

  SoSeparator * node = SoDB::readAll(in);

  if (node) {
    PRIVATE(this)->children->truncate(0);
    PRIVATE(this)->children->append((SoNode *)node);
  }
  else {
    if (in->getCurFileName() == PRIVATE(this)->fullurlname) {
      // Take care of popping the file off the stack. This is a bit
      // "hack-ish", but its done this way instead of loosening the
      // protection of SoInput::popFile().
      char dummy;
      while (!in->eof() && in->get(dummy)) {}
      assert(in->eof());
      
      // Make sure the stack is really popped on EOF. Popping happens
      // when attempting to read when the current file in the stack is
      // at EOF.
      SbBool gotchar = in->get(dummy);
      if (gotchar) in->putBack(dummy);
    }

    // Note that we handle this differently than Inventor, which lets
    // the whole import fail.
    SoReadError::post(in, "Unable to read Inline file: \"%s\"",
                      filename.getString());
  }

  return TRUE;
}

// Callback for the field sensor.
void
SoX3DInline::urlFieldModified(void * userdata, SoSensor * COIN_UNUSED_ARG(sensor))
{
  SoX3DInline * thisp = (SoX3DInline *)userdata;
  SoInput in;
  thisp->pimpl->fullurlname.makeEmpty();
  if (sovrmlinline_readassofile) {
    (void)thisp->readLocalFile(&in);
  }
  else {
    thisp->requestURLData();
  }
}

#undef PRIVATE

#endif // HAVE_X3D
