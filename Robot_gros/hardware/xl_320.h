#ifndef XL_320_H
#define	XL_320_H

#define XL_320_HEADER 0xFFFFFD00
#define BROADCAST_ID 0xFE

struct XL_320_socket_s;

struct XL_320_servo_s {
	struct XL_320_socket_s * socket_ptr;
	uint8_t ID;
};

struct XL_320_group_s {
	struct XL_320_socket_s * socket_ptr_list[253];
	uint8_t nbr_socket;
	struct XL_320_servo_s * servo_ptr_list[253];
	uint8_t nbr_servo;
};

struct XL_320_socket_s {
	void (*send_function)(char *,uint8_t);
	struct XL_320_group_s group;
};

typedef struct XL_320_servo_s XL_320_servo_t;
typedef struct XL_320_group_s XL_320_group_t;
typedef struct XL_320_socket_s XL_320_socket_t;

typedef struct{
	union {
		struct {
			uint32_t header;
		};
		struct {
			uint8_t RES;
			uint8_t H_BYTE1;
			uint8_t H_BYTE2;
			uint8_t H_BYTE3;
		};
	};
	uint8_t ID;
	union {
		struct {
			uint16_t len;
		};
		struct {
			uint8_t len_L;
			uint8_t len_H;
		};
	};
	uint8_t instr;
	uint8_t * param;
	union {
		struct {
			uint16_t crc;
		};
		struct {
			uint8_t crc_L;
			uint8_t crc_H;
		};
	};
} XL_320_frame_t;

//http://support.robotis.com/en/product/dynamixel/xl-320/xl-320.htm
typedef enum {
	MODEL_NUMBER,
	FIRMWARE_VERSION,
	ID,
	BAUDRATE,
	RETURN_DELAY_TIME,
	CW_ANGLE_LIMIT,
	CCW_ANGLE_LIMIT,
	CONTROL_MODE,
	LIMIT_TEMPERATURE,
	LOWER_LIMIT_VOLTAGE,
	UPPER_LIMIT_VOLTAGE,
	MAX_TORQUE,
	RETURN_LEVEL,
	ALARM_SHUTDOWN,
	TORQUE_ENABLE,
	LED,
	D_GAIN,
	I_GAIN,
	P_GAIN,
	GOAL_POSITION,
	GOAL_VELOCITY,
	GOAL_TORQUE,
	PRESENT_POSITION,
	PRESENT_SPEED,
	PRESENT_LOAD,
	PRESENT_VOLTAGE,
	PRESENT_TEMPERATURE,
	REGISTERED_INSTRUCTION,
	MOVING,
	HDW_ERROR_STATUS,
	PUNCH,
	NBR_FIELD, //just to know the total number
} XL_320_field_t;

//http://support.robotis.com/en/product/dynamixel/xl-320/xl-320.htm#Actuator_Address_19
typedef enum {
	LED_OFF=0,
	LED_RED=0b001,
	LED_GREEN=0b010,
	LED_YELLOW=0b011,
	LED_BLUE=0b100,
	LED_PINK=0b101,
	LED_BLUE_GREEN=0b110,
	LED_WHITE=0b111,
} XL_320_led_color_t;

typedef enum {
	WHEEL_MODE=1,
	JOIN_MODE=2,
} XL_320_control_mode_t;

//http://support.robotis.com/en/product/dynamixel_pro/communication/instruction_status_packet.htm
typedef enum {
	PING=0x01,
	READ=0x02,
	WRITE=0x03,
	REG_WRITE=0x04,
	ACTION=0x05,
	FACTORY_RESET=0x06,
	REBOOT=0x08,
	STATUS=0x55,
	SYNC_READ=0x82,
	SYNC_WRITE=0x83,
	BULK_READ=0x92,
	BULK_WRITE=0x93,
} XL_320_instruction_t;

//used to initialize a socket for a servo chain
void init_socket(XL_320_socket_t * socket_ptr, void (*send_function)(char *,uint8_t));
//used to initialize a group/subgroup of servos
void init_group(XL_320_group_t * group_ptr);
//used to initialize a servo and place it in a root group
void init_servo(XL_320_servo_t * servo_ptr, uint8_t ID, XL_320_socket_t * socket_ptr);
//used to add a servo to a custom subgroup
void add_servo_to_group(XL_320_servo_t * servo_ptr, XL_320_group_t * group);


//used for sending data to a entire group
void send_data_group(XL_320_group_t * group, XL_320_field_t data_field, uint16_t value, uint8_t now);
//used for sending data to a single servo
void send_data_servo(XL_320_servo_t * servo_ptr, XL_320_field_t data_field, uint16_t value, uint8_t now);
//used for performing all pending action (now=0), usefull to synchronize actions
// /!\ if servos are not connected to the same socket, synchronization is not guaranteed
void launch_previous_action(XL_320_group_t * group);
//used to set/change the led color
void set_led_color_servo(XL_320_servo_t * servo_ptr, XL_320_led_color_t color, uint8_t now);
//used to change between WHEEL and JOIN mode (WHEEL = infinite rotation, JOIN = position control)
void set_control_mode_servo(XL_320_servo_t * servo_ptr, XL_320_control_mode_t mode, uint8_t now);
//need to be in WHEEL mode, in JOIN mode the servo will reach the goal position at this speed rate
void set_speed_servo(XL_320_servo_t * servo_ptr, uint16_t speed, uint8_t now);
//need to be in JOIN mode, in WHEEL mode there is no effect
void set_angle_servo(XL_320_servo_t * servo_ptr, uint16_t angle, uint8_t now);
//used to set limit torque
void set_torque_servo(XL_320_servo_t * servo_ptr, uint16_t torque, uint8_t now);
//used to change the actual servo's ID
void set_ID_servo(XL_320_servo_t * servo_ptr, uint8_t new_ID);
//required before switching to a different control mode (WHEEL/JOIN)
void disable_power_servo(XL_320_servo_t * servo_ptr, uint8_t now);
//used to re enable the servo after a disable
void enable_power_servo(XL_320_servo_t * servo_ptr, uint8_t now);

#endif	/* XL_320 */
