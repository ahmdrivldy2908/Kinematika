#define encoderA TIM1->CNT  // cnt enocder bawaan
#define encoderB TIM3->CNT
#define encoderC TIM2->CNT

#define motorA TIM9->CCR1   // ccr pwm
#define motorB TIM9->CCR2
#define motorC TIM10->CCR1



 HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL); //ENCA
 HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL); //ENCB
 HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL); //ENCC

 HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1); //PWMA
 HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2); //PWMB
HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1); //PWMC


// nanti di sini bisa saja ada kinematika yang di ambil sebelum masuk ke kontrol motor



void kontrol_motor()
{
	for(int i = 0; i < 3; i++)
	{
		error_motor[i] = sp_motor[i] - v_motor[i];

		p_motor[i] = kp_motor * error_motor[i];
		i_motor[i] += ki_motor * error_motor[i];
		d_motor[i] = kd_motor * (error_motor[i] - previous_error_motor[i]);

		previous_error_motor[i] = error_motor[i];

		if(i_motor[i] > 999) i_motor[i] = 999;
		else if(i_motor[i] < -999) i_motor[i] = -999;

		output_motor[i] = p_motor[i] + i_motor[i] + d_motor[i];

		if(output_motor[i] > 999) output_motor[i] = 999;
		else if(output_motor[i] < -999) output_motor[i] = -999;
	}

	if(status_kontrol == SET)
	{
		for(int i = 0; i < 3; i++)
		{
			output_motor[i] = 0;
			error_motor[i] = 0;
			previous_error_motor[i] = 0;
			p_motor[i] = 0;
			i_motor[i] = 0;
			d_motor[i] = 0;
		}
	}

	if(output_motor[0] > 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
	}

	if(output_motor[1] > 0)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, SET);
	}

	if(output_motor[2] > 0)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, RESET);

	}
	else
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, SET);
	}

	motorA = abs(output_motor[0]);
	motorB = abs(output_motor[1]);  // nah ini nilainya bakal jadi pwm abs kan pwm pasti positif
	motorC = abs(output_motor[2]);
}




