struct VOut
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

float4 main(VOut input) : SV_TARGET
{
	return input.color;
}
