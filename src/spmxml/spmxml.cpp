// Реализация классов для работы с XML, XPath, DTD

#include "stdspm.h"
#include "spmxml.h"

CSpmXml::CSpmXml(bool bAutoDestroy) : m_pXMLDoc(0), m_pCurNode(0), m_bModified(false), m_pCurNodeSet(0), m_nCurItem(-1), m_bAutoDestroy(bAutoDestroy)
{
}

CSpmXml::CSpmXml(xmlDocPtr pDoc, bool bAutoDestroy, bool bModified)
{
	m_pXMLDoc		= pDoc;

	if (pDoc)
		m_pCurNode	= xmlDocGetRootElement(pDoc);
	else
		m_pCurNode	= 0;

	m_bModified		= bModified;
	m_bAutoDestroy	= bAutoDestroy;
	m_pCurNodeSet	= 0;
	m_nCurItem		= -1;
}

CSpmXml::CSpmXml(xmlNodePtr pNode, bool bAutoDestroy, bool bModified)
{
	if (pNode)
	{
		m_pXMLDoc	= pNode->doc;
		m_pCurNode	= pNode;
	}
	else
	{
		m_pXMLDoc	= 0;
		m_pCurNode	= 0;
	}

	m_bModified		= bModified;
	m_bAutoDestroy	= bAutoDestroy;
	m_pCurNodeSet	= 0;
	m_nCurItem		= -1;
}

bool CSpmXml::Attach(xmlDocPtr pDoc, bool bAutoDestroy, bool bModified)
{
	if (pDoc == 0)
		return false;

	Detach();

	m_pXMLDoc	= pDoc;
	m_pCurNode	= xmlDocGetRootElement(pDoc);
	m_bModified	= bModified;
	m_bAutoDestroy = bAutoDestroy;

	return true;
}

bool CSpmXml::Attach(xmlNodePtr pNode, bool bAutoDestroy, bool bModified)
{
	if (pNode == 0)
		return false;

	Detach();

	m_pCurNode	= pNode;
	m_pXMLDoc	= pNode->doc;
	m_bModified	= bModified;
	m_bAutoDestroy = bAutoDestroy;
	
	return true;
}

void CSpmXml::Detach()
{
	m_pCurNode		= 0;
	m_pXMLDoc		= 0;
	m_bModified		= false;
	m_bAutoDestroy	= true;
	m_pCurNodeSet	= 0;
	m_nCurItem		= -1;
	
	m_lstNodes.clear();
}

void CSpmXml::Destroy()
{
	Detach();

	if (m_pXMLDoc)
	{
		xmlFreeDoc(m_pXMLDoc);
		m_pXMLDoc = 0;
	}
}

CSpmXml::~CSpmXml()
{
	if (m_bAutoDestroy)
		Destroy();
}

bool CSpmXml::New(const QString& strRootNode, const QString& strDTDFile)
{
	Destroy();

	m_pXMLDoc = xmlNewDoc(BAD_CAST "1.0");
	if (0 == m_pXMLDoc)
		return false;

	m_pCurNode = xmlNewNode(0, BAD_CAST strRootNode.toUtf8().data());
	if (0 == m_pCurNode)
		return false;

	xmlDocSetRootElement(m_pXMLDoc, m_pCurNode);
	
	if (strDTDFile.size())
		xmlCreateIntSubset(m_pXMLDoc, BAD_CAST strRootNode.toUtf8().data(), NULL, BAD_CAST strDTDFile.toUtf8().data());

	SetModified();
	return true;
}

bool CSpmXml::Load(const QString& strFileName, bool bDTDValidation)
{
	xmlParserCtxtPtr pXMLParser = xmlNewParserCtxt();
	if (0 == pXMLParser)
		return false;


	int nOptions = XML_PARSE_NOBLANKS;
	if (bDTDValidation)
		nOptions |= XML_PARSE_DTDVALID;

	m_pXMLDoc = xmlCtxtReadFile(pXMLParser, strFileName.toLocal8Bit().data(), NULL, nOptions);

	if (0 == m_pXMLDoc)
	{
		xmlFreeParserCtxt(pXMLParser);
		return false;
	}

	// Проверка корректности структуры
	if (bDTDValidation && (false == pXMLParser->valid))
	{
		xmlFreeParserCtxt(pXMLParser);
		return false;
	}

	m_pCurNode = xmlDocGetRootElement(m_pXMLDoc);
	if (0 == m_pCurNode)
		return false;

	SetModified(false);
	xmlFreeParserCtxt(pXMLParser);
	return true;
}

bool CSpmXml::LoadXML(const QString& strXML, bool bDTDValidation)
{
	xmlParserCtxtPtr pXMLParser = xmlNewParserCtxt();
	if (0 == pXMLParser)
		return false;

	int nOptions = XML_PARSE_NOBLANKS;
	if (bDTDValidation)
		nOptions |= XML_PARSE_DTDVALID;

	m_pXMLDoc = xmlCtxtReadDoc(pXMLParser, (xmlChar*)strXML.toUtf8().data(), "", NULL, nOptions);

	if (0 == m_pXMLDoc)
	{
		xmlFreeParserCtxt(pXMLParser);
		return false;
	}

	// Проверка корректности структуры
	if (bDTDValidation && (false == pXMLParser->valid))
	{
		xmlFreeParserCtxt(pXMLParser);
		return false;
	}

	m_pCurNode = xmlDocGetRootElement(m_pXMLDoc);
	if (0 == m_pCurNode)
		return false;

	SetModified(false);
	xmlFreeParserCtxt(pXMLParser);
	return true;
}

bool CSpmXml::Save(const QString& strFileName)
{
	if (0 == m_pXMLDoc)
		return false;

	if (-1 == xmlSaveFormatFileEnc(strFileName.toLocal8Bit(), m_pXMLDoc, "UTF-8", 1))
		return false;

	SetModified(false);
	return true;
}

bool CSpmXml::SaveXML(QString& strXML, const QString& strCodec)
{
	strXML.clear();

	if (0 == m_pXMLDoc)
		return false;

	int len = 0;
	xmlChar* pDoc = 0;
	
	xmlDocDumpMemoryEnc(m_pXMLDoc, &pDoc, &len, strCodec.toLocal8Bit());
	if ((0 == pDoc) || (0 == len))
		return false;

	//strXML.fromLocal8Bit((const char*)pDoc);
	strXML = (const char*)pDoc;

	return true;
}

bool CSpmXml::IsModified()
{
	return m_bModified;
}

void CSpmXml::SetModified(bool bModified)
{
	m_bModified = bModified;
}

xmlNodePtr CSpmXml::AddNode(const QString& strNodeName,	xmlNodePtr pContext, char nContext,	const QString& strContent)
{
	pContext = GetNode(pContext);
	if (0 == pContext)
		return 0;

	xmlNodePtr pResNode = xmlNewChild(pContext, 0, BAD_CAST strNodeName.toUtf8().data(), strContent.isEmpty()? 0: BAD_CAST strContent.toUtf8().data());
	if (0 == pResNode)
		return 0;

	xmlUnlinkNode(pResNode);

	if (!AddNode(pResNode, pContext, nContext))
	{
		xmlFreeNode(pResNode);
		return 0;
	}

	return pResNode;
}

bool CSpmXml::AddNode(xmlNodePtr pNode, xmlNodePtr pContext, char nContext)
{
	if (0 == pNode)
		return false;

	pContext = GetNode(pContext);
	if (0 == pContext)
		return false;

	xmlNodePtr pCurNode = 0;
	switch (nContext)
	{
	case SPM_XML_CHILD:
		pCurNode = xmlAddChild(pContext, pNode);
		break;

	case SPM_XML_NEXT_SIBLING:
		pCurNode = xmlAddNextSibling(pContext, pNode);
		break;

	case SPM_XML_PREV_SIBLING:
		pCurNode = xmlAddPrevSibling(pContext, pNode);
		break;

	default:
		return false;
	}

	if (0 == pCurNode)
		return false;

	m_pCurNode = pCurNode;
	SetModified();
	return true;
}

bool CSpmXml::MoveNode(xmlNodePtr pNode, xmlNodePtr pContext, char nContext)
{
	if (0 == pNode)
		return false;

	xmlUnlinkNode(pNode);

	return AddNode(pNode, pContext, nContext);
}

bool CSpmXml::DeleteNode(xmlNodePtr pNode)
{
	if (0 == pNode)
	{
		if (0 == m_pCurNode)
			return false;

		pNode = m_pCurNode;
		m_pCurNode = m_pCurNode->parent;
	}

	xmlUnlinkNode(pNode);
	xmlFreeNode(pNode);
	SetModified();
	return true;
}

bool CSpmXml::DeleteNodes(const QString& strXPathQuery, xmlNodePtr pParent)
{
	if (strXPathQuery.isEmpty())
		return false;

	pParent = GetNode(pParent);
	if (0 == pParent)
		return false;

	QString strQuery;
	if (strXPathQuery.left(2) != "//") // локальный запрос
	{
		strQuery = (char *)xmlGetNodePath(pParent);
		strQuery += strXPathQuery;
	}
	else
		strQuery = strXPathQuery;

	xmlXPathContextPtr pContext = xmlXPathNewContext(m_pXMLDoc);
	if (0 == pContext)
		return false;

	xmlXPathObjectPtr pQuery = xmlXPathEvalExpression(BAD_CAST strQuery.toUtf8().data(), pContext);
	xmlXPathFreeContext(pContext);
	if (0 == pQuery)
		return false;

	xmlNodeSetPtr pNodeSet = pQuery->nodesetval;
	if ((0 == pNodeSet) || (0 == pNodeSet->nodeNr))
		return false;

	for (int i = 0; i < pNodeSet->nodeNr; i++)
	{
		xmlNodePtr pNode = pNodeSet->nodeTab[i];
		xmlUnlinkNode(pNode);
		SetModified();
	}

	xmlXPathFreeNodeSet(pNodeSet);
	return true;
}

QString CSpmXml::GetPath(xmlNodePtr pNode)
{
	QString strRes;

	pNode = GetNode(pNode);
	if (0 == pNode)
		return strRes;

	return QString::fromUtf8((char *)xmlGetNodePath(pNode));
}

QString CSpmXml::GetName(xmlNodePtr pNode)
{
	QString strRes;

	pNode = GetNode(pNode);
	if (0 == pNode)
		return strRes;

	return QString::fromUtf8((char *)pNode->name);
}

QVariant CSpmXml::GetValue(xmlNodePtr pNode)
{
	QVariant vtRes;

	pNode = GetNode(pNode);
	if (0 == pNode)
		return vtRes;

	if (pNode->type != XML_TEXT_NODE && pNode->type != XML_COMMENT_NODE)	// patch by vpasha 01.09.09
		return vtRes;

	QString strValue = QString::fromUtf8((char *)xmlNodeGetContent(pNode));
	if (strValue.startsWith(":", Qt::CaseInsensitive)) // Возможно хранится вариант
	{
		vtRes = UnpackValue(strValue);
		if (vtRes.isValid())
			return vtRes;
		else
			return strValue;
	}
	else
		return strValue;
}

bool CSpmXml::SetValue(const QVariant& vtValue, xmlNodePtr pNode)
{
	pNode = GetNode(pNode);
	if (0 == pNode)
		return false;

	QString strValue = PackValue(vtValue);
	if (strValue.isEmpty())
		return false;

	xmlNodeSetContent(pNode, BAD_CAST strValue.toUtf8().data());
	SetModified();
	return true;
}

QVariant CSpmXml::GetAttr(const QString& strAttrName, xmlNodePtr pNode)
{
	QVariant vtRes;

	pNode = GetNode(pNode);
	if (0 == pNode)
		return vtRes;

	if (!xmlHasProp(pNode, BAD_CAST strAttrName.toUtf8().data()))
		return vtRes;

	QString strValue = QString::fromUtf8((char *)xmlGetProp(pNode, BAD_CAST strAttrName.toUtf8().data()));
	if (strValue.startsWith(":", Qt::CaseInsensitive)) // Возможно хранится вариант
	{
		vtRes = UnpackValue(strValue);
		if (vtRes.isValid())
			return vtRes;
		else
			return strValue;
	}
	else
		return strValue;
}

QString CSpmXml::PackValue(const QVariant& vtValue)
{
	QString strValue;

	switch (vtValue.type())
	{
	case QVariant::Size:
		{
			QSize size = vtValue.toSize();
			strValue.sprintf(":%s:%d:%d", vtValue.typeName(), size.width(), size.height());
		}
		break;
	case QVariant::Point:
		{
			QPoint pt = vtValue.toPoint();
			strValue.sprintf(":%s:%d:%d", vtValue.typeName(), pt.x(), pt.y());
		}
		break;

	default:
		strValue = vtValue.toString();
		break;
	};	

	return strValue;
}

QVariant CSpmXml::UnpackValue(const QString& strValue)
{
	QVariant vtRes;

	QStringList parts = strValue.split(":", QString::SkipEmptyParts);
	if (parts.size() == 0)
		return vtRes;

	switch(QVariant::nameToType(parts.at(0).toUtf8().data()))
	{
	case QVariant::Size:
		{
			if (parts.size() != 3)
				break;

			return QSize(parts.at(1).toInt(), parts.at(2).toInt());
		}
		break;
	case QVariant::Point:
		{
			if (parts.size() != 3)
				break;

			return QPoint(parts.at(1).toInt(), parts.at(2).toInt());
		}
		break;
	}

	return vtRes;
}

bool CSpmXml::SetAttr(const QString& strAttrName, const QVariant& vtAttrVal, xmlNodePtr pNode, bool bCreate)
{
	pNode = GetNode(pNode);
	if (0 == pNode)
		return false;

	QString strValue = PackValue(vtAttrVal);

	if (0 == xmlHasProp(pNode, BAD_CAST strAttrName.toUtf8().data()))
	{
		if (false == bCreate)
			return false;

		return 0 != xmlNewProp(pNode, BAD_CAST strAttrName.toUtf8().data(), BAD_CAST strValue.toUtf8().data());
	}

	bool bRes = (0 != xmlSetProp(pNode, BAD_CAST strAttrName.toUtf8().data(), BAD_CAST strValue.toUtf8().data()));
	if (bRes)
		SetModified();

	return bRes;
}

bool CSpmXml::DeleteAttr(const QString& strAttrName, xmlNodePtr pNode)
{
	pNode = GetNode(pNode);
	if (0 == pNode)
		return false;

	bool bRes = (0 == xmlUnsetProp(pNode, BAD_CAST strAttrName.toUtf8().data()));
	if (bRes)
		SetModified();

	return bRes;
}

QString CSpmXml::GetQuery(QStringList lstKeys, xmlNodePtr pNode)
{
	pNode = GetNode(pNode);
	if (0 == pNode)
		return "";

	QStringList strQuery("//");
	strQuery.append(QString::fromUtf8((char *)pNode->name));

	if (lstKeys.size())
	{
		strQuery.append("[");

		for (int i = 0; i < lstKeys.size(); i++)
		{
			QVariant vtValue = GetAttr(lstKeys.at(i));
			if (!vtValue.isValid())
				return "";

			if (i > 0)
				strQuery.append("and");

			strQuery.append("(@");
			strQuery.append(lstKeys.at(i));
			strQuery.append("='");
			strQuery.append(vtValue.toString());
			strQuery.append("')");
		}

		strQuery.append("]");
	}

	return strQuery.join("");
}


xmlNodePtr CSpmXml::Clone(xmlNodePtr pNode, bool bDeep)
{
	pNode = GetNode(pNode);
	if (0 == pNode)
		return 0;

	int nRecursive = 1;
	if (!bDeep)
		nRecursive = 2;

	return xmlCopyNode(pNode, nRecursive);
}

xmlNodePtr CSpmXml::GetPosition()
{
	if (0 == m_pXMLDoc)
		return 0;

	if (0 == m_pCurNode)
		m_pCurNode = xmlDocGetRootElement(m_pXMLDoc);

	return m_pCurNode;
}

void CSpmXml::SetPosition(xmlNodePtr pNode)
{
	if (0 == m_pXMLDoc)
		return;

	if (pNode)
		m_pCurNode = pNode;
	else
		m_pCurNode = xmlDocGetRootElement(m_pXMLDoc);
}

xmlNodePtr CSpmXml::MoveParent()
{
	xmlNodePtr pNode = GetNode(0);
	if (0 == pNode)
		return 0;

	if (0 == pNode->parent)
		return 0;

	m_pCurNode = pNode->parent;
	return m_pCurNode;
}

bool CSpmXml::HasChilds(xmlNodePtr pNode)
{
	pNode = GetNode(pNode);

	if (0 == pNode)
		return false;

	return 0 != pNode->children;
}

xmlNodePtr CSpmXml::MoveFirstChild()
{
	xmlNodePtr pNode = GetNode(0);
	if (0 == pNode)
		return 0;

	if (0 == pNode->children)
		return 0;

	m_pCurNode = pNode->children;
	return m_pCurNode;
}

xmlNodePtr CSpmXml::MoveNextSibling()
{
	xmlNodePtr pNode = GetNode(0);
	if (0 == pNode)
		return 0;

	if (0 == pNode->next)
		return 0;

	m_pCurNode = pNode->next;
	return m_pCurNode;
}

xmlNodePtr CSpmXml::MoveFirst(const QString& strXPathQuery, xmlNodePtr pParent, int* pnCount)
{
	if (strXPathQuery.isEmpty())
		return 0;

	pParent = GetNode(pParent);
	if (0 == pParent)
		return 0;

	QString strQuery;
	if (strXPathQuery.left(2) != "//") // локальный запрос
	{
		strQuery = (char *)xmlGetNodePath(pParent);
		strQuery += strXPathQuery;
	}
	else
		strQuery = strXPathQuery;

	xmlXPathContextPtr pContext = xmlXPathNewContext(m_pXMLDoc);
	if (0 == pContext)
		return 0;

	xmlXPathObjectPtr pQuery = xmlXPathEvalExpression(BAD_CAST strQuery.toUtf8().data(), pContext);
	xmlXPathFreeContext(pContext);

	if (0 == pQuery)
		return 0;

	if (m_pCurNodeSet)
	{
		xmlXPathFreeNodeSet(m_pCurNodeSet);
		m_pCurNodeSet	= 0;
	}

	m_nCurItem = 0;

	m_pCurNodeSet = pQuery->nodesetval;
	if (0 == m_pCurNodeSet)
		return 0;

	if (pnCount)
		*pnCount = m_pCurNodeSet->nodeNr;

	if (0 == m_pCurNodeSet->nodeNr)
		return 0;

	m_pCurNode = m_pCurNodeSet->nodeTab[m_nCurItem];
	return m_pCurNode;
}

xmlNodePtr CSpmXml::MoveNext()
{
	if (0 == m_pXMLDoc)
		return 0;

	if (0 == m_pCurNodeSet)
		return 0;

	m_nCurItem++;

	if (m_nCurItem < m_pCurNodeSet->nodeNr)
	{
		m_pCurNode = m_pCurNodeSet->nodeTab[m_nCurItem];
		return m_pCurNode;
	}
	else
	{
		xmlXPathFreeNodeSet(m_pCurNodeSet);
		m_pCurNodeSet = 0;
		m_nCurItem = 0;
		return 0;
	}
}

bool CSpmXml::SetContent(const QString& strContent,	xmlNodePtr pNode)
{
	pNode = GetNode(pNode);
	if (0 == pNode)
		return false;

	xmlNodeSetContent(pNode, BAD_CAST strContent.toUtf8().data());
	return true;
}

QString CSpmXml::GetContent(xmlNodePtr pNode)
{
	pNode = GetNode(pNode);
	if (0 == pNode)
		return "";

	return QString::fromUtf8((char *)xmlNodeGetContent(pNode));
}

bool CSpmXml::Push(xmlNodePtr pNode)
{
	pNode = GetNode(pNode);

	if (0 == pNode)
		return false;

	m_lstNodes.push_back(pNode);
	return true;
}

xmlNodePtr CSpmXml::Pop()
{
	if (0 == m_lstNodes.size())
		return 0;

	m_pCurNode = m_lstNodes.back();
	m_lstNodes.pop_back();
	return m_pCurNode;
}

bool CSpmXml::PushQuery()
{
	if (0 == m_pCurNodeSet)
		return false;

	m_lstSets.push_back(CNodeSet(m_pCurNodeSet, m_nCurItem));
	return true;
}

bool CSpmXml::PopQuery()
{
	if (0 == m_lstSets.size())
		return false;

	if (m_pCurNodeSet)
		xmlXPathFreeNodeSet(m_pCurNodeSet);

	CNodeSet& nodeset = m_lstSets.back();
	m_pCurNodeSet = nodeset.set;
	m_nCurItem = nodeset.cur;
	m_lstSets.pop_back();
	return true;
}

xmlNodePtr CSpmXml::GetNode(xmlNodePtr pNode)
{	
	if (0 == m_pXMLDoc)
		return 0;

	if (pNode)
		return pNode;

	if (m_pCurNode)
		return m_pCurNode;

	return xmlDocGetRootElement(m_pXMLDoc);
}