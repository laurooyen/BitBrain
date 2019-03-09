// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Common.h"

#include <iostream>
#include <cmath>

namespace BB
{
	void ProgressBar(const char* text, int progress, int total, int barWidth)
	{
		if (progress % (total / barWidth) == 0)
		{
			float percentage = (float)progress / (float)total;

			std::cout << text << " [";

			for (int i = 0; i < barWidth; i++)
			{
				std::cout << ((i < percentage * barWidth) ? "#" : "-");
			}

			std::cout << "] " << std::ceil(percentage * 100) << " %\r" << std::flush;
		}
	}
}
