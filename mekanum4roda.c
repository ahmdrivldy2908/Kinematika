short int v_motor[3], sp_motor[3];
float p_motor[3], i_motor[3], d_motor[3];
float error_motor[3], previous_error_motor[3], output_motor[3];
float sp[3];

#define kp_motor
#define Ki_motor
#define Kd_motor

void jalan(float Vx, float Vy, float W)
{
    float sp[4];

    // mekanum 4 roda (depan kiri, depan kanan, belakang kiri, belakang kanan)

    // mekanum engga pake sudut seperti omni 
    sp[0] = Vx - Vy - W; 
    sp[1] = Vx + Vy + W;
    sp[2] = Vx + Vy - W; 
    sp[3] = Vx - Vy + W; 

    for(int i = 0; i < 4; i++)
    {
        sp_motor[i] = sp[i];
    }
}

void kontrolmotor(){
        error_motor[i] = sp_motor[i] - v_motor[i];

		p_motor[i] = kp_motor * error_motor[i];
		i_motor[i] += Ki_motor * error_motor[i];
		d_motor[i] = Kd_motor * (error_motor[i] - previous_error_motor[i]);

		previous_error_motor[i] = error_motor[i];

        if (i_motor[i] > 999) i_motor[i] = 999;
        else if (i_motor[i] < -999) i_motor[i] = - 999;

        output_motor[i] = p_motor[i] + i_motor[i] + v_motor[i];

        if (output_motor[i] > 999)output_motor[i] = 999;
        else if (output_motor < -999 ) output_motor[i] = -999



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

    if(output_motor[3] > 0)
    // gpio ny nanti sesuain saja dengan wiring ya 
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
    motord = abs(output_motor[3]);



}


