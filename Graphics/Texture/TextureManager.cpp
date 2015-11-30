#include "TextureManager.h"


CTextureManager::CTextureManager()
{
}


CTextureManager::~CTextureManager()
{
	Destroy();
}


CTexture * CTextureManager::GetTexture(const std::string &Filename)
{
	return GetResource(Filename);
}


void CTextureManager::Reload()
{
	TMapResource::iterator it = m_Resources.begin();
	while (it != m_Resources.end())
	{
		it->second->Reload();
		it++;
	}
}