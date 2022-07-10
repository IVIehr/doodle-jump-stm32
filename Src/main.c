/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "LiquidCrystal.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

PCD_HandleTypeDef hpcd_USB_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM1_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// ******************************** Musical Notes ********************************
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST     0

int start_melody[] = {
		REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,
		REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
		REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
		NOTE_C5,2, REST,2,
};

int game_over_melody[] = {
		NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4,
		NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
		NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,
};

int falling_melody[] = {
		5000,1, 4000,1, 3000,1,
		2000,1, 1500,1, 1000,1
};

// ******************************** LCD Pins ********************************
#define LCD_PIN_4  256           // PIN 8
#define LCD_PIN_5  512           // PIN 9
#define LCD_PIN_6  1024          // PIN 10
#define LCD_PIN_11 2048          // PIN 11
#define LCD_PIN_12 4096          // PIN 12
#define LCD_PIN_13 8192          // PIN 13
#define LCD_PIN_14 16384         // PIN 14

// ***************************** Seven Segment ******************************
#define SEVEN_SEG_DIGIT_1 512     // PIN 9
#define SEVEN_SEG_DIGIT_2 1024    // PIN 10
#define SEVEN_SEG_DIGIT_3 8192    // PIN 13
#define SEVEN_SEG_DIGIT_4 64      // PIN 6
#define SEVEN_SEG_DP 	  2       // PIN 1 - PORT B

// **************************** Seven Segment IC *****************************
#define SEVEN_SEG_IC_A 32         //pin_5
#define SEVEN_SEG_IC_B 256        //pin_8
#define SEVEN_SEG_IC_C 512        //pin_9
#define SEVEN_SEG_IC_D 16         //pin_4

// ******************************** Keypad ***********************************
#define KEYPAD_PIN_1 1        //pin_0
#define KEYPAD_PIN_2 2        //pin_1
#define KEYPAD_PIN_3 4        //pin_2
#define KEYPAD_PIN_4 8        //pin_3
#define KEYPAD_PIN_5 16       //pin_4
#define KEYPAD_PIN_6 32       //pin_5
#define KEYPAD_PIN_7 64       //pin_6
#define KEYPAD_PIN_8 128      //pin_7

// ***************************** Custom Chars ********************************
typedef unsigned char byte;

byte font_d[8] = { 0x1E, 0x19, 0x19, 0x19, 0x19, 0x1E, 0x00, 0x1F };
byte font_o[8] = { 0x0E, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00,  0x1F};
byte font_l[8] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x0F, 0x00, 0x1F};
byte font_e[8] = {0x0F, 0x10, 0x1E, 0x1E, 0x10, 0x0F, 0x00, 0x1F};
byte font_r[8] = {0x0E, 0x19, 0x19, 0x1E, 0x1A, 0x1B, 0x00, 0x1F};
byte font_dragon[8] = {0x1F, 0x15, 0x1F, 0x1F, 0x0E, 0x0A,  0x0A, 0x1B};
byte font_doodler[8] = { 0x0E, 0x1B, 0x1E, 0x1E, 0x1C, 0x1F, 0x0A, 0x0A };
byte font_stair[8] = { 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


#define FONT_D			0
#define FONT_O			1
#define FONT_L			2
#define FONT_E			3
#define FONT_R			4
#define FONT_DOODLER	5
#define FONT_DRAGON		6
#define FONT_STAIR		7

byte stair[8] = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 };
byte spring[8] = { 0x09, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x12 };
byte broken_stair[8] = { 0x10, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x10 };
byte doodler[8] = { 0x00, 0x00, 0x1E, 0x0F, 0x0D, 0x1F, 0x02, 0x00 };
byte doodler_on_stair[8] = { 0x10, 0x10, 0x1E, 0x17, 0x15, 0x1F, 0x12, 0x10 };
byte doodler_on_broken_stair[8] = { 0x10, 0x10, 0x1E, 0x07, 0x05, 0x1F, 0x12,
		0x10 };
byte hole[8] = { 0x04, 0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x0E, 0x04 };
byte dragon[8] = { 0x00, 0x10, 0x1F, 0x0D, 0x0D, 0x1F, 0x10, 0x00 };

#define CHR_NULL					' '
#define CHR_STAIR 					0
#define CHR_SPRING 					1
#define CHR_BROKEN_STAIR 			2
#define CHR_DOODLER 				3
#define CHR_DOODLER_STAIR 			4
#define CHR_HOLE 					5
#define CHR_DRAGON 					6
#define CHR_DOODLER_BROKEN_STAIR 	7

#define GAME_OVER_DRAGON 	1
#define GAME_OVER_HOLE 		2
#define GAME_OVER_FALL 		3

/*******************************************************************************
 * Global Control Variables
 ******************************************************************************/
int score = 0;
int level = 9;

int prob_stair[10] = { 60, 55, 50, 45, 40, 35, 30, 25, 20, 15 };
int prob_broken[10] = { 7, 8, 9, 10, 10, 12, 14, 16, 18, 20};
//int prob_enemy[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int prob_enemy[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 2, 20 };
int prob_spring[10] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };

int board[20][4];
int is_spring[20][4];

int initialized = 0;
int pos_x, pos_y;

int jump_state = 0;
int jump_up = 1;
int spring_jump = 0;

int ssi = 0;						// 7 Segment index
int ssd[4] = { 1, 0, 0, 0 };		// 7 Segment digits

int last_stair;

int play_sound = 0;
int sound_start = 0;

int is_game_over = 0;

#define PAGE_GAME	0
#define PAGE_MAIN	1
#define PAGE_MENU	2
#define PAGE_ABOUT	3
#define PAGE_NAME	4
int page = 1;

int init_done = 0;

char username[30] = "Doodler";
unsigned char buffer[100];

/*******************************************************************************
 * RTC
 ******************************************************************************/
RTC_TimeTypeDef time;
RTC_DateTypeDef date;

void rtc() {
	HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
}


/*******************************************************************************
 * Game Logic
 ******************************************************************************/
void game_over(int code) {
	// Start game over mode
	is_game_over = 1;

	// Stop timers
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_TIM_Base_Stop_IT(&htim4);

	// Play melody
	int notes = sizeof(game_over_melody) / sizeof(game_over_melody[0]) / 2;
	play_melody(game_over_melody, notes);

	// Cover the screen
	for (int i=0; i<20; i++) {
		setCursor(i, 0);
		write(0xFF);
	}
	setCursor(19, 1);
	write(0xFF);
	setCursor(19, 2);
	write(0xFF);
	for (int i=19; i>=0; i--) {
		setCursor(i, 3);
		write(0xFF);
	}
	setCursor(0, 2);
	write(0xFF);
	setCursor(0, 1);
	write(0xFF);
	for (int i=1; i<19; i++) {
		setCursor(i, 1);
		write(0xFF);
	}
	for (int i=18; i>=1; i--) {
		setCursor(i, 2);
		write(0xFF);
	}
	clear();

	// Print the messages
	char buf[20];
	setCursor(0, 0);
	print("GAME OVER!");
	setCursor(0, 1);
	print(username);
	setCursor(0, 2);
	sprintf(buf, "SCORE: %d", score);
	print(buf);

	// TODO: send to uart
	rtc();
	int n = sprintf(buffer, "%s Game Over! %d-%d-%d %d:%d\n", username, date.Year, date.Month, date.Date, time.Hours, time.Minutes);
	HAL_UART_Transmit(&huart2, buffer, n, 50);
}

void move_doodler(int x, int y, int x_dest, int y_dest) {
	setCursor(x, y);
	if (is_spring[x][y]) {
		write(CHR_SPRING);
	} else {
		write(board[x][y]);
	}

	if (board[x][y] == CHR_HOLE || board[x][y] == CHR_DRAGON) {
		game_over(GAME_OVER_DRAGON);
	} else {
		setCursor(x_dest, y_dest);
		switch (board[x_dest][y_dest]) {
		case CHR_STAIR:
			write(CHR_DOODLER_STAIR);
			break;
		case CHR_SPRING:
			write(CHR_DOODLER_STAIR);
			break;
		case CHR_BROKEN_STAIR:
			write(CHR_DOODLER_BROKEN_STAIR);
			break;
		default:
			write(CHR_DOODLER);
			break;
		}
	}

	pos_x = x_dest;
	pos_y = y_dest;
}

void add_objects(int i) {
	int r = rand() % 100;
	int y = rand() % 4;
	if (r <= prob_stair[level] || i - last_stair >= 4) {
		r = rand() % 100;
		setCursor(i, y);
		if (r <= prob_broken[level]) {
			board[i][y] = CHR_BROKEN_STAIR;
			write(CHR_BROKEN_STAIR);
		} else {
			board[i][y] = CHR_STAIR;
			write(CHR_STAIR);
			last_stair = i;
		}
	} else if (rand() % 100 <= prob_spring[level] || i - last_stair >= 4) {
		setCursor(i, y);
		board[i][y] = CHR_STAIR;
		is_spring[i][y] = 1;
		write(CHR_SPRING);
		last_stair = i;
	} else if ((rand() % 100) <= prob_enemy[level]) {
		setCursor(i, y);
		int item = rand() % 2 == 0 ? CHR_HOLE : CHR_DRAGON;
		write(item);
		board[i][y] = item;
		last_stair = i;
	}
}

void game_step() {
	// Blink the LEDs in the game over mode
	if (is_game_over) {
		HAL_GPIO_TogglePin(GPIOE, 0b1111111100000000);
		return;
	}

	// ADC Sampling
	HAL_ADC_Start_IT(&hadc1);

	// 0. Init (one time)
	if (initialized == 0) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 4; j++) {
				board[i][j] = CHR_NULL;
				is_spring[i][j] = 0;
			}
		}

		pos_x = 1;
		pos_y = rand() % 4;

		board[pos_x][pos_y] = CHR_STAIR;
		setCursor(pos_x, pos_y);
		write(CHR_DOODLER_STAIR);

		last_stair = pos_x;
		for (int i = 2; i < 20; i++) {
			add_objects(i);
		}

		initialized = 1;
		return;
	}

	// 1. Move
	if (jump_up == 1) {
		if (pos_x == 9) {
			// Scroll down
			int temp;
			for (int i=0; i<20; i++) {
				for (int j=0; j<4; j++) {
					temp = board[i][j];
					if (temp != CHR_NULL) {
						setCursor(i, j);
						if (i == pos_x && j == pos_y) {
							write(CHR_DOODLER);
						} else {
							write(CHR_NULL);
						}
						int is_it_spring = is_spring[i][j];
						is_spring[i][j] = 0;
						board[i][j] = CHR_NULL;
						if (i > 0) {
							is_spring[i-1][j] = is_it_spring;
							board[i-1][j] = temp;
							setCursor(i-1, j);
							if (j == pos_y && i-1 == pos_x) {
								switch (temp) {
								case CHR_HOLE:
									game_over(GAME_OVER_HOLE);
									break;
								case CHR_DRAGON:
									game_over(GAME_OVER_DRAGON);
									break;
								case CHR_STAIR:
									write(CHR_DOODLER_STAIR);
									jump_up = 1;
									jump_state = 0;
									break;
								case CHR_BROKEN_STAIR:
									write(CHR_DOODLER_BROKEN_STAIR);
									break;
								}
							} else {
								if (is_it_spring) {
									write(CHR_SPRING);
								} else {
									write(temp);
								}
							}
						}
					}
				}
			}

			// Update jump state
			jump_state++;
			if ((spring_jump == 0 && jump_state == 7) || (spring_jump == 1 && jump_state == 20)) {
				jump_up = 0;
				jump_state = 7;
			}

			// Update Score
			score += level;
			ssd[3] = score % 10;
			ssd[2] = (score / 10) % 10;
			ssd[1] = score / 100;

			// Add new objects
			add_objects(19);
		} else {
			move_doodler(pos_x, pos_y, pos_x+1, pos_y);
			jump_state++;
			if ((spring_jump == 0 && jump_state == 7) || (spring_jump == 1 && jump_state == 20)) {
				jump_up = 0;
				spring_jump = 0;
				jump_state = 7;
				if (board[pos_x][pos_y] == CHR_STAIR)  {
					jump_up = 1;
					jump_state = 0;
					if (is_spring[pos_x][pos_y]) {
						spring_jump = 1;
					}

					// Sound Effect
					HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
					change_tone(400);
					play_sound = 1;
					sound_start = HAL_GetTick();
				}
			}
		}
	} else {
		if (board[pos_x][pos_y] == CHR_BROKEN_STAIR) {
			board[pos_x][pos_y] = CHR_NULL;
		}
		if (pos_x-1 < 0) {
			game_over(GAME_OVER_FALL);
		} else {
			move_doodler(pos_x, pos_y, pos_x-1, pos_y);
			switch(board[pos_x][pos_y]) {
			case CHR_NULL:
				jump_state--;
				break;
			case CHR_STAIR:
				jump_state = 0;
				jump_up = 1;

				if (is_spring[pos_x][pos_y]) {
					spring_jump = 1;
				}

				// Sound Effect
				HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
				change_tone(400);
				play_sound = 1;
				sound_start = HAL_GetTick();
			}

		}
	}
}

/*******************************************************************************
 * 7 Segment
 ******************************************************************************/
void select_digit(int d) {
	HAL_GPIO_WritePin(GPIOF, SEVEN_SEG_DIGIT_1 | SEVEN_SEG_DIGIT_2, 1);
	HAL_GPIO_WritePin(GPIOC, SEVEN_SEG_DIGIT_3, 1);
	HAL_GPIO_WritePin(GPIOE, SEVEN_SEG_DIGIT_4, 1);
	if (is_game_over) return;
	if (d == 0) {
		HAL_GPIO_WritePin(GPIOF, SEVEN_SEG_DIGIT_1, 0);
	} else if (d == 1) {
		HAL_GPIO_WritePin(GPIOF, SEVEN_SEG_DIGIT_2, 0);
	} else if (d == 2) {
		HAL_GPIO_WritePin(GPIOC, SEVEN_SEG_DIGIT_3, 0);
	} else if (d == 3) {
		HAL_GPIO_WritePin(GPIOE, SEVEN_SEG_DIGIT_4, 0);
	}
}

void show_digit(int i) {
	HAL_GPIO_WritePin(GPIOB, SEVEN_SEG_IC_A, (i & 1) > 0);
	HAL_GPIO_WritePin(GPIOB, SEVEN_SEG_IC_B, (i & 2) > 0);
	HAL_GPIO_WritePin(GPIOB, SEVEN_SEG_IC_C, (i & 4) > 0);
	HAL_GPIO_WritePin(GPIOB, SEVEN_SEG_IC_D, (i & 8) > 0);
}

void timer_7seg() {
	ssd[0] = level;
	HAL_GPIO_WritePin(GPIOB, SEVEN_SEG_DP, ssi == 0);
	select_digit(ssi);
	show_digit(ssd[ssi]);
	ssi++;
	ssi %= 4;
}

/*******************************************************************************
 * ADC Sampling Interrupt & UART
 ******************************************************************************/
uint8_t uart_buffer[8] = { 0 };

void adc_sample() {

	if (play_sound == 1 && HAL_GetTick() - sound_start >= 50) {
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		play_sound = 0;
	}

//	HAL_ADC_Start_IT(&hadc1);
//	int n = sprintf(buffer, "Level: %d\n", ssd[0]);
//	HAL_UART_Transmit(&huart2, buffer, n, 100);

	// Read UART
//	n = strlen(uart_buffer);
//	if ( n > 0 && uart_buffer[n-1] == '*') {
//		n = sprintf(buffer, "R: |%s|\n", uart_buffer);
//		HAL_UART_Transmit(&huart2, buffer, n, 100);
////		uart_buffer[0] = '\0';
//	}
}

void uart_received() {
	HAL_UART_Receive_IT(&huart2, uart_buffer, 8);
}

/*******************************************************************************
 * Volume
 ******************************************************************************/
void adc_volume(int value) {
	level = (int) ((value * 10.0) / 256.0);
}


/*******************************************************************************
 * Menu Page
 ******************************************************************************/
void menu_page() {
	clear();
	page = PAGE_MENU;
	setCursor(13, 1);
	print("MENU");
	setCursor(13, 2);
	write(FONT_STAIR); write(FONT_STAIR); write(FONT_STAIR); write(FONT_STAIR);
	setCursor(0, 0);
	print("1.Start");
	setCursor(0, 1);
	print("2.Set Name");
	setCursor(0, 2);
	print("3.About");
}

/*******************************************************************************
 * Game Page
 ******************************************************************************/
void game_page() {
	clear();
	page = PAGE_GAME;

	// Seed PRNG
	rtc();
	srand(HAL_GetTick() * time.Seconds);

	// Create custom characters
	createChar(CHR_STAIR, stair);
	createChar(CHR_SPRING, spring);
	createChar(CHR_BROKEN_STAIR, broken_stair);
	createChar(CHR_DOODLER, doodler);
	createChar(CHR_DOODLER_STAIR, doodler_on_stair);
	createChar(CHR_DOODLER_BROKEN_STAIR, doodler_on_broken_stair);
	createChar(CHR_HOLE, hole);
	createChar(CHR_DRAGON, dragon);

	// Start Timers
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
}


/*******************************************************************************
 * Keypad
 ******************************************************************************/
int last_pressed = -1000;
char keypad_buf[100];
char last_char = '\0';

void HAL_GPIO_EXTI_Callback(uint16_t pin) {
	if (init_done == 1 && HAL_GetTick() - last_pressed >= 400) {

		if (pin == KEYPAD_PIN_1 || pin == KEYPAD_PIN_2 || pin == KEYPAD_PIN_3 || pin == KEYPAD_PIN_4) {

			// Handle pagination
			if (HAL_GetTick() - last_pressed >= 1000 && (page == PAGE_MAIN || page == PAGE_ABOUT)) {
				menu_page();
			} else {
				// Find row
				int row;
				if (pin == KEYPAD_PIN_1)
					row = 0;
				else if (pin == KEYPAD_PIN_2)
					row = 1;
				else if (pin == KEYPAD_PIN_3)
					row = 2;
				else if (pin == KEYPAD_PIN_4)
					row = 3;

				// Find col
				int col = 0;
				for (int i = 0; i <= 3; i++) {
					int x = 1 << (4 + i);
					HAL_GPIO_WritePin(GPIOD,
					KEYPAD_PIN_5 | KEYPAD_PIN_6 | KEYPAD_PIN_7 | KEYPAD_PIN_8, 0);
					HAL_GPIO_WritePin(GPIOD, x, 1);
					if (HAL_GPIO_ReadPin(GPIOD, 1 << (row))) {
						col = i;
					}
				}

				// Re-init the keypad
				HAL_GPIO_WritePin(GPIOD, KEYPAD_PIN_5 | KEYPAD_PIN_6 | KEYPAD_PIN_7 | KEYPAD_PIN_8, 1);

				// Use (row, col) to detect the key
				if (page == PAGE_MENU) {
					if (row == 3) {
						if (col == 2) {
							clear();
							page = PAGE_ABOUT;
							setCursor(0, 0);
							print("A.Farokh");
							setCursor(0, 1);
							print("M.Navhidimehr");
							rtc();
							setCursor(0, 2);
							sprintf(keypad_buf, "%04d-%02d-%02d", date.Year + 2000, date.Month, date.Date);
							print(keypad_buf);
							setCursor(0, 3);
							sprintf(keypad_buf, "%02d:%02d:%02d", time.Hours, time.Minutes, time.Seconds);
							print(keypad_buf);
						} else if (col == 1) {
							clear();
							page = PAGE_NAME;
							last_char = '\0';
							setCursor(0, 0);
							print("Name:");
							setCursor(0, 1);
							print(username);
						} else if (col == 0) {
							game_page();
						}
					}
				} else if (page == PAGE_NAME) {
					if (row == 1 && col == 3) {					// Submit name
						menu_page();
					}
					int len = strlen(username);
					if (row == 3 && col == 3) { 				// Backspace
						if (last_char == '\0') {
							username[len-1] = '\0';
							setCursor(len-1, 1);
							write(' ');
						} else {
							last_char = '\0';
							setCursor(len, 1);
							write(' ');
						}
					} else if (row == 2 && col == 3) {			// Confirm char
						if (last_char != '\0') {
							username[len] = last_char;
							username[len+1] = '\0';
							setCursor(len, 1);
							write(last_char);
							last_char = '\0';
						}
					} else {
						if (row == 3) {
							if (col == 1) {						// abc
								if (last_char == '\0') {
									last_char = 'a';
								} else if (last_char == 'a') {
									last_char = 'b';
								} else if (last_char == 'b') {
									last_char = 'c';
								} else if (last_char == 'c') {
									last_char = 'a';
								}
							} else if (col == 2) {
								if (last_char == '\0') {		// def
									last_char = 'd';
								} else if (last_char == 'd') {
									last_char = 'e';
								} else if (last_char == 'e') {
									last_char = 'f';
								} else if (last_char == 'f') {
									last_char = 'd';
								}
							}
						} else if (row == 2) {
							if (col == 0) {						// ghi
								if (last_char == '\0') {
									last_char = 'g';
								} else if (last_char == 'g') {
									last_char = 'h';
								} else if (last_char == 'h') {
									last_char = 'i';
								} else if (last_char == 'i') {
									last_char = 'g';
								}
							} else if (col == 1) {
								if (last_char == '\0') {		// jkl
									last_char = 'j';
								} else if (last_char == 'j') {
									last_char = 'k';
								} else if (last_char == 'k') {
									last_char = 'l';
								} else if (last_char == 'l') {
									last_char = 'j';
								}
							} else if (col == 2) {
								if (last_char == '\0') {		// mno
									last_char = 'm';
								} else if (last_char == 'm') {
									last_char = 'n';
								} else if (last_char == 'n') {
									last_char = 'o';
								} else if (last_char == 'o') {
									last_char = 'm';
								}
							}
						} else if (row == 1) {
							if (col == 0) {						// pqrs
								if (last_char == '\0') {
									last_char = 'p';
								} else if (last_char == 'p') {
									last_char = 'q';
								} else if (last_char == 'q') {
									last_char = 'r';
								} else if (last_char == 'r') {
									last_char = 's';
								} else if (last_char == 's') {
									last_char = 'p';
								}
							} else if (col == 1) {
								if (last_char == '\0') {		// tuv
									last_char = 't';
								} else if (last_char == 't') {
									last_char = 'u';
								} else if (last_char == 'u') {
									last_char = 'v';
								} else if (last_char == 'v') {
									last_char = 't';
								}
							} else if (col == 2) {
								if (last_char == '\0') {		// wxyz
									last_char = 'w';
								} else if (last_char == 'w') {
									last_char = 'x';
								} else if (last_char == 'x') {
									last_char = 'y';
								} else if (last_char == 'y') {
									last_char = 'z';
								} else if (last_char == 'z') {
									last_char = 'w';
								}
							}
						} else if (row == 0 && col == 1) {		// space
							if (last_char == '\0') {
								username[len] = ' ';
								username[len+1] = '\0';
							}
						}
						if (last_char != '\0') {
							setCursor(len, 1);
							write(last_char);
						}
					}
				} else if (page == PAGE_GAME) {
					if (row == 3) {
						if (col == 3 || col == 1) {
							int y_dest = (col == 3 ? pos_y + 1 : pos_y + 3) % 4;
							move_doodler(pos_x, pos_y, pos_x, y_dest);
							rtc();
							int n = sprintf(buffer, "%s-%d-%d-%d-%d:%d-%c\n", username, date.Year, date.Month, date.Date, time.Hours, time.Minutes, col == 1 ? 'L' : 'R');
							HAL_UART_Transmit(&huart2, buffer, n, 50);
						} else if (col == 2) {
							// Shoot
							for (int i=pos_x; i<20; i++) {
								if (board[i][pos_y] == CHR_DRAGON) {
									board[i][pos_y] = CHR_NULL;
									setCursor(i, pos_y);
									write(CHR_NULL);
									break;
								}
							}
							rtc();
							int n = sprintf(buffer, "%s-%d-%d-%d-%d:%d-S\n", username, date.Year, date.Month, date.Date, time.Hours, time.Minutes);
							HAL_UART_Transmit(&huart2, buffer, n, 50);
						}
					}
				}
			}
		}

		last_pressed = HAL_GetTick();
	}
}

/*******************************************************************************
 * Buzzer
 ******************************************************************************/
TIM_HandleTypeDef *pwm_timer = &htim1;
uint32_t pwm_channel = TIM_CHANNEL_1;
uint32_t internal_clock_freq, prescaler, timer_clock, period_cycles,
		pulse_width;

void change_tone(uint16_t pwm_freq) {
	// pwm_freq (1 - 20000)
	if (pwm_freq == 0 || pwm_freq > 20000) {
		__HAL_TIM_SET_COMPARE(pwm_timer, pwm_channel, 0);
	} else {
		internal_clock_freq = HAL_RCC_GetSysClockFreq();
		prescaler = 1 + internal_clock_freq / pwm_freq / 60000;
		timer_clock = internal_clock_freq / prescaler;
		period_cycles = timer_clock / pwm_freq;
		pulse_width = 500 * period_cycles / 1000 / 2;
		pwm_timer->Instance->PSC = prescaler - 1;
		pwm_timer->Instance->ARR = period_cycles - 1;
		pwm_timer->Instance->EGR = TIM_EGR_UG;
		__HAL_TIM_SET_COMPARE(pwm_timer, pwm_channel, pulse_width);
	}
}


void play_melody(int* melody, int notes) {
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	int wholenote = (60000 * 4) / 250;
	int divider = 0, noteDuration = 0;

	for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
		divider = melody[thisNote + 1];
		if (divider > 0) {
			noteDuration = (wholenote) / divider;
		} else if (divider < 0) {
			noteDuration = (wholenote) / (divider * -1);
			noteDuration *= 1.5;
		}
		change_tone(melody[thisNote]);
		HAL_Delay(noteDuration);
	}
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}


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
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */

	// Init LCD
	LiquidCrystal(GPIOD, LCD_PIN_4, LCD_PIN_5, LCD_PIN_6, LCD_PIN_11,
	LCD_PIN_12, LCD_PIN_13, LCD_PIN_14);
	begin(20, 4);

	// Init RTC
	time.Hours = 20;
	time.Minutes = 0;
	time.Seconds = 0;
	HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
	date.Date = 11;
	date.Month = 7;
	date.Year = 22;
	HAL_RTC_SetDate(&hrtc, &date,  RTC_FORMAT_BIN);

	// Start UART
	HAL_UART_Receive_IT(&huart2, uart_buffer, 100);

	// Init Keypad
	HAL_GPIO_WritePin(GPIOD, KEYPAD_PIN_5 | KEYPAD_PIN_6 | KEYPAD_PIN_7 | KEYPAD_PIN_8, 1);

	// Display main page
	createChar(FONT_D, font_d);
	createChar(FONT_O, font_o);
	createChar(FONT_L, font_l);
	createChar(FONT_E, font_e);
	createChar(FONT_R, font_r);
	createChar(FONT_DOODLER, font_doodler);
	createChar(FONT_STAIR, font_stair);
	createChar(FONT_DRAGON, font_dragon);
	setCursor(2, 1);
	write(FONT_D); write(FONT_O); write(FONT_O); write(FONT_D); write(FONT_L); write(FONT_E); write(FONT_R);
	setCursor(13, 3);
	write(FONT_STAIR);
	setCursor(13, 2);
	write(FONT_DOODLER);
	setCursor(16, 2);
	write(FONT_STAIR);
	setCursor(15, 0);
	write(FONT_DRAGON);

	// Play start melody
	int notes = sizeof(start_melody) / sizeof(start_melody[0]) / 2;
	play_melody(start_melody, notes);

	// Set the init flag
	init_done = 1;




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_RTC
                              |RCC_PERIPHCLK_TIM1|RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_8B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 39;
  hrtc.Init.SynchPrediv = 999;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 500;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7199;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 9999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 599;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 9999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

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
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|GPIO_PIN_6|LD4_Pin|LD3_Pin
                          |LD5_Pin|LD7_Pin|LD9_Pin|LD10_Pin
                          |LD8_Pin|LD6_Pin|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8
                          |GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_I2C_SPI_Pin PE6 LD4_Pin LD3_Pin
                           LD5_Pin LD7_Pin LD9_Pin LD10_Pin
                           LD8_Pin LD6_Pin PE1 */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|GPIO_PIN_6|LD4_Pin|LD3_Pin
                          |LD5_Pin|LD7_Pin|LD9_Pin|LD10_Pin
                          |LD8_Pin|LD6_Pin|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : MEMS_INT3_Pin MEMS_INT4_Pin */
  GPIO_InitStruct.Pin = MEMS_INT3_Pin|MEMS_INT4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC13 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PF9 PF10 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB4 PB5 PB8
                           PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 PD10 PD11
                           PD12 PD13 PD14 PD4
                           PD5 PD6 PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD2 PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
