set(COCOS_RENDERER_HEADER
    renderer/CCCallbackCommand.h
    renderer/CCCustomCommand.h
    renderer/CCGroupCommand.h
    renderer/CCMaterial.h
    renderer/CCMeshCommand.h
    renderer/CCPass.h
    renderer/CCPipelineDescriptor.h
    renderer/CCQuadCommand.h
    renderer/CCRenderCommand.h
    renderer/CCRenderCommandPool.h
    renderer/CCRenderState.h
    renderer/CCRenderer.h
    renderer/CCTechnique.h
    renderer/CCTexture2D.h
    renderer/CCTextureAtlas.h
    renderer/CCTextureCache.h
    renderer/CCTextureCube.h
    renderer/CCTrianglesCommand.h
    renderer/ccShaders.h
    
    renderer/backend/ProgramManager.h
    renderer/backend/ProgramStateRegistry.h

    renderer/backend/Backend.h
    renderer/backend/Buffer.h
    renderer/backend/CommandBuffer.h
    renderer/backend/DepthStencilState.h
    renderer/backend/Device.h
    renderer/backend/Program.h
    
    renderer/backend/Macros.h
    renderer/backend/RenderPassDescriptor.h
    renderer/backend/RenderPipeline.h
    renderer/backend/RenderTarget.h
    renderer/backend/ShaderModule.h
    renderer/backend/Texture.h
    renderer/backend/PixelFormatUtils.h
    renderer/backend/Types.h
    renderer/backend/Enums.h
    renderer/backend/VertexLayout.h
    renderer/backend/ProgramState.h
    renderer/backend/ShaderCache.h
    renderer/backend/DeviceInfo.h
    )

set(COCOS_RENDERER_SRC
    renderer/CCCallbackCommand.cpp
    renderer/CCCustomCommand.cpp
    renderer/CCGroupCommand.cpp
    renderer/CCMaterial.cpp
    renderer/CCMeshCommand.cpp
    renderer/CCPass.cpp
    renderer/CCQuadCommand.cpp
    renderer/CCRenderCommand.cpp
    renderer/CCRenderState.cpp
    renderer/CCRenderer.cpp
    renderer/CCTechnique.cpp
    renderer/CCTexture2D.cpp
    renderer/CCTextureAtlas.cpp
    renderer/CCTextureCache.cpp
    renderer/CCTextureCube.cpp
    renderer/CCTrianglesCommand.cpp
    renderer/ccShaders.cpp
    renderer/CCColorizer.cpp
    
    renderer/backend/ProgramManager.cpp
    renderer/backend/ProgramStateRegistry.cpp

    renderer/backend/CommandBuffer.cpp
    renderer/backend/DepthStencilState.cpp
    renderer/backend/Device.cpp
    renderer/backend/ShaderModule.cpp
    renderer/backend/Texture.cpp
    renderer/backend/PixelFormatUtils.cpp
    renderer/backend/Types.cpp
    renderer/backend/VertexLayout.cpp
    renderer/backend/Program.cpp
    renderer/backend/ProgramState.cpp
    renderer/backend/ShaderCache.cpp
    renderer/backend/RenderPassDescriptor.cpp
    )

if(CC_USE_GFX)
    list(APPEND COCOS_RENDERER_HEADER
        renderer/backend/gfx/BufferGFX.h
        renderer/backend/gfx/CommandBufferGFX.h
        renderer/backend/gfx/DepthStencilStateGFX.h
        renderer/backend/gfx/DeviceGFX.h
        renderer/backend/gfx/ProgramGFX.h
        renderer/backend/gfx/RenderPipelineGFX.h
	renderer/backend/gfx/RenderTargetGFX.h
        renderer/backend/gfx/ShaderModuleGFX.h
        renderer/backend/gfx/TextureGFX.h
        renderer/backend/gfx/UtilsGFX.h
        renderer/backend/gfx/DeviceInfoGFX.h
    )
    list(APPEND COCOS_RENDERER_SRC
        renderer/backend/gfx/BufferGFX.cpp
        renderer/backend/gfx/CommandBufferGFX.cpp
        renderer/backend/gfx/DepthStencilStateGFX.cpp
        renderer/backend/gfx/DeviceGFX.cpp
        renderer/backend/gfx/ProgramGFX.cpp
        renderer/backend/gfx/RenderPipelineGFX.cpp
	renderer/backend/gfx/RenderTargetGFX.cpp
        renderer/backend/gfx/ShaderModuleGFX.cpp
        renderer/backend/gfx/TextureGFX.cpp
        renderer/backend/gfx/UtilsGFX.cpp
        renderer/backend/gfx/DeviceInfoGFX.cpp
    )
elseif(ANDROID OR WINDOWS OR LINUX)
    list(APPEND COCOS_RENDERER_HEADER
        renderer/backend/opengl/BufferGL.h
        renderer/backend/opengl/CommandBufferGL.h
        renderer/backend/opengl/DepthStencilStateGL.h
        renderer/backend/opengl/DeviceGL.h
        renderer/backend/opengl/ProgramGL.h
        renderer/backend/opengl/RenderPipelineGL.h
        renderer/backend/opengl/ShaderModuleGL.h
        renderer/backend/opengl/TextureGL.h
        renderer/backend/opengl/UtilsGL.h
        renderer/backend/opengl/DeviceInfoGL.h
        renderer/backend/opengl/RenderTargetGL.h
    )
    list(APPEND COCOS_RENDERER_SRC
        renderer/backend/opengl/BufferGL.cpp
        renderer/backend/opengl/CommandBufferGL.cpp
        renderer/backend/opengl/DepthStencilStateGL.cpp
        renderer/backend/opengl/DeviceGL.cpp
        renderer/backend/opengl/ProgramGL.cpp
        renderer/backend/opengl/RenderPipelineGL.cpp
        renderer/backend/opengl/ShaderModuleGL.cpp
        renderer/backend/opengl/TextureGL.cpp
        renderer/backend/opengl/UtilsGL.cpp
        renderer/backend/opengl/DeviceInfoGL.cpp
        renderer/backend/opengl/RenderTargetGL.cpp
    )
else()
    list(APPEND COCOS_RENDERER_HEADER
        renderer/backend/metal/BufferMTL.h
        renderer/backend/metal/BufferManager.h
        renderer/backend/metal/CommandBufferMTL.h
        renderer/backend/metal/RenderTargetMTL.h
        renderer/backend/metal/DepthStencilStateMTL.h
        renderer/backend/metal/DeviceMTL.h
        renderer/backend/metal/RenderPipelineMTL.h
        renderer/backend/metal/ShaderModuleMTL.h
        renderer/backend/metal/TextureMTL.h
        renderer/backend/metal/UtilsMTL.h
        renderer/backend/metal/ProgramMTL.h
        renderer/backend/metal/DeviceInfoMTL.h
    )
    list(APPEND COCOS_RENDERER_SRC
        renderer/backend/metal/BufferMTL.mm
        renderer/backend/metal/BufferManager.mm
        renderer/backend/metal/CommandBufferMTL.mm
        renderer/backend/metal/RenderTargetMTL.mm
        renderer/backend/metal/DepthStencilStateMTL.mm
        renderer/backend/metal/DeviceMTL.mm
        renderer/backend/metal/RenderPipelineMTL.mm
        renderer/backend/metal/ShaderModuleMTL.mm
        renderer/backend/metal/TextureMTL.mm
        renderer/backend/metal/UtilsMTL.mm
        renderer/backend/metal/ProgramMTL.mm
        renderer/backend/metal/DeviceInfoMTL.mm
    )
endif()
