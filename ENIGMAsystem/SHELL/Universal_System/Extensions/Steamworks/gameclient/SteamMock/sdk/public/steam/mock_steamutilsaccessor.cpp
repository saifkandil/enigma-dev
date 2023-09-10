/** Copyright (C) 2023-2024 Saif Kandil
***
*** This file is a part of the ENIGMA Development Environment.
***
*** ENIGMA is free software: you can redistribute it and/or modify it under the
*** terms of the GNU General Public License as published by the Free Software
*** Foundation, version 3 of the license or any later version.
***
*** This application and its source code is distributed AS-IS, WITHOUT ANY
*** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
*** FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
*** details.
***
*** You should have received a copy of the GNU General Public License along
*** with this code. If not, see <http://www.gnu.org/licenses/>
**/

#include "mock_steamutilsaccessor.h"

bool SteamUtilsAccessor::GetImageSize(int iImage, uint32 *pnWidth, uint32 *pnHeight) {
  *pnWidth = 184;
  *pnHeight = 184;
  return true;
}

bool SteamUtilsAccessor::GetImageRGBA(int iImage, uint8 *pubDest, int nDestBufferSize) {
  for (unsigned i{0}; i < (unsigned)nDestBufferSize; i++) pubDest[i] = 0;
  return true;
}

uint32 SteamUtilsAccessor::GetAppID() {
  return 480;  // Spacewar's AppID
}

void SteamUtilsAccessor::SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition) {}

void SteamUtilsAccessor::SetWarningMessageHook() {}

bool SteamUtilsAccessor::IsOverlayEnabled() { return true; }

void SteamUtilsAccessor::SetOverlayNotificationInset(int nHorizontalInset, int nVerticalInset) {}
