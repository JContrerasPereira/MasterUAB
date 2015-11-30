#include "Material.h"
#include "Effect\EffectTechnique.h"
#include "Engine.h"

CMaterial::CMaterial(CXMLTreeNode &TreeNode) : CNamed(TreeNode)
{
	std::string l_EffectTechnique = TreeNode.GetPszProperty("effect_technique");
	m_EffectTechnique = CEngine::GetSingletonPtr()->GetEffectManager()->GetResource(l_EffectTechnique);

	if (l_EffectTechnique == "diffuse_technique")
	{
		for (int i = 0; i < TreeNode.GetNumChildren(); ++i)
		{
			CXMLTreeNode l_Texture = TreeNode(i);
			CTexture * Texture = new CTexture();
			Texture->Load(l_Texture.GetPszProperty("filename"));
			m_Textures.push_back(Texture);
		}
	}
}


CMaterial::~CMaterial()
{
	Destroy();
}


void CMaterial::Apply()
{
	for (int i = 0; i < m_Textures.size(); ++i)
	{
		m_Textures[i]->Activate(1);
	}
}


CEffectTechnique * CMaterial::GetEffectTechnique()
{
	return m_EffectTechnique;
}

void CMaterial::Destroy()
{
	for (int i = 0; i < m_Textures.size(); ++i)
	{
		delete m_Textures[i];
	}

	m_Textures.clear();
}