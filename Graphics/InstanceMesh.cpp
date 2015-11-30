#include "InstanceMesh.h"
#include "Engine.h"

CInstanceMesh::CInstanceMesh(const std::string &Name, const std::string &CoreName)
{
}

void CInstanceMesh::Render(CRenderManager *RM)
{
	RM->Render(CEngine::GetSingleton().GetContextManager(), CEngine::GetSingleton().GetMaterialManager());
}