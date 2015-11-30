#include "EffectManager.h"

CEffectManager::CEffectManager()
{
}


CEffectManager::~CEffectManager()
{
	Destroy();
}


void CEffectManager::Reload()
{
}


void CEffectManager::Load(const std::string &Filename)
{
	CXMLTreeNode l_XML;
	if (l_XML.LoadFile(Filename.c_str()))
	{
		CXMLTreeNode l_Effects = l_XML["effects"];
		if (l_Effects.Exists())
		{
			for (int i = 0; i < l_Effects.GetNumChildren(); ++i)
			{
				CXMLTreeNode l_Effect = l_Effects(i);

				if (l_Effect.GetName() == std::string("effect_technique"))
				{
					CEffectTechnique * Effect = new CEffectTechnique(l_Effect);
					AddResource(Effect->GetName(), Effect);
				}
				else if (l_Effect.GetName() == std::string("vertex_shader"))
				{
					CEffectVertexShader * Effect = new CEffectVertexShader(l_Effect);
					m_VertexShaders.AddResource(Effect->GetName(), Effect);
				}
				else if (l_Effect.GetName() == std::string("pixel_shader"))
				{
					CEffectPixelShader * Effect = new CEffectPixelShader(l_Effect);
					m_PixelShaders.AddResource(Effect->GetName(), Effect);
				}
			}
		}
	}
}


CEffectVertexShader * CEffectManager::GetVertexShader(const std::string &VertexShader)
{
	TMapResource::iterator it = m_Resources.find(VertexShader);

	if (it != m_Resources.end())
	{
		return it->second->GetVertexShader();
	}
	else
	{
		return NULL;
	}
}


CEffectPixelShader * CEffectManager::GetPixelShader(const std::string &PixelShader)
{
	TMapResource::iterator it = m_Resources.find(PixelShader);

	if (it != m_Resources.end())
	{
		return it->second->GetPixelShader();
	}
	else
	{
		return NULL;
	}
}