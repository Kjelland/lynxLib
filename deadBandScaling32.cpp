int32_t deadbandScaling(int32_t input, int32_t inMax, int32_t inMin, int32_t outMax, int32_t outMin, int32_t deadband)
	{

		if (input > deadband)
		{
			return ((input - deadband)*(outMax / (inMax - deadband)));
		}
		else if (input < - deadband)
		{
			return ((input + deadband)*(outMin / (inMin + deadband)));
		}
		return 0;
	}
