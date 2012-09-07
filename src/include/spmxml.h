/// \file ���������� ������� ��� ������ � XML, XPath, DTD

#ifndef _SYSTEMPROM_XML_H
#define _SYSTEMPROM_XML_H

// � ���������� ������� ���������� ��������� ��������� ���� ������ ������������ ������:
// ../../common/libxml2/include
// ../../common/iconv/include

#include <QString>
#include <QVariant>

#include "libxml/xmlreader.h"
#include "libxml/xpath.h"

#ifdef SPM_XML_EXPORTS
	#if defined(WIN32) || defined(_WIN32)
		#define SPM_XML_API __declspec(dllexport)
	#else
		#define SPM_XML_API 
	#endif
#else
	#if defined(WIN32) || defined(_WIN32)
		#define SPM_XML_API __declspec(dllimport)
	#else
		#define SPM_XML_API 
	#endif
#endif

#define SPM_XML_CHILD			1	///< ����� ���� ��������� � ��������� ������������ ����
#define SPM_XML_NEXT_SIBLING	2	///< ����� ���� ��������� �� ����������� �����
#define SPM_XML_PREV_SIBLING	3	///< ����� ���� ��������� ����� ����������� �����

/// �����-�������� ��� ������ � XML ����������
class SPM_XML_API CSpmXml
{
public:
	/// ����������� �� ���������.
	/// ��������� ���������� ������������� ��� ������ ������� \ref New, \ref Load ��� \ref Attach
	CSpmXml(				
				bool bAutoDestroy = true	/// < ������� ��������������� ������������ ���� ��������, ��������� � ����������. ������ ������������ �������� �������������� ��� ������ ������� \ref Destroy
			);

	/// ����������� ��� �������� � ������������� ���������.
	CSpmXml(
				xmlDocPtr pDoc,				/// < ��������� �� ������������� ��������
				bool bAutoDestroy = false,	/// < ������� ��������������� ������������ ���� ��������, ��������� � ����������. ������ ������������ �������� �������������� ��� ������ ������� \ref Destroy
				bool bModified = false		/// < ������� ������� ��������� ��������� � ������� �������� ��� ���������� ����������
			);

	/// ����������� ��� �������� � ������������� ��������� �� ��������� ����.
	/// ��������� ���� �������� ������� ����� ��� ���������� ����������� ��������.
	CSpmXml	(
				xmlNodePtr pNode,			/// < ��������� �� ���� �������������� ��������
				bool bAutoDestroy = false,	/// < ������� ��������������� ������������ ���� ��������, ��������� � ����������. ������ ������������ �������� �������������� ��� ������ ������� \ref Destroy
				bool bModified = false		/// < ������� ������� ��������� ��������� � ������� �������� ��� ���������� ����������
			);

	/// ����������
	virtual ~CSpmXml();

// ���������
public:
	/// �������� ��� ������� ������� � ������� ���������
	xmlDocPtr operator ->() {return m_pXMLDoc;};

	/// �������� �������������� ���� � ������ ���������
	operator xmlDocPtr() {return m_pXMLDoc;};

	/// �������� �������������� ���� � ������ ���� ���������
	operator xmlNodePtr() {return m_pCurNode;};

// �������
public:
	/// �������� � ������������� ���������.
	/// \return ������� ���������� ���������� ��������.
	bool Attach	(
					xmlDocPtr pDoc,				/// < ��������� �� ������������� ��������
					bool bAutoDestroy = false,	/// < ������� ��������������� ������������ ���� ��������, ��������� � ����������. ������ ������������ �������� �������������� ��� ������ ������� \ref Destroy
					bool bModified = false		/// < ������� ������� ��������� ��������� � ������� �������� ��� ���������� ����������
				);

	/// �������� � ������������� ��������� �� ��������� ����.
	/// ��������� ���� �������� ������� ����� ��� ���������� ����������� ��������.
	/// \return ������� ���������� ���������� ��������.
	bool Attach	(
					xmlNodePtr pNode,			/// < ��������� �� ���� �������������� ��������
					bool bAutoDestroy = false,	/// < ������� ��������������� ������������ ���� ��������, ��������� � ����������. ������ ������������ �������� �������������� ��� ������ ������� \ref Destroy
					bool bModified = false		/// < ������� ������� ��������� ��������� � ������� �������� ��� ���������� ����������
				);

	/// ������������ �� ���������
	void Detach();

	/// ������������ ���� ��������, ��������� � ����������
	void Destroy();

	/// �������� ������ ���������
	/// \return ������� ���������� �������� ���������.
	bool New(
				const QString& strRootNode, /// < ������������ ��������� ���� ���������
				const QString& strDTDFile = "" /// < ������ ��� ����� � DTD ���������� ������������ ���������
			);

	/// �������� ������������� ���������
	/// \return ������� ���������� �������� ���������.
	bool Load	(
					const QString& strFileName,			 ///< ������ ��� ����� ����������� ���������
					bool bDTDValidation = true			///< ������� ������������� �������� ������������ ��������� 
				);

	/// �������� ������������� ��������� �� ������
	/// \return ������� ���������� �������� ���������.
	bool LoadXML(
					const QString& strXML, /// < ��������� ���������� ����������� ���������
					bool bDTDValidation = true	/// < ������� ������������� �������� ������������ ��������� 
				);

	/// ���������� ��������� � ����
	/// \return ������� ���������� ���������� ���������.
	bool Save	(
					const QString& strFileName /// < ������ ��� ����� ��� ���������� ���������
				);

	/// ���������� ��������� � ������
	/// \return ������� ���������� ���������� ���������.
	bool SaveXML(
					QString& strXML, /// < ������ ��� ���������� ���������
					const QString& strCodec = "ASCII" /// < ��������� �������� ������
				);

	/// �������� ������� ���������.
	/// \return ������� ������� ��������� ��������� � ������� �������� ��� ���������� ����������
	bool IsModified	();

	/// ��������� �������� ������� ���������
	void SetModified(
						bool bModified = true /// < ������� ������� ��������� ��������� � ������� �������� ��� ���������� ����������
					);

	/// �������� ������ ����.
	/// ����� ��������� �������� ����, �� ���������� ������� ��� ���������.
	/// \return ��������� �� ��������� ����. ���� ������������ 0, �� ��� �������� �������� ������
	xmlNodePtr AddNode	(
							const QString& strNodeName,		///< ������������ ������������ ����
							xmlNodePtr pContext = 0,		///< ��������� �� ����������� ����. ���� ���������� 0, ����������� ����� ��������� ������� ����.
							char nContext = SPM_XML_CHILD,	///< ��������� ������ ���� ������������ ������������
							const QString& strContent = ""	///< ���������� ����
						);

	/// ���������� ������������� ����, ���������� �������� ���������� libxml ��� ��� ������ ������� \ref Clone
	/// \return ������� ��������� ���������� ��������
	bool AddNode	(
						xmlNodePtr pNode,				///< ��������� �� �������������� ����
						xmlNodePtr pContext = 0,		///< ��������� �� ����������� ����. ���� ���������� 0, ����������� ����� ��������� ������� ����.
						char nContext = SPM_XML_CHILD	///< ��������� ������ ���� ������������ ������������
					);

	/// ������� ����, ���������� �������� ���������� libxml ��� ��� ������ ������� \ref Clone
	/// \return ������� ��������� ���������� ��������
	bool MoveNode	(
						xmlNodePtr pNode,				///< ��������� �� ������������ ����
						xmlNodePtr pContext = 0,		///< ��������� �� ����������� ����. ���� ���������� 0, ����������� ����� ��������� ������� ����.
						char nContext = SPM_XML_CHILD	///< ��������� ������ ���� ������������ ������������
					);

	/// �������� ����
	/// \return ������� ��������� �������� ����.
	bool DeleteNode	(
						xmlNodePtr pNode = 0 ///< ��������� ����. ���� ������� 0, �� ��������� ������� ����.
					);

	/// �������� ������ �����, ��������������� XPath �������
	/// \return ������� ��������� �������� �����.
	bool DeleteNodes(
						const QString& strXPathQuery,		///< XPath ������, ������������ ��� ��������� ������ ��������� �����
						xmlNodePtr pParent = 0				///< ����, � ��������� �������� �������������� �����. ���� ���������� 0, �� ����� �������������� � ��������� �������� ����
					);

	/// ��������� ����������� ���� ����
	/// \return ���������� ���� ����.
	QString GetPath	(
						xmlNodePtr pNode = 0		///< ����, ��� ��� ���������� �������. ���� ������� 0, �� ������������ ��� �������� ����
					);

	/// ��������� ����� ����
	/// \return ��� ����.
	QString GetName	(
						xmlNodePtr pNode = 0		///< ����, ��� ��� ���������� �������. ���� ������� 0, �� ������������ ��� �������� ����
					);

	/// ��������� �������� ����
	/// \return �������� ����. ���� ��� ��������� �������� �������� ������, ��� ������������� �������� ��������������� � QVariant::Invalid
	QVariant GetValue	(
							xmlNodePtr pNode = 0		///< ����, ��� �������� ���������� �������. ���� ������� 0, �� �������� ������� � �������� ����
						);

	/// ��������� �������� ����
	/// \return ������� ��������� ���������� ��������.
	bool SetValue	(
						const QVariant& vtValue,	///< ��������������� ��������
						xmlNodePtr pNode = 0		///< ����, ��� �������� ���������� ����������. ���� ������� 0, �� ��������������� �������� �������� ����
					);

	/// ��������� �������� ��������
	/// \return �������� ��������. ���� ��� ��������� �������� �������� ������, ��� ������������� �������� ��������������� � QVariant::Invalid
	QVariant GetAttr(
					const QString& strAttrName, ///< �������� ��������
					xmlNodePtr pNode = 0		///< ����, ���������� �������. ���� ������� 0, �� ������� ������� � �������� ��������
				);

	/// ��������� �������� ��������
	/// \return ������� ��������� ���������� ��������.
	bool SetAttr(
					const QString& strAttrName, ///< �������� ��������
					const QVariant& vtAttrVal,	///< ��������������� ��������
					xmlNodePtr pNode = 0,		///< ����, ���������� �������. ���� ������� 0, �� ������� ������� � �������� ����
					bool bCreate = true			///< ������� ������������� �������� �������� ��� ��� ����������
				);

	/// �������� ��������
	/// \return ������� ��������� ���������� ��������.
	bool DeleteAttr	(
						const QString& strAttrName,	///< ��� ���������� ��������.
						xmlNodePtr pNode = 0		///< ����, ���������� �������. ���� ������� 0, �� ������� ��������� � �������� ����
					);

	/// ��������� XPath ������� ��� ������ ����
	/// \return ������, ���������� XPath ������ ��� ������ ����
	QString GetQuery(
						QStringList lstKeys,		///< ������������ �������� ���������
						xmlNodePtr pNode = 0		///< ���� ��� ��������� �������. ���� ������� 0, ������ ����������� ��� �������� ����
					);

	/// ������������ ����. ������������� ���� � ���������� ����� ������������ � ������ ����� ��������� ��� ������ ������� \ref AddNode
	/// \return ��������� �� ������������� ����. ���� ������������ 0, �� ��� ������������ �������� ������.
	xmlNodePtr Clone(
						xmlNodePtr pNode = 0, ///< ����������� ����. ���� ������� 0, �� ����������� ������� ����
						bool bDeep = true	  ///< ������� ������������ ������������, ��� ������� ����������� �� ��������� ���������� ����
					);

	/// ��������� �������� ����
	/// \return ��������� �� ������� ����. ���� ������������ 0, �� ������� ���� �� ���������.
	xmlNodePtr GetPosition();

	/// ��������� �������� ����
	void SetPosition(
						xmlNodePtr pNode = 0	///< ��������� �� ����, ��������������� � �������� ��������. ���� ���������� 0, �� � �������� �������� ��������������� �������� ����
					);

	/// ����������� � ������������� ����.
	/// \return ��������� �� ������������ ����. ���� ������������ 0, �� ��� �������� �� ������������ ���� �������� ������.
	xmlNodePtr MoveParent();

	/// �������� ������� �������� �����.
	/// \return ������� ������� �������� �����.
	bool HasChilds	(
						xmlNodePtr pNode = 0 ///< ����������� ����. ���� ������� 0, �� ������� ���� ����������� �� ������� �������� �����.
					);

	/// ����������� � ������� ��������� ����.
	/// \return ��������� �� ������ �������� ����. ���� ������������ 0, �� �������� ����� �� ���������� ��� ��� �������� �������� ������.
	xmlNodePtr MoveFirstChild();

	/// ����������� � ��������� ����.
	/// \return ��������� �� �������� ����. ���� ������������ 0, �� ������ ���� �� ����������.
	xmlNodePtr MoveNextSibling();

	/// ����������� � ������� ����, ���������������� XPath �������.
	/// \return ��������� �� ����. ���� ������������ 0, �� ������ ���� �� ����������.
	xmlNodePtr MoveFirst(
							const QString& strXPathQuery, ///< XPath ������
							xmlNodePtr pParent = 0,		  ///< ����, � ��������� �������� �������������� �����. ���� ���������� 0, �� ����� �������������� � ��������� �������� ����
							int* pnCount = 0			  ///< ���������� �����, ��������������� �������
						);
	/// ����������� � ���������� ����, ���������������� XPath �������.
	/// \return ��������� �� ����. ���� ������������ 0, �� ������ ���� �� ����������.
	xmlNodePtr MoveNext();

	/// ������ ��������� ����������� ����
	/// \return ������� ���������� ���������� ��������� �����������.
	bool SetContent	(
						const QString& strContent,	///< ���������� ���� 
						xmlNodePtr pNode = 0		///< ����, ��� ��������� �����������. ���� ������� 0, �� ��������������� ���������� �������� ����
					);

	/// ��������� ����������� ����
	/// \return ���������� ����.
	QString GetContent	(
							xmlNodePtr pNode = 0		///< ����, ��� ��������� �����������. ���� ������� 0, �� ������������ ���������� �������� ����
						);

	/// ���������� ���� � �����.
	/// \return ������� ��������� ���������� ��������.
	bool Push	(
					xmlNodePtr pNode = 0		///< ����������� ����. ���� ������� 0, �� ����������� ������� ����
				);
	
	/// �������������� ���� �� ����� � ��������� ��� � �������� ��������.
	/// \return ��������� �� ��������������� ����. ��� ������ ����� ������������ ��������� �� ������� ����.
	xmlNodePtr Pop();	

	/// ���������� �������� ������� � �����.
	/// \return ������� ��������� ���������� ��������.
	bool PushQuery();

	/// �������������� ������� �� �����. ����� �������������� �������� ������������� �������� ��� ������ ������� \ref MoveNext
	/// \return ������� ��������� ���������� ��������.
	bool PopQuery();

private:
	xmlNodePtr GetNode(xmlNodePtr pNode);
	QString PackValue(const QVariant& vtValue);
	QVariant UnpackValue(const QString& strValue);

private:
	xmlDocPtr		m_pXMLDoc;			// XML �������� libxml2
	xmlNodePtr		m_pCurNode;			// ������� ���� ���������
	xmlNodeSetPtr	m_pCurNodeSet;		// ������� ������
	int				m_nCurItem;			// ������� ������� �������
	bool			m_bModified;		// ������� ������� ��������� ��������� � ������� �������� ��� ���������� ����������
	bool			m_bAutoDestroy;		// ������� ��������������� ������������ ���� ��������, ��������� � ����������

private:
	struct CNodeSet
	{
		CNodeSet(xmlNodeSetPtr _set, int _cur): set(_set), cur(_cur) {};

		xmlNodeSetPtr set;
		int	cur;
	};

	QList<CNodeSet>		m_lstSets;		// ���� ��������
	QList<xmlNodePtr>	m_lstNodes;		// ���� �����
};

#endif // _SYSTEMPROM_XML_H