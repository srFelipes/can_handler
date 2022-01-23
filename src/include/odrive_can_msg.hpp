#include <linux/can.h>

namespace odrive_can_msg
{
    enum cmds
    {
        MSG_CO_NMT_CTRL = 0x000, // CANOpen NMT Message REC
        MSG_ODRIVE_HEARTBEAT,
        MSG_ODRIVE_ESTOP,
        MSG_GET_MOTOR_ERROR, // Errors  RTR
        MSG_GET_ENCODER_ERROR, //rtr
        MSG_GET_SENSORLESS_ERROR, //rtr
        MSG_SET_AXIS_NODE_ID,
        MSG_SET_AXIS_REQUESTED_STATE,
        MSG_SET_AXIS_STARTUP_CONFIG,
        MSG_GET_ENCODER_ESTIMATES, //rtr
        MSG_GET_ENCODER_COUNT,  //rtr
        MSG_SET_CONTROLLER_MODES, 
        MSG_SET_INPUT_POS,
        MSG_SET_INPUT_VEL,
        MSG_SET_INPUT_TORQUE,
        MSG_SET_LIMITS,
        MSG_START_ANTICOGGING,
        MSG_SET_TRAJ_VEL_LIMIT,
        MSG_SET_TRAJ_ACCEL_LIMITS,
        MSG_SET_TRAJ_INERTIA,
        MSG_GET_IQ, //rtr
        MSG_GET_SENSORLESS_ESTIMATES, //rtr
        MSG_RESET_ODRIVE,
        MSG_GET_VBUS_VOLTAGE,
        MSG_CLEAR_ERRORS,
        MSG_SET_LINEAR_COUNT,
        MSG_SET_POS_GAIN,
        MSG_SET_VEL_GAINS,
        MSG_CO_HEARTBEAT_CMD = 0x700, // CANOpen NMT Heartbeat  SEND
    };
    bool is_rtr(cmds cmd_id){

        return (cmd_id == MSG_GET_MOTOR_ERROR || 
                cmd_id == MSG_GET_ENCODER_ERROR || 
                cmd_id == MSG_GET_SENSORLESS_ERROR ||
                cmd_id == MSG_GET_ENCODER_ESTIMATES||
                cmd_id == MSG_GET_ENCODER_COUNT|| 
                cmd_id == MSG_GET_IQ ||
                cmd_id == MSG_GET_SENSORLESS_ESTIMATES);
    }

    can_frame to_odrive(int axis_id, cmds cmd_id, uint8_t data[], int len )
    {
        can_frame frame_to_send;
        frame_to_send.can_id=(axis_id << 5 | cmd_id);           //since a new byte is defined CAN_EFF_FLAG is cleared
        if (is_rtr(cmd_id)){
            frame_to_send.can_id|=CAN_RTR_FLAG;
        }
        for (int i=0;i<len;i++){
            frame_to_send.data[i]=data[len-i-1];
        }
    }

}