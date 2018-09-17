#ifndef		__APP_CONFIG_H
#define		__APP_CONFIG_H

#include "stm32f10x.h"

class AppConfig
{
	public:
		static AppConfig& getInstance(void)
		{
			static AppConfig config;
			return config;
		}
		
	private:
		uint8_t mRowHeighe[4]; // 4列的行高
		
	private:
		AppConfig(void); 
};



#endif
