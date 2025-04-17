#pragma once

//These are a bunch of defines used for storing/chacking input values

#define FOREWARD_PRESSED 0b1
#define FOREWARD_RELEASED FOREWARD_PRESSED ^ UINT32_MAX
#define BACKWARD_PRESSED 0b10
#define BACKWARD_RELEASED BACKWARD_PRESSED ^ UINT32_MAX
#define LEFT_PRESSED 0b100
#define LEFT_RELEASED LEFT_PRESSED ^ UINT32_MAX
#define RIGHT_PRESSED 0b1000
#define RIGHT_RELEASED RIGHT_PRESSED ^ UINT32_MAX

#define USE_PRESSED 0b10000
#define USE_RELEASED USE_PRESSED ^ UINT32_MAX

//May eventually remove these if I don't care to support keyboard only controls

#define ROTATE_LEFT_PRESSED 0b100000
#define ROTATE_LEFT_RELEASED ROTATE_LEFT_PRESSED ^ UINT32_MAX
#define ROTATE_RIGHT_PRESSED 0b1000000
#define ROTATE_RIGHT_RELEASED ROTATE_RIGHT_PRESSED ^ UINT32_MAX

#define LMB_PRESSED 0b10000000
#define LMB_RELEASED LMB_PRESSED ^ UINT32_MAX
#define RMB_PRESSED 0b100000000
#define RMB_RELEASED RMB_PRESSED ^ UINT32_MAX

#define TOGGLE_MAP_PRESSED 0b1000000000
#define TOGGLE_MAP_RELEASED TOGGLE_MAP_PRESSED ^ UINT32_MAX