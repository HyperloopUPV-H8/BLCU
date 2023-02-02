//Ethernet::inscribe();
//
//	HAL_Init();
//	SystemClock_Config();
//	PeriphCommonClock_Config();
//
//	UART::set_up_printf(UART::uart2);
//
//	DatagramSocket socket = DatagramSocket("192.168.1.4", 6969, "192.168.1.3", 6969);
//	//ServerSocket socket = ServerSocket("192.168.1.4", 49420);
//	Pin::start();
//	UART::start();
//	HAL_ETH_Start_IT(&heth);
//	MX_LWIP_Init();
//
//
//	double data = 1234.0;
//	Packet packet = {
//			69,
//			PacketValue<uint16_t>(&data, 1),
//	};
//	//Order order = packet;
//	while (1) {
//		MX_LWIP_Process();
//
//		socket.send(packet);
//		ErrorHandlerModel::ErrorHandlerUpdate();
//		//socket.send_order(order);
//	}
