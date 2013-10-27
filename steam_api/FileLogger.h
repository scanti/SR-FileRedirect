#pragma once

#include "stdafx.h"

bool InitLogger(char *FileName);
bool PrintLog(char *message,...);
void CloseLogger();
