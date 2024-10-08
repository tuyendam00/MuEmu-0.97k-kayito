#include "stdafx.h"
#include "ItemMove.h"
#include "ItemManager.h"
#include "MemScript.h"
#include "Util.h"

CItemMove gItemMove;

CItemMove::CItemMove()
{
	this->m_ItemMoveInfo.clear();
}

CItemMove::~CItemMove()
{

}

void CItemMove::Load(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == NULL)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, path);

		return;
	}

	if (!lpMemScript->SetBuffer(path))
	{
		ErrorMessageBox(lpMemScript->GetLastError());

		delete lpMemScript;

		return;
	}

	this->m_ItemMoveInfo.clear();

	try
	{
		eTokenResult token;

		while (true)
		{
			token = lpMemScript->GetToken();

			if (token == TOKEN_END || token == TOKEN_END_SECTION)
			{
				break;
			}

			ITEM_MOVE_INFO info;

			info.Index = lpMemScript->GetNumber();

			info.Index = SafeGetItem(GET_ITEM(info.Index, lpMemScript->GetAsNumber()));

			info.AllowDrop = lpMemScript->GetAsNumber();

			info.AllowSell = lpMemScript->GetAsNumber();

			info.AllowTrade = lpMemScript->GetAsNumber();

			info.AllowVault = lpMemScript->GetAsNumber();

			this->m_ItemMoveInfo.insert(std::pair<int, ITEM_MOVE_INFO>(info.Index, info));
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

bool CItemMove::CheckItemMoveAllowDrop(int index)
{
	std::map<int, ITEM_MOVE_INFO>::iterator it = this->m_ItemMoveInfo.find(index);

	if (it == this->m_ItemMoveInfo.end())
	{
		return 1;
	}
	else
	{
		return ((it->second.AllowDrop == 0) ? 0 : 1);
	}
}

bool CItemMove::CheckItemMoveAllowSell(int index)
{
	std::map<int, ITEM_MOVE_INFO>::iterator it = this->m_ItemMoveInfo.find(index);

	if (it == this->m_ItemMoveInfo.end())
	{
		return 1;
	}
	else
	{
		return ((it->second.AllowSell == 0) ? 0 : 1);
	}
}

bool CItemMove::CheckItemMoveAllowTrade(int index)
{
	std::map<int, ITEM_MOVE_INFO>::iterator it = this->m_ItemMoveInfo.find(index);

	if (it == this->m_ItemMoveInfo.end())
	{
		return 1;
	}
	else
	{
		return ((it->second.AllowTrade == 0) ? 0 : 1);
	}
}

bool CItemMove::CheckItemMoveAllowVault(int index)
{
	std::map<int, ITEM_MOVE_INFO>::iterator it = this->m_ItemMoveInfo.find(index);

	if (it == this->m_ItemMoveInfo.end())
	{
		return 1;
	}
	else
	{
		return ((it->second.AllowVault == 0) ? 0 : 1);
	}
}