#include "EffectVertexShader.h"
#include "Engine.h"
#include "VertexTypes.h"


CEffectVertexShader::CEffectVertexShader(const CXMLTreeNode &TreeNode) : CEffectShader(TreeNode)
{
	m_VertexType = TreeNode.GetPszProperty("vertex_type");
	Load();
}


CEffectVertexShader::~CEffectVertexShader()
{
}


bool CEffectVertexShader::Load()
{
	ID3DBlob *l_VSBlob = NULL;
	bool l_Loaded = LoadShader(m_Filename, m_EntryPoint, m_ShaderModel, &l_VSBlob);
	if (!l_Loaded)
		return false;
	CRenderManager *l_RenderManager = CEngine::GetSingleton().GetRenderManager();
	ID3D11Device *l_Device = CEngine::GetSingleton().GetRenderManager()->GetDevice();
	HRESULT l_HR = l_Device->CreateVertexShader(l_VSBlob->GetBufferPointer(), l_VSBlob->GetBufferSize(), NULL, &m_VertexShader);
	if (FAILED(l_HR))
	{
		l_VSBlob->Release();
		return false;
	}
	if (m_VertexType == "MV_POSITION_NORMAL_TEXTURE_VERTEX")
		l_Loaded = TTEXTURE_VERTEX::CreateInputLayout(l_RenderManager, l_VSBlob, &m_VertexLayout);
	else if (m_VertexType == "MV_POSITION_COLOR_VERTEX")
		l_Loaded = TCOLORED_VERTEX::CreateInputLayout(l_RenderManager, l_VSBlob, &m_VertexLayout);
	else
		//Info("Vertex type '%s' not recognized on CEffectVertexShader::Load", m_VertexType.c_str());
	l_VSBlob->Release();
	if (!l_Loaded)
		return false;
	return CreateConstantBuffer();
}


void CEffectVertexShader::Destroy()
{
	int i = 0;
}