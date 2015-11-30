#include "StaticMesh.h"
#include <fstream>


CStaticMesh::CStaticMesh(const CXMLTreeNode &TreeNode) 
	: CNamed(TreeNode)
	, m_NumFaces(0)
	, m_NumVertexs(0)
{
	Load(TreeNode.GetPszProperty("filename"));
}


CStaticMesh::~CStaticMesh()
{
}

//Llegir fitxer .mesh
bool CStaticMesh::Load(const std::string &FileName)
{
	std::ifstream file(FileName.c_str(), std::ios::in | std::ios::binary);

	return true;
}


bool CStaticMesh::Reload()
{
	return true;
}


void CStaticMesh::Render(CRenderManager *RM) const
{

}