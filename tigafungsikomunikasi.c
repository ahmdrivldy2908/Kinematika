// ada 3 fungi komunikasi buat uart yg biasnaya di pakai


// ini funsgi callback yang di jalankan ketika di panggil dan bersifat berhasil dah dapat langsung menerima data
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		if(remote_terima[0]=='K' && remote_terima[1]=='R' && remote_terima[2]=='I')
		{
			memcpy(&remote.lX , remote_terima + 3, 1);
			memcpy(&remote.lY , remote_terima + 4, 1);
			memcpy(&remote.rX , remote_terima + 5, 1);
			memcpy(&remote.rY , remote_terima + 6, 1);
			memcpy(&remote.r1 , remote_terima + 7, 1);
			memcpy(&remote.l1 , remote_terima + 8, 1);
			memcpy(&remote.r2 , remote_terima + 9, 1);
			memcpy(&remote.l2 , remote_terima + 10, 1);
			memcpy(&remote.sqr , remote_terima + 11, 1);
			memcpy(&remote.crs , remote_terima + 12, 1);
			memcpy(&remote.tri , remote_terima + 13, 1);
			memcpy(&remote.cir , remote_terima + 14, 1);
			memcpy(&remote.up , remote_terima + 15, 1);
			memcpy(&remote.down , remote_terima + 16, 1);
			memcpy(&remote.left , remote_terima + 17, 1);
			memcpy(&remote.right , remote_terima + 18, 1);
			memcpy(&remote.share , remote_terima + 19, 1);
			memcpy(&remote.option , remote_terima + 20, 1);
			memcpy(&remote.r3 , remote_terima + 21, 1);
			memcpy(&remote.l3 , remote_terima + 22, 1);

			vx = map(remote.lX, -127, 128, min_v[0], max_v[0]);
			vy = map(remote.lY, -127, 128, min_v[1], max_v[1]);
			vw = map(remote.rX, -127, 128, min_v[2], max_v[2]);

			if(remote.r1 == 1){
				pos_extend_remote += 1;
				if(pos_extend_remote >= 1740) pos_extend_remote = 1740;
			}
			else if(remote.l1 == 1){
				pos_extend_remote -= 1;
				if(pos_extend_remote <= 0) pos_extend_remote = 0;
			}

			if(remote.left == 1) terima_shot_state = 1;
			else if(remote.cir == 1) terima_shot_state = 100;
			else if(remote.tri == 1) {
				terima_shot_state = 120;
//				pos_extend_short_shot = 500;
			}
			else if(remote.sqr == 1) terima_shot_state = 140;

			else if(remote.up == 1) latch_mode = 1;
			else if(remote.down == 1) latch_mode = 2;

			else terima_shot_state = 0;

			HAL_UART_Receive_DMA(&huart1, (uint8_t*)remote_terima, sizeof(remote_terima));
		}
		else
		{
			HAL_UART_Receive_DMA(&huart1, (uint8_t*)remote_terima, sizeof(remote_terima));

		}
	}

	if(huart->Instance == USART3)
	{
		if(data_terima_slave[0]=='S' && data_terima_slave[1]=='L' && data_terima_slave[2]=='V')
		{
			memcpy(&odo_posx , data_terima_slave + 3, 4);
			memcpy(&odo_posy , data_terima_slave + 7, 4);
			memcpy(&odo_posw , data_terima_slave + 11, 4);
			memcpy(&odo_posx_buffer , data_terima_slave + 15, 4);
			memcpy(&odo_posy_buffer , data_terima_slave + 19, 4);
			memcpy(&odo_posw_buffer , data_terima_slave + 23, 4);
			memcpy(&data_extend , data_terima_slave + 27, 2);

			HAL_UART_Receive_DMA(&huart3, (uint8_t*)data_terima_slave, sizeof(data_terima_slave));

		}
		else
		{
			HAL_UART_Receive_DMA(&huart3, (uint8_t*)data_terima_slave, sizeof(data_terima_slave));
		}
	}

}

// ini fungsi yang di jalankan ketika berhasil namun belum mesti benar datanya dan bakal abort atau meminta coba lagi
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		if(!(remote_terima[0]=='K' && remote_terima[1]=='R' && remote_terima[2]=='I'))
		{
			HAL_UART_AbortReceive(&huart1);
			HAL_UART_Receive_DMA(&huart1, (uint8_t*)remote_terima, sizeof(remote_terima));
		}
	}

	if(huart->Instance == USART3)
	{
		if(!(data_terima_slave[0]=='S' && data_terima_slave[1]=='L' && data_terima_slave[2]=='V'))
		{
			HAL_UART_AbortReceive(&huart3);
			HAL_UART_Receive_DMA(&huart3, (uint8_t*)data_terima_slave, sizeof(data_terima_slave));
		}
	}

}


// nah ini juga yang di gunakan ketika erorr dan langusng melakukan receive ulang lagi
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)

{
	if(huart->Instance == USART1)
	{
		HAL_UART_Receive_DMA(&huart1, (uint8_t*)remote_terima, sizeof(remote_terima));

	}

	if(huart->Instance == USART3)
	{
		HAL_UART_Receive_DMA(&huart3, (uint8_t*)data_terima_slave, sizeof(data_terima_slave));
	}
}
