#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

bool check_com_port(const std::string& portName) {
    // Try to open the COM port
    HANDLE hComm = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hComm == INVALID_HANDLE_VALUE) {
        // If the port can't be opened, it might be in use or unavailable
        return false;
    }

    // Port opened successfully, close it
    CloseHandle(hComm);
    return true;
}

void scan_com_ports() {
    std::cout << "FSPort Version 0.9.3" << std::endl;
    std::cout << "Created by mca_rz\n" << std::endl;
    
    std::vector<std::string> availablePorts;

    // Scan ports from COM1 to COM256
    for (int i = 1; i <= 256; ++i) {
        std::string portName = "\\\\.\\COM" + std::to_string(i);  // Format COM port name
        if (check_com_port(portName)) {
            availablePorts.push_back(portName);
        }
    }

    // Handle different cases based on the number of found ports
    if (availablePorts.empty()) {
        std::cout << "[ERROR] 0 Port found, is the device connected?" << std::endl;
    } else {
        for (size_t i = 0; i < availablePorts.size(); ++i) {
            std::cout << "[FSPort] " << availablePorts[i] << " - Name" << std::endl;
        }
    }
}

int main() {
    scan_com_ports();  // Start scanning
    return 0;
}
