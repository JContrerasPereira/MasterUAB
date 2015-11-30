#ifndef STATIC_MESH_H
#define STATIC_MESH_H

#include "Utils\Named.h"
#include <vector>
#include "RenderableObject\RenderableVertexs.h"
#include "Material\Material.h"

class CRenderManager;

class CStaticMesh : public CNamed
{
protected:
	std::vector<CRenderableVertexs*> m_RVs;
	std::vector<CMaterial *> m_Materials;
	unsigned int m_NumVertexs, m_NumFaces;
public:
	CStaticMesh(const CXMLTreeNode &TreeNode);
	~CStaticMesh();
	bool Load(const std::string &FileName);
	bool Reload();
	void Render(CRenderManager *RM) const;
};

#endif