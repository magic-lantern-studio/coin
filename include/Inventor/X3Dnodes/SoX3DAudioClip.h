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

#ifndef COIN_SOX3DAUDIOCLIP_H
#define COIN_SOX3DAUDIOCLIP_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/lists/SbStringList.h>
#include <Inventor/SbTime.h>

class SoX3DAudioClipP;

class COIN_DLL_API SoX3DAudioClip : public SoNode
{
  typedef SoNode inherited;
  SO_NODE_HEADER(SoX3DAudioClip);

public:
  typedef void *open_func(const SbStringList &url, 
                            SoX3DAudioClip *clip, void *userdataptr);
  typedef size_t read_func(void *datasource, 
                             void *buffer, int numframes, int &channels,
                             SoX3DAudioClip *clip, void *userdataptr);
  typedef int seek_func(void *datasource, long offset, int whence,
                          SoX3DAudioClip *clip, void *userdataptr);
  typedef long tell_func(void *datasource,
                         SoX3DAudioClip *clip, void *userdataptr);
  typedef int close_func(void *datasource,
                         SoX3DAudioClip *clip, void *userdataptr);
  
  static void initClass(void);
  SoX3DAudioClip(void);

  SoSFString description;
  SoSFBool loop;
  SoSFFloat pitch;
  SoSFTime startTime;
  SoSFTime stopTime;
  SoMFString url;

  static void  setSubdirectories(const SbList<SbString> &subdirectories);
  static const SbStringList & getSubdirectories();
  static void setDefaultPauseBetweenTracks(SbTime pause);
  static SbTime getDefaultPauseBetweenTracks();
  static void setDefaultIntroPause(SbTime pause);
  static SbTime getDefaultIntroPause();
  static void setDefaultSampleRate(int samplerate);
  static int getDefaultSampleRate();
  static void setDefaultTimerInterval(SbTime interval);
  static SbTime getDefaultTimerInterval();

  int getSampleRate();

  void * open(const SbStringList &url);
  size_t read(void *datasource, void *buffer, int numframes, int &channels);
  int    seek(void *datasource, long offset, int whence);
  long   tell(void *datasource);
  int    close(void *datasource);

  void setCallbacks(open_func *opencb, read_func *readcb, seek_func *seekcb,
                    tell_func *tellcb, close_func *closecb, void *userdataptr);

protected:
  virtual ~SoX3DAudioClip();
  SoSFTime duration_changed; // eventOut
  SoSFBool isActive;         // eventOut

private:
  SoX3DAudioClipP *pimpl;
  friend class SoX3DAudioClipP;
};

#endif // ! COIN_SOX3DAUDIOCLIP_H
