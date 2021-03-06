/* ***** BEGIN LICENSE BLOCK *****
 * This file is part of openfx-misc <https://github.com/devernay/openfx-misc>,
 * Copyright (C) 2015 INRIA
 *
 * openfx-misc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * openfx-misc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with openfx-misc.  If not, see <http://www.gnu.org/licenses/gpl-2.0.html>
 * ***** END LICENSE BLOCK ***** */

/*
 * OFX TestOpenGL plugin.
 */

#ifndef Misc_TestOpenGL_h
#define Misc_TestOpenGL_h

#include "ofxsImageEffect.h"
#include "ofxsMacros.h"

void getTestOpenGLPluginID(OFX::PluginFactoryArray &ids);

/** @brief The plugin that does our work */
class TestOpenGLPlugin : public OFX::ImageEffect
{
public:
    /** @brief ctor */
    TestOpenGLPlugin(OfxImageEffectHandle handle);

private:
    /* Override the render */
    virtual void render(const OFX::RenderArguments &args) OVERRIDE FINAL;

    /* The purpose of this action is to allow a plugin to set up any data it may need
     to do OpenGL rendering in an instance. */
    virtual void contextAttached() OVERRIDE FINAL;
    /* The purpose of this action is to allow a plugin to deallocate any resource
     allocated in \ref ::kOfxActionOpenGLContextAttached just before the host
     decouples a plugin from an OpenGL context. */
    virtual void contextDetached() OVERRIDE FINAL;

    /* The OpenGL context is also set when beginSequenceRender() and endSequenceRender()
     are called. This may be useful to allocate/deallocate sequence-specific OpenGL data. */
    //virtual void beginSequenceRender(const OFX::BeginSequenceRenderArguments &args) OVERRIDE FINAL;
    //virtual void endSequenceRender(const OFX::EndSequenceRenderArguments &args) OVERRIDE FINAL;

    void renderGL(const OFX::RenderArguments &args);
    void renderMesa(const OFX::RenderArguments &args);
    void contextAttachedMesa();
    void contextDetachedMesa();

    // override the rod call
    virtual bool getRegionOfDefinition(const OFX::RegionOfDefinitionArguments &args, OfxRectD &rod) OVERRIDE FINAL;

    virtual void getClipPreferences(OFX::ClipPreferencesSetter &clipPreferences) OVERRIDE FINAL;

private:
    // do not need to delete these, the ImageEffect is managing them for us
    OFX::Clip *_dstClip;
    OFX::Clip *_srcClip;

    OFX::Double2DParam *_scale;
    OFX::Double2DParam *_sourceScale;
    OFX::DoubleParam *_sourceStretch;
    OFX::DoubleParam *_teapotScale;
    OFX::DoubleParam *_angleX;
    OFX::DoubleParam *_angleY;
    OFX::DoubleParam *_angleZ;
    OFX::BooleanParam *_projective;
    OFX::BooleanParam *_mipmap;
    OFX::BooleanParam *_anisotropic;
    OFX::BooleanParam *_useGPUIfAvailable;

    bool _haveAniso;
    float _maxAnisoMax;
};

#endif // Misc_TestOpenGL_h
