#include "Utils\SingletonPattern.h"
#include "RenderManager.h"
#include "Material\MaterialManager.h"
#include "ContextManager.h"
#include "Effect\EffectManager.h"
#include "RenderableObject\RenderableObjectsManager.h"
#include "Mesh\StaticMeshManager.h"

class CEngine : public CSingleton<CEngine>
{
private:
	CRenderManager *m_RenderManager;
	CMaterialManager *m_MaterialManager;
	CContextManager *m_ContextManager;
	CEffectManager * m_EffectManager;
	CRenderableObjectsManager * m_RenderableObjectsManager;
	CStaticMeshManager * m_StaticMeshManager;
public:
	CEngine(CMaterialManager * MaterialManager, CRenderManager * RenderManager, CContextManager * ContextManager, CEffectManager * EffectManager, CRenderableObjectsManager * RenderableObjectsManager, CStaticMeshManager * StaticMeshManager)
		: m_MaterialManager(MaterialManager)
		, m_RenderManager(RenderManager)
		, m_ContextManager(ContextManager)
		, m_EffectManager(EffectManager)
		, m_RenderableObjectsManager(RenderableObjectsManager)
		, m_StaticMeshManager(StaticMeshManager)
	{
	}
	virtual ~CEngine()
	{
	}
	CRenderManager * GetRenderManager() { return m_RenderManager; }
	CMaterialManager * GetMaterialManager() { return m_MaterialManager; }
	CContextManager * GetContextManager() { return m_ContextManager; }
	CEffectManager * GetEffectManager() { return m_EffectManager; }
	CRenderableObjectsManager * GetRenderableObjectsManager() { return m_RenderableObjectsManager; }
	CStaticMeshManager * GetStaticMeshManager() { return m_StaticMeshManager; }
};