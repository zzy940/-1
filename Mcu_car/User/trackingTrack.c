#include "trackingTrack.h"
/**
 * @description: 循迹红外传感器初始化
 * @return {*}
 */
void Follow_InfSensor_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;  //定义结构体变量
    /* GPIOB Periph clock enable */

    /*1：使能*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    /*2：引脚初始化*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;  //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  //

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    forward(0);  //前进
}

// x1-15 x2-14 x3-13 x3-12
/**
 * @description: 检测左侧出线 判断是否右拐
 * @return {int} 0为无障碍 1为遇到障碍
 */
int Fellow_Right() {
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 1) {
        stop();
        // turnRight(10, 0);
        turnLeft(100, 1,0);
        // forward(0);
        return 1;
    }
    return 0;
}

/**
 * @description: 检测右侧出线 判断是否左拐
 * @return {int} 0为无障碍 1为遇到障碍
 */
int Fellow_Left() {
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 1) {
        stop();
        // turnLeft(10,0);
        turnRight(100, 1,0);
        // forward(0);
        return 1;
    }
    return 0;
}

/**
 * @description: 检测左侧出线 判断是否右拐
 * @return {int} 0为无障碍 1为遇到障碍
 */
int Fellow_Right_mid() {
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0) {
        stop();

        turnRight(100, 1,0);
        // forward(0);
        return 1;
    }
    return 0;
}

/**
 * @description: 检测右侧出线 判断是否左拐
 * @return {int} 0为无障碍 1为遇到障碍
 */
int Fellow_Left_mid() {
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) {
        stop();
        turnLeft(100, 1,0);
        // forward(0);
        return 1;
    }
    return 0;
}

int allcheck() {
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0 &&
        GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0 &&
        GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 0 &&
        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0)
        return 1;else return 0;
}