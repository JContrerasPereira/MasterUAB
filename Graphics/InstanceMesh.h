#ifndef INSTANCE_MESH
#define INSTANCE_MESH

#include "RenderableObject\RenderableObject.h"
#include "StaticMesh.h"

class CInstanceMesh : public CRenderableObject
{
private:
	CStaticMesh *m_StaticMesh;
public:
	CInstanceMesh(const std::string &Name, const std::string &CoreName);
	~CInstanceMesh();
	void Render(CRenderManager *RM);
};

#endif