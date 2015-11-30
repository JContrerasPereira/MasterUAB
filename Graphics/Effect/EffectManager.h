#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "Utils\TemplatedMapManager.h"
#include "Effect\EffectTechnique.h"
#include "Effect\EffectParameters.h"
#include "Effect\EffectVertexShader.h"
#include "Effect\EffectPixelShader.h"

class CEffectManager : public CTemplatedMapManager<CEffectTechnique>
{
private:
	CTemplatedMapManager<CEffectVertexShader> m_VertexShaders;
	CTemplatedMapManager<CEffectPixelShader> m_PixelShaders;
public:
	static CEffectParameters m_Parameters;
	CEffectManager();
	virtual ~CEffectManager();
	void Reload();
	void Load(const std::string &Filename);
	CEffectVertexShader * GetVertexShader(const std::string &VertexShader);
	CEffectPixelShader * GetPixelShader(const std::string &PixelShader);
};

#endif