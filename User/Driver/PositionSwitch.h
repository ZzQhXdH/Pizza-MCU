#ifndef		__POSITION_SWITCH_H
#define		__POSITION_SWITCH_H

#include "stm32f10x.h"
#include <stdint.h>

class PositionSwitch
{
	enum {
		YL_SW2 = 0x400000,
		YL_SW1 = 0x200000,
		DOOR_SW5 = 0x100000, // 预留 小门门禁开关
		DOOR_SW4 = 0x080000, // 预留
		DOOR_SW3 = 0x040000, // 预留
		DOOR_SW2 = 0x020000, // 补货按钮
		DOOR_SW1 = 0x010000, // 大门门禁开关
		
		QHHT_SW2 = 0x008000, // 保温门下微动开关
		QHQJ_SW1 = 0x004000, // 保温门上微动开关
		ZY_SW2 = 0x002000, // 内推货右微动开关
		ZY_SW1 = 0x001000, // 内推货左微动开关
		SJ_SW2 = 0x000800, // 外升降下微动开关
		SJ_SW1 = 0x000400, // 外升降上微动开关
		QW_SW2 = 0x000200, // 取物门下微动开关
		QW_SW1 = 0x000100, // 取物门上微动开关
		
		QHQJ_SW4 = 0x000002, // 外推货外微动开关
		QHQJ_SW3 = 0x000001, // 外推货内微动开关
	};
	
	public:
		static void vInit(void);
		
		inline static bool isRotationZeroChecked(void) { return 0x00 != (GPIOA->IDR & 0x10); } // 旋转步进电机零点
		 
		inline static bool isInteriorPushChecked(void) { return 0x00 != (GPIOA->IDR & 0x40); } // 内推货槽型开关
		
		inline static bool isStepFault(void) { return 0x00 != (GPIOA->IDR & 0x80); } // 升降步进电机异常
		
		inline static bool isRasterFault(void) { return 0x00 != (GPIOA->IDR & 0x100); } // 光栅防夹手
		
		inline static bool is48VoltFault(void) { return 0x00 == (GPIOB->IDR & 0x2000); } // 48V异常
		
		inline static bool isIrdaChecked(void) { return 0x00 != (GPIOC->IDR & 0x01); } // 红外检测有货
		
		inline static bool isMicroWaveFault(void) { return 0x00 == (GPIOC->IDR & 0x04); } // 微波是否泄露
		
		inline static bool isTakeGoods(void) { return 0x00 != (GPIOC->IDR & 0x08); } // 货物是否到了托盘
		
		static uint32_t xGetValue(void);
		
		inline static bool isWicketChecked(void) { return (xGetValue() & DOOR_SW5) == 0x00; } // 小门门禁开关
		
		inline static bool isReplenishChecked(void) { return (xGetValue() & DOOR_SW2) == 0x00; } // 补货按钮
		
		inline static bool isDoorChecked(void) { return (xGetValue() & DOOR_SW1) == 0x00; } // 大门门禁开关
		
		inline static bool isHeatDoorDownChecked(void) { return (xGetValue() & QHHT_SW2) == 0x00; } // 保温门下门禁开关
		
		inline static bool isHeatDoorUpChecked(void) { return (xGetValue() & QHQJ_SW1) == 0x00; } // 保温门上门禁开关
		
		inline static bool isPushRightChecked(void) { return (xGetValue() & ZY_SW2) == 0x00; } // 内推货右微动开关
		
		inline static bool isPushLeftChecked(void) { return (xGetValue() & ZY_SW1) == 0x00; } // 内推货左微动开关
		
		inline static bool isExternDownChecked(void) { return (xGetValue() & SJ_SW2) == 0x00; } // 外升降下微动开关
		
		inline static bool isExternUpChecked(void) { return (xGetValue() & SJ_SW1) == 0x00; } // 外升降上微动开关
		
		inline static bool isPickingDownChecked(void) { return (xGetValue() & QW_SW2) == 0x00; } // 取物门下微动开关
		
		inline static bool isPickingUpChecked(void) { return (xGetValue() & QW_SW1) == 0x00; } // 取物门上微动开关
		
		inline static bool isExternPushExtrenChecked(void) { return (xGetValue() & QHQJ_SW4) == 0x00; } // 外推货外微动开关
		
		inline static bool isExternPushInteriorChecked(void) { return (xGetValue() & QHQJ_SW3) == 0x00; } // 外推货内微动开关
 	
	private:
		PositionSwitch(void) {}
};





#endif
