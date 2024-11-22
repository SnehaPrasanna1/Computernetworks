#include <iostream>
#include <cstring>
using namespace std;

// Function to perform CRC division and check for errors
int crc(char *ip, char *op, char *poly, int mode)
{
    // Step 1: Copy the input message to the output buffer
    strcpy(op, ip);

    // If mode is 1 (transmission), append zeros at the end of the message
    if (mode) {
        int ipLen = strlen(ip);
        int polyLen = strlen(poly) - 1;  // Length of the polynomial (without leading 1)
        // Append zeros to the message (message length + poly length - 1)
        for (int i = ipLen; i < ipLen + polyLen; i++) {
            op[i] = '0';
        }
        op[ipLen + polyLen] = '\0';  // Null-terminate the string
    }

    // Step 2: Perform CRC division (XOR operation)
    int msgLen = strlen(op);
    int polyLen = strlen(poly);

    for (int i = 0; i <= msgLen - polyLen; i++) {
        if (op[i] == '1') {  // Only perform XOR if the current bit is 1
            for (int j = 0; j < polyLen; j++) {
                // XOR operation: If bit in op[i+j] is different from poly[j], flip it
                if (op[i + j] == poly[j]) {
                    op[i + j] = '0';
                } else {
                    op[i + j] = '1';
                }
            }
        }
    }

    // Step 3: Check if the remainder (last bits) are all zeros
    for (int i = msgLen - polyLen + 1; i < msgLen; i++) {
        if (op[i] == '1') {
            return 0;  // Error detected
        }
    }
    return 1;  // No error detected
}

int main()
{
    char ip[50], op[50], recv[50];
    char poly[] = "10001000000100001";  // CRC polynomial (could be modified)

    // Input the original message
    cout << "Enter the input message in binary: ";
    cin >> ip;

    // Transmit the message (appending zeros based on the polynomial length)
    crc(ip, op, poly, 1);

    // Output the transmitted message (original message + CRC checksum)
    cout << "The transmitted message is: " << ip << op + strlen(ip) << endl;

    // Input the received message
    cout << "Enter the received message in binary: ";
    cin >> recv;

    // Check for errors in the received message
    if (crc(recv, op, poly, 0)) {
        cout << "No error in data transmission" << endl;
    } else {
        cout << "Error in data transmission has occurred" << endl;
    }

    return 0;
}
