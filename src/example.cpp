#include <iostream> 
#include <thread>
#include <functional>
#include <chrono>
#include "capnotrainer.h"


CapnoTrainer* capno = nullptr;

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
           //std::cout << "Received CO2 data with length: " << data.size() << "  with handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_BATTERY)
        {
            std::cout << "[GO Device] Battery data with length: " << data.at(0) << "  with handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_ETCO2_AVERAGE)
        {
            std::cout << "[GO Device] ETCO2 average data with length: " << data.at(0) << "  with handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_BPM_AVERAGE)
        {
            std::cout << "[GO Device] BPM average data with length: " << data.at(0) << "  with handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_INSP_CO2_AVERAGE)
        {
            std::cout << "[GO Device] Insp. CO2 average data with length: " << data.at(0) << "  with handle: " << (int)conn_handle << std::endl;
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
            std::cout << "[ANR-Corp-M40 Device] EMG data with length: " << data.size() << "  with handle: " << (int)conn_handle << std::endl;
        }
    }
    break;

    case DONGLE_DEVTYPE_HRV:
    {
        if (data_type == DATA_RR_INTERVALS)
        {
            std::cout << "[HRV Device] RR-interval data with length: " << data.at(0) << "  with handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_HEART_RATE)
        {
            std::cout << "[HRV Device] heart rate data with length: " << data.at(0) << "  with handle: " << (int)conn_handle << std::endl;
        }
    }
    break;

    case DONGLE_DEVTYPE_O2_RING:
    {
        if (data_type == DATA_SPO2)
        {
            std::cout << "[O2-Ring Device] SpO2 data with value: " << data.at(0) << "  on handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_HEART_RATE)
        {
            std::cout << "[O2-Ring Device] heart rate data with value: " << data.at(0) << "  on handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_BATTERY)
        {
            std::cout << "[O2-Ring Device] O2 Ring battery data with value: " << data.at(0) << "  on handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_MOTION_PRESENT)
        {
            std::cout << "[O2-Ring Device] O2 ring motion data with value: " << data.at(0) << "  on handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_FINGER_PRESENT)
        {
            std::cout << "[O2-Ring Device] O2 ring motion  with value: " << data.at(0) << "  on handle: " << (int)conn_handle << std::endl;
        }
        if (data_type == DATA_HR_STRENGTH)
        {
            std::cout << "[O2-Ring Device] heart rate data with value: " << data.at(0) << "  on handle: " << (int)conn_handle << std::endl;
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
    while (count >= 0) {
        std::cout << "Please enter an integer: ";
        std::cin >> count;
        std::cout << "You entered: " << count << std::endl;

        if (capno != nullptr) {
            if (count == 1) {
                capno->Disconnect();
            } 
            if (count == 2) {
                capno->Connect("COM15", "COM16");
            }
        }
    }

    return;
}

int main(int argc, char* argv[]) {

    std::cout << "MSVC Version" << _MSC_VER << std::endl;

    /*if (argc != 3)
    {
        std::cout << "Please run as following: \n main.exe COMx COMy" << std::endl;
        return 0;
    }*/

    // port names can be found based on 
    // port enumeration and pid/vid values. 
    const char* port1 = "COM4"; //argv[1]; //  "/dev/ttyACM0";
    const char* port2 = "COM5"; //argv[2]; //  "/dev/ttyACM1";

    std::cout << "CapnoTrainer: " << CapnoTrainer::GetVersion() << std::endl;

    try {
        capno = new CapnoTrainer(user_data_callback, true);
        capno->Connect(port1, port2);
        // capno->Initialize();
        // std::thread t1(std::thread([]() { capno->Initialize(); }));
        // std::thread t2(std::thread([]() { counter();  }));
        // t1.join();
        // t2.join();
    }
    catch (asio::system_error& e) {
        std::cout << e.what() << std::endl;
    }

    while (true) {
    }

    return 0;
}