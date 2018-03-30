﻿/*
drivemix.cpp

Misc functions for drive/disk info
*/
/*
Copyright © 1996 Eugene Roshal
Copyright © 2000 Far Group
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "headers.hpp"
#pragma hdrstop

#include "drivemix.hpp"
#include "config.hpp"
#include "notification.hpp"
#include "platform.security.hpp"

static std::pair<os::fs::drives_set, bool> SavedLogicalDrives;

void UpdateSavedDrives(const std::any& Payload)
{
	if (!SavedLogicalDrives.second)
		return;

	const auto& Message = std::any_cast<const update_devices_message&>(Payload);
	const os::fs::drives_set Drives(Message.Drives);

	if (Message.Arrival)
		SavedLogicalDrives.first |= Drives;
	else
		SavedLogicalDrives.first &= ~Drives;
}

os::fs::drives_set allowed_drives_mask()
{
	return Global->Opt->Policies.ShowHiddenDrives?
		os::fs::drives_set{}.set() :
		os::security::allowed_drives_mask();
}

os::fs::drives_set os::fs::get_logical_drives()
{
	if (!SavedLogicalDrives.second || !(Global && Global->Opt && Global->Opt->RememberLogicalDrives))
	{
		SavedLogicalDrives.first = GetLogicalDrives();
		SavedLogicalDrives.second = true;
	}

	return SavedLogicalDrives.first;
}

bool IsDriveTypeRemote(UINT DriveType)
{
	return DriveType == DRIVE_REMOTE || DriveType == DRIVE_REMOTE_NOT_CONNECTED;
}
