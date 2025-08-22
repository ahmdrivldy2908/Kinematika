void jalan(float kecepatan_x, float kecepatan_y, float kecepatan_sudut)
{

    //sudut dapat berubah sesuain posisi roda nya aja di kali ke 0.0174533 buat konversi nilai ke radia
    float sp[3];
    sp[0] = (kecepatan_x * -sinf(300*0.0174533)) + (kecepatan_y * cosf(300*0.0174533)) + kecepatan_sudut;
    sp[1] = (kecepatan_x * -sinf(60*0.0174533))  + (kecepatan_y * cosf(60*0.0174533))  + kecepatan_sudut;
    sp[2] = (kecepatan_x * -sinf(180*0.0174533)) + (kecepatan_y * cosf(180*0.0174533)) + kecepatan_sudut;

    for(int i=0; i<3; i++)
    {
        sp_motor[i] = sp[i];
    }
}


void kontrol_motor()
{

    // pid kecepatan 3 roda 
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
	motorB = abs(output_motor[1]);
	motorC = abs(output_motor[2]);
}