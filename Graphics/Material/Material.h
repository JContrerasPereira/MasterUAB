#ifndef MATERIAL_H
#define MATERIAL_H

#include "Utils\Named.h"
#include <vector>
#include "Texture\Texture.h"
#include "Effect\EffectTechnique.h"


class CMaterial : public CNamed
{
private:
	std::vector<CTexture *> m_Textures;
	CEffectTechnique *m_EffectTechnique;
	void Destroy();
public:
	CMaterial(CXMLTreeNode &TreeNode);
	virtual ~CMaterial();
	virtual void Apply();
	CEffectTechnique * GetEffectTechnique();
};

#endif