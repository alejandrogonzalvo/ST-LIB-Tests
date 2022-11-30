#include "main.h"
#include "adc.h"
#include "cordic.h"
#include "dma.h"
#include "eth.h"
#include "fdcan.h"
#include "fmac.h"
#include "lptim.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "ST-LIB.hpp"
/* USER CODE END Includes */

void SystemClock_Config(void);
void PeriphCommonClock_Config(void);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  PeriphCommonClock_Config();

  /* USER CODE BEGIN 1 */
  uint8_t adc = ADC::inscribe(PF11).value_or(69);
  uint8_t adc2 = ADC::inscribe(PA6).value_or(70);
  uint8_t adc3 = ADC::inscribe(PF13).value_or(71);
  uint8_t adc4 = ADC::inscribe(PF14).value_or(72);
//  uint8_t adc5 = ADC::inscribe(PC2).value_or(73);
//  uint8_t adc6 = ADC::inscribe(PC3).value_or(74);
  Pin::start();
  /* USER CODE END 1 */

  /* Initialize all configured peripherals */
  MX_ETH_Init();
  MX_DMA_Init();
  ADC::start();
  MX_FDCAN1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_TIM12_Init();
  MX_TIM23_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_CORDIC_Init();
  MX_FMAC_Init();
  MX_RTC_Init();
  MX_TIM15_Init();
  MX_TIM16_Init();
  MX_LPTIM1_Init();
  MX_LPTIM3_Init();
  MX_SPI3_Init();
  MX_TIM17_Init();
  MX_FDCAN3_Init();
  MX_LPTIM2_Init();
  MX_TIM2_Init();

  /* USER CODE BEGIN 2 */

  ADC::turn_on(adc);
  ADC::turn_on(adc2);
  ADC::turn_on(adc2);
//  ADC::turn_on(adc2);
  ADC::turn_on(adc3);
//  ADC::turn_on(adc5);

  while(1) {
	  HAL_Delay(100);
	  float value = ADC::get_value(adc).value();
	  float value2 = ADC::get_value(adc2).value();
	  float value3 = ADC::get_value(adc3).value();
	  float value4 = ADC::get_value(adc4).value();
//	  float value5 = ADC::get_value(adc5).value();
//	  float value6 = ADC::get_value(adc6).value();
	  __NOP();
  };

  /* USER CODE END 2 */

}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 275;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInitStruct.PLL2.PLL2M = 1;
  PeriphClkInitStruct.PLL2.PLL2N = 24;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 3 */

/* USER CODE END 3 */

void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  __disable_irq();
  /* USER CODE END Error_Handler_Debug */
}

