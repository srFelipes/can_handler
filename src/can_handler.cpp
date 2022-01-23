#include <iostream> //input output
#include <cstring>	//c++ string definition
#include <unistd.h> //UNIX comunication
#include "include/odrive_can_msg.hpp"

//General socket libraries
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

class can_handler
{
private:
	/* data */
	int s;
	struct sockaddr_can addr;
	struct ifreq ifr;

public:
	can_handler(std::string can_type); //parametrized constructor
	can_handler();					   //default constructor
	~can_handler();
	int can_connect();
	int can_write(can_frame frame);
	int can_write_wait_answer();
	int can_listen();
};

can_handler::can_handler(void)
{
	s = -1;
}
int can_handler::can_connect()
{
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
	{
		perror("Socket");
		return 1;
	}

	strcpy(ifr.ifr_name, "vcan0");
	ioctl(s, SIOCGIFINDEX, &ifr);

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("Bind");
		return 1;
	}
	else
	{
		return 0;
	}
}

can_handler::~can_handler()
{
	if (close(s) < 0)
	{
		perror("Closes");
	}
}

int can_handler::can_write(can_frame frame)
{
	if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
	{
		perror("Write");
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{ // la clase logra conectarse satisfactoriamente a Vcan0 y escribir, devuelve error porque
	/* Can id is 32bit long, it includes the EFF and RTR flags
 * Controller Area Network Identifier structure
 *
 * bit 0-28	: CAN identifier (11/29 bit)
 * bit 29	: error message frame flag (0 = data frame, 1 = error message)
 * bit 30	: remote transmission request flag (1 = rtr frame)
 * bit 31	: frame format flag (0 = standard 11 bit, 1 = extended 29 bit)
 */
	// can_handler ch;
	// ch.can_connect();
	// can_frame toSend;
	// // toSend.can_id=0x29A;  //this is the identifier can_id = axis_id << 5 | cmd_id
	// // toSend.can_dlc=1;
	// // toSend.data[0]='f';
	// ch.can_write(toSend);
	// std::cout << "saludsfgd oreltewcita \n";
	// return 1;
	
	// uint32_t axis_id=0x1;
	// uint32_t cmd_id=0x5;
	// uint32_t can_id=axis_id << 5 | cmd_id;

	if (0b0){
		std::cout<<"terminado2";
	}
	
}
