#pragma once

namespace renderer
{
	/// <summary>
	/// GLSL shader programs
	/// </summary>

	struct GLSL 
	{
		static char World3DEntityVertexShaderCode[];
		static char World3DBlockVertexShaderCode[];
		static char World3DBlockFragmentCode[];
		static char LoadingShaderCode[];
		static char LoadingFragmentCode[];
	};

}
