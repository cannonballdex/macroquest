/*
 * MacroQuest2: The extension platform for EverQuest
 * Copyright (C) 2002-2019 MacroQuest Authors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "pch.h"
#include "MQ2DataTypes.h"

using namespace mq;
using namespace mq::datatypes;

bool MQ2PluginType::GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest)
{
	MQPlugin* pPlugin = reinterpret_cast<MQPlugin*>(VarPtr.Ptr);
	if (!pPlugin)
		return false;

	MQTypeMember* pMember = MQ2PluginType::FindMember(Member);
	if (!pMember)
		return false;

	switch (static_cast<PluginMembers>(pMember->ID))
	{
	case Name:
		Dest.Ptr = pPlugin->szFilename;
		Dest.Type = pStringType;
		return true;

	case Version:
		Dest.Float = pPlugin->fpVersion;
		Dest.Type = pFloatType;
		return true;

	default: break;
	}

	return false;
}

bool MQ2PluginType::dataPlugin(const char* szIndex, MQTypeVar& Ret)
{
	if (!szIndex[0])
		return false;
	if (IsNumber(szIndex))
	{
		int index = GetIntFromString(szIndex, 0) - 1;
		if (index < 0)
			index = 0;

		MQPlugin* pPlugin = pPlugins;
		while (index)
		{
			pPlugin = pPlugin->pNext;
			if (!pPlugin)
				return false;
			index--;
		}

		Ret.Ptr = pPlugin;
		Ret.Type = pPluginType;
		return true;
	}
	else
	{
		// name
		MQPlugin* pPlugin = pPlugins;
		while (pPlugin)
		{
			if (!_stricmp(pPlugin->szFilename, szIndex))
			{
				Ret.Ptr = pPlugin;
				Ret.Type = pPluginType;
				return true;
			}

			pPlugin = pPlugin->pNext;
		}
	}

	return false;
}
