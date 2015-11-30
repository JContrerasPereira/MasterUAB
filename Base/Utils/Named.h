#ifndef NAMED_H
#define NAMED_H

#include "XML\XMLTreeNode.h"

class CNamed
{
protected:
	std::string m_Name;

public:
	CNamed() {}
	CNamed(const CXMLTreeNode &TreeNode);
	CNamed(const std::string &Name);
	virtual void SetName(const std::string &Name);
	virtual const std::string &GetName();
};

#endif