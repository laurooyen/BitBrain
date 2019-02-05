// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Common.h"

#include <iostream>
#include <ctime>

namespace BB
{
	void ProgressBar(const char* text, int progress, int total, int barWidth, int updateFrequency)
	{
		if (progress % (total / updateFrequency) == 0)
		{
			float percentage = (float)progress / (float)total;

			std::cout << text << " [";

			for (int i = 0; i < barWidth; i++)
			{
				std::cout << ((i < percentage * barWidth) ? "#" : "-");
			}

			std::cout << "] " << (percentage * 100) << " %\r" << std::flush;
		}
	}

	std::string GetTimeStamp()
	{
		time_t t = time(0);
		struct tm timeinfo;
		localtime_s(&timeinfo, &t);

		char buffer[20];
		strftime(buffer, 20, "%Y%m%d-%H%M%S", &timeinfo);

		return std::string(buffer);
	}
}
