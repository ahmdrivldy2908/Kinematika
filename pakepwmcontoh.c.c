


//setelah itu kita harus deklarasi sintaks ini buat panggil pwm 
HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1); //PWMA    
HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2); //PWMB
HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1); //PWMC


// terus baru bisa di pakai 

while(
    jalamotor(motor, speed);   // nah ini ganti aja sesuaai motor yang igin di gerakan
)



jalanmotor(int motorA, int speed){
    if (motorA == 1){
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
        TIM9->CCR1 = 500;
    }

    if (motorA == 1){
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, SET);   // pin di sesuian aja
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
        TIM9->CCR2 = 500;
    }


    if (motorA == 1){
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
        TIM10->CCR1 = 500;
    }

}
