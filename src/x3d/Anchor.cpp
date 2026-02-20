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
  \class SoX3DAnchor SoX3DAnchor.h Inventor/X3Dnodes/SoX3DAnchor.h
  \brief The SoX3DAnchor class is used for linking to other URL resources.

  \ingroup coin_X3Dnodes

  \WEB3DCOPYRIGHT

  \verbatim

  Anchor {
    eventIn      MFNode   addChildren
    eventIn      MFNode   removeChildren
    exposedField MFNode   children        []
    exposedField SFString description     ""
    exposedField SFNode   metadata        NULL
    exposedField MFString parameter       []
    exposedField MFString url             []
    field        SFVec3f  bboxCenter      0 0 0     # (-inf, inf)
    field        SFVec3f  bboxSize        -1 -1 -1  # (0, inf) or -1,-1,-1
  }
  \endverbatim

  The Anchor grouping node retrieves the content of a URL when the
  user activates (e.g., clicks) some geometry contained within the
  Anchor node's children. If the URL points to a valid X3D file, that
  world replaces the world of which the Anchor node is a part (except
  when the parameter field, described below, alters this
  behaviour). If non-X3D data is retrieved, the browser shall
  determine how to handle that data; typically, it will be passed to
  an appropriate non-X3D browser.

  Exactly how a user activates
  geometry contained by the Anchor node depends on the pointing device
  and is determined by the X3D browser. Typically, clicking with the
  pointing device will result in the new scene replacing the current
  scene. An Anchor node with an empty url does nothing when its
  children are chosen. A description of how multiple Anchors and
  pointing-device sensors are resolved on activation is contained in
  20.2, Concepts (<https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/pointingsensor.html#Concepts>).

  More details on the children, addChildren, and removeChildren fields
  can be found in 10.2, Concepts
  (<https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Concepts>).

  The description field in the Anchor node specifies a textual
  description of the Anchor node. This may be used by browser-specific
  user interfaces that wish to present users with more detailed
  information about the Anchor.

  The parameter exposed field may be
  used to supply any additional information to be interpreted by the
  browser. Each string shall consist of "keyword=value" pairs. For
  example, some browsers allow the specification of a 'target' for a
  link to display a link in another part of an HTML document. The
  parameter field is then:

  \verbatim
  Anchor {
    parameter [ "target=name_of_frame" ]
    ...
  }
  \endverbatim

  An Anchor node may be used to bind the initial Viewpoint node in a
  world by specifying a URL ending with "#ViewpointName" where
  "ViewpointName" is the name of a viewpoint defined in the X3D
  file. For example:

  \verbatim
  Anchor {
    url "http://www.school.edu/X3D/someScene.wrl#OverView"
    children  Shape { geometry Box {} }
  }
  \endverbatim

  specifies an anchor that loads the X3D file "someScene.wrl" and
  binds the initial user view to the Viewpoint node named "OverView"
  when the Anchor node's geometry (Box) is activated. If the named
  Viewpoint node is not found in the X3D file, the X3D file is
  loaded using the default Viewpoint node binding stack rules (see
  X3DViewpoint).

  If the url field is specified in the form
  "#ViewpointName" (i.e. no file name), the Viewpoint node with the
  given name ("ViewpointName") in the Anchor's runtime name scope(s)
  shall be bound (set_bind TRUE).  The results are undefined if there
  are multiple Viewpoints with the same name in the Anchor's runtime
  name scope(s). The results are undefined if the Anchor node is not
  part of any runtime name scope or is part of more than one runtime
  name scope. See 4.4.7, Run-time name scope, for a description of
  runtime name scopes. See X3DViewpoint, for the Viewpoint
  transition rules that specify how browsers shall interpret the
  transition from the old Viewpoint node to the new one. For example:

  \verbatim
  Anchor {
    url "#Doorway"
    children Shape {
      geometry Sphere {}
    }
  }
  \endverbatim

  binds the viewer to the viewpoint defined by the "Doorway" viewpoint
  in the current world when the sphere is activated. In this case, if
  the Viewpoint is not found, no action occurs on activation.

  More details on the url field are contained in 9.2.1, X3D and the World
  Wide Web
  (<https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/concepts.html#URLs>).
  
  The bboxCenter and bboxSize fields specify a bounding box
  that encloses the Anchor's children. This is a hint that may be used
  for optimization purposes. The results are undefined if the
  specified bounding box is smaller than the actual bounding box of
  the children at any time.  The default bboxSize value, (-1, -1, -1),
  implies that the bounding box is not specified and if needed shall
  be calculated by the browser. More details on the bboxCenter and
  bboxSize fields can be found in 10.2.2, Bounding boxes
  (<https://www.web3d.org/documents/specifications/19775-1/V3.0/Part01/components/group.html#Boundingboxes>).

*/

/*!
  \var SoMFString SoX3DAnchor::url

  The URL or URN string.
*/

/*!
  \var SoSFString SoX3DAnchor::description

  The textual description of the URL.
*/

/*!
  \var SoSFNode SoX3DAnchor::metadata

  Can contain an SoX3DMetadataObject. Is NULL by default.
*/

/*!
  \var SoMFString SoX3DAnchor::parameter

  May be used to supply additional information to the browser.

  Each string should be pairs of \e keyword = \e value.
*/

/*!
  \var SoSFVec3f SoX3DAnchor::bboxCenter
  Children bounding box hint center. Default value is (0, 0, 0).
*/

/*!
  \var SoX3DAnchor::bboxSize
  Children bounding box size hint. Default value is (-1, -1, -1).
*/

#include <Inventor/X3Dnodes/SoX3DAnchor.h>

#include <cstdlib>

#include <Inventor/X3Dnodes/SoX3DMacros.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>

#include "nodes/SoSubNodeP.h"

// static members
SoX3DAnchorCB * SoX3DAnchor::fetchurlcb;
void * SoX3DAnchor::userdata;

SO_NODE_SOURCE(SoX3DAnchor);

/*!
  \copydetails SoNode::initClass(void)
*/
void
SoX3DAnchor::initClass(void) // static
{
  SO_NODE_INTERNAL_INIT_CLASS(SoX3DAnchor, SO_X3D_NODE_TYPE);
  SoX3DAnchor::fetchurlcb = NULL;
  SoX3DAnchor::userdata = NULL;
}


/*!
  Default constructor.
*/
SoX3DAnchor::SoX3DAnchor(void)
{
  SO_X3DNODE_INTERNAL_CONSTRUCTOR(SoX3DAnchor);

  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(url);
  SO_X3DNODE_ADD_EXPOSED_FIELD(description, (""));
  SO_X3DNODE_ADD_EXPOSED_FIELD(metadata, (NULL));
  SO_X3DNODE_ADD_EMPTY_EXPOSED_MFIELD(parameter);

  SO_X3DNODE_ADD_FIELD(bboxCenter, (0.0f, 0.0f, 0.0f));
  SO_X3DNODE_ADD_FIELD(bboxSize, (-1.0f, -1.0f, -1.0f));
}

/*!
  Destructor.
*/
SoX3DAnchor::~SoX3DAnchor()
{
}

/*!
  Sets the callback that will be called when the node is selected.
*/
void
SoX3DAnchor::setFetchURLCallBack(SoX3DAnchorCB * f, void * closure)
{
  SoX3DAnchor::fetchurlcb = f;
  SoX3DAnchor::userdata = closure;
}

// doc in parent
void
SoX3DAnchor::handleEvent(SoHandleEventAction * action)
{
  SoState * state = action->getState();
  state->push();
  const SoEvent * event = action->getEvent();
  if (event->isOfType(SoMouseButtonEvent::getClassTypeId()) &&
      SoX3DAnchor::fetchurlcb) {
    const SoMouseButtonEvent * mbevent = (SoMouseButtonEvent*)event;
    if (SoMouseButtonEvent::isButtonPressEvent(mbevent, 
                                               SoMouseButtonEvent::BUTTON1)) {
      int urls = this->url.getNum();
      SbString s = "";
      for (int i = 0; i < urls; i++) {
        this->url.get1(i, s);
        if (s.getLength() > 0) {
          break;
        }
      }
      if (s.getLength() > 0) {
        SoX3DAnchor::fetchurlcb(s, SoX3DAnchor::userdata, this);
      }
    }
  }
  inherited::handleEvent(action);
  state->pop();
}

#endif // HAVE_X3D
