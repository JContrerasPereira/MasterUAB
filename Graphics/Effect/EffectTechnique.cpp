#include "EffectTechnique.h"


CEffectTechnique::CEffectTechnique(CXMLTreeNode &TreeNode) : CNamed(TreeNode)
{
	m_PixelShaderName = TreeNode.GetPszProperty("pixel_shader");
	m_VertexShaderName = TreeNode.GetPszProperty("vertex_shader");
}


CEffectTechnique::~CEffectTechnique()
{
}


CEffectVertexShader * CEffectTechnique::GetVertexShader()
{
	return m_VertexShader;
}


CEffectPixelShader * CEffectTechnique::GetPixelShader()
{
	return m_PixelShader;
}


void CEffectTechnique::Refresh()
{
}