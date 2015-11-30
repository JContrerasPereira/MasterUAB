#include "StaticMesh.h"


CStaticMesh::CStaticMesh(const CXMLTreeNode &TreeNode) : CNamed(TreeNode)
{
	Load(TreeNode.GetPszProperty("filename"));
}


CStaticMesh::~CStaticMesh()
{
}

//Llegir fitxer .mesh
bool CStaticMesh::Load(const std::string &FileName)
{
	return true;
}


bool CStaticMesh::Reload()
{
	return true;
}


void CStaticMesh::Render(CRenderManager *RM) const
{

}