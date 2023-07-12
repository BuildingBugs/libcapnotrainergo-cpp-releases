## Setup 

You can statically linked *libcapnotrainergo.lib* under *capnotrainer/build/Release/...*

## Example

To run the example with Visual Studio:

1) add it to a new or existing project. 
2) add additional include directories for *capnotrainer/include* and *asio/asio/include*
3) add additional libraries directories for *capnotrainer/build/Release/Win32/libcapnotrainergo/
4) add additional dependencies as *libcapnotrainergo.lib*
5) build the project


## Usage

1) CapnoTrainer universal dongle creates two CDC ACM serial ports. Unfortunately, ASIO does not have a port-enumeration so you can use the PID/VID of the COM ports to auto detect if a dongle is physically connected or not. 
2) Once the dongle is connected, you can create instantiate a CapnoTrainer object and pass it three arguments i.e. the two comports/serial port paths as COMx, COMy (for Windows) or /dev/ttyUSBx, /dev/ttyUSBy (for Linux) or similar to Mac. 
3) The third argument is a std::function which works a callback function. This function gets called every time a new data point (either from CapnoTrainer GO, HRV belt, EMG sensors etc) is received on the dongle. All the data comes at 10Hz (more or less). 
4) The callback function takes the following argument (see example in src folder for referece): 

```C++
void user_data_callback(std::vector<float> data, DeviceType device_type, uint8_t conn_handle, DataType data_type);
```

The enum definiation for DeviceType, DataType can be found in *capnotrainergo/include/commons.h*

5) The *CapnoTrainer().Initialize()* function is blocking so please use either QThreads or other system threads. 
6) The serial port resources are cleaned up on program exit so there is no need for port-close/CapnoTrainer().Close() method to be called. 