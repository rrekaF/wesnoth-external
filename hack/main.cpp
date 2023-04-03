#include <Windows.h>
#include <iostream>
int main() {
	
	HWND wesnoth_window = FindWindow(NULL, L"The Battle for Wesnoth - 1.14.9");

	DWORD process_id = 0;
	GetWindowThreadProcessId(wesnoth_window, &process_id);


	HANDLE wesnoth_process = OpenProcess(PROCESS_ALL_ACCESS, true, process_id);


	DWORD gold_val_addr = 0;
	SIZE_T bytes_read = 0;
	DWORD gold_val = -1;

	ReadProcessMemory(wesnoth_process, (void*)0x017EED18, &gold_val_addr, 4, &bytes_read);
	gold_val_addr += 0xA90;
	ReadProcessMemory(wesnoth_process, (void*)gold_val_addr, &gold_val_addr, 4, &bytes_read);
	gold_val_addr += 4;
	ReadProcessMemory(wesnoth_process, (void*)gold_val_addr, &gold_val, 4, &bytes_read);
	
	
	DWORD new_gold_val = gold_val;
	SIZE_T bytes_written = 0;
	std::cout << "Current gold: " << gold_val <<"\n";
	while (new_gold_val !=  (-1)) {
		
		std::cout << "Change to(-1 to exit): ";
		std::cin >> new_gold_val;
		if (new_gold_val == -1) {
			system("pause");
			return 0;
		}
		WriteProcessMemory(wesnoth_process, (void*)gold_val_addr, &new_gold_val, 4, &bytes_written);
		std::cout << "Gold value changed from " << gold_val << " to " << new_gold_val << std::endl;
	}
		
	return 0;
}