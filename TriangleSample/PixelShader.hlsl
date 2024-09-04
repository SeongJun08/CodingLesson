Texture2D shaderTexture;
SamplerState defaultSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

struct VOut
{
    float4 position : SV_Position;
    float2 tex : TEXCOORD0;
};

float4 main(VOut input) : SV_TARGET
{
    //float4 color = shaderTexture.Sample(defaultSampler, input.tex);
    
    /*
    color[0] = color[1] = color[2] = (color.r + color.g + color.b) / 3;
    if (color[0] > 0.5)
    {
        color[0] = color[1] = color[2] = 1;
    }
    else
    {
        color[0] = color[1] = color[2] = 0;
    }
    */
    
    //float4 color;
    
    //float2 uv = input.tex;
    //uv = uv - float2(0.5, 0.5);
    //color = 1 - length(uv);
    //color *= 0.5;
    //color += shaderTexture.Sample(defaultSampler, input.tex);
    //color.a = 1;
    
    float4 color = shaderTexture.Sample(defaultSampler, input.tex);
    
    return color;
}
