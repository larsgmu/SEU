/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "utility.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define R25    		  10000.0
#define T25           298.15
#define BETA          3900
#define PRINT		  &huart2
#define UART_ESP8266  &huart1

// Orion Context IoT name
#define IoT_NAME   	 "SensorSEU21_LYK" //LYK=LarsyKnut

// Orion Context Broker
#define ORION_PORT   	 "10000"      // Old port "1026"
#define ORION_ADDRESS   "pperez2.disca.upv.es" // Old: "pperez-seu-or.disca.upv.es"

// Orion Operations
#define ORION_UPDATE	"POST /v1/updateContext HTTP/1.1\r\nContent-Type: application/json\r\nAccept: application/json\r\nContent-Length:"
#define ORION_UPDATE_BODY_TEMP   "{ \"contextElements\": [{\"type\": \"Sensor\", \"isPattern\": \"false\",\"id\": \"%s\",\"attributes\": [ {\"name\": \"temp\",\"type\": \"float\",\"value\": \"%f\"}]}],\"updateAction\": \"APPEND\"}"


#define ORION_QUERY	"POST /v1/queryContext HTTP/1.1\r\nContent-Type: application/json\r\nAccept: application/json\r\nContent-Length:"
#define ORION_QUERY_BODY_TEMP   "{ \"entities\": [{\"type\": \"Sensor\",\"isPattern\": \"false\",\"id\": \"%s\"}]}"


/* ESP RESPONSE WHEN NO WIFI TRYING TO ACCESS CONTEXTBROKER:

OrionConteOrionContextBroker_update
POST /v1/queryContext HTTP/1.1

ERROR
Content-Type: application/json

Accept: application/json

busy p…
Content-Le
ERROR
ngth: 80

ERROR


ERROR
{ “entities”: [{“type”: “Sensor”,”isPattern”: “false”,”id”: “SensorSEU21_LYK”}]}Done
 *
 */




/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_rx;

/* Definitions for displayTask */
osThreadId_t displayTaskHandle;
const osThreadAttr_t displayTask_attributes = {
  .name = "displayTask",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for temperatureTask */
osThreadId_t temperatureTaskHandle;
const osThreadAttr_t temperatureTask_attributes = {
  .name = "temperatureTask",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for networkComTask */
osThreadId_t networkComTaskHandle;
const osThreadAttr_t networkComTask_attributes = {
  .name = "networkComTask",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for timerMutex */
osMutexId_t timerMutexHandle;
const osMutexAttr_t timerMutex_attributes = {
  .name = "timerMutex"
};
/* Definitions for temperatureMutex */
osMutexId_t temperatureMutexHandle;
const osMutexAttr_t temperatureMutex_attributes = {
  .name = "temperatureMutex"
};
/* Definitions for modeMutex */
osMutexId_t modeMutexHandle;
const osMutexAttr_t modeMutex_attributes = {
  .name = "modeMutex"
};
/* USER CODE BEGIN PV */
mode 			MODE =  					ONLINE;
network_status	NETWORK_STATUS = 			OK;
int 			ALARM = 					0;
float 			global_temperature_buffer = 0.0;
int     		light_list[4]=				{0,0,0,0};
char    		global_time_buffer[6];
char			buff_sprintf100[100];
char 			buff_sprintf_body[256];
char   		    buff_sprintf1024[1024];
uint8_t 		buff_sprintf100_1[100];
uint8_t 		buff_recv[2048];
uint8_t 		buff_response1[2048];



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC1_Init(void);
void startDisplayTask(void *argument);
void startTemperatureTask(void *argument);
void startNetworkComTask(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of timerMutex */
  timerMutexHandle = osMutexNew(&timerMutex_attributes);

  /* creation of temperatureMutex */
  temperatureMutexHandle = osMutexNew(&temperatureMutex_attributes);

  /* creation of modeMutex */
  modeMutexHandle = osMutexNew(&modeMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */


  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of displayTask */
 // displayTaskHandle = osThreadNew(startDisplayTask, NULL, &displayTask_attributes);

  /* creation of temperatureTask */
  temperatureTaskHandle = osThreadNew(startTemperatureTask, NULL, &temperatureTask_attributes);

  /* creation of networkComTask */
  networkComTaskHandle = osThreadNew(startNetworkComTask, NULL, &networkComTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|BUZZER_Pin|LED_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_2_Pin|LED_0_Pin|LED_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin BUZZER_Pin LED_3_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|BUZZER_Pin|LED_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_2_Pin LED_0_Pin LED_1_Pin */
  GPIO_InitStruct.Pin = LED_2_Pin|LED_0_Pin|LED_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BTN_0_Pin */
  GPIO_InitStruct.Pin = BTN_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BTN_0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BTN_1_Pin */
  GPIO_InitStruct.Pin = BTN_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BTN_1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */


/*
 * Function for setting the lights and activating the Buzzer
 * */
void set_lights_and_buzzer(int buzz){
	HAL_GPIO_WritePin(GPIOB, LED_0_Pin, light_list[0]);
	HAL_GPIO_WritePin(GPIOB, LED_1_Pin, light_list[1]);
	HAL_GPIO_WritePin(GPIOB, LED_2_Pin, light_list[2]);
	HAL_GPIO_WritePin(GPIOA, LED_3_Pin, light_list[3]);

	HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, buzz);

}


/*
 * time_buffer_write() and time_buffer_read() makes sure the reading and writing to the global buffer happens with mutual exclution
 * */
void time_buffer_write(char* time, int size){
	while( osMutexAcquire(timerMutexHandle, 10000/portTICK_RATE_MS) != osOK);	// Aquire mutex
	for(int i=0; i < size;i++){
		global_time_buffer[i] = time[i];
	}
	while(osMutexRelease(timerMutexHandle) != osOK);	//Release mutex
}

/*
 * time_buffer_write() and time_buffer_read() makes sure the reading and writing to the global buffer happens with mutual exclution
 * */
void time_buffer_read(char* time, int size){

	while(osMutexAcquire(timerMutexHandle, 10000/portTICK_RATE_MS) != osOK);	// Aquire mutex
	for(int i = 0; i<size; i++){
		time[i] = global_time_buffer[i];
	}
	while(osMutexRelease(timerMutexHandle) != osOK);
}

/*
 * temperature_buffer_write() and temperature_buffer_read() makes sure the reading and writing to the global buffer happens with mutual exclution
 * */
void temperature_buffer_write(float temperature){
	while( osMutexAcquire(temperatureMutexHandle, 10000/portTICK_RATE_MS) != osOK);	// Aquire mutex
	global_temperature_buffer = temperature;
	while(osMutexRelease(temperatureMutexHandle) != osOK);	//Release mutex
}

/*
 * temperature_buffer_write() and temperature_buffer_read() makes sure the reading and writing to the global buffer happens with mutual exclution
 * */
float temperature_buffer_read(){
	float temperature = 0.0;
	while(osMutexAcquire(temperatureMutexHandle, 10000/portTICK_RATE_MS) != osOK);	// Aquire mutex
	temperature = global_temperature_buffer;
	while(osMutexRelease(temperatureMutexHandle) != osOK);
	return temperature;
}

/*
 *	 This function takes in the response from a HTTP request and cleans away so were left with only the JSON.
 */
void clean_time_response(char * data, int maxlen){

	int t,h,l,o,i = 0;
	char * res;
	int indexbk;
	char bytes[4];

	res = data;

	for(t=0; t < maxlen; t++) buff_response1[t] = '*';

	for(t = 0; t< maxlen;){
		res = strnstr(res, "+IPD", maxlen-t);
		if(res!=NULL){
			bytes[0]=*(res+5);
			bytes[1]=*(res+6);
			bytes[2]=*(res+7);
			bytes[3]=*(res+8);

			for(h=0;h<4;h++) if(bytes[h]==':'){o=h;bytes[h]=0;}
			l=atoi(bytes);

			for(h=0;h<l;h++)buff_response1[t+h]=*(res+h+o+6);
			indexbk = t+h;
			t=t+l;
			res = res+t+o+6; // To avoid +IPD
		}else{
			buff_response1[indexbk] = 0;
			break;
		}
	}
	i=0;
	do{
	}while(buff_response1[i++]!='{');
	i--;

	for(t = 0; t < (2048-i); t++){
		buff_response1[t] = buff_response1[t+1];
	}

}


void clean_cb_response(char * data, int maxlen){

	int t,h,l,o,i = 0;
	char * res;
	int indexbk;
	char bytes[4];

	res = data;

	for(t=0; t < maxlen; t++) buff_response1[t] = '*';


}

/*
 * This functions send a HTTP request to worldclockapi.com to get the current time
 * */
void ESP8266_get_time(void) {
	int ct;
	sprintf(buff_sprintf100,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n","worldclockapi.com","80");
	HAL_UART_Transmit(UART_ESP8266,( unsigned char *) buff_sprintf100, strlen( buff_sprintf100),100000); // cabecera
	osDelay(100);
	sprintf(buff_sprintf100,"GET /api/json/cet/now HTTP/1.1\r\nAccept: text/html\r\nHost: worldclockapi.com\r\n\r\n");
	sprintf(buff_sprintf100_1,( unsigned char *)"AT+CIPSEND=%d\r\n",strlen(buff_sprintf100));
	HAL_UART_Transmit(UART_ESP8266,( unsigned char *) buff_sprintf100_1, strlen( buff_sprintf100_1),100000); // cabecera
	osDelay(100);

	for (ct=0;ct<2048;ct++) buff_recv[ct]=0;
	HAL_UART_Receive_DMA(UART_ESP8266, buff_recv,2048);
	HAL_UART_Transmit(UART_ESP8266,( unsigned char *) buff_sprintf100, strlen( buff_sprintf100),100000); // cabecera
	osDelay(500);
	HAL_UART_DMAStop(UART_ESP8266);

	clean_time_response(( unsigned char *)buff_recv,2048);
}

/*
 * This function is to set up the ESP8266 to connect to wifi. It is only runned once.
 * */
void ESP8266_Boot(void)
{
	int ct;
	// Reset ESP
	for (ct=0;ct<2048;ct++) buff_recv[ct]=0;
	HAL_UART_Receive_DMA(UART_ESP8266, buff_recv,2048);
	HAL_UART_Transmit(UART_ESP8266, ( unsigned char *)"AT+RST\r\n",strlen("AT+RST\r\n"),10000);
	osDelay(2000);
	HAL_UART_DMAStop(UART_ESP8266);
	HAL_UART_Transmit(&huart2, buff_recv,strlen((char*)buff_recv),10000);


	// Tiene IP?
	for (ct=0;ct<2048;ct++) buff_recv[ct]=0;
	HAL_UART_Receive_DMA(UART_ESP8266, buff_recv,2048);
	HAL_UART_Transmit(UART_ESP8266, ( unsigned char *)"AT+CIFSR\r\n",strlen("AT+CIFSR\r\n"),10000);
	osDelay(2000);
	HAL_UART_DMAStop(UART_ESP8266);
	HAL_UART_Transmit(&huart2, buff_recv,strlen((char*)buff_recv),10000);


	// Pon en modo station=1,  station+access_point=3
	for (ct=0;ct<2048;ct++) buff_recv[ct]=0;
	HAL_UART_Receive_DMA(UART_ESP8266, buff_recv,2048);
	HAL_UART_Transmit(UART_ESP8266, ( unsigned char *) "AT+CWMODE=1\r\n",strlen("AT+CWMODE=1\r\n"),100000);
	osDelay(2000);
	HAL_UART_DMAStop(UART_ESP8266);
	HAL_UART_Transmit(&huart2, buff_recv,strlen((char *)buff_recv),10000);

	// Programa la contraseña del access-point
	for (ct=0;ct<2048;ct++) buff_recv[ct]=0;
	HAL_UART_Receive_DMA(UART_ESP8266, buff_recv,2048);
	//HAL_UART_Transmit(UART_ESP8266,( unsigned char *) "AT+CWJAP=\"routerSEU\",\"00000000\"\r\n",strlen("AT+CWJAP=\"routerSeu\",\"00000000\"\r\n"),10000);
	HAL_UART_Transmit(UART_ESP8266,( unsigned char *) "AT+CWJAP=\"Lowi338D\",\"VVGH3T7SR28SQ9\"\r\n",strlen("AT+CWJAP=\"Lowi338D\",\"VVGH3T7SR28SQ9\"\r\n"),10000);
	//HAL_UART_Transmit(UART_ESP8266,( unsigned char *) "AT+CWJAP=\"Lars iPhone\",\"noerart1234\"\r\n",strlen("AT+CWJAP=\"Lars iPhone\",\"noerart1234\"\r\n"),10000);
	osDelay(10000);
	HAL_UART_DMAStop(UART_ESP8266);
	HAL_UART_Transmit(&huart2, buff_recv,strlen((char *)buff_recv),10000);


	// verifica si hay IP
	for (ct=0;ct<2048;ct++) buff_recv[ct]=0;
	HAL_UART_Receive_DMA(UART_ESP8266, buff_recv,2048);
	HAL_UART_Transmit(UART_ESP8266, ( unsigned char *)"AT+CIFSR\r\n",strlen("AT+CIFSR\r\n"),10000);
	osDelay(4000);
	HAL_UART_DMAStop(UART_ESP8266);
	HAL_UART_Transmit(&huart2, buff_recv,strlen((char *)buff_recv),10000);

}

/*
 * Orion context broker functions
 *
 * */

void OrionContextBroker_update(void) {
    int ct;


     float temp_act = 30;
     temp_act = temperature_buffer_read();
   	 sprintf(buff_sprintf100,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",ORION_ADDRESS,ORION_PORT); //Start tcp with context broker
   	 HAL_UART_Transmit(UART_ESP8266,( unsigned char *) buff_sprintf100, strlen( buff_sprintf100),100000); // Send it to the ESP
   	 osDelay(100);

   	 sprintf(buff_sprintf_body,ORION_UPDATE_BODY_TEMP,IoT_NAME,temp_act); // Fill the context body buffer with the context
   	 sprintf(buff_sprintf1024,"%s %d\r\n\r\n%s",ORION_UPDATE,strlen(buff_sprintf_body),buff_sprintf_body); //Fill the full request buffer with request, size and body

   	 sprintf(buff_sprintf100_1,( unsigned char *)"AT+CIPSEND=%d\r\n",strlen(buff_sprintf1024));
   	 HAL_UART_Transmit(UART_ESP8266,( unsigned char *) buff_sprintf100_1, strlen( buff_sprintf100_1),100000); // Prepare ESP with size of request
   	 osDelay(100);

   	 for (ct=0;ct<2048;ct++) buff_recv[ct]=0; //Empty recieve buffer
   	 HAL_UART_Receive_DMA(UART_ESP8266, buff_recv,2048); // Set esp response to save in receive buffer
   	 HAL_UART_Transmit(UART_ESP8266,( unsigned char *) buff_sprintf1024, strlen( buff_sprintf1024),100000); // Transimt the request
   	 osDelay(2000);
   	 HAL_UART_DMAStop(UART_ESP8266);

   	 printf("%s",buff_recv); //Print response

}


void OrionContextBroker_query(void) {

	/*
	 * send queryContext to contextbroker
	 * cleanUp the response (different function)
	 * */

	int ct;



	sprintf(buff_sprintf100,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",ORION_ADDRESS,ORION_PORT); //Start tcp with context broker
	HAL_UART_Transmit(UART_ESP8266,( unsigned char *) buff_sprintf100, strlen( buff_sprintf100),100000); // Send it to the ESP
	osDelay(100);

	sprintf(buff_sprintf_body,ORION_QUERY_BODY_TEMP,IoT_NAME); // Fill the context body buffer with the context
	sprintf(buff_sprintf1024,"%s %d\r\n\r\n%s",ORION_QUERY,strlen(buff_sprintf_body),buff_sprintf_body); //Fill the full request buffer with request, size and body

	sprintf(buff_sprintf100_1,( unsigned char *)"AT+CIPSEND=%d\r\n",strlen(buff_sprintf1024));
	HAL_UART_Transmit(UART_ESP8266,( unsigned char *) buff_sprintf100_1, strlen( buff_sprintf100_1),100000); // Prepare ESP with size of request
	osDelay(100);

	for (ct=0;ct<2048;ct++) buff_recv[ct]=0; //Empty recieve buffer
	HAL_UART_Receive_DMA(UART_ESP8266, buff_recv,2048); // Set esp response to save in receive buffer
	HAL_UART_Transmit(UART_ESP8266,( unsigned char *) buff_sprintf1024, strlen( buff_sprintf1024),100000); // Transimt the request
	osDelay(2000);
	HAL_UART_DMAStop(UART_ESP8266);
	//printf("%s",buff_recv); //Print response
	clean_time_response(( unsigned char *)buff_recv,2048);

}



/* USER CODE END 4 */

/* USER CODE BEGIN Header_startDisplayTask */
/**
  * @brief  Function implementing the displayTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_startDisplayTask */
void startDisplayTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */


  for(;;)
  {
	 osDelay(1000);

	 // Get temperature from global buffer
	 float temperature = 0.0;
	 temperature = temperature_buffer_read();

	 // Get time from global buffer
	 char time[6];
	 time_buffer_read(time,6);

	 printf("Time: %s - Temperature: %.2f\r\n",time,temperature);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_startTemperatureTask */
/**
* @brief Function implementing the temperatureTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startTemperatureTask */
void startTemperatureTask(void *argument)
{
  /* USER CODE BEGIN startTemperatureTask */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1000);
	  		  uint32_t valueAD;
	  		  float VRNTC,RNTC,TNTC;
	  		  int buzzer = 0;

	  		  ADC_ChannelConfTypeDef sConfig = {0};
	  			// configuracion del canal de entrada A/D
	  		  sConfig.Channel = ADC_CHANNEL_1;
	  		  sConfig.Rank = 1;
	  		  //sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLE_5;
	  		  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	  		  // Disparo la conversion
	  		  HAL_ADC_Start(&hadc1);
	  		  // Espero la finalización
	  		  HAL_ADC_PollForConversion(&hadc1, 10000);
	  		  // Leo el valor de la conversión 4095 y 0
	  		  valueAD=HAL_ADC_GetValue(&hadc1);
	  		  //printf("valor %d \r\n",valueAD);

	  		  TNTC=BETA/(log((-10000.0*3.3/(valueAD*3.3/4095.9-3.3)-10000.0)/R25)+BETA/T25)-273.18;

	  		  temperature_buffer_write(TNTC);

	  		  if(TNTC>32){
	  			  for(int i = 0; i<4; i++){
	  				  light_list[i] = 1;
	  			  }
	  			  if(TNTC>34){
	  				  buzzer = 1;
	  			  }
	  		  } else if(TNTC > 29){
	  				light_list[0]=0;
	  				light_list[1]=1;
	  				light_list[2]=1;
	  				light_list[3]=1;
	  				buzzer = 0;
	  		  } else if(TNTC > 26){
	  				light_list[0]=0;
	  				light_list[1]=0;
	  				light_list[2]=1;
	  				light_list[3]=1;
	  				buzzer=0;
	  		  }else if(TNTC > 23){
	  				light_list[0]=0;
	  				light_list[1]=0;
	  				light_list[2]=0;
	  				light_list[3]=1;
	  				buzzer = 0;
	  		  }else{
	  			  for(int i = 0; i<4; i++){
	  				  light_list[i]=0;
	  			  }
	  			  buzzer = 0;
	  		  }
	  		  buzzer=0;

	  		  set_lights_and_buzzer(buzzer);

  }
  /* USER CODE END startTemperatureTask */
}

/* USER CODE BEGIN Header_startNetworkComTask */
/**
* @brief Function implementing the networkComTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startNetworkComTask */
void startNetworkComTask(void *argument)
{
  /* USER CODE BEGIN startNetworkComTask */
	char * temp_time;
	char * temp_string;
	char   temp_source_alarm[strlen("SensorSEU21_XXX")];
	int    temp_light_list[4];
	int    temp_alarm;
	printf("BOOTING ESP8266_Boot\r\n");
	ESP8266_Boot();
	printf("DONE BOOTING\r\n");

  /* Infinite loop */
  for(;;)
  {
	  mode mode = ONLINE; //TODO create mutex getMode method
	  if(mode == LOCAL) {

		 /*
		  * 1. Get time from worldclockapi.com
		  * 2. Write to global buffer
		  * 3. Goto sleep for x seconds
		  * */

		  ESP8266_get_time();

		  temp_time = strstr(buff_response1,"currentDateTime");
		  temp_time = temp_time+strlen("currentDateTime:yyyy-mm-dd:")+2; // +2 to skip ""
			int q = 0;
			do{
			}while(temp_time[q++]!='+'); //iterate over the timestamp, already know it ends with +
			q--;
			for(q; q < strlen(temp_time);q++)temp_time[q]=NULL; //Remove the rest of the response

			if(temp_time[0] != 0){
				time_buffer_write(temp_time, strlen(temp_time)); // Write current time to global time buffer
				temp_time[0] = 0;
			}
			fflush(NULL);
			osDelay(2000);

	  }




	if(mode == ONLINE){
		OrionContextBroker_query(); // query LED and BUZZER values

		// LEDS
		temp_string = strstr(buff_response1,"LEDS");
		temp_string = strstr(buff_response1,"value");
		temp_string += strlen("value\" : \"");
		for (int i = 0; i<4; i++){
			temp_light_list[i] = (temp_string[i])-'0';
		}
		printf("LEDS: %d%d%d%d\r\n", temp_light_list[0],temp_light_list[1],temp_light_list[2],temp_light_list[3]);


		// Alarm/buzzer
		temp_string = strstr(buff_response1,"alarm");
		temp_string = strstr(temp_string,"value");
		temp_string += strlen("value\" : \"");
		temp_alarm = (temp_string[0])-'0';
		printf("Alarm: %d\r\n", temp_alarm);


		// If alarm, check reason
		if(temp_alarm){
			temp_string = strstr(buff_response1,"source_alarm");
			temp_string = strstr(temp_string,"value");
			temp_string += strlen("value\" : \"");
			int i=0;
			while(temp_string[i]!='"'){
				temp_source_alarm[i]=temp_string[i];
				i++;
			}


			/*
			int q=0;
			do{
				temp_source_alarm[q]=temp_string[q];

			}while(temp_string[q++]!='}');*/
			printf("Source Alarm: %s\r\n", temp_source_alarm);
		}else{

		}

		//printf("%s",buff_response1); //Print response





		//OrionContextBroker_update();	// SEND TEMPERATURE



	  }
	  osDelay(2000);

  }
  /* USER CODE END startNetworkComTask */
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
