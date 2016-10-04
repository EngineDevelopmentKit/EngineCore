#pragma once
#ifndef __EDK_GFX_PIPELINE_STATE_H__
#define __EDK_GFX_PIPELINE_STATE_H__

namespace EDK
{
    namespace Graphics
    {
        class ShaderProgram;
        class PipelineSignature;

        class PipelineState
        {



            ShaderProgram *mShaderProgram;
            PipelineSignature *mPipelineSignature;
        };
    }
}

#endif