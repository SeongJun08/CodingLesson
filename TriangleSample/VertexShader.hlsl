struct VOut
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

VOut main( float4 pos : POSITION, float4 col : COLOR )
{
    VOut output;
    
    output.position = pos;
    output.color = col;

    return output;
}
