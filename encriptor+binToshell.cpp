#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdint>

unsigned char rotate_left(unsigned char val, int shift) {
    shift %= 8;
    return (val << shift) | (val >> (8 - shift));
}

unsigned char hello(uint32_t k , size_t x){

    
    

    unsigned char roll_key = static_cast<unsigned char>(k & 0xFF);

roll_key = rotate_left(roll_key ^ x, x % 7);
         
  
    return roll_key;






}


int main(int arguc , char* arguv[]){

    uint32_t key = //put your key;
     
    if(arguc < 2){

        std::cout<<"usage:"<<arguv[0]<<"file.bin"<<std::endl;

        return 1;
    }

    std::ifstream binery(arguv[1] , std::ios::binary | std::ios::ate);

    if(!binery.is_open()){

        std::cout<<"error while opening the file"<<std::endl;
        return 1;
    }

    std::streamsize size = binery.tellg();
    binery.seekg(0 , std::ios::beg);

    std::vector<unsigned char> buffer(size);
    if(!binery.read(reinterpret_cast<char*>(buffer.data()) , size)){

       std::cout<<"couldn't find the file"<<std::endl;
       return 1;

    }
      std::cout<<"\"";

     

    for(size_t i =0 ; i < buffer.size(); ++i){

        unsigned char encrip_byte = buffer[i] ^ hello(key , i);//this part will encript the code
    

        std::cout<<"\\x" << std::hex << std::setw(2)<< std::setfill('0')<<(int)encrip_byte;


        if((i+1) % 15 == 0){

            std::cout<<"\""<<std::endl<<"\"";
        }
        

     
         
    }


    std::cout<<"\""<<std::endl;
        std::cout<<"the size of the file is"<<std::dec<<size<<std::endl;

   return 1;


}
