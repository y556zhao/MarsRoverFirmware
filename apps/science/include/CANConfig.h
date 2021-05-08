#pragma once

#include "CANInterface.h"
#include "CANMsg.h"
#include "hw_bridge.h"

static void sendACK(HWBRIDGE::SCIENCE_ACK_VALUES ackValue);
static mbed_error_status_t scienceSetControlMode(void);
static mbed_error_status_t scienceSetJointPIDParams(void);
static mbed_error_status_t commonSwitchCANBus(void);

namespace CANConfig {

using namespace HWBRIDGE;

static CANMsgMap rxMsgMap = {
    // Streamed messages
    {CANID::SCIENCE_SET_JOINT_POSITION,
     {
         {CANSIGNAL::SCIENCE_SET_GENEVA_POSITION, 0},
         {CANSIGNAL::SCIENCE_SET_ELEVATOR_POSITION, 0},
         {CANSIGNAL::SCIENCE_SET_COVER_POSITION, 0},
         {CANSIGNAL::SCIENCE_SET_SHOVEL_POSITION, 0},
     }},
    {CANID::SCIENCE_SET_JOINT_ANGULAR_VELOCITY,
     {
         {CANSIGNAL::SCIENCE_SET_GENEVA_ANGULAR_VELOCITY, 0},
     }},

    // One-shot messages
    {CANID::SCIENCE_SET_CONTROL_MODE,
     {
         {CANSIGNAL::SCIENCE_GENEVA_CONTROL_MODE, (CANSignalValue_t)SCIENCE_GENEVA_CONTROL_MODE_VALUES::SNA},
         {CANSIGNAL::SCIENCE_ELEVATOR_CONTROL_MODE, (CANSignalValue_t)SCIENCE_ELEVATOR_CONTROL_MODE_VALUES::SNA},
     }},
    {CANID::SCIENCE_SET_JOINT_PID_PARAMS,
     {
         {CANSIGNAL::SCIENCE_JOINT_PIDID, (CANSignalValue_t)SCIENCE_JOINT_PIDID_VALUES::SNA},
         {CANSIGNAL::SCIENCE_JOINT_PID_PROPORTIONAL_GAIN,
          (CANSignalValue_t)SCIENCE_JOINT_PID_PROPORTIONAL_GAIN_VALUES::SNA},
         {CANSIGNAL::SCIENCE_JOINT_PID_INTEGRAL_GAIN, (CANSignalValue_t)SCIENCE_JOINT_PID_INTEGRAL_GAIN_VALUES::SNA},
         {CANSIGNAL::SCIENCE_JOINT_PID_DERIVATIVE_GAIN,
          (CANSignalValue_t)SCIENCE_JOINT_PID_DERIVATIVE_GAIN_VALUES::SNA},
         {CANSIGNAL::SCIENCE_JOINT_PID_DEADZONE, (CANSignalValue_t)SCIENCE_JOINT_PID_DEADZONE_VALUES::SNA},
     }},
    {CANID::COMMON_SWITCH_CAN_BUS,
     {
         {CANSIGNAL::COMMON_CAN_BUS_ID, (CANSignalValue_t)COMMON_CAN_BUS_ID_VALUES::SNA},
     }},
};

static CANMsgMap txMsgMap = {
    {CANID::SCIENCE_REPORT_JOINT_DATA,
     {
         {CANSIGNAL::SCIENCE_REPORT_GENEVA_POSITION, 0},
         {CANSIGNAL::SCIENCE_REPORT_ELEVATOR_POSITION, 0},
         {CANSIGNAL::SCIENCE_REPORT_GENEVA_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::SCIENCE_REPORT_ELEVATOR_ANGULAR_VELOCITY, 0},
     }},
    {CANID::SCIENCE_REPORT_SENSOR_DATA,
     {
         {CANSIGNAL::SCIENCE_MOISTURE_DATA, 0},
         {CANSIGNAL::SCIENCE_TEMPERATURE_DATA, 0},
     }},
    {CANID::SCIENCE_REPORT_FAULTS,
     {
         {CANSIGNAL::SCIENCE_GENEVA_ENCODER_STATE, (CANSignalValue_t)SCIENCE_GENEVA_ENCODER_STATE_VALUES::SNA},
         {CANSIGNAL::SCIENCE_ELEVATOR_ENCODER_STATE, (CANSignalValue_t)SCIENCE_ELEVATOR_ENCODER_STATE_VALUES::SNA},
         {CANSIGNAL::SCIENCE_MOISTURE_SENSOR_STATE, (CANSignalValue_t)SCIENCE_MOISTURE_SENSOR_STATE_VALUES::SNA},
     }},
    {CANID::SCIENCE_REPORT_DIAGNOSTICS,
     {
         {CANSIGNAL::SCIENCE_REPORT_NUM_STREAMED_MSGS_RECEIVED, 0},
         {CANSIGNAL::SCIENCE_REPORT_NUM_ONE_SHOT_MSGS_RECEIVED, 0},
     }},
};

const static CANMsg::CANMsgHandlerMap rxOneShotMsgHandler = {
    {CANID::SCIENCE_SET_CONTROL_MODE, &scienceSetControlMode},
    {CANID::SCIENCE_SET_JOINT_PID_PARAMS, &scienceSetJointPIDParams},
    {CANID::COMMON_SWITCH_CAN_BUS, &commonSwitchCANBus},
};

CANInterface::Config config = {
    // CAN bus pins
    .can1_RX = CAN1_RX,
    .can1_TX = CAN1_TX,
    .can2_RX = CAN2_RX,
    .can2_TX = CAN2_TX,

    // Message maps and handlers
    .rxMsgMap            = &rxMsgMap,
    .txMsgMap            = &txMsgMap,
    .rxOneShotMsgHandler = &rxOneShotMsgHandler,
};

}  // namespace CANConfig
