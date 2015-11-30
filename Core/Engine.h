#include "Utils\SingletonPattern.h"
#include "RenderManager.h"
#include "Material\MaterialManager.h"
#include "ContextManager.h"
#include "Effect\EffectManager.h"

class CEngine : public CSingleton<CEngine>
{
private:
	CRenderManager *m_RenderManager;
	CMaterialManager *m_MaterialManager;
	CContextManager *m_ContextManager;
	CEffectManager * m_EffectManager;
public:
	CEngine(CMaterialManager * MaterialManager, CRenderManager * RenderManager, CContextManager * ContextManager, CEffectManager * EffectManager)
		: m_MaterialManager(MaterialManager)
		, m_RenderManager(RenderManager)
		, m_ContextManager(ContextManager)
		, m_EffectManager(EffectManager)
	{
	}
	virtual ~CEngine()
	{
	}
	CRenderManager * GetRenderManager() { return m_RenderManager; }
	CMaterialManager * GetMaterialManager() { return m_MaterialManager; }
	CContextManager * GetContextManager() { return m_ContextManager; }
	CEffectManager * GetEffectManager() { return m_EffectManager; }
};