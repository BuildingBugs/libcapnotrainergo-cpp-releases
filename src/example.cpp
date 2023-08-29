#include <iostream> 
#include <thread>
#include <functional>
#include <chrono>
#include "capnotrainer.h"

void user_data_callback(std::vector<float> data, DeviceType device_type, uint8_t conn_handle, DataType data_type)
{
    // this callback function is called every time a 
    // new data point is received on the dongle. 

    // the data point is parsed based on its device type and 
    // passed to this function. 

    // Users are instructed to deep copy paste before the 
    // buffer goes out of scope.
    switch (device_type)
    {
    case DONGLE_DEVTYPE_CAPNO_GO:
    {
        if (data_type == DATA_CO2)
        {
            std::cout << "Received CO2 data with length: " << data.size() << "  with handle: " << (int)conn_handle << std::endl;
        }

        if (data_type == DATA_CAPNO_BATTERY)
        {
            std::cout << "Received Battery data with length: " << data.size() << "  with handle: " << (int)conn_handle << std::endl;
        }

        if (data_type == DATA_CAPNO_STATUS)
        {
            // capno status (future implementation)
        }
    }
    break;

    case DONGLE_DEVTYPE_EMG:
    {
        if (data_type == DATA_EMG)
        {
            std::cout << "Received EMG data with length: " << data.size() << "  with handle: " << (int)conn_handle << std::endl;
        }
    }
    break;

    case DONGLE_DEVTYPE_HRV:
    {
        if (data_type == DATA_RR_INTERVALS)
        {
            std::cout << "Receuved RR-interval data with length: " << data.size() << "  with handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_HEART_RATE)
        {
            // Some HRV devices outputs heart rate 
            // but we have not implemented it as it is 
            // an average heart rate instead of an instanteneous one. 
        }
    }
    break;

    case DONGLE_DEVTYPE_CAPNO_6:
    {
        // NOT IMPLEMENTED
    }
    break;

    default:
        break;
    }


}


void counter() {

    int count = 0;
    while (true)
    {
        count += 1;
        //std::cout << "Counter: " << count << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

int main(int argc, char* argv[]) {

    if (argc != 3)
    {
        std::cout << "Please run as following: \n main.exe COMx COMy" << std::endl;
        return 0;
    }

    // port names can be found based on 
    // port enumeration and pid/vid values. 
    const char* port1 = argv[1]; //  "/dev/ttyACM0";
    const char* port2 = argv[2]; //  "/dev/ttyACM1";

    std::cout << "CapnoTrainer: " << CapnoTrainer::GetVersion() << std::endl;

    try {
        CapnoTrainer capno(port1, port2, user_data_callback, true);
        // Initilize is blocking. 
        // its better to call it on a new thread. 
        // QThread works as well. 
        std::thread t1(std::thread([&capno]() { capno.Initialize(); }));
        t1.join();
    }
    catch (asio::system_error& e) {
        std::cout << e.what() << std::endl;
    }


    return 0;
}